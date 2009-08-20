#ifndef _ISTDOPS_INL_
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


#define _ISTDOPS_INL_

#include <string.h>

template <class Element>
inline Element& elementForOps (Element& e) { 
	return e;
}

template <class Element> 
inline Element const& elementForOps (Element const& e) { 
	return e;
}

// IStdMemOps

//inline void* IStdMemOps::allocate (size_t s) const 
//{
//    return ::operator new (s);
//}
//
//inline void IStdMemOps::deallocate (void* p ) const { 
//	::operator delete (p);
//}

template <class ElementOps>
inline void* IWStdMemOps <ElementOps>::Allocate (size_t s) const{ 
	return ivElementOps.allocate (s);
}

template <class ElementOps>
inline void IWStdMemOps <ElementOps>::Deallocate (void* p) const { 
	ivElementOps.deallocate (p);
}

template <class Element>
inline void assign (Element& e1, Element const& e2) { 
	e1 = e2;
}

// public members

template <class Element>
inline void IStdAsOps <Element>::assign (Element& e1, Element const& e2) const{ 
	::assign (e1, e2);
}

template <class Element, class ElementOps>
inline void
IWStdAsOps <Element, ElementOps>::Assign (Element& e1, Element const& e2) const{ 
	ivElementOps.assign (e1, e2);
}

// ---------
// IStdEqOps
// ---------

template <class Element>
inline bool equal (Element const& e1, Element const& e2) { 
	return (e1 == e2);
}

inline bool equal (char const* e1, char const* e2) { 
	return (strcmp (e1, e2) == 0);
}

// public members

template <class Element>
inline bool IStdEqOps <Element>:: equal (Element const& e1, Element const& e2) const { 
	return ::equal (elementForOps (e1), elementForOps (e2));
}

template <class Element, class ElementOps>
inline bool IWStdEqOps <Element, ElementOps>::Equal (Element const& e1, Element const& e2) const { 
	return ivElementOps.equal (e1, e2);
}

template <class Key, class ElementOps>
inline bool IWStdEqKeyOps <Key, ElementOps>::Equal (Key const& k1, Key const& k2) const{ 
	return ivElementOps.keyOps.equal (k1, k2);
}

// ----------
// IStdCmpOps
// ----------

template <class Element>
inline long compare (Element const& e1, Element const& e2) { 
	if      (e1 < e2) return -1;
	else if (e2 < e1) return  1;
	else              return  0;
}

inline long compare (int e1, int e2) { 
	return (e1 - e2);
}

inline long compare (char const* e1, char const* e2) { 
	return strcmp (e1, e2);
}

// public members

template <class Element>
inline long IStdCmpOps <Element>::compare (Element const& e1, Element const& e2) const { 
	return ::compare (elementForOps (e1), elementForOps (e2));
}

template <class Element, class ElementOps>
inline long IWStdCmpOps <Element, ElementOps>::Compare (Element const& e1, Element const& e2) const { 
	return ivElementOps.compare (e1, e2);
}

template <class Key, class ElementOps>
inline long IWStdCmpKeyOps <Key, ElementOps>::Compare (Key const& k1, Key const& k2) const { 
	return ivElementOps.keyOps.compare (k1, k2);
}

// ----------
// IStdHshOps
// ----------

inline unsigned long hash (int e, unsigned long h) { 
	return e % h;
}

inline unsigned long hash (char const* s, unsigned long h) { 
	unsigned long hashValue = 0, g;
	
	for (char* p = (char*)s; *p != '\0'; p++) {
		hashValue = (hashValue << 4) + *p;
		if ((g = hashValue & 0xf0000000L) != 0) {
			hashValue ^= (g >> 24);
			hashValue ^= g;
		}
	}
  return hashValue % h;
} 
// public members

template <class Element>
inline unsigned long IStdHshOps <Element>::hash (Element const& e, unsigned long h) const{ 
	return ::hash (elementForOps (e), h);
}

template <class Element, class ElementOps> inline unsigned long IWStdHshOps <Element, ElementOps>:: Hash (Element const& e, unsigned long h) const{ 
	return ivElementOps.hash (e, h);
}

template <class Key, class ElementOps>
inline unsigned long IWStdHshKeyOps <Key, ElementOps>::Hash (Key const& k, unsigned long h) const { 
	return ivElementOps.keyOps.hash (k, h);
}

// ----------
// IStdKeyOps
// ----------

// public members

#if __IBMCPP__ >= 400 
template <class Element, class _Key> _Key const& key(Element const& element);
#endif

template <class Element, class _Key>
inline _Key const& IStdKeyOps <Element, _Key>::key (Element const& e) const { 
	return ::key (elementForOps (e));
}

template <class Element, class _Key, class ElementOps>
inline _Key const& IWStdKeyOps <Element, _Key, ElementOps>::Key (Element const& e) const{ 
	return ivElementOps.key (e);
}

#endif // _ISTDOPS_INL_