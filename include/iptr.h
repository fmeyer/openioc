#ifndef _IPTR_H_
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


#define _IPTR_H_

template <class Element>
class IElemPointer {
	public:
           IElemPointer ();
           IElemPointer (Element*);
           IElemPointer (IElemPointer <Element> const&) ;
           
		   Element& operator*() const;
 	 	   Element* operator->() const;
           operator Element*() const;
  		   
           Element *getElement();
           Element *const getElement() const;           
	private:
		   Element* ivPtr;
};

template <class Element>
inline IElemPointer <Element>::IElemPointer () : ivPtr (0) {
}

template <class Element>
inline Element *IElemPointer<Element>::getElement() 
  {
  return *this->ivPtr;
  }

template <class Element>
inline Element *const IElemPointer<Element>::getElement() const
  {
  return this->ivPtr;
  }

template <class Element>
inline IElemPointer <Element>::IElemPointer (IElemPointer <Element> const& elem) 
  {
  this->ivPtr = elem.getElement();
  }

template <class Element>
inline IElemPointer <Element>::IElemPointer (Element* ptr) : ivPtr (ptr){
}

template <class Element> 
inline Element& IElemPointer <Element>::operator* () const { 
	return *ivPtr;
}

template <class Element>
inline Element* IElemPointer <Element>::operator-> () const { 
	return ivPtr;
}

template <class Element>
inline IElemPointer <Element>::operator Element* () const { 
	return ivPtr;
}

template <class Element>
inline Element& elementForOps (IElemPointer <Element>& ptr) { 
	return *ptr.ivPtr;
}

template <class Element>
inline Element const& elementForOps (IElemPointer <Element> const& ptr) { 
	return *ptr.ivPtr;
}

#endif //_IPTR_H_