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

#ifndef JSON_CREATOR_STRING_WRITER_H
#define JSON_CREATOR_STRING_WRITER_H

#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace JsonCreator
{
	class BaseStringWriter
	{
		public:
			const char *GetString()
			{
				return m_clStream.GetString();
			}

		protected:
			BaseStringWriter()
			{
				//empty
			}

		private:
			BaseStringWriter(const BaseStringWriter &rhs);
			BaseStringWriter operator=(const BaseStringWriter &rhs);

		protected:
			rapidjson::StringBuffer m_clStream;
	};

	class StringWriter: private BaseStringWriter
	{
		public:
			StringWriter():
				m_clWriter(m_clStream)
			{
				//empty
			}

		public:
			using BaseStringWriter::GetString;

			StringWriter& StartObject()
			{
				m_clWriter.StartObject();

				return *this;
			}

			StringWriter& EndObject()
			{
				m_clWriter.EndObject();

				return *this;
			}

			StringWriter& StartArray()
			{
				m_clWriter.StartArray();

				return *this;
			}

			StringWriter& EndArray()
			{
				m_clWriter.EndArray();

				return *this;
			}

			StringWriter& String(const char *str, std::size_t length, bool copy = false) 
			{
				m_clWriter.String(str, length, copy);

				return *this;
			}

			StringWriter &String(const char *str)
			{
				m_clWriter.String(str);

				return *this;
			}

		private:
			rapidjson::Writer<rapidjson::StringBuffer> m_clWriter;
	};
}

#endif
