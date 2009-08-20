#ifndef ITIME_H_
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


#define ITIME_H_

#include <istring.hpp>
#include <slvdefault.h>
#include <ctime>

class ITime
{
	public:
		ITime();
		ITime( int hours, int minutes, int seconds = 0 )
           {
		   long tTime = 0;
			
	  	   if ( hours >= 24 ) hours = hours % 24;
		   tTime = seconds + (minutes*60) + (hours * 3600);
		   if ( tTime  >= 0 ) tTime  -= 86400;
		   this->pClTime = tTime  + 14400;
		   }


		ITime(long timeIdentifier){
			if ( timeIdentifier >= 0 ) timeIdentifier -= 86400;
			this->pClTime = timeIdentifier + 14400;
		}

		time_t _getTime_t();
		time_t _getTime_t() const;
		bool operator >(ITime source) const;
		bool operator >(ITime source);

		~ITime();
		ITime  now();
		IString  asString(const char *fmt = "%X")const;
		
		ITime & operator=(ITime source);
	    ITime & operator=(ITime* source);

		bool operator <(const ITime source)const; 
		bool operator >=(const ITime source)const;
		bool operator <=(const ITime source)const;
		bool operator==(const ITime) const;
		

		
		ITime operator+=(ITime source){
			ITime *value = new ITime(this->pClTime + source.pClTime + 14400 + 43200);
			this->pClTime = value->pClTime;
			delete (value);
			return *this;
		};
		
		ITime operator-=(ITime source){
			ITime *value = new ITime(this->pClTime - source.pClTime);
			this->pClTime = value->pClTime;
			delete (value);
			return *this;
		};
		
		ITime& operator-(ITime source){
			ITime *value = new ITime(this->pClTime - source.pClTime);
			return *value;
		};
		
		ITime operator + (ITime source){
			ITime *value = new ITime(this->pClTime + source.pClTime + 14400 + 43200);
			return *value;
		};

		int hours(){
			struct tm *time_now;
			time_now = localtime(&pClTime);
			return time_now->tm_hour - 1;
		};  
		
		int minutes(){
			struct tm *time_now;
			time_now = localtime(&pClTime);
			return time_now->tm_min;
		};
		
		long asSeconds() {
			long tTime;
			
			struct tm *time_now;
			time_now = localtime(&pClTime);

			int seconds = time_now->tm_sec;
			int minutes = time_now->tm_min;
			int hours = time_now->tm_hour - 1;
			
			if ( hours == -1 ) hours = 23;
			
			tTime = seconds + (minutes*60) + (hours * 3600);

			return tTime;
		}

	private:
		time_t pClTime;
};

#endif /*ITIME_H_*/