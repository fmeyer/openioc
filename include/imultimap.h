#ifndef _IMULTIMAP_H_
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


#define _IMULTIMAP_H_


#include <map>
#include <slvdefault.h>
#include <iexception.hpp>
#include <icursor.h>

using namespace std;

template <class Element, class Key> class IMultiMap : public std::multimap<Key, Element> {
    public:
	    typedef ICursor<std::multimap<Key, Element>, Element, Key> Cursor;
               
        virtual void add (Element, Key);
        virtual bool add (Element);
		virtual void addAllFrom(IMultiMap<Element,Key>);         
		virtual void copy(IMultiMap<Element,Key>);
                
        virtual Element elementAt(Cursor);
        virtual Element elementAt(Cursor) const;        
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
		
		//Added
		virtual Cursor *newCursor();
        
        IMultiMap();
    private:
};

//Added
template <class Element , class Key>
inline IMultiMap<Element, Key>::Cursor* IMultiMap<Element, Key>::newCursor()
  {
  Cursor *_tmp = new Cursor(*this);
  
  return _tmp;
  }


template <class Element, class Key> 
inline IMultiMap<Element, Key>::IMultiMap() : std::multimap<Key, Element>() {
}

template <class Element, class Key> 
inline void IMultiMap<Element, Key>::add(Element newElement, Key newKey) {
	this->insert( make_pair ( newKey, newElement ) ) ;
}

template <class Element, class Key> 
inline bool IMultiMap<Element, Key>::add(Element newElement) {
	
	Cursor tmpCur(*this);
	this->insert( make_pair ( key ( newElement), newElement ) ) ;
	return true;	
}

template <class Element, class Key> 
inline INumber IMultiMap<Element, Key>::numberOfElements() {
	return this->size();
}

template <class Element, class Key> 
inline bool IMultiMap<Element, Key>::isEmpty() {
	return !this->size();
}

template <class Element, class Key> 
inline void IMultiMap<Element, Key>::removeAt(typename IMultiMap<Element,Key>::Cursor& localCursor) {
	if (localCursor.isValid()) {
		this->erase(localCursor.getIterator());
		localCursor.inValidate();
	}
}

template <class Element, class Key> 
inline Element IMultiMap<Element, Key>::elementAt(Cursor localCursor) const 
  {
  return localCursor.element();
  }

template <class Element, class Key> 
inline Element IMultiMap<Element, Key>::elementAt(Cursor localCursor) {
	return localCursor.element();
}

template <class Element, class Key> 
inline Element IMultiMap<Element, Key>::elementWithKey(Key localKey) {
	typename std::multimap<Key, Element>::iterator it = this->find(localKey);
	
	if ( it != this->end() ) {
		return it->second;
	} else {
		throw (INOTCONTAINSKEYEXCEPTION);
	}
}

template <class Element, class Key>
inline Element IMultiMap<Element, Key>::elementAtPosition(IPosition index) {
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
inline bool IMultiMap<Element, Key>::replaceElementWithKey( Element newElement, typename IMultiMap<Element,Key>::Cursor& localCursor) {
	
	Cursor*	cursor = new Cursor(*this);
	
    cursor->setCursorToKey(key(newElement));
	
    if (cursor->isValid()) {
			typename multimap<Key, Element>::iterator it = find ( key( cursor->element()));		
			if ( it != this->end() ) {
				this->erase( it );
				this->add(newElement);
			}
		return true;
	}
	localCursor = *cursor;
	return false;
}

template <class Element, class Key> 
inline bool IMultiMap<Element, Key>::replaceElementWithKey( Element newElement) {
	Cursor localCursor(*this);
	localCursor.setCursorToKey(key(newElement));
	
	if (localCursor.isValid()) {

		typename multimap<Key, Element>::iterator it = find ( key( newElement ));		
		if ( it != this->end() ) {
			this->erase( it );
			this->add(newElement);
		}
		return true;
	}
	return false;
}

template <class Element, class Key>
inline bool IMultiMap<Element, Key>::locateElementWithKey( const Key _localKey, typename IMultiMap<Element, Key>::Cursor& localCursor) {
	typename multimap<Key, Element>::iterator it;
	it = this->find ( _localKey );
	
	if ( it != this->end() ) { 
		localCursor.setIterator(it);
		localCursor.valid = true;
		return true;
	}
	else { 
		localCursor.valid = false;
		return false;
	}
}		   

template <class Element, class Key>
inline bool IMultiMap<Element, Key>::containsElementWithKey( Key _localKey) {
	typename multimap<Key, Element>::iterator it;
	it = this->find ( _localKey );
	
	if ( it != this->end() ) { 
		return true;
	}
	else return false;
}		   

template <class Element, class Key>
inline bool IMultiMap<Element, Key>::removeElementWithKey( const Key _localKey ) {
	Cursor localCursor (*this);

	localCursor.setCursorToKey(_localKey);
	if (localCursor.isValid()) {
		this->erase(localCursor.getIterator());
		return true;
	}	return false;
}

template <class Element, class Key>
inline bool IMultiMap<Element, Key>::remove( Element _lcElement ) {
	
	Cursor localCursor( *this );
	
	this->locateElementWithKey(key ( _lcElement), localCursor);
	
	if (localCursor.isValid()) {
		this->erase(localCursor.getIterator());
		localCursor.inValidate();
		return true;
	}	return false;
}

template <class Element, class Key>
inline bool IMultiMap<Element, Key>::removeLast( ) {
	return this->erase( key( this->lastElement() ) );
}

template <class Element, class Key>
inline bool IMultiMap<Element, Key>::removeAll() {
	this->clear();
	return true;
}		        

template <class Element, class Key>
inline void IMultiMap<Element, Key>::addAllFrom(IMultiMap<Element,Key> _local) {
	this->insert(_local.begin(), _local.end());
}

template <class Element, class Key>
inline void IMultiMap<Element, Key>::copy(IMultiMap<Element,Key> _local) {
	this->insert(_local.begin(), _local.end());
}

template <class Element, class Key>
inline bool IMultiMap<Element, Key>::setToPosition(int _position, Cursor& _localCursor) {
	int i = 1;
	
	for ( _localCursor.setToFirst(); _localCursor.isValid();  _localCursor.setToNext()) {
		if (i++ == _position) {
    		return true;
		}
	}
	return false;
}

template <class Element, class Key>
inline bool IMultiMap<Element, Key>::replaceAt(Cursor _localCursor , Element _localElement) {
	

	if (_localCursor.isValid()) {
		typename multimap<Key, Element>::iterator it = find ( key( _localCursor.element()));		
		
		if ( it != this->end() ) {
			this->erase( it );
			this->add(_localElement);
		}
		return true;
	}
	return false;
}

template <class Element, class Key>
inline Element IMultiMap<Element, Key>::anyElement() {
	Cursor tmp ( *this );
	tmp.setToFirst();
	return tmp.element();
}

template <class Element, class Key>
inline void IMultiMap<Element, Key>::removeAtPosition(IPosition _pos) {
	Cursor localCursor(*this);
	int i = 1;
	for ( localCursor.setToFirst(); localCursor.isValid() && (i <= this->numberOfElements());  localCursor.setToNext()) {
		if (i++ == _pos) {
			this->remove(localCursor.element());
			return;
		}
	}
}

template <class Element, class Key>
inline Element IMultiMap<Element, Key>::lastElement( ) {
		Cursor localCursor(*this);
		localCursor.setToLast();
		return localCursor.element();
}

template <class Element, class Key>
inline Element IMultiMap<Element, Key>::firstElement( ) {
		Cursor localCursor(*this);
		localCursor.setToFirst();
		return localCursor.element();
}


#endif //_IMULTIMAP_H_