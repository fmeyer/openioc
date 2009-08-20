#ifndef _ISTDOPS_
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


#define _ISTDOPS_

#include <iglobals.h>
#include <stddef.h>


template <class Element> Element& elementForOps (Element& e);
template <class Element> Element const& elementForOps (Element const& e);

class IStdMemOps {
	public:
		void* allocate   (size_t, char const*, unsigned long) const;
		void  deallocate (void*) const;
};

template <class ElementOps> class IWStdMemOps {
	ElementOps ivElementOps;

	public:
		void* Allocate   (size_t) const;
		void  Deallocate (void*) const;
};

template <class Element> class IStdAsOps {
	public:
		void assign (Element&, Element const&) const;
};

template <class Element, class ElementOps> class IWStdAsOps {
	ElementOps ivElementOps;
	
	public:
		void Assign (Element&, Element const&) const;
};

// equality

template <class Element> class IStdEqOps {
	public:
		bool equal (Element const&, Element const&) const;
};

template <class Element, class ElementOps> class IWStdEqOps {
	ElementOps ivElementOps;
	public:
		bool Equal (Element const&, Element const&) const;
};

template <class Key, class ElementOps> class IWStdEqKeyOps {
	ElementOps ivElementOps;
	public:
		bool Equal (Key const&, Key const&) const;
};

// ordering relation

template <class Element> class IStdCmpOps {
	public:
		long compare (Element const&, Element const&) const;
};

template <class Element, class ElementOps> class IWStdCmpOps {
	ElementOps ivElementOps;
	public:
		long Compare (Element const&, Element const&) const;
};

template <class Key, class ElementOps> class IWStdCmpKeyOps {		
	ElementOps ivElementOps;
	public:
		long Compare (Key const&, Key const&) const;
};

// hash function

template <class Element> class IStdHshOps {
	public:
		unsigned long hash (Element const&, unsigned long) const;
};

template <class Element, class ElementOps> class IWStdHshOps {
	ElementOps ivElementOps;
	public:
		unsigned long Hash (Element const&, unsigned long) const;
};

template <class Key, class ElementOps> class IWStdHshKeyOps {
	ElementOps ivElementOps;
	public:
		unsigned long Hash (Key const&, unsigned long) const;
};

// key selection

template <class Element, class Key> class IStdKeyOps {
	public:
		Key const& key (Element const&) const;
};

template <class Element, class _Key, class ElementOps> class IWStdKeyOps {	
	ElementOps ivElementOps;
	public:
		_Key const& Key (Element const&) const;
};

// standard operation combinations

template <class Element> class IStdOps : public IStdMemOps,public IStdAsOps <Element> {
};

template <class Element, class ElementOps> class IWStdOps : public IWStdMemOps <ElementOps>, public IWStdAsOps <Element, ElementOps> {
	public:
		IWStdOps (void* = 0) {}
};

template <class Element> class IEOps : public IStdOps <Element>, public IStdEqOps <Element> {
};

template <class Element, class ElementOps> class IWEOps :  public IWStdOps <Element, ElementOps>,  public IWStdEqOps <Element, ElementOps> {
	public:
		IWEOps (void* = 0) {}
};

template <class Element> class ICOps : public IStdOps <Element>, public IStdCmpOps <Element> {
};

template <class Element, class ElementOps> class IWCOps :   public IWStdOps <Element, ElementOps>,   public IWStdCmpOps <Element, ElementOps> {
	public:
		IWCOps (void* = 0) {}
};

// Para suporte em versoes antigas. 

template <class Element> class IECOps : public IEOps <Element>, public IStdCmpOps <Element> {
};

template <class Element> class IEHOps : public IEOps <Element>, public IStdHshOps <Element> {
};

template <class Element, class ElementOps> class IWEHOps : public IWEOps <Element, ElementOps>, public IWStdHshOps <Element, ElementOps> {
	public:
		IWEHOps (void* = 0) {}
};

template <class Key> class IKCKeyOps : public IStdCmpOps <Key> {
};

template <class Key, class ElementOps> class IWKCKeyOps : public IWStdCmpKeyOps <Key, ElementOps> {
};

template <class Element, class Key> class IKCOps : public IStdOps <Element>, public IStdKeyOps <Element, Key> {
	public:
		IKCKeyOps <Key> keyOps;
};

template <class Element, class _Key, class ElementOps> class IWKCOps : public IWStdOps <Element, ElementOps>, public IWStdKeyOps <Element, _Key, ElementOps> {
	public:
		IWKCKeyOps <_Key, ElementOps> keyOps;
		IWKCOps (void* = 0) {};
};

template <class Key> class IKEHKeyOps : public IStdEqOps <Key>, public IStdHshOps <Key> {
};

template <class Key, class ElementOps>
class IWKEHKeyOps :  public IWStdEqKeyOps <Key, ElementOps>, public IWStdHshKeyOps <Key, ElementOps> {
	public:
};

template <class Element, class Key> class IKEHOps : public IStdOps <Element>, public IStdKeyOps <Element, Key> {
	public:
		IKEHKeyOps <Key> keyOps;
};

template <class Element, class _Key, class ElementOps>
class IWKEHOps : public IWStdOps <Element, ElementOps>, public IWStdKeyOps <Element, _Key, ElementOps> {
	public:
		IWKEHKeyOps <_Key, ElementOps> keyOps;
		IWKEHOps (void* = 0) {}
};

template <class Key> class IEKCKeyOps : public IStdCmpOps <Key> {
};

template <class Key, class ElementOps> class IWEKCKeyOps : public IWStdCmpKeyOps <Key, ElementOps> {
};

template <class Element, class Key> class IEKCOps : public IEOps <Element>, public IStdKeyOps <Element, Key> {
	public:
		IEKCKeyOps <Key> keyOps;
};

template <class Element, class _Key, class ElementOps> class IWEKCOps : public IWEOps <Element, ElementOps>,public IWStdKeyOps <Element, _Key, ElementOps> {
	public:
		IWEKCKeyOps <_Key, ElementOps> keyOps;
		IWEKCOps (void* = 0) {}
};

template <class Key> class IEKEHKeyOps : public IStdEqOps <Key>, public IStdHshOps <Key> {
};

template <class Key, class ElementOps> class IWEKEHKeyOps : public IWStdEqKeyOps <Key, ElementOps>, public IWStdHshKeyOps <Key, ElementOps> {
};

template <class Element, class Key> class IEKEHOps : public IEOps <Element>, public IStdKeyOps <Element, Key> {
	public:
		IEKEHKeyOps <Key> keyOps;
};


template <class Element, class _Key, class ElementOps> class IWEKEHOps : public IWEOps <Element, ElementOps>, public IWStdKeyOps <Element, _Key, ElementOps> {
	public:
		IWEKEHKeyOps <_Key, ElementOps> keyOps;
		IWEKEHOps (void* = 0) {}
};

#include <istdops.inl>

#endif // _ISTDOPS_