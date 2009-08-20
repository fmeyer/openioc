#ifndef _ICOMPACT_H_
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


#define _ICOMPACT_H_

//#ifndef _IKB_H_
//#define _IKB_H_

#include <map>
#include <slvdefault.h>
#include <iexception.hpp>
#include <icursor.h>
#include <istdops.h>

using namespace std;

template <class Element, class Key, class ElementOps> class IGHashKeySet : public std::map<Key, Element> {
    public:
	    typedef ICursorG<std::map<Key, Element>, Element, Key, ElementOps> Cursor;
               
        virtual void add (Element, Key);
        virtual bool add (Element);
		virtual void addAllFrom(IGHashKeySet<Element,Key, ElementOps>);         
		virtual void copy(IGHashKeySet<Element,Key, ElementOps>);
                
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
        
        IGHashKeySet();
    private:
    	ElementOps comparator;
    
};



template <class Element, class Key, class ElementOps>
inline bool IGHashKeySet<Element, Key, ElementOps>::setToFirst(Cursor& _localCursor){
	return _localCursor.setToFirst();
}

 
template <class Element, class Key, class ElementOps>
inline bool IGHashKeySet<Element, Key, ElementOps>::setToNext(Cursor& _localCursor){
	return _localCursor.setToNext();
}

template <class Element, class Key, class ElementOps>
inline IGHashKeySet<Element, Key, ElementOps>::IGHashKeySet() : std::map<Key, Element>() {
}

template <class Element, class Key, class ElementOps>
inline void IGHashKeySet<Element, Key, ElementOps>::add(Element newElement, Key newKey) {
	this->insert( make_pair ( newKey, newElement ) ) ;
}

template <class Element, class Key, class ElementOps>
inline bool IGHashKeySet<Element, Key, ElementOps>::add(Element newElement) {

	if (!this->containsElementWithKey (comparator.key ( newElement))) { 
		this->insert( make_pair ( comparator.key ( newElement), newElement ) ) ;
		return true;	
	} else return false;
}

template <class Element, class Key, class ElementOps>
inline INumber IGHashKeySet<Element, Key, ElementOps>::numberOfElements() {
	return this->size();
}

template <class Element, class Key, class ElementOps>
inline bool IGHashKeySet<Element, Key, ElementOps>::isEmpty() {
	return !this->size();
}

template <class Element, class Key, class ElementOps>
inline void IGHashKeySet<Element, Key, ElementOps>::removeAt(typename IGHashKeySet<Element,Key, ElementOps>::Cursor& localCursor) {
	if (localCursor.isValid()) {
		this->erase(localCursor.getIterator());
		localCursor.inValidate();
	}
}

template <class Element, class Key, class ElementOps>
inline Element IGHashKeySet<Element, Key, ElementOps>::elementAt(Cursor localCursor) {
	return localCursor.element();
}

template <class Element, class Key, class ElementOps>
inline Element IGHashKeySet<Element, Key, ElementOps>::elementWithKey(Key localKey) {
	typename std::map<Key, Element>::iterator it = this->find(localKey);

	if ( it != this->end() ) {
		return it->second;
	} else {
		throw (INOTCONTAINSKEYEXCEPTION);
	}
}

template <class Element, class Key, class ElementOps>
inline Element IGHashKeySet<Element, Key, ElementOps>::elementAtPosition(IPosition index) {
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
inline bool IGHashKeySet<Element, Key, ElementOps>::replaceElementWithKey( Element newElement, typename IGHashKeySet<Element,Key, ElementOps>::Cursor& localCursor) {
	
	Cursor*	cursor = new Cursor(*this);
    cursor->setCursorToKey(comparator.key(newElement));
    if (cursor->isValid()) {
			typename map<Key, Element>::iterator it = find ( comparator.key( cursor->element()));		
			if ( it != this->end() ) {
				this->erase( it );
				this->add(newElement);
			}
		return true;
	}
	localCursor = *cursor;
	return false;
}

template <class Element, class Key, class ElementOps>
inline bool IGHashKeySet<Element, Key, ElementOps>::replaceElementWithKey( Element newElement) {
	Cursor localCursor(*this);
	localCursor.setCursorToKey(comparator.key(newElement));
	
	if (localCursor.isValid()) {

		typename map<Key, Element>::iterator it = find ( comparator.key( newElement ));		
		if ( it != this->end() ) {
			this->erase( it );
			this->add(newElement);
		}
		return true;
	}
	return false;
}

template <class Element, class Key, class ElementOps>
inline bool IGHashKeySet<Element, Key, ElementOps>::locateElementWithKey( const Key _localKey, typename IGHashKeySet<Element, Key, ElementOps>::Cursor& localCursor) {
	typename map<Key, Element>::iterator it;
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

template <class Element, class Key, class ElementOps>
inline bool IGHashKeySet<Element, Key, ElementOps>::containsElementWithKey( Key _localKey) {
	typename map<Key, Element>::iterator it;
	it = this->find ( _localKey );
	
	if ( it != this->end() ) { 
		return true;
	}
	else return false;
}		   

template <class Element, class Key, class ElementOps>
inline bool IGHashKeySet<Element, Key, ElementOps>::removeElementWithKey( const Key _localKey ) {
	return this->erase( _localKey );
}

template <class Element, class Key, class ElementOps>
inline bool IGHashKeySet<Element, Key, ElementOps>::remove( Element _lcElement ) {
	typename map<Key, Element>::iterator it;
	it = find ( comparator.key( _lcElement ) );
	if ( it != this->end() ) {
		this->erase( comparator.key( _lcElement ) );
		return true;
	} return false;
}

template <class Element, class Key, class ElementOps>
inline bool IGHashKeySet<Element, Key, ElementOps>::removeLast( ) {
	return this->erase( comparator.key( this->lastElement() ) );
}

template <class Element, class Key, class ElementOps>
inline bool IGHashKeySet<Element, Key, ElementOps>::removeAll() {
	this->clear();
	return true;
}		        

template <class Element, class Key, class ElementOps>
inline void IGHashKeySet<Element, Key, ElementOps>::addAllFrom(IGHashKeySet<Element,Key, ElementOps> _local) {
	this->insert(_local.begin(), _local.end());
}

template <class Element, class Key, class ElementOps>
inline void IGHashKeySet<Element, Key, ElementOps>::copy(IGHashKeySet<Element,Key, ElementOps> _local) {
	this->insert(_local.begin(), _local.end());
}

template <class Element, class Key, class ElementOps>
inline bool IGHashKeySet<Element, Key, ElementOps>::setToPosition(int _position, Cursor& _localCursor) {
	int i = 1;
	for ( _localCursor.setToFirst(); _localCursor.isValid();  _localCursor.setToNext()) {
		if (i++ == _position) {
    		return true;
		}
	}
	return false;
}

template <class Element, class Key, class ElementOps>
inline bool IGHashKeySet<Element, Key, ElementOps>::replaceAt(Cursor _localCursor , Element _localElement) {
	

	if (_localCursor.isValid()) {
		typename map<Key, Element>::iterator it = find ( comparator.key( _localCursor.element()));		
		
		if ( it != this->end() ) {
			this->erase( it );
			this->add(_localElement);
		}
		return true;
	}
	return false;
}

template <class Element, class Key, class ElementOps>
inline Element IGHashKeySet<Element, Key, ElementOps>::anyElement() {
	Cursor tmp ( *this );
	tmp.setToFirst();
	return tmp.element();
}

template <class Element, class Key, class ElementOps>
inline void IGHashKeySet<Element, Key, ElementOps>::removeAtPosition(IPosition _pos) {
	Cursor localCursor(*this);
	int i = 1;
	for ( localCursor.setToFirst(); localCursor.isValid() && (i <= this->numberOfElements());  localCursor.setToNext()) {
		if (i++ == _pos) {
			this->remove(localCursor.element());
			return;
		}
	}
}

template <class Element, class Key, class ElementOps>
inline Element IGHashKeySet<Element, Key, ElementOps>::lastElement( ) {
		Cursor localCursor(*this);
		localCursor.setToLast();
		return localCursor.element();
}

template <class Element, class Key, class ElementOps>
inline Element IGHashKeySet<Element, Key, ElementOps>::firstElement( ) {
		Cursor localCursor(*this);
		localCursor.setToFirst();
		return localCursor.element();
}
//#endif //_IKB_H_
	

#endif //_ICOMPACT_H_