#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include "rapidjson/document.h"

void LoadJSON(const wchar_t* i_path)
{
    std::ifstream file(i_path, std::ios::binary);
    if (!file.is_open())
    {
        std::wcout << L"File not opened: " << i_path << std::endl;
        return;
    }

    auto size = std::filesystem::file_size(i_path) + 1;
    char* buffer = new char[size] {0};
    file.read(buffer, size);

    rapidjson::Document document;
    document.Parse(buffer);

    if (document.HasParseError())
    {
        std::cout << "JSON parse error at offset: " << document.GetErrorOffset() << std::endl;
    }
    delete[] buffer;
    file.close();
}

int main()
{
    LoadJSON(L"../../data/test.json");
    return 0;
}