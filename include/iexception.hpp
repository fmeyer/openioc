#ifndef IEXCEPTION_H_
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


#define IEXCEPTION_H_

#include <iexceptionlocation.hpp>
#include <slvdefault.h>
#include <istring.hpp>

#define IEXCEPTION IException(__FILE__,__FUNCTION__,__LINE__)
#define INOTCONTAINSKEYEXCEPTION INotContainsKeyException (__FILE__,__FUNCTION__,__LINE__)
#define IPOSITIONINVALIDEXCEPTION IPositionInvalidException (__FILE__,__FUNCTION__,__LINE__)
#define IEMPTYEXCEPTION IEmptyException (__FILE__,__FUNCTION__,__LINE__)
#define ICURSORINVALIDEXCEPTION ICursorInvalidException (__FILE__,__FUNCTION__,__LINE__)




class IException
  {
  public:
    IException(const char* fileName, const char* functionName,unsigned long lineNumber);
	~IException();
		
	IException()
	  {
	  this->_IOCErrorId = 0;
	  this->_text = "IException";
	  }
		  
	IExceptionLocation *locationAtIndex(unsigned long locationIndex) ;
	char* name();
	
	long errorId();
	
	IString text();

  private:
	 char pClName[200];
	 IExceptionLocation exlocClArray[5];
	
  protected:

	  long _IOCErrorId;
	  IString _text;
	  
  };

typedef IException INotContainsKeyException;  
typedef IException IPositionInvalidException; 
typedef IException IKeyAlreadyExistsException;
typedef IException IEmptyException;
typedef IException ICursorInvalidException;


#endif /*IEXCEPTION_H_*/