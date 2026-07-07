#include <filesystem>
#include <format>
#include <fstream>
#include <vector>
#include "rapidjson/document.h"
#include "debugging/LogUtils.hpp"

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
    }
    delete[] buffer;
    file.close();
}

int main()
{
    LoadJSON(L"../../data/test.json");
    return 0;
}