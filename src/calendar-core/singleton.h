/*
 * singleton.h
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; version 2 of the License.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *  Created on: 2008-09-24
 *  Author: Dariusz Gadomski <dgadomski@gmail.com>
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

namespace TinyOrganizer
{

template<class T>
class Singleton
{
public:
	Singleton() {};
	virtual ~Singleton() = 0;

	static T & getSingleton();

private:

};

template<class T>
T & Singleton<T>::getSingleton()
{
	static T instance;
	return instance;
}

template<class T>
Singleton<T>::~Singleton()
{
	// dummy Singleton destructor
}

}

#endif /* SINGLETON_H_ */
