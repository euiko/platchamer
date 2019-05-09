group "3rdparty"
-- dofile "3rdparty/xbgi.lua"
dofile "3rdparty/sdl_bgi.lua"
dofile "3rdparty/sdl2.lua"
dofile "3rdparty/cereal.lua"

dofile(path.join(BX_DIR, "scripts/bx.lua"))
dofile(path.join(BGFX_DIR, "scripts/bgfx.lua"))
dofile(path.join(BIMG_DIR, "scripts/bimg.lua"))
dofile "3rdparty/freetype2.lua"
dofile "3rdparty/imgui.lua"
dofile "3rdparty/imgui-sdl.lua"

bgfxProject("", "StaticLib", {})

project "platchamer"
  	language "C++"
    kind     "ConsoleApp"
    defines {
        "STB_IMAGE_IMPLEMENTATION=1",
        "ECS_NO_RTTI",
        "ENTRY_CONFIG_USE_SDL=1",
        "SDL_VIDEO_DRIVER_X11=1",
        "IMGUI_IMPL_OPENGL_LOADER_GLEW=1",
        -- "BGFX_CONFIG_MULTITHREADED=0",
    }

    PLATCHAMER_SRC_DIR = path.join(PROJECT_DIR, "src")
    PLATCHAMER_INC_DIR = path.join(PROJECT_DIR, "include")
    ENTCOSY_SRC_DIR = path.join(PLATCHAMER_SRC_DIR, "libs/entcosy/src")

    includedirs {
        "/usr/include",
        path.join(PROJECT_DIR, "3rdparty"),
        path.join(BGFX_DIR, "3rdparty"),
        path.join(BX_DIR,   "include"),
        path.join(BIMG_DIR, "include"),
        path.join(BGFX_DIR, "include"),
        path.join(BGFX_DIR, "examples"),
        PLATCHAMER_INC_DIR,
        PLATCHAMER_SRC_DIR,
        ENTCOSY_SRC_DIR,
        CEREAL_INCLUDE_DIR,
        FREETYPE2_INC_DIR,
        IMGUI_SDL_DIR,
        IMGUI_DIR,
        BGFX_STB_DIR,
        -- XBGI_SRC_DIR,
        -- path.join(XBGI_SRC_DIR, "common"),
    }

    files {
        path.join(PLATCHAMER_SRC_DIR, "**"),
        -- path.join(PROJECT_DIR, "include/**.h"),
    }

    excludes {
        path.join(PLATCHAMER_SRC_DIR, "libs/entcosy/**.cpp"),
        path.join(PLATCHAMER_SRC_DIR, "libs/entcosy/3rdparty/**"),
    }

    links {
        -- "xbgi",
        "imgui_sdl",
        "imgui",
        "freetype2",
        "sdl_bgi",
        "SDL2",
        "bgfx",
        "bimg",
        "bx",
    }

    buildoptions {
        "-std=c++17",
        "-Wno-c++11-narrowing"
    }

    configuration "linux or bsd"
        linkoptions { "-fPIC" }
        initX11()
        links {
            "GL",
            "GLU",
            "GLEW",
            "glut",
            "EGL",
            "GLESv2",
        }

