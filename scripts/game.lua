group "3rdparty"
dofile "3rdparty/xbgi.lua"

project "platchamer"
  	language "C++"
    kind     "ConsoleApp"

    PLATCHAMER_SRC_DIR = path.join(PROJECT_DIR, "src") 

    includedirs {
        PLATCHAMER_SRC_DIR,
        XBGI_SRC_DIR,
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
    
