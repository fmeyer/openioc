#ifndef _IKB_H_
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


#define _IKB_H_

#include <map>
#include <istdops.h>
#include <slvdefault.h>
#include <iexception.hpp>
#include <icursor.h>

using namespace std;

template <class Element, class Key, class ElementOps> class IGKeyBag : public std::multimap<Key, Element> {
    public:
	    typedef ICursorG<std::multimap<Key, Element>, Element, Key, ElementOps> Cursor;
               
        virtual void add (Element, Key);
        virtual bool add (Element);
		virtual void addAllFrom(IGKeyBag<Element,Key, ElementOps>);         
		
		virtual void copy(IGKeyBag<Element,Key, ElementOps>);
                
        virtual Element elementAt(Cursor);
        virtual Element elementWithKey(Key);
        virtual Element elementAtPosition(IPosition);
        virtual Element anyElement();
        virtual Element lastElement();
        virtual Element firstElement();
        virtual bool containsElementWithKey(Key );
        virtual bool isEmpty ();

        virtual bool replaceAt(Cursor , Element); // needds
        virtual bool replaceElementWithKey(Element, Cursor&); 
        virtual bool replaceElementWithKey(Element);
        virtual bool locateElementWithKey(const Key, Cursor&);        
        
        virtual bool removeElementWithKey(Key);
        virtual bool remove(Element);
        virtual bool removeLast();
		virtual void removeAt(Cursor&);
		virtual void removeAtPosition (IPosition);
		virtual bool removeAll();
		
		virtual bool setToPosition(int , Cursor&);
		virtual INumber numberOfElements();
		
		virtual bool setToFirst(Cursor&);
		virtual bool setToNext(Cursor&);
		
		virtual bool locateNextElementWithKey( Key, Cursor &);

        virtual INumber numberOfElementsWithKey(Key mykey) {
          return this->count(mykey);
        }

        IGKeyBag();
        
        IGKeyBag(unsigned long){};        
        
		virtual Cursor* newCursor() {
		  Cursor* localCursor = new Cursor(*this);
		  return localCursor;
		}

	    //Internal use only
		virtual void _resort();
       
    private:
    	ElementOps comparator;
    	bool isSorted;
    
};

//
//this sorts implements IOC two-member-with-same-key inverse sort
//
template <class Element, class Key, class ElementOps>
inline void IGKeyBag<Element, Key, ElementOps>::_resort() {
  #ifndef __SLVIOC_NO_IOC_COMPATIBLE_SORT__
  //Need�s at least 2 members...
  if (this->numberOfElements() < 2) return;
  
  //this methods, sorts using IOC logic	  
  IGKeyBag<Element, Key, ElementOps> tmp;

  //create two iterators
  typename std::multimap<Key, Element>::iterator left  = this->begin();
  typename std::multimap<Key, Element>::iterator right = this->begin();		  

  //step forward one iterator
  right++;//Avan�o um na frente          
  
  //loop until the end of the element
  while (right != this->end())
    {
    //if i have two elements with the same key, swap() then        
    if (left->first == right->first) 
      {
      tmp.add(right->second);
      tmp.add(left->second);

      //step down 2 times
      left++; right++;
      left++; right++;		      
        
      }
	else
	  {
      //add just like the sequence
      tmp.add(right->second);
      tmp.add(left->second);		      
              
      //step down 2 times              
	  left++; right++;
	  left++; right++;		      
      }

    }//while

  //now, clean up my members
  this->clear();          
  
  //create a new iterator based on temporary collection tmp
  typename std::multimap<Key, Element>::iterator newones = tmp.begin();

  //loop until tmp ends          
  while (newones != tmp.end()) 
    {
    //add ordered like IOC sorting
    this->add(newones->second);
    //step forward
    newones++;
    }

  #endif //__SLVIOC_NO_IOC_COMPATIBLE_SORT__
  
  this->isSorted = true;            
}//end

template <class Element, class Key, class ElementOps>
inline bool IGKeyBag<Element, Key, ElementOps>::locateNextElementWithKey( Key _localkey, Cursor& _localCursor) {
	_localCursor.setToNext(); // eu gostaria mas o cursor nao muda milagrosamente de posicao para o proximo.	
  
	while (_localCursor.getIterator() != this->end()) {
    	if (_localCursor.getIterator()->first == _localkey) {

    		return true;
    	}
		_localCursor.setToNext();
    }
	return false;
}


template <class Element, class Key, class ElementOps>
inline bool IGKeyBag<Element, Key, ElementOps>::setToFirst(Cursor& _localCursor){
	return _localCursor.setToFirst();
}

 
template <class Element, class Key, class ElementOps>
inline bool IGKeyBag<Element, Key, ElementOps>::setToNext(Cursor& _localCursor){
	return _localCursor.setToNext();
}

template <class Element, class Key, class ElementOps>
inline IGKeyBag<Element, Key, ElementOps>::IGKeyBag() : std::multimap<Key, Element>() {
}

template <class Element, class Key, class ElementOps>
inline void IGKeyBag<Element, Key, ElementOps>::add(Element newElement, Key newKey) 
  {
  this->isSorted = false;
  this->insert( make_pair ( newKey, newElement ) ) ;
  }

template <class Element, class Key, class ElementOps>
inline bool IGKeyBag<Element, Key, ElementOps>::add(Element newElement) 
  {
  this->isSorted = false;  
  this->insert(this->end() ,  make_pair ( comparator.key ( newElement), newElement ) ) ;
  return true;	
  }

template <class Element, class Key, class ElementOps>
inline INumber IGKeyBag<Element, Key, ElementOps>::numberOfElements() {
	return this->size();
}

template <class Element, class Key, class ElementOps>
inline bool IGKeyBag<Element, Key, ElementOps>::isEmpty() {
	return !this->size();
}

template <class Element, class Key, class ElementOps>
inline void IGKeyBag<Element, Key, ElementOps>::removeAt(typename IGKeyBag<Element,Key, ElementOps>::Cursor& localCursor) {
	if (localCursor.isValid()) {
		this->erase(localCursor.getIterator());
		localCursor.inValidate();
	}
}

template <class Element, class Key, class ElementOps>
inline Element IGKeyBag<Element, Key, ElementOps>::elementAt(Cursor localCursor) {
  //check if it�s sorted
  //if (!this->isSorted) this->_resort();
  	
  	return localCursor.element();
}

template <class Element, class Key, class ElementOps>
inline Element IGKeyBag<Element, Key, ElementOps>::elementWithKey(Key localKey) {
	
	Cursor localCursor ( *this );

 	for ( localCursor.setToFirst(); localCursor.isValid(); localCursor.setToNext() ) {
 		if ( comparator.key(localCursor.element() ) == localKey ) {
 			if ( localCursor.getIterator()->first != localKey ) {
 				this->replaceElementWithKey(localCursor.element(), localCursor);
 			}
 			return localCursor.element();
 		}
	}
	throw (INOTCONTAINSKEYEXCEPTION);
}	
	
template <class Element, class Key, class ElementOps>
inline Element IGKeyBag<Element, Key, ElementOps>::elementAtPosition(IPosition index) 
  {
  //check if it�s sorted
  if (!this->isSorted) this->_resort();
  
  Cursor localCursor(*this);
  int i = 1;
  for ( localCursor.setToFirst(); localCursor.isValid();  localCursor.setToNext()) {
		if (i++ == index) {
    		return localCursor.element();
		}
	}
	return localCursor.element();
  }

template <class Element, class Key, class ElementOps>
inline bool IGKeyBag<Element, Key, ElementOps>::replaceElementWithKey( Element newElement, typename IGKeyBag<Element,Key, ElementOps>::Cursor& localCursor) {
    if (localCursor.isValid()) {
		this->erase( localCursor.getIterator() );    	
		this->add(newElement);
		return true;
	}
	return false;
}

template <class Element, class Key, class ElementOps>
inline bool IGKeyBag<Element, Key, ElementOps>::replaceElementWithKey( Element newElement) {
	Cursor localCursor(*this);	
	localCursor.setCursorToKey(comparator.key(newElement));
	
	if (localCursor.isValid()) {

		typename multimap<Key, Element>::iterator it = find ( comparator.key( newElement ));		
		if ( it != this->end() ) {
			this->erase( it );
			this->add(newElement);
		}
		return true;
	}
	return false;
}

template <class Element, class Key, class ElementOps>
inline bool IGKeyBag<Element, Key, ElementOps>::locateElementWithKey( const Key _localKey, typename IGKeyBag<Element, Key, ElementOps>::Cursor& localCursor) {
 	for ( localCursor.setToFirst(); localCursor.isValid(); localCursor.setToNext() ) {
 		if ( comparator.key(localCursor.element() ) == _localKey ) {
 			if ( localCursor.getIterator()->first != _localKey ) {
 				this->replaceElementWithKey(localCursor.element(), localCursor);
 			}
			localCursor.valid = true; 			
 			return true;
 		}
	}
	localCursor.valid = false;
	return false;
}		   

template <class Element, class Key, class ElementOps>
inline bool IGKeyBag<Element, Key, ElementOps>::containsElementWithKey( Key _localKey) {
	typename multimap<Key, Element>::iterator it;
	it = this->find ( _localKey );
	
	if ( it != this->end() ) { 
		return true;
	}
	else return false;
}		   

template <class Element, class Key, class ElementOps>
inline bool IGKeyBag<Element, Key, ElementOps>::removeElementWithKey( const Key _localKey ) {
	return this->erase( _localKey );
}

template <class Element, class Key, class ElementOps>
inline bool IGKeyBag<Element, Key, ElementOps>::remove( Element _lcElement ) {
	typename multimap<Key, Element>::iterator it;
	it = find ( comparator.key( _lcElement ) );
	if ( it != this->end() ) {
		this->erase( comparator.key( _lcElement ) );
		return true;
	} return false;
}

template <class Element, class Key, class ElementOps>
inline bool IGKeyBag<Element, Key, ElementOps>::removeLast( ) {
	return this->erase( comparator.key( this->lastElement() ) );
}

template <class Element, class Key, class ElementOps>
inline bool IGKeyBag<Element, Key, ElementOps>::removeAll() {
	this->clear();
	return true;
}		        

template <class Element, class Key, class ElementOps>
inline void IGKeyBag<Element, Key, ElementOps>::addAllFrom(IGKeyBag<Element,Key, ElementOps> _local) {
	this->insert(_local.begin(), _local.end());
}

template <class Element, class Key, class ElementOps>
inline void IGKeyBag<Element, Key, ElementOps>::copy(IGKeyBag<Element,Key, ElementOps> _local) {
	this->insert(_local.begin(), _local.end());
}

template <class Element, class Key, class ElementOps>
inline bool IGKeyBag<Element, Key, ElementOps>::setToPosition(int _position, Cursor& _localCursor) {
	int i = 1;
	for ( _localCursor.setToFirst(); _localCursor.isValid();  _localCursor.setToNext()) {
		if (i++ == _position) {
    		return true;
		}
	}
	return false;
}

template <class Element, class Key, class ElementOps>
inline bool IGKeyBag<Element, Key, ElementOps>::replaceAt(Cursor _localCursor , Element _localElement) {
	

	if (_localCursor.isValid()) {
		typename multimap<Key, Element>::iterator it = find ( comparator.key( _localCursor.element()));		
		
		if ( it != this->end() ) {
			this->erase( it );
			this->add(_localElement);
		}
		return true;
	}
	return false;
}

template <class Element, class Key, class ElementOps>
inline Element IGKeyBag<Element, Key, ElementOps>::anyElement() { 
	Cursor tmp ( *this );
	
	if ( tmp.isValid() ) { 
		tmp.setToFirst();
		return tmp.element();
	} else throw (ICURSORINVALIDEXCEPTION);
	
}

template <class Element, class Key, class ElementOps>
inline void IGKeyBag<Element, Key, ElementOps>::removeAtPosition(IPosition _pos) {
	Cursor localCursor(*this);
  	
  	int i = 1;
	
	if (!(localCursor.isValid()) ) 
		throw (ICURSORINVALIDEXCEPTION);
  	else 
  		if ((_pos>this->size()) && (_pos < 1)) 
  			throw (IPOSITIONINVALIDEXCEPTION);
  		else {
    		for ( localCursor.setToFirst(); localCursor.isValid() && (i <= this->numberOfElements());  localCursor.setToNext()) {
				if (i++ == _pos) {
	    			this->remove(localCursor.element());
	    			return;
	    		}//if
	  
	  		}//for
	
    	}//else
}//end

template <class Element, class Key, class ElementOps>
inline Element IGKeyBag<Element, Key, ElementOps>::lastElement( ) {
	Cursor localCursor(*this);
	localCursor.setToLast();
	  
	if (!(localCursor.isValid()) ) 
		throw (ICURSORINVALIDEXCEPTION);
	else 
		return localCursor.element();
}

template <class Element, class Key, class ElementOps>
inline Element IGKeyBag<Element, Key, ElementOps>::firstElement( )  {
	Cursor localCursor(*this);
	localCursor.setToFirst();  	
	  
	if (!(localCursor.isValid()) ) 
		throw (ICURSORINVALIDEXCEPTION);
	else 
		return localCursor.element();
}
#endif //_IKB_H_