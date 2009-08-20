#ifndef _DEFAULT_H_
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


#define _DEFAULT_H_

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>

#define True true 
#define False false 

typedef bool IBoolean;
typedef unsigned long INumber;
typedef unsigned long IPosition;

#define ntohll(x) (((_int64)(ntohl((int)((x << 32) >> 32))) << 32) | (unsigned int)ntohl(((int)(x >> 32))))
#define htonll(x) ntohll(x)

#define ITRACE_DEVELOP(p1) std::cout<<(p1)<<std::endl
#endif //_DEFAULT_H_