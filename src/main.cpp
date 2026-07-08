#include <filesystem>
#include <format>
#include <fstream>
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "debugging/LogUtils.hpp"
#include "TestObject.h"

void SaveJSON(const wchar_t* i_path, rapidjson::Document& i_document)
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    i_document.Accept(writer);

    std::ofstream file(i_path, std::ios::trunc);
    file.write(buffer.GetString(), buffer.GetSize());
    file.close();
}

void WriteDefaultJSON()
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& a = document.GetAllocator();

    {
        rapidjson::Value array;
        array.SetArray();
        document.AddMember("created_a", array, a);
    }
    {
        rapidjson::Value object;
        object.SetObject();
        document["created_a"].PushBack(object, a);
    }
    {
        rapidjson::Value myBool;
        myBool.SetBool(true);
        document["created_a"][0].AddMember("t", myBool, a);
    }
    {
        rapidjson::Value myString;
        myString.SetString("const string test");
        document["created_a"][0].AddMember("s", myString, a);
    }
    {
        rapidjson::Value myDynamicString;
        std::string rawString = "dynamic str testing";
        myDynamicString.SetString(rawString.c_str(), static_cast<rapidjson::SizeType>(rawString.size()), a);
        document["created_a"][0].AddMember("dynamic_s", myDynamicString, a);
    }
    SaveJSON(L"../../data/new.json", document);
}

void LoadJSON(const wchar_t* i_path)
{
    std::ifstream file(i_path, std::ios::binary);
    if (!file.is_open())
    {
        WLOG(LOG_WARN, L"File not opened: {}", i_path);
        return;
    }

    auto size = std::filesystem::file_size(i_path) + 1;
    char* buffer = new char[size] {0};
    file.read(buffer, size);

    rapidjson::Document document;
    document.Parse(buffer);

    if (document.HasParseError())
    {
        LOG(LOG_WARN, "JSON parse error at offset {}", document.GetErrorOffset());
        delete[] buffer;
        file.close();
        return;
    }

    if (!document.IsObject())
    {
        delete[] buffer;
        file.close();
        return;
    }

    // Querying document
    TestObject obj{};
    if (document.HasMember("hello") && document["hello"].IsString())
    {
        obj.m_hello = document["hello"].GetString();
    }
    if (document.HasMember("t") && document["t"].IsBool())
    {
        obj.m_t = document["t"].GetBool();
    }
    obj.m_f = document["f"].GetBool();
    assert(document.HasMember("n") && document["n"].GetType() == rapidjson::Type::kNullType);
    obj.m_n = 0;
    obj.m_pi = document["pi"].GetFloat();
    if (document.HasMember("a") && document["a"].IsArray())
    {
        auto a = document["a"].GetArray();
        obj.m_a.reserve(a.Size());
        for (rapidjson::Value::ConstValueIterator itr = a.Begin(); itr != a.End(); itr++)
        {
            if (itr->IsInt())
            {
                obj.m_a.push_back(itr->GetInt());
            }
        }
    }

    delete[] buffer;
    file.close();
}

int main()
{
    LoadJSON(L"../../data/test.json");
    WriteDefaultJSON();
    return 0;
}