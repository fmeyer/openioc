#ifndef ICURSOR_H_
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


#define ICURSOR_H_

#include <slvdefault.h>

#define forICursor(c) \
	for ( (c).setToFirst(); (c).isValid(); (c).setToNext())
	
#define forCursor(c) \
	for ( (c).setToFirst(); (c).isValid(); (c).setToNext())

template <class Type, class Element, class Key >
class ICursor {
    private:
        Type* copyInstance;
        typename Type::iterator it;

    public:
        bool valid;            
    
        ICursor(Type&);
        ICursor(const Type&);        
        
        //Construir ICursor a partir 
        //de IKeySet<NodeCoil*,IString>
    
		virtual ~ICursor(){};
        virtual bool setToNext();
        virtual bool setToFirst();
        virtual bool setToLast();
		virtual bool isValid();
		virtual bool setToPrevious();
        virtual bool locateElement( Element );
        virtual bool setCursorToElement( Element );
		virtual bool setCursorToKey( Key );		
        virtual void inValidate();
        virtual void copy (ICursor);
        virtual Element element();
        virtual Key getKey();
        virtual Type* getInstance();
		virtual typename Type::iterator getIterator();
		virtual void setIterator(typename Type::iterator lc);
};

template <class Type, class Element, class Key>
inline ICursor<Type, Element, Key>::ICursor(Type& contParam) : valid ( false ) {
     this->copyInstance = &contParam;
}

//Cole��o constante
template <class Type, class Element, class Key>
inline ICursor<Type, Element, Key>::ICursor(const Type& contParam) : valid ( false )  {
	this->copyInstance = const_cast<Type*>(&contParam);
}

template <class Type, class Element, class Key >
inline void ICursor<Type, Element, Key>::inValidate(){
	valid = false;
}

template <class Type, class Element, class Key>
inline bool ICursor<Type, Element, Key>::isValid() {
	
	if ( copyInstance->size() == 0 ) return false;
	return valid;
}

template <class Type, class Element, class Key>
inline void ICursor<Type, Element, Key>::copy(ICursor lcursor) {
	this->copyInstance = lcursor.getInstance();
	this->it = lcursor.getIterator();
     valid = false;
}

template <class Type, class Element, class Key>
inline bool ICursor<Type, Element, Key>::setToNext() {
	
	if ( valid )  { 
		if ( (++it) != this->copyInstance->end() ) 
			 valid = true;
		else valid = false;
	}
	return valid;
}

template <class Type, class Element, class Key>
inline bool ICursor<Type, Element, Key>::setToFirst() {
	valid = false;
	if ( copyInstance->size() ) { 
		it = this->copyInstance->begin();
		valid = true;
		return valid;
	} 
	return false;
}

template <class Type, class Element, class Key>
inline bool ICursor<Type, Element, Key>::setToLast() {
	it = this->copyInstance->end();
    it--;
    valid = true;
	return isValid();
}

template <class Type, class Element, class Key>
inline bool ICursor<Type, Element, Key>::setToPrevious() {
	if ( it != this->copyInstance->begin() ) {
		it--;
		valid = true;		
	} else  { 
		valid = false;
	}
	return isValid();
}

template <class Type, class Element, class Key>
inline bool ICursor<Type, Element, Key>::locateElement(Element localElement) {
	for (this->setToFirst(); this->isValid(); this->setToNext()) {
 		if ( this->element() == localElement )
 			return true;
	}
	return false;
};

template <class Type, class Element, class Key>
inline bool ICursor<Type, Element, Key>::setCursorToElement(Element _localElement) {
	for( this->setToFirst(); this->isValid(); this->setToNext() ) {
		if (this->element() == _localElement)
			return true;
	}
	return false;	
};

template <class Type, class Element, class Key>
inline Element ICursor<Type, Element, Key>::element() { 
     return it->second;
}

template <class Type, class Element, class Key>
inline Key ICursor<Type, Element, Key>::getKey() { 
	return it->first;
}

template <class Type, class Element, class Key>
inline Type* ICursor<Type, Element, Key>::getInstance() { 
	return this->copyInstance;
}

template <class Type, class Element, class Key>
inline typename Type::iterator ICursor<Type, Element, Key>::getIterator() {
	return it;	
}

template <class Type, class Element, class Key>
inline void ICursor<Type, Element, Key>::setIterator(typename Type::iterator lc) {
	it = lc;
}

template <class Type, class Element, class Key>
inline bool ICursor<Type, Element, Key>::setCursorToKey(Key _localKey) {
	
	if ( !copyInstance->size() )  {
		valid = false;
		return false; 
	}
	it = copyInstance->find(_localKey);

	if (it == copyInstance->end()) {
		valid = false;
	} else {
		valid = true;
	}
	
	return valid;
};
/*************************************************************************************/

template <class Type, class Element, class Key, class ElementOpts >
class ICursorG {
    private:
        Type* copyInstance;
        typename Type::iterator it;

    public:
        bool valid;            
    
        ICursorG(Type&);
	virtual ~ICursorG(){};
        virtual bool setToNext();
        virtual bool setToFirst();
        virtual bool setToLast();
	virtual bool isValid();
	virtual bool setToPrevious();
        virtual bool locateElement( Element );
        virtual bool setCursorToElement( Element );
	virtual bool setCursorToKey( Key );		
        virtual void inValidate();
        virtual void copy (ICursorG);
        virtual Element element();
        virtual Key getKey();
        virtual Type* getInstance();
	virtual typename Type::iterator getIterator();
	virtual void setIterator(typename Type::iterator lc);
};

template <class Type, class Element, class Key, class ElementOpts >
inline ICursorG<Type, Element, Key, ElementOpts>::ICursorG(Type& contParam) {
     this->copyInstance = &contParam;
     valid = false;
}

template <class Type, class Element, class Key, class ElementOpts >
inline void ICursorG<Type, Element, Key, ElementOpts>::inValidate(){
	valid = false;
}

template <class Type, class Element, class Key, class ElementOpts >
inline bool ICursorG<Type, Element, Key, ElementOpts>::isValid() {
	
	if ( copyInstance->size() == 0 ) return false;
	return valid;
}

template <class Type, class Element, class Key, class ElementOpts >
inline void ICursorG<Type, Element, Key, ElementOpts>::copy(ICursorG lcursor) {
	this->copyInstance = lcursor.getInstance();
	this->it = lcursor.getIterator();
     valid = false;
}

template <class Type, class Element, class Key, class ElementOpts >
inline bool ICursorG<Type, Element, Key, ElementOpts>::setToNext() {
	if ( valid )  { 
		if ( (++it) != this->copyInstance->end() ) 
			 valid = true;
		else valid = false;
	}
	return valid;
}

template <class Type, class Element, class Key, class ElementOpts >
inline bool ICursorG<Type, Element, Key, ElementOpts>::setToFirst() {
	valid = false;
	if ( copyInstance->size() ) { 
		it = this->copyInstance->begin();
		valid = true;
		return valid;
	} 
	return false;
}

template <class Type, class Element, class Key, class ElementOpts >
inline bool ICursorG<Type, Element, Key, ElementOpts>::setToLast() {
	it = this->copyInstance->end();
    it--;
    valid = true;
	return isValid();
}

template <class Type, class Element, class Key, class ElementOpts >
inline bool ICursorG<Type, Element, Key, ElementOpts>::setToPrevious() {
	if ( it != this->copyInstance->begin() ) {
		it--;
		valid = true;		
	} else  { 
		valid = false;
	}
	return isValid();
}

template <class Type, class Element, class Key, class ElementOpts >
inline bool ICursorG<Type, Element, Key, ElementOpts>::locateElement(Element localElement) {
	for (this->setToFirst(); this->isValid(); this->setToNext()) {
 		if ( this->element() == localElement )
 			return true;
	}
	return false;
};

template <class Type, class Element, class Key, class ElementOpts >
inline bool ICursorG<Type, Element, Key, ElementOpts>::setCursorToElement(Element _localElement) {
	for( this->setToFirst(); this->isValid(); this->setToNext() ) {
		if (this->element() == _localElement)
			return true;
	}
	return false;	
};

template <class Type, class Element, class Key, class ElementOpts >
inline Element ICursorG<Type, Element, Key, ElementOpts>::element() { 
     return it->second;
}

template <class Type, class Element, class Key, class ElementOpts >
inline Key ICursorG<Type, Element, Key, ElementOpts>::getKey() { 
	return it->first;
}

template <class Type, class Element, class Key, class ElementOpts >
inline Type* ICursorG<Type, Element, Key, ElementOpts>::getInstance() { 
	return this->copyInstance;
}

template <class Type, class Element, class Key, class ElementOpts >
inline typename Type::iterator ICursorG<Type, Element, Key, ElementOpts>::getIterator() {
	return it;	
}

template <class Type, class Element, class Key, class ElementOpts >
inline void ICursorG<Type, Element, Key, ElementOpts>::setIterator(typename Type::iterator lc) {
	it = lc;
}

template <class Type, class Element, class Key, class ElementOpts >
inline bool ICursorG<Type, Element, Key, ElementOpts>::setCursorToKey(Key _localKey) {
	
	if ( !copyInstance->size() )  {
		valid = false;
		return false; 
	}
	it = copyInstance->find(_localKey);

	if (it == copyInstance->end()) {
		valid = false;
	} else {
		valid = true;
	}
	
	return valid;
};

/*************************************************************************************/

template <class Type, class Element>
class ICursorEl {
    private:
        Type* copyInstance;
        typename Type::iterator it;
    public:
        bool valid;    
        ICursorEl(Type&);
        ICursorEl(const Type&);        

		virtual ~ICursorEl(){};
        virtual bool setToNext();
        virtual bool setToFirst();
        virtual bool setToLast();
		virtual bool isValid();
		virtual bool setToPrevious();
        virtual bool locateElement( Element );
        virtual bool setCursorToElement( Element );
        virtual void inValidate() ;
        virtual Element element();
        virtual Element &elementR();        
        virtual Type* getInstance();
		virtual typename Type::iterator getIterator();
		virtual void setIterator(typename Type::iterator lc);
};

template <class Type, class Element>
inline ICursorEl<Type, Element>::ICursorEl(Type& contParam) 
  {
  this->copyInstance = &contParam;
  
  //if (this->copyInstance->size() > 0) this->setToFirst();
  valid = false;
  }

template <class Type, class Element>
inline ICursorEl<Type, Element>::ICursorEl(const Type& contParam) 
  {
  this->copyInstance = const_cast<Type*>(&contParam);
  valid = false;  	
  }

template <class Type, class Element >
inline void ICursorEl<Type, Element>::inValidate(){
	valid = false;
}

template <class Type, class Element>
inline bool ICursorEl<Type, Element>::isValid() 
  {
  if ( copyInstance->size() == 0 ) return false;
  return valid;
  }

template <class Type, class Element>
inline bool ICursorEl<Type, Element>::setToNext() {  
	
	if ( valid )  { 
		if ( (++it) != this->copyInstance->end() ) 
			 valid = true;
		else valid = false;
	}
	return valid;	
}

template <class Type, class Element>
inline bool ICursorEl<Type, Element>::setToFirst() 
  {
  valid = false;
  if ( copyInstance->size() ) 
    { 
	it = this->copyInstance->begin();
	valid = true;
	return (it == this->copyInstance->begin() ? true : false);
	} 
  
  return false;
  }

template <class Type, class Element>
inline bool ICursorEl<Type, Element>::setToLast() 
  {
  it = this->copyInstance->end();
  it--;
  valid = true;
  return isValid();
  }

template <class Type, class Element>
inline bool ICursorEl<Type, Element>::setToPrevious() 
  {
  if ( it != this->copyInstance->begin() ) 
    {
    it--;
    valid = true;		
    } 
  else  
    { 
	valid = false;
	}
  
  return isValid();
  }

template <class Type, class Element>
inline bool ICursorEl<Type, Element>::locateElement(Element localElement) {
	for (this->setToFirst(); this->isValid(); this->setToNext()) {
 		if ( this->element() == localElement )
 			return true;
	}
	return false;
};

template <class Type, class Element>
inline bool ICursorEl<Type, Element>::setCursorToElement(Element _localElement) {
	for( this->setToFirst(); this->isValid(); this->setToNext() ) {
		if (this->element() == _localElement)
			return true;
	}
	return false;	
};

template <class Type, class Element>
inline Element ICursorEl<Type, Element>::element() {
     return *it;
}

template <class Type, class Element>
inline Element &ICursorEl<Type, Element>::elementR() 
  {
  #ifdef __GCC__
  return (Element &)it;  
  #else
  return *it;
  #endif
  }

template <class Type, class Element>
inline Type* ICursorEl<Type, Element>::getInstance() { 
	return this->copyInstance;
}

template <class Type, class Element>
inline typename Type::iterator ICursorEl<Type, Element>::getIterator() {
	return it;	
}

template <class Type, class Element>
inline void ICursorEl<Type, Element>::setIterator(typename Type::iterator lc) {
	it = lc;
}

#endif /*ICURSOR_H_*/