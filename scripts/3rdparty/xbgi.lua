xbgi =  dependency(nil, "xbgi")
  	language "C"
  	kind "StaticLib"
    defines {
        "M_PI=3.14159265358979323846",
    }
    
    XBGI_DIR = path.join(GAME_3RDPARTY_DIR, "xbgi")
    XBGI_SRC_DIR = path.join(XBGI_DIR, "src")

    includedirs {
        XBGI_SRC_DIR,
    }

    files {
        path.join(XBGI_SRC_DIR, "*.c"),
        path.join(XBGI_SRC_DIR, "*.h"),
    }

    excludes {
        path.join(XBGI_SRC_DIR, "demo.c"),
        path.join(XBGI_SRC_DIR, "usleep.c"),
    }

    buildoptions_c {
        "-std=c11",
    }

