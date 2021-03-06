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

#ifndef JSON_CREATOR_DEFS_H
#define JSON_CREATOR_DEFS_H

//Windows?
#if defined _MSC_VER
	#if defined _DEBUG
		#define JSON_CREATOR_DEBUG

		#define JSON_CREATOR_ASSERT_THROW
	#endif
#elif defined __linux__
	#if !defined NDEBUG
		#define JSON_CREATOR_DEBUG
		#define JSON_CREATOR_ASSERT_THROW
	#endif
#else
	#error "Unknown compiler, please report"
#endif

#if defined JSON_CREATOR_ASSERT_THROW

	#include <stdexcept>

	namespace JsonCreator
	{
		class AssertException: std::runtime_error
		{
			public:
				AssertException(const char *msg):
					std::runtime_error(msg)
				{
					//empty
				}
		};
	}

	#include <cassert>

	//#define JC_ASSERT(EXP, MSG) { if(!(EXP)) throw AssertException(MSG); }
	#define JC_ASSERT(EXP, MSG) { assert(EXP); }
#endif

#endif
