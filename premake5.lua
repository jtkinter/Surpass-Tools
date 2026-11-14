project "Surpass-Tools"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "src/**.h",
        "src/**.cpp",
    }

    includedirs {
        "/src",
        "%{wks.location}/" .. ImGuiDir,
        "%{wks.location}/" .. ImGuiDir .. "/backends",
        "%{wks.location}/" .. CoreDir .. "/src",
		"%{wks.location}/" .. "%{IncludeDir.GLFW}",
		"%{wks.location}/" .. "%{IncludeDir.GLAD}",
        "%{wks.location}/" .. "%{IncludeDir.GLM}"
    }

    links {
        "Surpass-Core",
        "ImGui",
        "GLFW",
        "GLAD",
        "opengl32"
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS"
    }


    filter "configurations: Debug"
        defines "DEBUG"
        symbols "on"
        runtime "Debug"

    filter "configurations: Release"
        defines "NDEBUG"
        optimize "on"
        runtime "Release"