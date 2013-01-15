JsonCreator
===========

A simple library for easy JSON strings generation.

This library requires rapidjson and works as a wrapper for Json generation.

It is easy for making mistakes or generating invalid JSON strings using ad hoc 
generation or even with rapidjson facilities. 

This library aims to encapsulate JSON creation in C++ objects for avoiding mistakes and with assertions when problems arise.

Also it tries to make the generation as fast as possible, no object tree is created, just an string.

You can also provide your own "Writer" class that writes the JSON direct to a socket or file.

###Usage###

Example:

```javascript
{
    "first_name":"Leia",
    "last_name":"Morgana",
    "address":
    {
        "planet":"Alderaan",
        "city":"Unknown"
    }
}
```

For generating above JSON, you can simple go concatenating strings and you are done. But it is easy to forget to include a comma and also handle all those double quotes. Using JsonCreator you can simple write:

```cpp
#include <JsonCreator/StringWriter.h>
#include <JsonCreator/Object.h>
#include <iostream>

int main(int, char **)
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
	
	std::cout << writer.GetString() << std::endl;
}
```

Notice that scope is used to control object start / finish. The same applies for arrays. Also the library will assert or throw an exception (macro controlled) if you make a mistake. 

###Compiling###

Right now the library is header only. Just copy the folder include/JsonCreator to your compiler include folder or configure it for seeing it and you are ready go.

Compiling is only required if you want to build and run test cases, in this case, Boost Unit testing is also required. 

A Visual Studio Express 2012 project is provided. 

###Disclaimer###

This is not a JSON parser, if you need a JSON parser, we recomend rapidjson: http://code.google.com/p/rapidjson/

###Roadmap###

* Direct support for numbers
* More native writers support

###License###

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
