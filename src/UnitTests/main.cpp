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

#define BOOST_TEST_MODULE JsonCreator
#include <boost/test/unit_test.hpp>

#include <JsonCreator/StringWriter.h>
#include <JsonCreator/Object.h>

BOOST_AUTO_TEST_CASE(Basic)
{	
	JsonCreator::StringWriter writer;

	{
		auto obj = JsonCreator::MakeObject(writer);		

		obj.AddStringValue("name", "bcs");
	}

	BOOST_CHECK(strcmp(writer.GetString(), "{\"name\":\"bcs\"}") == 0);
}

BOOST_AUTO_TEST_CASE(NestedObject)
{	
	JsonCreator::StringWriter writer;

	{
		auto obj = JsonCreator::MakeObject(writer);		

		obj.AddStringValue("name", "bcs");
		{
			auto address =  obj.AddObject("address");		

			BOOST_REQUIRE_THROW(obj.AddStringValue("abc", "abc"), JsonCreator::AssertException);

			BOOST_REQUIRE_THROW(obj.AddObject("abc"), JsonCreator::AssertException);

			address.AddStringValue("street", "Blah");
			address.AddStringValue("city", "Mordor");
			address.AddIntValue("number", 353);
			address.AddBool("valid", true);
			address.AddBool("home", false);
		}

		obj.AddStringValue("age", "2");

		obj.AddObject("empty");
	}

	BOOST_CHECK(strcmp(writer.GetString(), "{\"name\":\"bcs\",\"address\":{\"street\":\"Blah\",\"city\":\"Mordor\",\"number\":353,\"valid\":true,\"home\":false},\"age\":\"2\",\"empty\":{}}") == 0);
}

BOOST_AUTO_TEST_CASE(ObjectWithArray)
{
	JsonCreator::StringWriter writer;

	{
		auto obj = JsonCreator::MakeObject(writer);

		{
			auto ar = obj.AddArray("values");

			ar.AddString("Hello");
			ar.AddString("World");
		}
	}

	BOOST_CHECK(strcmp(writer.GetString(), "{\"values\":[\"Hello\",\"World\"]}") == 0);
}


BOOST_AUTO_TEST_CASE(ObjectWithArrayWithObject)
{
	JsonCreator::StringWriter writer;

	{
		auto obj = JsonCreator::MakeObject(writer);

		{
			auto ar = obj.AddArray("values");

			ar.AddString("Hello");
			ar.AddString("World");

			{
				auto nestedObject = ar.AddObject();

				nestedObject.AddStringValue("msg", "nested");
			}
		}

		obj.AddArray("empty");
	}

	BOOST_CHECK(strcmp(writer.GetString(), "{\"values\":[\"Hello\",\"World\",{\"msg\":\"nested\"}],\"empty\":[]}") == 0);
}

BOOST_AUTO_TEST_CASE(ArrayOnly)
{
	JsonCreator::StringWriter writer;

	{
		auto ar = JsonCreator::MakeArray(writer);

		ar.AddString("1");
		ar.AddString("2");
		ar.AddString("3");
	}

	BOOST_CHECK(strcmp(writer.GetString(), "[\"1\",\"2\",\"3\"]") == 0);
}

BOOST_AUTO_TEST_CASE(Address)
{
	JsonCreator::StringWriter writer;

	{
		auto obj = JsonCreator::MakeObject(writer);

		obj.AddStringValue("first_name", "Leia");
		obj.AddStringValue("last_name", "Morgana");

		{
			auto address = obj.AddObject("address");

			address.AddStringValue("planet", "Alderaan");
			address.AddStringValue("city", "Unknown");
		}
	}

	BOOST_CHECK(strcmp(writer.GetString(), "{\"first_name\":\"Leia\",\"last_name\":\"Morgana\",\"address\":{\"planet\":\"Alderaan\",\"city\":\"Unknown\"}}") == 0);
}