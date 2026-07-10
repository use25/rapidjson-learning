#pragma once
#include "rapidjson/reader.h"
#include <string>

struct TestObject {
	std::string m_hello;
	bool m_t;
	bool m_f;
	char m_n;
	char m_i;
	float m_pi;
	std::vector<char> m_a;
};

struct TestObjectHandler : public rapidjson::BaseReaderHandler<rapidjson::UTF8<>, TestObjectHandler>
{
    enum class Key { None, Hello, T, F, N, I, Pi, A };

    TestObject* mo_obj;
    Key m_currentKey = Key::None;
    bool m_inArray = false;

    TestObjectHandler(TestObject& i_obj) : rapidjson::BaseReaderHandler<rapidjson::UTF8<>, TestObjectHandler>()
        , mo_obj(&i_obj)
    {
    }

    bool Key(const char* str, rapidjson::SizeType length, bool /*copy*/)
    {
        std::string_view key(str, length);
        if (key == "hello")     m_currentKey = Key::Hello;
        else if (key == "t")    m_currentKey = Key::T;
        else if (key == "f")    m_currentKey = Key::F;
        else if (key == "n")    m_currentKey = Key::N;
        else if (key == "i")    m_currentKey = Key::I;
        else if (key == "pi")   m_currentKey = Key::Pi;
        else if (key == "a")    m_currentKey = Key::A;
        else                    m_currentKey = Key::None; // unknown key, ignore its value
        return true;
    }

    bool String(const char* str, rapidjson::SizeType length, bool /*copy*/)
    {
        if (m_currentKey == Key::Hello)
        {
            mo_obj->m_hello.assign(str, length);
        }
        return true;
    }

    bool Bool(bool b)
    {
        if (m_currentKey == Key::T) mo_obj->m_t = b;
        else if (m_currentKey == Key::F) mo_obj->m_f = b;
        return true;
    }

    bool Null()
    {
        if (m_currentKey == Key::N) mo_obj->m_n = 0;
        return true;
    }

    bool Double(double d)
    {
        if (m_currentKey == Key::Pi) mo_obj->m_pi = static_cast<float>(d);
        return true;
    }

    bool Int(int i)
    {
        if (m_inArray) mo_obj->m_a.push_back(static_cast<char>(i));
        else if (m_currentKey == Key::I) mo_obj->m_i = static_cast<char>(i);
        return true;
    }
    bool Uint(unsigned u) { return Int(static_cast<int>(u)); }

    bool StartArray()
    {
        if (m_currentKey == Key::A) m_inArray = true;
        return true;
    }

    bool EndArray(rapidjson::SizeType /*count*/)
    {
        m_inArray = false;
        m_currentKey = Key::None;
        return true;
    }

    bool StartObject() { return true; }
    bool EndObject(rapidjson::SizeType) { return true; }
};