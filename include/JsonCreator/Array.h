/*
JsonCreator
May 2013
Copyright (c) 2013-2013 Bruno Sanches http://github.com/bcsanches/JsonCreator

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef JSON_CREATOR_ARRAY_H
#define JSON_CREATOR_ARRAY_H

#include "JsonCreator/BaseValue.h"

namespace JsonCreator
{	
	template<typename T>
	class Object;

	template <typename T>
	class Array: BaseValue<T>
	{
		public:
			Array(T &writer):
				BaseValue<T>(writer)
			{
				this->GetWriter()->StartArray();
			}

			~Array()
			{
				this->GetWriter()->EndArray();
			}

			void AddString(const char *str)
			{
				this->GetWriter()->String(str);
			}
			
			Object<T> AddObject()
			{
				return Object<T>(*this);
			}

		private:					
			friend Object<T>;

			Array(BaseValue<T> &parent):
				BaseValue<T>(parent, typename BaseValue<T>::NonCopyConstructorTag{})
			{
				this->GetWriter()->StartArray();
			}
	};

	template <typename T>
	Array<T> MakeArray(T &writer)
	{
		return Array<T>(writer);
	}
}

#endif
