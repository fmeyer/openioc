#ifndef ISTRING_H_	
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


#define ISTRING_H_

#include <slvdefault.h>
#include <string>

namespace std {
	inline string itos(long i) { 
			std::stringstream s;
			s << i;
			return s.str();
	}
	
	inline string dtos(double i) { 
			std::stringstream s;
			s << i;
			return s.str();
	}
	inline string ctos(char c) {
		char* s = "";
		s[0] = c;
		std::string valor(s);
		return valor;
	}
     
}



class IString : public std::string {
public:
	IString() : std::string() {}	
	IString(const char* s) : std::string(s) {}
	IString(std::string strT) : std::string(strT) {}
	IString(long longValue) : std::string(std::itos(longValue)) {}
	IString(int longValue) : std::string(std::itos(longValue)) {}	
	IString(double dbValue) : std::string(std::dtos(dbValue)) {}
	IString(unsigned long longValue) : std::string(std::itos(longValue)) {}
	IString(unsigned char c[]):std::string((char*)c){} //A.Herrmann
	IString(const char c):std::string((const char*)c){}//A.Herrmann	
	
	virtual ~IString(){}
	
	bool     isLike(IString s);
	double	 asDouble();
	double   asDouble() const {
		return atof(this->c_str());
	}
		
	IString  asString();
	long     asInt();
	IString  word(int i);
	IString  upperCase();

	void change(IString a, IString b, int i);
	IString insert(const char* pString,  int index = 0,  char padCharacter = ' ');
	IString insert(char pString , int  index = 0, char padCharacter = ' ');
	
	IString strip( const char* = " ");
	
	int lastIndexOf(char c, int startPos = 0);
	int lastIndexOf(const char* _Pchar, int startPos = 0);	

	int indexOf(const char* , int startPos = 0);
	int indexOf(const char, int startPos = 0 );

	IString	 remove(int );
//	IString& remove (int , int) ;

	IString& remove(int _pos, int _length){
		static IString _str;
		std::string _tail;

		if ((_pos < 0) || (_pos > this->length())) {
				return *this;
		} 
		if ( _length < 0 ) _length = this->length();
	
		switch ( _pos ) {
			case 0: {
				_pos++;
				break;
			};
		}
		_pos--;
		_str  = this->subString(1, _pos);
		
		if ( (_pos + _length +1) <= (this->length()) ) {
			_str += this->subString(_pos + _length +1, this->length());
		}
		*this = _str;
		return _str;
	}
	
	IString reverse();
	IString words(int , int );
	int numWords();
	
//IString change(const char* _Pchar, const char* _Pchara);

	IString change(const char* _Pchar, const char* _Pchara) {
		std::string _localizator = _Pchar;
		std::string _localTrocator = _Pchara;
		std::string newhead = "";
		std::string tmp;
		std::string::iterator it;
		std::string bkp = *this;
		int i = 0;
	
		if (_localizator == "" ) return *this;
		
		it = bkp.begin();
		
		while ((it != bkp.end()) && (i < bkp.length())) {
			tmp = bkp.substr(i,_localizator.length());
			
			if ( tmp == _localizator ) {
				newhead = bkp.substr(0,i);
				if ( _localTrocator.length() >= 0 ) 
					newhead = newhead + _Pchara;
				newhead = newhead + bkp.substr(i+_localizator.length());
				bkp = newhead;
				it = bkp.begin();
			}
			it++;
			i++;
		}
		*this = bkp;
		return *this;
}	
	
	IString sbstr (int in, int f ) {
		std::string retvalue; 
		std::string value(this->c_str());
		
		for ( int i = in; i < f; i++ ) {
			retvalue += value.at(i);
		}
		return retvalue;
	}
	
	
	IString removeWords(int _initWord, int _numbOfWords);
	bool operator ==(const char*);
	bool operator ==(char*);	
	bool operator ==(const IString&);
	bool operator ==(const IString*);
	bool operator !=(const char);
	
	IString operator [] (int _position);
	
	char& operator [] (IPosition _position) {
		return std::string::operator[](_position);
	}

	IString& translate( const IString& pInputChars, const IString& pOutputChars, char padCharacter = ' ' ) {
		int _stdIt = 0;
		int _stdIl = 0;
		
		std::string _tmpRet(*this);
		
		while ( _stdIt < pOutputChars.length() ) {
			if ( pOutputChars.at(_stdIt) != padCharacter ) {
				_stdIl = 0;
				while (_stdIl != this->length()) {
					if ( pInputChars.at(_stdIt) == this->at(_stdIl) ) {
						_tmpRet[_stdIl] = pOutputChars.at(_stdIt);
					}
				    _stdIl++;	
				}
			}
			_stdIt++;
		}
		*this = _tmpRet;
		return *this;
	}
	
	int occurrencesOf(IString _lcValue) {
		int _carry = 0;
		std::string::size_type _offset = this->find_first_of( _lcValue.c_str());
		
		while ( _offset != std::string::npos ) {
			_carry++;
			_offset = this->find_first_of( _lcValue.c_str(), _offset + _lcValue.length() + 1);
		}
		return _carry;
	}
	
	long includes(IString _lcValue){
		std::string::size_type _offset = this->find_first_of( _lcValue.c_str());
		if (_offset != std::string::npos )
			return _offset;
		else 
			return 0;
	} 
  
	IString change(char c1 , char c2) {
		IString pr1(c1), pr2(c2); 
		
		return this->change(pr1.c_str(), pr2.c_str());
	}
	IString change(IString pr1 , const char* pr2){
		return this->change(pr1.c_str(), pr2);
	}
  
	friend std::ostream& operator <<(std::ostream& aStream, const IString& aString){
	 	aStream << aString.c_str();
	 	return aStream;
	}    

	operator const char* () const { 
    	char* pCharArray = new char[this->length()];
    	strcpy(pCharArray, this->c_str());
    	return pCharArray;
	}
	
	operator char* () const { 
    	char* pCharArray = new char[this->length()];
    	strcpy(pCharArray, this->c_str());
    	return pCharArray;
	}

	IString  subString(int i, int length = 1 );
    unsigned long asUnsigned(); 

	bool isNumber();
	
	bool isDigits() {
		int i;
		for (int i = 0 ; i < this->length() ; i ++ ) {
			if (!std::isdigit(this->at(i))) {
				return false;
			}
		}
		return true;
	}

	IString strip(char pString) {
		IString _localstr(pString);
		return this->strip(_localstr.c_str());
	}
	

	bool isWhiteSpace() { 
		std::string::iterator it; 
		
		if (this->length() == 0 ) return false;
		
		for ( it = this->begin(); it!= this->end(); it++ ) {
			if ( *it != ' ' )
				return false;
		}
		return true;
	}

	bool isLike(IString s) const {
	        IString _localpattern = "*?";
	        IString::iterator _lcstrIterator;
	        IString::iterator _lcptrIterator;
	        int _strIndex = 0;
	 
	        //Tira a constância, gera um C char e inicializa uma nova versão
	        //(cópia) de this;
	        IString copia ((const_cast<IString*>(this))->c_str());
	
	        _lcstrIterator = copia.begin();
	        _lcptrIterator = s.begin();
	
	        while ( _lcptrIterator != s.end() && _lcstrIterator != copia.end() ) {
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
	
};

#endif /*ISTRING_H_*/