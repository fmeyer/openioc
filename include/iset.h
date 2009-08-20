#ifndef _ISET_H_
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


#define _ISET_H_

#include <set>
#include <slvdefault.h>
#include <icursor.h>
#include <algorithm>


template <class Element> class ISet : public std::set<Element> {
    public:
    
	    typedef ICursorEl<std::set<Element>, Element> Cursor;
	    
		virtual Cursor* newCursor() {
			Cursor* localCursor = new Cursor(*this);
			return localCursor;
		}	    
               
        virtual bool add (Element);
        virtual void addAllFrom ( ISet<Element> );
		virtual void addAsLast(Element);
        
        virtual Element elementAt(Cursor);
        virtual Element elementAtPosition(IPosition);
        virtual Element anyElement();
        
        virtual bool locate (Element, Cursor&);        
        virtual bool contains(Element);
        virtual bool setToPosition(IPosition, Cursor& );
        virtual INumber numberOfElements();
        
        virtual void removeAt(Cursor&);         
        virtual bool removeAll();
        virtual bool remove(Element);

        virtual bool isFirst(Cursor curExterno);

        //sorted iterator
        typename std::set<Element>::iterator _sort_iterator;
        
        virtual bool sortedAdd(Element elem)
          {
          
          if (this->size() == 0)
            {
            this->insert(elem);
            this->_sort_iterator = this->begin();
            }
          else
            {
            if (elem < *this->_sort_iterator) 
				std::swap(*this->insert(elem).first , *this->_sort_iterator);
            }

          //retorno.first
          return true;
          }
       
        ISet();
        ISet(typename std::set<Element>::iterator begin
           , typename std::set<Element>::iterator end):std::set<Element>(begin , end){}
           
    private: 
    	std::pair<typename std::set<Element>::iterator,bool> retorno;
};

template <class Element>
inline ISet<Element>::ISet() {
}


template <class Element> bool ISet<Element>::isFirst(Cursor curExterno)
  {
  	
  //Element Position Testing
  //Member functions used to test whether elements are at particular positions.
  //isFirst
  //public:bool isFirst(ICursor const&) const
  //This is supported on WIN OS/2 AIX OS/400 390
  //Provides the same function as isFirstAt().
  //isFirstAt
  //public:bool isFirstAt(ICursor const&) const
  //This is supported on WIN OS/2 AIX OS/400 390
  //Returns true if the given cursor points to the first element of the collection.
  //Preconditions
  //The cursor must belong to the collection and must point to an element of
  //the collection.
  Cursor curLocal(*this);
  curLocal.setToFirst();

  return (curExterno.element() == curLocal.element());
  }


template <class Element>
inline bool ISet<Element>::add (Element _element) 
  {
  //return this->sortedAdd(_element);
  retorno = insert( _element );
  return retorno.second;
  }

template <class Element>
inline void ISet<Element>::addAllFrom (ISet<Element> _appendSet ) {
	this->insert(_appendSet.begin(), _appendSet.end());
}

template <class Element>
inline void ISet<Element>::addAsLast(Element _localElement ) {
	this->insert( this->end(), _localElement );
}

template <class Element>
inline Element ISet<Element>::elementAt (Cursor _localCursor) 
  {
  if ( _localCursor.isValid() ) 
    {
	return _localCursor.element();
	}
  return (Element)NULL;
  }

template <class Element>
inline Element ISet<Element>::elementAtPosition(IPosition index) {
	Cursor localCursor(*this);
	int i = 1;

	for ( localCursor.setToFirst(); localCursor.isValid();  localCursor.setToNext()) {
		if (i++ == index) {
    		return localCursor.element();
		}
	}
	return (Element)NULL;	
}

template <class Element>
inline bool ISet<Element>::contains(Element _lcElement) {
	Cursor localCursor(*this);

	for ( localCursor.setToFirst(); localCursor.isValid();  localCursor.setToNext()) {
		if (_lcElement == localCursor.element()) {
    		return true;
		}
	}
	return false;	
}


template <class Element>
inline bool ISet<Element>::setToPosition(IPosition _position, Cursor& _localCursor) {
	int i = 1;

	for ( _localCursor.setToFirst(); _localCursor.isValid();  _localCursor.setToNext()) {
		if (i++ == _position) {
    		return true;
		}
	}
	return false;	
}

template <class Element>
inline Element ISet<Element>::anyElement() {
	Cursor tmp ( *this );
	this->setToPosition((this->numberOfElements()/2)+1, tmp);
	
	return tmp.element();
}

template <class Element>
inline INumber  ISet<Element>::numberOfElements() {
	return this->size();
}


template <class Element> 
inline bool ISet<Element>::locate(Element newElement, Cursor& localCursor) {
	bool valid = false;
	
	for ( localCursor.setToFirst(); localCursor.isValid();  localCursor.setToNext()) {
		if ( localCursor.element() == newElement ) {
			valid = true;
			break;
		}
	}
	return valid;
}

template <class Element> 
inline bool ISet<Element>::remove ( Element _localEl) {
	
	bool ok = false;
	Cursor cursorFind(*this);
	ok = this->locate(_localEl, cursorFind); 

	if ( ok ) {
		std::set<Element>::erase(_localEl);	
	}
	return ok;
}

template <class Element> 
inline void ISet<Element>::removeAt ( Cursor & _localCursor) {
	if ( _localCursor.isValid() ) { 
		this->erase(_localCursor.element());
		_localCursor.inValidate();
	}
}

template <class Element> 
inline bool ISet<Element>::removeAll() {
	this->clear();
	return true;
}

#endif //_ISET_H_