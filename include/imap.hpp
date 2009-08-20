#ifndef IMAP_H_
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


#define IMAP_H_

#include <map>
#include <slvdefault.h>
#include <iexception.hpp>
#include <icursor.h>

using namespace std;

template <class Element> class cmp_map {
	public:
		bool operator () ( Element* a, Element* b)  const {
			if ( *a < *b )
				return true;
			return false;
		}
		bool operator () ( Element a, Element b)  const {
			if ( a < b )
				return true;
			return false;
		}
		
};

//typedef cmp_mojo<mojo*> comparator;

template <class Element, class Key> class IMap : public std::map<Key, Element, cmp_map<Key> > {
    public:
	    typedef ICursor<std::map<Key, Element, cmp_map<Key> >, Element, Key> Cursor;
               
        virtual void add (Element, Key);
        virtual bool add (Element);
	virtual void addAllFrom(IMap<Element,Key>);         
	virtual void copy(IMap<Element,Key>);
                
        virtual Element  elementAt(Cursor);
        virtual Element  elementWithKey(Key);
        virtual Element  elementAtPosition(IPosition);
        virtual Element  anyElement();
        virtual Element  lastElement();
        virtual Element  firstElement();
        //Implementa��o - const
        virtual Element  elementAt(Cursor) const;
        virtual Element  elementAtPosition(IPosition) const;
        virtual Element  elementWithKey(Key) const;      		       

    
        virtual bool containsElementWithKey(Key );
        virtual bool isEmpty ();
        virtual bool isFirst ( Cursor );

        virtual bool replaceAt(Cursor , Element); // needds
        virtual bool replaceElementWithKey(Element, Cursor&); 
        virtual bool replaceElementWithKey(Element);
        virtual bool locateElementWithKey(const Key, Cursor&);
        virtual bool contains(Element); 

virtual INumber numberOfElements() const; 
        virtual bool locateElementWithKey(const Key, Cursor&) const;                
        virtual bool containsElementWithKey(Key ) const;

        virtual bool removeElementWithKey(Key);
        virtual bool remove(Element);
        virtual bool removeLast();
		virtual void removeAt(Cursor&);
		virtual void removeAtPosition (IPosition);
		virtual bool removeAll();

        virtual INumber numberOfDifferentKeys() {
          return numberOfElements();
        }

		virtual bool setToPosition(int , Cursor&);
		virtual INumber numberOfElements();

     
        IMap();
    private:
};

template <class Element, class Key> 
inline bool IMap<Element, Key>::contains(Element _localElement) {
	return containsElementWithKey ( key ( _localElement ) );
}

template <class Element, class Key> 
inline bool IMap<Element, Key>::isFirst(Cursor _lcursor) {
	if ( this->firstElement() == _lcursor.element() ) 
		return true;
	else 
		return false;
}


template <class Element, class Key> 
inline IMap<Element, Key>::IMap() : std::map<Key, Element,cmp_map<Key> >() {
}

template <class Element, class Key> 
inline void IMap<Element, Key>::add(Element newElement, Key newKey) {
	this->operator[](key(newElement)) = newElement;		
//	this->insert( make_pair ( newKey, newElement ) ) ;			
}

template <class Element, class Key> 
inline bool IMap<Element, Key>::add(Element newElement) {
	
  Cursor tmpCur(*this);
  
  bool retorno = false;

  if ( !locateElementWithKey(key(newElement), tmpCur) ) { 
	this->operator[](key(newElement)) = newElement;		  
//	this->insert( make_pair ( key ( newElement), newElement ) ) ;		
	retorno = true;
  } 
  return retorno;
}

template <class Element, class Key> 
inline INumber IMap<Element, Key>::numberOfElements() const{
	return this->size();
}

template <class Element, class Key> 
inline INumber IMap<Element, Key>::numberOfElements() {
	return this->size();
}

template <class Element, class Key> 
inline bool IMap<Element, Key>::isEmpty() {
	return !this->size();
}

template <class Element, class Key> 
inline void IMap<Element, Key>::removeAt(typename IMap<Element,Key>::Cursor& localCursor) {
//	Key localKey = make_pair ( newKey, newElement ) key(localCursor.element());
	localCursor.inValidate();
	this->erase(localCursor.getIterator());
}

template <class Element, class Key> 
inline Element IMap<Element, Key>::elementAt(Cursor localCursor) const {
	return this->elementWithKey(key(localCursor.element()));
}

template <class Element, class Key> 
inline Element IMap<Element, Key>::elementAt(Cursor localCursor) {
	return this->elementWithKey(key(localCursor.element()));
}


template <class Element, class Key> 
inline Element IMap<Element, Key>::elementWithKey(Key _localKey) {
	int DEBUG_COUNT = 0;

	Cursor localCursor(*this);
 	for ( localCursor.setToFirst(); localCursor.isValid(); localCursor.setToNext() ) {
 		if ( key(localCursor.element() ) == _localKey ) {
			return (localCursor.element());
 		}
	}
	return localCursor.element();
}

template <class Element, class Key> 
inline Element IMap<Element, Key>::elementWithKey(Key localKey) const {
	return const_cast<IMap<Element, Key>*>(this)->elementWithKey(localKey);
}


template <class Element, class Key>
inline Element IMap<Element, Key>::elementAtPosition(IPosition index) const{
	Cursor localCursor(*this);
	int i = 1;
	for ( localCursor.setToFirst(); localCursor.isValid();  localCursor.setToNext()) {
		if (i++ == index) {
    		return localCursor.element();
		}
	}
	return localCursor.element();
}

template <class Element, class Key>
inline Element IMap<Element, Key>::elementAtPosition(IPosition index) {
	Cursor localCursor(*this);
	int i = 1;
	for ( localCursor.setToFirst(); localCursor.isValid();  localCursor.setToNext()) {
		if (i++ == index) {
    		return localCursor.element();
		}
	}
	return localCursor.element();
}


template <class Element, class Key> 
inline bool IMap<Element, Key>::replaceElementWithKey( Element newElement, typename IMap<Element,Key>::Cursor& localCursor) {

	typename map<Key, Element, cmp_map<Key> >::iterator it; 
	it = localCursor.getIterator();
	
    if (localCursor.isValid()) {
    	if ( key ( newElement ) == key ( localCursor.element() ) ) {
			this->operator[](key(newElement)) = newElement;	
			return true;
    	}else {
			this->erase( it );    	
			this->add(newElement);
			return true;
    	}
	}
	return false;
}

template <class Element, class Key> 
inline bool IMap<Element, Key>::replaceElementWithKey( Element newElement) {
	Cursor localCursor(*this);

	localCursor.setCursorToKey(key(newElement));

	if (localCursor.isValid()) {
		this->operator[](key(newElement)) = newElement;	
		return true;
	}
	return false;
}


template <class Element, class Key>
inline bool IMap<Element, Key>::locateElementWithKey( const Key _localKey, typename IMap<Element, Key>::Cursor& localCursor) const {
	return const_cast<IMap<Element,Key>*>(this)->locateElementWithKey(_localKey , localCursor);	
}	


template <class Element, class Key>
inline bool IMap<Element, Key>::locateElementWithKey( const Key _localKey, typename IMap<Element, Key>::Cursor& localCursor) {
	
 	for ( localCursor.setToFirst(); localCursor.isValid(); localCursor.setToNext() ) {
 		if ( key(localCursor.element() ) == _localKey ) {
			localCursor.valid = true; 			
 			return true;
 		}
	}
		
	localCursor.valid = false;
	return false;
}		   

template <class Element, class Key>
inline bool IMap<Element, Key>::containsElementWithKey( Key _localKey) {
	typename map<Key, Element, cmp_map<Key> >::iterator it;
	it = this->find ( _localKey );
	
	if ( it != this->end() ) { 
		return true;
	}
	else return false;
}

template <class Element, class Key>
inline bool IMap<Element, Key>::containsElementWithKey( Key _localKey) const {
  typename map<Key, Element, cmp_map<Key> >::const_iterator it;
  

  it = this->find ( _localKey );
	
  if ( it != this->end() ) 
    { 
	return true;
	}
  else return false;
}


template <class Element, class Key>
inline bool IMap<Element, Key>::removeElementWithKey( const Key _localKey ) {
	return this->erase( _localKey );
}

template <class Element, class Key>
inline bool IMap<Element, Key>::remove( Element _lcElement ) {
	typename map<Key, Element, cmp_map<Key> >::iterator it;
  	it = this->begin();
  	
  	while (it != this->end()) {
	    if (it->second == _lcElement) { 
			this->erase(it);      	
      		return true;
      	}
   	 	it++;
    }
  
  return false;
}

template <class Element, class Key>
inline bool IMap<Element, Key>::removeLast( ) {
	return this->erase( key( this->lastElement() ) );
}

template <class Element, class Key>
inline bool IMap<Element, Key>::removeAll() {
	this->clear();
	return true;
}		        

template <class Element, class Key>
inline void IMap<Element, Key>::addAllFrom(IMap<Element,Key> _local) {
	this->insert(_local.begin(), _local.end());
}

template <class Element, class Key>
inline void IMap<Element, Key>::copy(IMap<Element,Key> _local) {
	this->insert(_local.begin(), _local.end());
}


template <class Element, class Key>
inline bool IMap<Element, Key>::setToPosition(int _position, Cursor& _localCursor) {
	int i = 1;

	for ( _localCursor.setToFirst(); _localCursor.isValid();  _localCursor.setToNext()) {
		if (i++ == _position) {
    		return true;
		}
	}
	return false;	
}

template <class Element, class Key>
inline bool IMap<Element, Key>::replaceAt(Cursor _localCursor , Element _localElement) 
  {
  if (_localCursor.isValid()) 
    {
	this->operator[](key(_localCursor.element())) = _localElement;	
   // _localCursor.setCursorToKey(key(_localCursor.element()));
  	return true;
	}
  return false;
  }

template <class Element, class Key>
inline Element IMap<Element, Key>::anyElement() {
	Cursor tmp ( *this );
	tmp.setToFirst();
	return tmp.element();
}

template <class Element, class Key>

inline void IMap<Element, Key>::removeAtPosition(IPosition _pos) {
	Cursor localCursor(*this);
	int i = 1;

	for ( localCursor.setToFirst(); localCursor.isValid() && (i <= this->numberOfElements());  localCursor.setToNext()) {
		if (i == _pos) {
			this->erase(localCursor.getIterator());
			return;
		}
		i++;
	}
}

template <class Element, class Key>
inline Element IMap<Element, Key>::lastElement( ) {
		Cursor localCursor(*this);
		localCursor.setToLast();
		return localCursor.element();
}

template <class Element, class Key>
inline Element IMap<Element, Key>::firstElement( ) {
		Cursor localCursor(*this);
		localCursor.setToFirst();
		return localCursor.element();
}

#endif /*IMAP_H_*/