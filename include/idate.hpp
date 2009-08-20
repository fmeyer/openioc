#ifndef __IDATE_HPP__
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


#define __IDATE_HPP__

//
// IDate
//

#include <ctime>
#include <cmath>
#include <string>
#include <sstream>
#include <iostream>

#include <istring.hpp>
#include <slvdefault.h>

#define IGREG_J (15+31L*(10+12L*1582))
#define IGREG_G 2299161


/*inline std::string itos(int i) 
  { 
  std::stringstream s;
  s << i;
  return s.str();
  }*/

class IDate
  {
  public:
    
    typedef enum 
      {
      SUNDAY = 0
      , MONDAY
      , TUESDAY
      , WEDNESDAY
      , THURSDAY  
      , FRIDAY
      , SATURDAY
      } WeekDay;
    
    typedef enum { January = 1 , 
				   February , 
				   March , 
				   April , 
				   May , 
				   June ,
				   July , 
				   August , 
				   September , 
				   October , 
				   November , 
				   December } Month;	
    
    
    //Construtor 
    IDate();    
    virtual ~IDate(){}
    
    IDate(unsigned long julian);
    
    IDate(int dia, int mes, int ano);
    
    INumber dayOfMonth() const;
    
    INumber monthOfYear(); 
           
    static IDate _today;
    
    static IDate today();
    
    INumber year();
    
    INumber dayOfWeek() ;
    
    unsigned long julianDate();
    
void jtog (unsigned long julian
                , int &iy
                , int &im
                , int &id)
  {

  long ja,jalpha,jb,jc,jd,je;
  
  if (( julian >= 2298884 ) && ( julian <= 2378000 ))
	julian = julian - 10;  

  if (julian >= IGREG_G) 
    {
	jalpha=(long)(((float) (julian-1867216)-0.25)/36524.25);
	ja=julian+1+jalpha-(long) (0.25*jalpha);
    }
  else ja=julian;
      
  jb=ja+1524;
  jc=(long)(6680.0+((float) (jb-2439870)-122.1)/365.25);
  jd=(long)(365*jc+(0.25*jc));
  je=(long)((jb-jd)/30.6001);
  id=jb-jd-(long) (30.6001*je);
  im=je-1;
  if (im > 12) im -= 12;
  iy=jc-4715;
  if (im > 2) --(iy);
  if (iy <= 0) --(iy);
	  
  }//void jtog (unsigned long julian




void jtog (unsigned long julian
                , int &iy
                , int &im
                , int &id) const
  {

  long ja,jalpha,jb,jc,jd,je;
  
  if (( julian >= 2298884 ) && ( julian <= 2378000 ))
	julian = julian - 10;    

  if (julian >= IGREG_G) 
    {
	jalpha=(long)(((float) (julian-1867216)-0.25)/36524.25);
	ja=julian+1+jalpha-(long) (0.25*jalpha);
    }
  else ja=julian;
      
  jb=ja+1524;
  jc=(long)(6680.0+((float) (jb-2439870)-122.1)/365.25);
  jd=(long)(365*jc+(0.25*jc));
  je=(long)((jb-jd)/30.6001);
  id=jb-jd-(long) (30.6001*je);
  im=je-1;
  if (im > 12) im -= 12;
  iy=jc-4715;
  if (im > 2) --(iy);
  if (iy <= 0) --(iy);
	  
  }//void jtog (unsigned long julian

    
    void gtoj ( int iy , int im , int id , unsigned long &jul);
    
    unsigned long getJulian();
    
    unsigned long getJulian() const;
    
    IDate &operator=(IDate* source);
    
    IDate &operator=(IDate source);
    
    bool operator != (IDate source) const; 
    
    bool operator  < (IDate source) const;
    
    bool operator  > (IDate source) const;
    
    bool operator  == (IDate source) const;
    
    int operator- (const IDate &source);
  
    int operator- (const IDate *source);    
    
    IDate &operator- (int i)
      {
      int ret;
      this->julianDay - 1;

      return *this;
      }    
    
    operator long(){return getJulian();}      
    
    IDate operator+( const int i );
    
    IDate &operator+( int i ) const
      {
      IDate tmp(this->getJulian() + 1);
      
      return tmp;
      
      //this->julianDay + i;
      //return (IDate(this->getJulian() + 1));     
       
      //return dynamic_cast<IDate&>(const_cast<IDate*>(this));
      }
    
    IDate& operator+= (int mday);
    
    static bool isValid(int _day, int _month, int _year);
    
    IString asString(const char *fmt) const;

    friend std::ostream& operator <<(std::ostream& aStream, const IDate& aDate)
      {
	  aStream << aDate.asString("%m/%d/%y");
	  return aStream;
      }
    
  
  protected:
    
    unsigned long julianDay;
  
  };
  
#endif  