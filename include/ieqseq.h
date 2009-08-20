#ifndef _IESEQ_H_	
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


#define _IESEQ_H_

#include <slvdefault.h>
#include <list>
#include <icursor.h>
#include <algorithm>
#include <iexception.hpp>

template <class Element> class IEqualitySequence : public std::list<Element>  {
    public:
		typedef ICursorEl<std::list<Element>, Element> Cursor;
        IEqualitySequence();
        //virtual ~IEqualitySequence(){};        

        virtual bool add (Element);
        virtual bool addAsLast ( Element );
        virtual bool addAsFirst ( Element );
        virtual bool addAsNext ( Element, Cursor& );
        virtual bool addAllFrom( IEqualitySequence<Element> );
        
        virtual void removeAt(Cursor&);
		virtual bool remove ( Element ) ;
        virtual int  removeAll();		
        virtual void removeAtPosition (IPosition);
        virtual void removeFirst ();
        
        virtual bool isFirst ( Cursor );
        virtual Element anyElement ();
        
        virtual Element elementAt(Cursor);
        virtual Element elementAt(Cursor) const;        
        virtual Element elementAtPosition(int);
        virtual Element *elementAtPositionR(int);        
        virtual Element firstElement();        
        //virtual Element firstElement() const;           
        
        virtual INumber numberOfElements();        
        virtual bool locate (Element, Cursor&);
        virtual bool isEmpty();
        virtual bool contains(Element);
        virtual bool setToPosition(long , Cursor& );
        virtual bool isLast(Cursor);

        virtual Element lastElement();        

		virtual Cursor* newCursor() {
			Cursor* localCursor = new Cursor(*this);
			return localCursor;
		}
		
        virtual bool allElementsDo(bool ( *applicatorFunction)( Element&,void * ));
        virtual bool sort( long (*applicatorFunction) (const Element& , const Element&) );
        virtual void swap(int , int); 

        //TODO
        virtual Element firstElement() const;
        virtual bool isEmpty() const;
        virtual INumber numberOfElements() const;
        virtual bool contains(Element) const ;  
        virtual Element anyElement() const;
        virtual bool isLast(Cursor) const;                                                  
};

template <class Element> 
inline IEqualitySequence<Element>::IEqualitySequence() : std::list<Element>() {
}

template <class Element> 
inline bool IEqualitySequence<Element>::add(Element newElement) {
	this->push_back(newElement);
	return true;
}

template <class Element> 
inline INumber IEqualitySequence<Element>::numberOfElements() {
	return this->size();
}

template <class Element> 
inline INumber IEqualitySequence<Element>::numberOfElements() const 
  {
  return this->size();
  }

template <class Element> 
inline void IEqualitySequence<Element>::removeAt(typename IEqualitySequence<Element>::Cursor& localCursor) {
		this->remove(localCursor.element());
}

template <class Element> 
inline void IEqualitySequence<Element>::removeFirst() {
		Cursor localCursor(*this);
		localCursor.setToFirst();
		this->remove(localCursor.element());
}

template <class Element> 
inline void IEqualitySequence<Element>::removeAtPosition(IPosition _pos) {
	Cursor localCursor(*this);
	int i = 1;
	for ( localCursor.setToFirst(); localCursor.isValid() && (i <= this->numberOfElements());  localCursor.setToNext()) {
		if (i++ == _pos) {
    		this->erase(localCursor.getIterator());
		}
	}
}

template <class Element> 
inline Element IEqualitySequence<Element>::elementAt(Cursor localCursor) 
  {
  //IEXCEPTION , INOTCONTAINSKEYEXCEPTION 
  //IPOSITIONINVALIDEXCEPTION , IEMPTYEXCEPTION 
  //ICURSORINVALIDEXCEPTION 
  //** SAFETY CHECKS **
  if (!(localCursor.isValid()) ) { 
  	//throw (ICURSORINVALIDEXCEPTION);
  	abort();
  }
  //else if ((_pos>this->size()) && (_pos < 1)) throw (IPOSITIONINVALIDEXCEPTION);
	  else return localCursor.element();
  }

template <class Element> 
inline Element IEqualitySequence<Element>::elementAt(Cursor localCursor) const
  {
  //IEXCEPTION , INOTCONTAINSKEYEXCEPTION 
  //IPOSITIONINVALIDEXCEPTION , IEMPTYEXCEPTION 
  //ICURSORINVALIDEXCEPTION 
  //** SAFETY CHECKS **
  if (!(localCursor.isValid()) ) throw (ICURSORINVALIDEXCEPTION);
  //else if ((_pos>this->size()) && (_pos < 1)) throw (IPOSITIONINVALIDEXCEPTION);
  else return localCursor.element();
  }

template <class Element> 
inline bool IEqualitySequence<Element>::addAsLast(Element newElement) {
	this->push_back(newElement);
	return true;
}

template <class Element> 
inline bool IEqualitySequence<Element>::locate(Element newElement, typename IEqualitySequence<Element>::Cursor& localCursor) {
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
inline bool IEqualitySequence<Element>::isEmpty() {
	return this->empty();
}

template <class Element> 
inline bool IEqualitySequence<Element>::isEmpty() const
  {
  return this->empty();
  }

template <class Element> 
inline int IEqualitySequence<Element>::removeAll() {
	int _numberOfElements = this->size();
    

    
	this->clear();


	
	return _numberOfElements;
}

template <class Element> 
inline Element IEqualitySequence<Element>::firstElement() {
	Cursor localCursor(*this);
	localCursor.setToFirst();	
	return localCursor.element();	
}

template <class Element> 
inline Element IEqualitySequence<Element>::firstElement() const {
	Cursor localCursor(*this);
	localCursor.setToFirst();	
	return localCursor.element();	
}

template <class Element> 
inline bool IEqualitySequence<Element>::addAsFirst ( Element _localEl) {
	this->push_front( _localEl );
	return true;
}

template <class Element> 
inline bool IEqualitySequence<Element>::addAsNext ( Element _localEl, typename IEqualitySequence<Element>::Cursor& _localCur) {
	typename std::list<Element>::iterator it;
	
	it = _localCur.getIterator();
	
	it = insert( ++it, _localEl );
	if ( it != this->end() ) {
		_localCur.setIterator(it);
		return true; 
	}else 
		return false;
}

template <class Element>
inline bool IEqualitySequence<Element>::addAllFrom(IEqualitySequence<Element> _local) {
	this->insert(this->end(),_local.begin(), _local.end());
	return true;
}


template <class Element> 
inline bool IEqualitySequence<Element>::remove ( Element _localEl) {

	Cursor cursorFind(*this);
	bool ok = this->locate(_localEl, cursorFind);
	if ( ok ) {
		std::list<Element>::remove(_localEl);	
	}
	return ok;
}

template <class Element>
inline bool IEqualitySequence<Element>::allElementsDo(bool ( *applicatorFunction)( Element&,void * )) 
  {
       
  Element _tmpElement;
  typename IEqualitySequence<Element>::Cursor localCursor(*this);

  for ( localCursor.setToFirst(); localCursor.isValid();  localCursor.setToNext()) 
    {
	_tmpElement = localCursor.element();
	(*applicatorFunction) (_tmpElement, (void *) NULL);
	}
  return true;
  }

template <class Element> 
inline Element IEqualitySequence<Element>::elementAtPosition ( int _position ) 
  {
  Cursor localCursor(*this);

  //this�s necessary becouse sometimes cursor points to the end collection
  localCursor.setToFirst();

  //IEXCEPTION , INOTCONTAINSKEYEXCEPTION 
  //IPOSITIONINVALIDEXCEPTION , IEMPTYEXCEPTION 
  //ICURSORINVALIDEXCEPTION 
  //** SAFETY CHECKS **
  if (!(localCursor.isValid()) ) throw (ICURSORINVALIDEXCEPTION);
  else if ((_position > this->size()) && (_position < 1)) throw (IPOSITIONINVALIDEXCEPTION);
  else  	
  	{
    int i = 1;
    
    for ( localCursor.setToFirst(); localCursor.isValid();  localCursor.setToNext()) 
      {
	  if (i++ == _position) 
	    {
        return localCursor.element();
	    }//if
	    
	  }//for
	  
  	}//else
  	
  }//end


template <class Element> 
inline Element *IEqualitySequence<Element>::elementAtPositionR ( int _position ) 
  {
  Cursor localCursor(*this);

  localCursor.setToFirst();

  //IEXCEPTION , INOTCONTAINSKEYEXCEPTION 
  //IPOSITIONINVALIDEXCEPTION , IEMPTYEXCEPTION 
  //ICURSORINVALIDEXCEPTION 
  //** SAFETY CHECKS **
  
  if (!(localCursor.isValid()) ) throw (ICURSORINVALIDEXCEPTION);
  else if ((_position > this->size()) && (_position < 1)) throw (IPOSITIONINVALIDEXCEPTION);
  else 
    {
    int i = 1;
  
    for (localCursor.setToFirst(); localCursor.isValid();  localCursor.setToNext()) 
      {
	  if (i++ == _position) 
	    {
        return &localCursor.elementR();
	    }
	    
	  }//for
	  
    }//else
	
  }//end


template <class Element> 
inline bool IEqualitySequence<Element>::contains ( Element _localElement ) {
	Cursor localCursor(*this);
	
	for ( localCursor.setToFirst(); localCursor.isValid();  localCursor.setToNext()) {
		if ( _localElement == localCursor.element() ) 
    		return true;
	}
	return false;
}

template <class Element> 
inline bool IEqualitySequence<Element>::contains ( Element _localElement ) const
  {
  Cursor localCursor(*this);
	
  for ( localCursor.setToFirst(); localCursor.isValid();  localCursor.setToNext()) 
    {
	if ( _localElement == localCursor.element() ) return true;
	}
	return false;
  }//


//--------------------------------


//Ordena de acordo com valor retornado passado pela fun��o de sort
//especifica das classes de regra de neg�cios da BMS
template <class Element> 
//inline bool IEqualitySequence<Element>::sort( long (*applicatorFunction) (Element *const &el1
//                                                               , Element *const &el2)) 
inline bool IEqualitySequence<Element>::sort( long (*applicatorFunction) (const Element &el1
                                                               , const Element &el2)) 
  {
  long i , j;
  
  bool isChanged = false; //devolve um flag indicado se houve ou naum algum sort



  //My basic Bubble sort, not qsort 
  for (i = 1 ; i <= this->numberOfElements() ; i++)
    {
    for (j = 1 ; j <= (this->numberOfElements()-i) ; j++)
      {

      
//      if (((*applicatorFunction) (this->elementAtPositionR(j) ,this->elementAtPositionR(j+1))) > 0)                  
      if (((*applicatorFunction) (this->elementAtPosition(j) ,this->elementAtPosition(j+1))) > 0)            
         {
         
         //Caso o elemento primeiro element (j) seja maior que o segundo (j+1)
         //entao troca seus valores (joga o segundo para cima)
         this->swap(j , j+1);

         isChanged = true;
            
         //Reinicia a contagem
         //j = 0;
            
         }//if
            
       }//for 2
          
    }//for 1

  return isChanged;        
  }//sort


//
// Troca dois elementos atraves de seu indice/posicao
//
template <class Element> 
inline void IEqualitySequence<Element>::swap(int left 
                                           , int right)
  {
  //Recebe c�pia
  //Elem tmp = this->elementAtPositionR(right);

  //Recebe c�pia
  Element copia_direita = this->elementAtPosition(right);      
      
  //recebe um ponteiro com o elemento do direita
  Element *direita  = this->elementAtPositionR(right);
      
  //recebe um ponteiro com o elemento da esquerda
  Element *esquerda  = this->elementAtPositionR(left);
      
  //inverte: direita << esquerda
  *direita = *esquerda;
      
  //esquerda << copia direita
  *esquerda = copia_direita;




  }//fim de swap()





template <class Element> 
inline Element  IEqualitySequence<Element>::lastElement( ) 
  {
  Cursor localCursor(*this);
  localCursor.setToLast();

  if (!(localCursor.isValid()) ) throw (ICURSORINVALIDEXCEPTION);
  else return localCursor.element();
  }

template <class Element> 
inline bool IEqualitySequence<Element>::setToPosition(long _position, Cursor& _localCursor) {
	int i = 1;

	for ( _localCursor.setToFirst(); _localCursor.isValid();  _localCursor.setToNext()) {
		if (i++ == _position) {
    		return true;
		}
	}
	return false;	
}

template <class Element> 
inline bool IEqualitySequence<Element>::isLast(Cursor _localCursor) {
	
	if ( this->lastElement( ) == _localCursor.element() ) 
		return true;
	else 
		return false;
}

template <class Element> 
inline bool IEqualitySequence<Element>::isLast(Cursor _localCursor) const
  {
  return const_cast<IEqualitySequence<Element>*>(this)->isLast(_localCursor);
  }

template <class Element>
inline bool IEqualitySequence<Element>::isFirst(Cursor _lcursor) 
  {
  	
  if (!(_lcursor.isValid()) ) throw (ICURSORINVALIDEXCEPTION);
    {
    if ( this->firstElement() == _lcursor.element() ) return true; 
    else return false;
    }
    
  }

template <class Element>
inline Element IEqualitySequence<Element>::anyElement() const 
  {
  return const_cast<IEqualitySequence<Element>*>(this)->anyElement();
  }

template <class Element>
inline Element IEqualitySequence<Element>::anyElement() 
  {
  //IEXCEPTION , INOTCONTAINSKEYEXCEPTION 
  //IPOSITIONINVALIDEXCEPTION , IEMPTYEXCEPTION 
  //ICURSORINVALIDEXCEPTION 
  //** SAFETY CHECKS **
  if ((this->size() == 0)) throw (IEMPTYEXCEPTION);
  else return this->firstElement();
  }

        
#endif /*IEQSEQ_H_*/