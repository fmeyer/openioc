
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


//
// Implementa��o IDate
//

#include <idate.hpp>
#include <ctime>

IDate IDate::_today;

INumber IDate::dayOfMonth() const   
  {
  int dia , mes , ano;

  jtog (this->julianDay , ano , mes , dia);

  return (INumber)dia;      
  }    


INumber IDate::monthOfYear()
  {
  int dia , mes , ano;

  jtog (this->julianDay , ano , mes , dia);

  return (INumber)mes;      
  }

IDate::IDate()
  {
  time_t rawtime;
  time ( &rawtime );
  struct tm *time_now;      	
  time_now = localtime(&rawtime);
  
  gtoj (time_now->tm_year+=1900
      , time_now->tm_mon+=1
      , time_now->tm_mday
      , this->julianDay);
  }


IDate::IDate(unsigned long julian)
  {
  this->julianDay = julian;    
  }

IDate::IDate(int dia, int mes, int ano)
  {

//	int md = mes % 12;
//	if(md==0) md=12;

  if ( mes > 15 ) dia = dia+1;			
  if ( mes > 13 ) mes -= 13;

  gtoj(ano , mes , dia , this->julianDay);
  
  }

IDate IDate::today()
  {
  return _today;
  }    


//
// Retorna o ano
//
INumber IDate::year() 
  {
  int dia , mes , ano;

  jtog (this->julianDay , ano , mes , dia);

  return (INumber)ano;
  	  
  }//INumber year() 


INumber IDate::dayOfWeek() 
  {
  int resto = (this->julianDay%7);

  return resto;
  }//INumber dayOfWeek() 


unsigned long IDate::julianDate() 
  {
  return this->julianDay;
  }






void IDate::gtoj ( int iy /* ano */
                 , int im /* mes */ 
                 , int id /* dia */ 
                 , unsigned long &jul)
  {

   
  int ja,jy=iy,jm;

  //if (jy == 0) return(-1) ;
  if (jy < 0) ++jy;
  if (im > 2) 
    {
    jm=im+1;
    }
  else 
    {
    --jy;
    jm=im+13;
    }
	  
  jul = (long) (floor(365.25*jy)+floor(30.6001*jm)+id+1720995);

  if (id+31L*(im+12L*iy) >= IGREG_J) 
    {
    ja=(int)(0.01*jy);
    jul += 2-ja+(int) (0.25*ja);
    }

  }//void gtoj ( int iy



unsigned long IDate::getJulian()
  {
  return this->julianDay;
  }
  

unsigned long IDate::getJulian() const
  {
  return this->julianDay;
  }

IDate &IDate::operator=(IDate* source)
  {
  this->julianDay = source->getJulian();
  return *this;
  }


IDate &IDate::operator=(IDate source)
  {
  this->julianDay = source.julianDay;
  return *this;
  }


bool IDate::operator != (IDate source) const 
  {
  if ( this->julianDay != source.getJulian() ) return true;
  else return false;
  }


bool IDate::isValid(int _day, int _month, int _year) 
  {
  if (_day < 1 || _year < 1 || _month < 1 || _month > 12 || _day > 31) return false;
	
  if ( _day == 31 && ( _month == 4 || _month == 6 || _month == 9 || _month == 11 ) ) 
  return false;
  
  if ( _month == 2 && _day >= 30 ) 
  return false;
  
  if ( (_month == 2 && _day == 29) && !(_year % 4 == 0 && ((_year % 100 != 0) || (_year % 400 == 0)))) 
  return false;
  
  return true;
  }  


IDate& IDate::operator+= (int mday) 
  {
  this->julianDay += mday;
  return *this;
  }


IString IDate::asString(const char *fmt) const
  {
  
  int dia , mes , ano_4;

  jtog(this->julianDay , ano_4 , mes , dia);
  
  
  
  /*std::cout << "\nj:" << this->julianDay 
            << ", ano:" << ano_4 
            << ", mes:" << mes 
            << " e dia:" << dia << std::endl;*/
  
  
  
  //Usar o ctime somente quando o ano for um desses caras
  if ((ano_4 > 1969) && (ano_4 < 2037))
    { 

	time_t rawtime;
	struct tm * timeinfo;
	int year, month ,day;

	if ( mes > 15 ) dia++;			
	if ( mes > 13 ) mes -= 13;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	timeinfo->tm_year = ano_4 - 1900;
	timeinfo->tm_mon = mes - 1;
    timeinfo->tm_mday = dia;
 
    char datestring[256];     
    strftime (datestring, sizeof(datestring), fmt, timeinfo);

    IString ret = datestring;
    return ret;  
    }


  //Sen�o, utilizar hardecoded 
  IString tmp , zerofill = "0";
  std::stringstream stmp;

  //Mascara "%d/%m/%Y"
  if (strcmp(fmt , "%d/%m/%Y") == 0)
    {
    
    if (dia < 10) stmp << zerofill << dia;
    else stmp << dia;
    
    stmp << "/";
    
    if (mes < 10) stmp << zerofill << mes;
    else stmp << mes;

    stmp << "/";
    
    if (ano_4 < 1000) stmp << zerofill;
    if (ano_4 < 100) stmp << zerofill;
    if (ano_4 < 10) stmp << zerofill;  
    
    stmp << ano_4;
    }


  //Mascara "%d/%m/%Y"
  if (strcmp(fmt , "%m/%d/%y") == 0)
    {
    //Mes
    if (mes < 10) stmp << zerofill << mes;
    else stmp << zerofill << mes;
    
    stmp << "/";
    
    //Dia
    if (dia < 10) stmp << zerofill << dia;
    else stmp << dia;

    stmp << "/";
    
    IString strip = std::itos(ano_4);

    //se tenho somente um digito, coloca um zero na frente
    if (strip.length() == 1) stmp << "0" << ano_4; 
    
    //se forem 3 digitos, entao pegar somente 2 ultimos
    if (strip.length() == 3) stmp << strip[1] << strip[2];

    //se forem 4 digitos, entao pegar somente 2 ultimos
    if (strip.length() == 4) stmp << strip[2] << strip[3];    

    }

	
  IString ret = stmp.str().c_str();
  
  return ret;
  }

IDate IDate::operator+( const int i ) 
  {
  this->julianDay += i;
  return *this;
  }





int IDate::operator- (const IDate &source)
//int IDate::operator- (const IDate source)
//IDate IDate::operator- (const IDate source)
  {
  int ret;
  
  ret = this->julianDay - source.getJulian();
  
 // std::cout << "ret:(" << ret << ")";
  
  return ret;
  }




int IDate::operator- (const IDate *source)
//int IDate::operator- (const IDate source)
//IDate IDate::operator- (const IDate source)
  {
  int ret;
  
  ret = this->julianDay - source->getJulian();
  
  //std::cout << "ret:(" << ret << ")";
  
  return ret;
  }

bool IDate::operator  == (IDate source) const
  {
  if ( this->julianDay == source.getJulian() ) 
  return true;
  else return false;
  } 


bool IDate::operator  > (IDate source) const
  {
  if ( this->julianDay > source.getJulian() ) 
  return true;
  else return false;
  }

bool IDate::operator  < (IDate source) const
  {
  if ( this->julianDay < source.getJulian() ) 
  return true;
  else return false;
  }