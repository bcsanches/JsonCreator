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
			BaseStringWriter(const BaseStringWriter& rhs) = delete;
			BaseStringWriter operator=(const BaseStringWriter& rhs) = delete;

			const char *GetString() const
			{
				return m_clStream.GetString();
			}

			size_t GetSize() const
			{
				return m_clStream.GetSize();
			}

		protected:
			BaseStringWriter() = default;			

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
			using BaseStringWriter::GetSize;

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

			StringWriter& String(const char *str, const rapidjson::SizeType length, const bool copy = false)
			{
				m_clWriter.String(str, length, copy);

				return *this;
			}

			StringWriter &String(std::string_view str)
			{
				return this->String(str.data() , static_cast<rapidjson::SizeType>(str.length()));
			}

			StringWriter &Int(int value)
			{
				m_clWriter.Int(value);

				return *this;
			}

			StringWriter &Pointer(const void *value)
			{
				m_clWriter.Uint64(reinterpret_cast<intptr_t>(value));

				return *this;
			}

			StringWriter &Bool(bool value)
			{
				m_clWriter.Bool(value);

				return *this;
			}

			StringWriter &Null()
			{
				m_clWriter.Null();

				return *this;
			}

		private:
			rapidjson::Writer<rapidjson::StringBuffer> m_clWriter;
	};
} // end of namespace JsonCreator

#endif
