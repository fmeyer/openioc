#ifndef _ISS_H_
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


#define _ISS_H_

#include <iset.h>

template <class Element> class ISortedSet : public ISet<Element>
  {
  public: 
    ISortedSet(){}
	virtual ~ISortedSet(){}
  
    //virtual Element anyElement();
  };

/*template <class Element>
inline Element ISortedSet<Element>::anyElement() 
  {
  typename ISortedSet::Cursor tmp ( *this );
  //std::cout << "\n\n elem: (" << this->numberOfElements() << ")";
  //103
  //this->setToPosition(18, tmp);
  this->setToPosition(this->numberOfElements()/5.72, tmp);
  return tmp.element();
  }*/


#endif //_ISS_H_