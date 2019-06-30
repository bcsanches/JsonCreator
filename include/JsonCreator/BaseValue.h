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

#ifndef JSON_CREATOR_BASE_VALUE
#define JSON_CREATOR_BASE_VALUE

#include "JsonCreator/Defs.h"

namespace JsonCreator
{
	template<typename T>
	class BaseValue
	{
		protected:
			struct NonCopyConstructorTag {};

			BaseValue(T &writer):
#ifdef JSON_CREATOR_DEBUG
				m_szChildCount(0),
				m_pclParent(nullptr),
#endif
				m_pclWriter(&writer)
			{
				//empty
			}

			BaseValue(BaseValue &&rhs):
#ifdef JSON_CREATOR_DEBUG
				m_szChildCount(rhs.m_szChildCount),
				m_pclParent(rhs.m_pclParent),
#endif
				m_pclWriter(rhs.m_pclWriter)
			{
				rhs.m_pclWriter = nullptr;
			}

			BaseValue(BaseValue &parent, const NonCopyConstructorTag /*unused*/):
#ifdef JSON_CREATOR_DEBUG
				m_szChildCount(0),
				m_pclParent(&parent),
#endif
				m_pclWriter(parent.m_pclWriter)
			{				
				#ifdef JSON_CREATOR_DEBUG
					m_pclParent->m_szChildCount++;
				#endif
			}

			~BaseValue()
			{
				#ifdef JSON_CREATOR_DEBUG
					JC_ASSERT(m_szChildCount == 0, "Pending child");
				#endif
				
				#ifdef JSON_CREATOR_DEBUG
					if(m_pclParent)
					{
						m_pclParent->m_szChildCount--;						
					}
				#endif
			}

#ifdef JSON_CREATOR_DEBUG
			bool HasChildren() const
			{
				return m_szChildCount > 0;
			}
#endif

			inline T *GetWriter() const
			{
				return m_pclWriter;
			}

		private:
			BaseValue(const BaseValue &rhs);
			BaseValue operator=(const BaseValue &rhs);

		private:									
			T *m_pclWriter;

#ifdef JSON_CREATOR_DEBUG
			size_t m_szChildCount;

			BaseValue *m_pclParent;
#endif
	};
}

#endif