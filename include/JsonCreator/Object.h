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

#ifndef JSON_CREATOR_OBJECT_H
#define JSON_CREATOR_OBJECT_H

#include "JsonCreator/BaseValue.h"
#include "JsonCreator/Array.h"

namespace JsonCreator
{
	template <typename T>
	class Object: protected BaseValue<T>
	{
		public:
			Object(T &writer):
				BaseValue(writer)
			{
				this->GetWriter()->StartObject();
			}

			Object(Object &&rhs):
				BaseValue(rhs)
			{
				//empty
			}
			
			~Object()
			{
				if(this->GetWriter())
					this->GetWriter()->EndObject();
			}

			void AddStringValue(const char *name, const char *value)
			{
				this->StartAttribute(name);

				this->GetWriter()->String(value);
			}

			Object AddObject(const char *name)
			{
				this->StartAttribute(name);

				return Object(static_cast<BaseValue &>(*this));
			}

			Array<T> AddArray(const char *name)
			{
				this->StartAttribute(name);

				return Array<T>(static_cast<BaseValue &>(*this));
			}

		private:
			void StartAttribute(const char *name)
			{
				#ifdef JSON_CREATOR_DEBUG
					JC_ASSERT(!this->HasChildren(), "Unable to add item, finalize child first");
				#endif

				this->GetWriter()->String(name);
			}

		private:
			Object(const Object &rhs);
			Object operator=(const Object &rhs);

			Object(BaseValue &parent):
				BaseValue(parent, BaseValue::NonCopyConstructorTag())
			{				
				this->GetWriter()->StartObject();				
			}

			friend Array<T>;
	};

	template <typename T>
	Object<T> MakeObject(T &writer)
	{
		return Object<T>(writer);
	}
}

#endif
