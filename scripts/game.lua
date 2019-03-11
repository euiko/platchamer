group "3rdparty"
-- dofile "3rdparty/xbgi.lua"
dofile "3rdparty/sdl_bgi.lua"
dofile "3rdparty/sdl2.lua"

dofile(path.join(BX_DIR, "scripts/bx.lua"))
dofile(path.join(BGFX_DIR, "scripts/bgfx.lua"))
dofile(path.join(BIMG_DIR, "scripts/bimg.lua"))
bgfxProject("", "StaticLib", {})

project "platchamer"
  	language "C++"
    kind     "ConsoleApp"
    defines {
        "STB_IMAGE_IMPLEMENTATION=1",
        "ECS_NO_RTTI",
        "ENTRY_CONFIG_USE_SDL=1",
        "SDL_VIDEO_DRIVER_X11=1",
    }

    PLATCHAMER_SRC_DIR = path.join(PROJECT_DIR, "src") 
    PLATCHAMER_INC_DIR = path.join(PROJECT_DIR, "include") 

    includedirs {
        "/usr/include",
        PLATCHAMER_INC_DIR,
        PLATCHAMER_SRC_DIR,
        path.join(BGFX_DIR, "include"),
        path.join(BX_DIR, "include"),
        path.join(BIMG_DIR, "include"),
        -- XBGI_SRC_DIR,
        -- path.join(XBGI_SRC_DIR, "common"),
    }
    
    files {
        path.join(PLATCHAMER_SRC_DIR, "**"),
        -- path.join(PROJECT_DIR, "include/**.h"),
    }
    links {
        -- "xbgi",
        "sdl_bgi",
        "SDL2",
        "bgfx",
        "bimg",
        "bx",
    }
    
    buildoptions {
        "-std=c++17",
    }

    configuration "linux or bsd"
        linkoptions { "-fPIC" }
        initX11()
        links {
            "GL",
            "GLU",
            "glut",
            "EGL",
            "GLESv2",
        }
    
