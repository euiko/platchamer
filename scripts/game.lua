group "3rdparty"
-- dofile "3rdparty/xbgi.lua"
dofile "3rdparty/sdl_bgi.lua"
dofile "3rdparty/sdl2.lua"

project "platchamer"
  	language "C++"
    kind     "ConsoleApp"
    defines {
        "STB_IMAGE_IMPLEMENTATION=1",
        "ECS_NO_RTTI",
    }

    PLATCHAMER_SRC_DIR = path.join(PROJECT_DIR, "src") 

    includedirs {
        "/usr/include",
        PLATCHAMER_SRC_DIR,
        XBGI_SRC_DIR,
        -- path.join(XBGI_SRC_DIR, "common"),
    }
    
    files {
        path.join(PLATCHAMER_SRC_DIR, "**"),
        -- path.join(PROJECT_DIR, "include/**.h"),
    }

    links {
        -- "xbgi",
        "sdl_bgi",
        "sdl2",
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
    
