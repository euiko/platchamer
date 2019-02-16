group "3rdparty"
dofile "3rdparty/xbgi.lua"

project "platchamer"
  	language "C++"
    kind     "ConsoleApp"
    defines {
        "STB_IMAGE_IMPLEMENTATION=1",
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
        "xbgi",
    }
    
    buildoptions {
        "-std=c++17",
    }

    configuration "linux or bsd"
        linkoptions { "-fPIC" }
        initX11()
        -- links {
        --     "dl",
        --     "GL",
        --     "GLU",
        --     "glut",
        --     "EGL",
        --     "GLESv2",
        -- }
    
