workspace "rapidjson-learning"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "rapidjson-learning"
    location ("generated/" .. _ACTION)

project "rapidjson-learning"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir ("generated/" .. _ACTION .. "/bin/%{cfg.buildcfg}")
    objdir ("generated/" .. _ACTION .. "/obj/%{cfg.buildcfg}")

    files { "src/**.h", "src/**.hpp", "src/**.cpp" }
    includedirs { "src", "externals/rapidjson/include" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter "system:windows"
        systemversion "latest"