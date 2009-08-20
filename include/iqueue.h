#ifndef _IQU_H_
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


#define _IQU_H_

#include <list>
#include <slvdefault.h>
#include <icursor.h>

template <class Element> class IQueue : public std::list<Element> {
    public:
	    typedef ICursorEl<std::list<Element>, Element> Cursor;
	    
		virtual Cursor* newCursor() {
			Cursor* localCursor = new Cursor(*this);
			return localCursor;
		}	    
               
		virtual bool enqueue(Element);
		virtual bool dequeue(Element&);
        virtual Element elementAt(Cursor);
        virtual INumber numberOfElements();
        virtual void add(Element);
        
        IQueue(){}
};

template <class Element>
inline void IQueue<Element>::add(Element _element)
  {
  this->push_front(_element);
  }



template <class Element>
inline bool IQueue<Element>::enqueue (Element _element) {
	   this->push_back(_element);
	   return true;
}

template <class Element>
inline bool IQueue<Element>::dequeue (Element& _element) 
  {
  //dequeue
  //Copies the first element of the collection to the given
  if ( this->size() > 0) 
    { 
	_element = this->front();
	this->pop_front();	
	return true;
	}
	
  return false;
  }

template <class Element>
inline Element IQueue<Element>::elementAt (Cursor _localCursor) {
	if ( _localCursor.isValid() ) {
		return _localCursor.element();
	}
	return (Element)NULL;
}


template <class Element>
inline INumber  IQueue<Element>::numberOfElements() {
	return this->size();
}

#endif //_IQU_H_