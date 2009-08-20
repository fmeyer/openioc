#include <istring.hpp>
/*
 * Copyright 2005 Fernando Meyer fmcamargo@gmail.com
 * http://www.fmeyer.org
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * STL to IBM IOC WRAPPER
 * 
 */


#include <algorithm>

IString IString::word(int i){
	
	if ( i > 0 ) {i--;}
	
	std::string s;
	int end = 0, start = 0;
	do {
		end = this->find(' ', start);
		if(i == 0) {
			s = this->substr(start, end-start);
			break;	
		}
		start = end+1;
		--i;		
	} while(end > -1);
	return IString(s.c_str());
}

void IString::change(IString a, IString b, int i){
	int start = this->find(a);
	if(start != -1)
		this->replace(start, a.length(), b);
}

double IString::asDouble(){
	return atof(this->c_str());
}

long IString::asInt(){
	return atoi(this->c_str());
}

int IString::lastIndexOf(char c, int startPos){
	unsigned int _loc = this->rfind(c, this->length());
	
	if ( _loc != std::string::npos) {
		_loc++;
		return _loc;
	} else
		return 0;
}

int	IString::lastIndexOf(const char* _stk_char, int startPos) {
	unsigned int _loc = this->rfind(_stk_char, this->length());
	
	if ( _loc != std::string::npos) {
		_loc++;
		return _loc;
	} else
		return 0;
}

IString IString::upperCase(){
	std::string s = this->c_str();
	transform( s.begin(), s.end(), s.begin(), ::toupper );
	return IString(s.c_str());
}

IString IString::asString(){
	return *this;
}

//Implementado por: A.Herrmann
//TODO::Testar 
IString IString::insert(char pString , int  index, char padCharacter) {
	
	std::string _str;
	_str  = _str.append( 1, pString);
	*this = this->insert(_str.c_str() , index, padCharacter);
	
	return *this;
}

//Implementado por: A.Herrmann
IString IString::insert(const char* pString,  int index,  char padCharacter){
	IString rtrString = "";
	std::string _str, _tail;
	std::string _piece(pString);
	int _diff = index - this->length();
	
	if ( index == 0 ) {
		rtrString = pString + *this;
		*this = rtrString;
		return *this;
	}

	if (( _diff ) < 1 ) { 
		_str  = this->subString(1, index);
		_tail = this->subString(index+1, this->length());
		rtrString = _str + _piece + _tail;
	} else {
		_str  = *this;
		_str  = _str.append( _diff, padCharacter );
		_str += pString;
		rtrString = _str;
	}
	
	*this = rtrString;
	return *this;
}	

IString IString::strip(const char* pString) {
	IString _localstr(*this);
	IString _stripper(pString);
	IString _strp = _localstr.subString(1, _stripper.length());

	if (!_strp.compare(_stripper) ) {
		_localstr = _localstr.subString(_stripper.length()+1, _localstr.length());
	}
	_strp = _localstr.subString(_localstr.length() - _stripper.length() + 1, _localstr.length());
	if (!_strp.compare(_stripper) ) {
		_localstr = _localstr.subString(1, _localstr.length()- _stripper.length());
	}
	*this = _localstr;
	return _localstr;
}


bool IString::isLike(IString s){
	IString _localpattern = "*?";
	IString::iterator _lcstrIterator;
	IString::iterator _lcptrIterator;
	int _strIndex = 0;
	
	_lcstrIterator = this->begin();
	_lcptrIterator = s.begin();
	
	while ( _lcptrIterator != s.end() && _lcstrIterator != this->end() ) {
		if ( *_lcptrIterator == '*'  ) {
			if ( *_lcstrIterator == *(_lcptrIterator+1) ) {
				_lcptrIterator++;
				_lcptrIterator++;
				_lcstrIterator++;
			} else _lcstrIterator++;
		}
		
		if ( *_lcptrIterator == '?'  ) {
			_lcptrIterator++;
			_lcstrIterator++;
		}
 
 		if ( *_lcptrIterator != '*' && *_lcptrIterator != '?' ) {
			if ( *_lcptrIterator != *_lcstrIterator )return false;
			_lcptrIterator++;
			_lcstrIterator++;
		}
	}
	return true;
}



int IString::indexOf(const char* _Pchar, int startPos){
	unsigned int _loc = this->find(_Pchar, startPos);
	
	if ( _loc != std::string::npos) {
		_loc++;
		return _loc;
	} else
		return 0;
}

int IString::indexOf(const char _char, int startPos){
	unsigned int _loc = this->find(_char, startPos);
	
	if ( _loc != std::string::npos) {
		_loc++;
		return _loc;
	} else
		return 0;
}

IString	IString::remove(int _pos){
	std::string _str, _tail;
	
	if ( _pos < 0 ) return *this;

	if ( _pos < 1 ) _pos = 0;
	else _pos--;
	
	_str  = this->subString(1, _pos);
	_tail = this->subString(_pos+1, this->length());
	
	*this = _str;
	return _str;
}


//IString& IString::remove(int _pos, int _length){
//	static IString _str;
//	
//	std::string _tail;
//	
//	if ((_pos < 0) || (_pos >= this->length())) {
//			return *this;
//	} 
//	
//	if ( _length < 0 ) _length = this->length();
//	
//	
//	switch ( _pos ) {
//		case 0: {
//			_pos++;
//			break;
//		};
//		default : _pos--;
//	}
//	
//	_str  = this->subString(1, _pos);
//	
//	if ( (_pos + _length +1) < (this->length()) ) {
//		_str += this->subString(_pos + _length, this->length());
//	}
//	
//	*this = _str;
//	return _str;
//}

IString IString::reverse(){
	std::string::reverse_iterator strIterator;
	IString returnvalue; 
	
	for ( strIterator = this->rbegin(); strIterator != this->rend(); strIterator++ ) 
		returnvalue += *strIterator;
	*this = returnvalue;
	return returnvalue;		
}

IString IString::words(int _firstWord, int _numWords ) {
	IString returnString;
	
	for ( int index = _firstWord; index < _numWords; index++ ) {
		returnString.append(this->word(index));
	}
	return returnString;
}

int IString::numWords() {
	std::string::iterator strIterator;
	int numWords = 0;
	
	for ( strIterator = this->begin(); strIterator != this->end(); strIterator++ )
		if ( *strIterator == ' ') numWords++;
	return numWords;
}

//IString IString::change(const char* _Pchar, const char* _Pchara){
//	IString bstString, bst;  
//
//    unsigned int pos = this->find_first_of( const string &str, size_type index = 0 );
//    if( pos ==  string::npos ) return "";
//    std::cout << "Passo 1" << std::endl;
//    bstString  = this->subString(1,pos);
//    std::cout << "Passo 2" << std::endl;    
//    bstString += bst;
//    std::cout << pos + bst.length() << std::endl;
//    std::cout << this->length()-1 << std::endl;
//    bstString += this->subString(pos + bst.length(), this->length()-1);
//    std::cout << "Passo 4" << std::endl;
//    
//    return bstString;
//}

IString IString::removeWords(int _initWord, int _numbOfWords){
	std::string::iterator it;
	std::string tmpStr = *this;
	std::string bkp = *this;
	bool deleter = false;
	
	unsigned int i = 1;
	int deleted = 0;
	int inipos, endpos, j = 0;
	
	if ( _initWord <= 0  || _numbOfWords == 0) return *this;
	
	if (_numbOfWords < 0 ) _numbOfWords *= -1;
	
	it = bkp.begin();
	
	while ((it != bkp.end()) && (i < bkp.length()) ) {
		if (*it == ' ') {
			i++; 
			if (deleter) {
				deleted++;
			}
		}

		if ((i == _initWord) && !deleter) { 
			inipos = j;
			tmpStr  = this->substr(0,inipos) ;					
			deleter = true;
		}
		
		if ( deleted == _numbOfWords ) {
			endpos = j;
			if (inipos == 0) endpos++;
			tmpStr += this->substr(endpos,this->length());
			break;
		}
		it++;
		j++;
	}
	if ( !deleted && (tmpStr != *this) ) tmpStr += " ";
	*this = tmpStr;
	return *this;
}


bool IString::operator ==(const char* pString1) {
	return !this->compare(pString1);
}

bool IString::operator ==(char* pString1) {
	return !this->compare(pString1);
}

bool IString::operator ==(const IString& string1) {
	return !this->compare(string1.c_str());
}

bool IString::operator !=(const char c) {
	IString str ( c ) ;
	return this->compare(str.c_str());
}

bool IString::operator ==(const IString* string1) {
	return !this->compare(string1->c_str());
}

unsigned long IString::asUnsigned() {
	  if (!this->isNumber()) return 0;
	
	  long v_ret = std::atoi(this->c_str());
	  if (v_ret < 0) v_ret*=-1;
	 
	  unsigned long uv_ret = (unsigned long) v_ret;
	  return uv_ret;
}


IString IString::operator [] (int _position) {
	return this->substr(--_position);
}

IString IString::subString(int i, int length) {
	std::string n = this->substr(--i, length);
	return IString(n.c_str());
}

bool IString::isNumber()  {
	bool ret = true ;
	bool decimalFound = false ;
	bool simbolo_negativo = false;

  	if (this->length() < 1) {
    	ret = false ;
    }  else { 
		for (int i = 0 ; i < this->length() ; i ++ ) {
			if (!std::isdigit(this->at(i))) {
	            #ifdef __LIBSLV_ISTRING_ASUNSIGNED_RETURN_MODULO_EXPR        
  					if ((this->at(i) == '-') && !simbolo_negativo) simbolo_negativo = true;
  					else ret = false ;
				#else
  					ret = false;
				#endif
			}
  		}
	}
  return ret;     
}