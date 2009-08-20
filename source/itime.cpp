#include <itime.hpp>
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


#include <istring.hpp>
#include <ctime>

ITime::ITime(){
	pClTime =  time(NULL);
}
ITime::~ITime() {}

//ITime::ITime( int hours, int minutes, int seconds) {
//	struct tm time_now;
//	time_now.tm_sec = seconds;
//	time_now.tm_min = minutes;
//	time_now.tm_hour = hours;
//	
//	if (mktime(&time_now) == -1) std::cout<< "-unknown-"  <<std::endl;
//	this->pClTime = mktime(&time_now);
//}
//


//ITime::ITime(unsigned long timeIdentifier){
//	struct tm *time_now= new (struct tm);
//	time_now->tm_sec = timeIdentifier;
//	this->pClTime = mktime(time_now);
//}

//Interna - devolve valor de membro private
time_t ITime::_getTime_t() 
  {
  return pClTime;
  }
  
time_t ITime::_getTime_t() const 
  {
  return pClTime;
  }		



bool ITime::operator >(ITime source) const
  {
  if ( difftime(this->pClTime,source._getTime_t()) > 0) return true;
  else return false;		  	
  }


bool ITime::operator >(ITime source)
  {
  if ( difftime(this->pClTime,source.pClTime) > 0) return true;
  else return false;
  }


bool ITime::operator <(const ITime source)const{
	if ( this->pClTime < source.pClTime ) 
		return true;
	else 
		return false;
} 
bool ITime::operator >=(const ITime source)const{
	if ( this->pClTime >= source.pClTime ) 
		return true;
	else 
		return false;
}
bool ITime::operator <=(const ITime source)const{
	if ( this->pClTime <= source.pClTime ) 
		return true;
	else 
		return false;
}

bool ITime::operator==(const ITime source) const {
	if ( difftime(this->pClTime,source.pClTime) == 0 ) 
		return true;
	else 
		return false;
}

ITime ITime::now()
{
	pClTime =  time(NULL);
	return *this;
}

IString ITime::asString(const char *fmt)const
{
	struct tm *time_now;
	
	time_t ftime = pClTime - 3600;
//	time_t ftime = pClTime;// - 3600;	
	time_now = localtime(&ftime);

	char datestring[256];
	strftime (datestring, sizeof(datestring), fmt, time_now);
	
	IString ret = datestring;
	return ret;
}

ITime & ITime::operator=(ITime source)
{
    this->pClTime = source.pClTime;
    return *this;
}

ITime & ITime::operator=(ITime* source)
{
   this->pClTime = source->pClTime;
    return *this;
}