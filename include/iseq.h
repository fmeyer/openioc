#ifndef _ISEQ_H_
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


#define _ISEQ_H_

#include <slvdefault.h>
#include <icursor.h>
#include <iexception.hpp>

#include <list> 

template <class Element> 
class ISequence : public std::list<Element> {
	public:
		typedef ICursorEl<std::list<Element>, Element> Cursor;

		virtual bool add(Element);
		virtual Element elementAtPosition(IPosition);
        virtual Element elementAt(Cursor);
        virtual Element firstElement();
		virtual Element lastElement();
        virtual INumber numberOfElements();      
		virtual void removeAtPosition(IPosition);        
        virtual void removeAll();
        virtual void addAsLast(Element);
        ISequence() {};
};

template <class Element>
inline bool  ISequence<Element>::add(Element _lcElement) 
  {

  typename std::list<Element>::iterator it = this->end();
	
  it = insert( it, _lcElement );
  if ( it != this->end() ) 
    {
	return true;
	}	
  
  return false;
  }

template <class Element>
inline Element ISequence<Element>::elementAtPosition(IPosition _pos) {
	Cursor localCursor(*this);
	int i = 1;
	for ( localCursor.setToFirst(); localCursor.isValid();  localCursor.setToNext()) {
		if (i++ == _pos) {
    		return localCursor.element();
		}
	}
	throw (IPOSITIONINVALIDEXCEPTION);
}

template <class Element>
inline void ISequence<Element>::removeAtPosition(IPosition _pos) {
	Cursor localCursor(*this);
	int i = 1;
	for ( localCursor.setToFirst(); localCursor.isValid() && (i <= this->numberOfElements());  localCursor.setToNext()) {
		if (i++ == _pos) {
			this->remove(localCursor.element());
			return;
		}
	}
	throw (IPOSITIONINVALIDEXCEPTION);
}

template <class Element>
inline Element ISequence<Element>::elementAt(Cursor _localcursor) {
	return _localcursor.element();
	
}

template <class Element>
inline INumber ISequence<Element>::numberOfElements() {
	return this->size();
}

template <class Element>
inline void ISequence<Element>::removeAll() {
	this->clear();
}

template <class Element>
inline void ISequence<Element>::addAsLast (Element e) {
	this->add( e );
}

template <class Element>
inline Element ISequence<Element>::firstElement() {
	Cursor localCursor(*this);
	localCursor.setToFirst();
	return localCursor.element();
}

template <class Element>
inline Element ISequence<Element>::lastElement() {
	Cursor localCursor(*this);
	localCursor.setToLast();
	return localCursor.element();
}

#endif