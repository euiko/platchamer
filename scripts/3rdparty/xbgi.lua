xbgi =  dependency(nil, "xbgi")
  	language "C"
  	kind "StaticLib"
    defines {
        "ENABLE_XPMLIB",
        "XBGI_DEFAULT_DRIVER=x11_driver",
        "M_PI=3.14159265358979323846",
    }
    
    XBGI_DIR = path.join(GAME_3RDPARTY_DIR, "xbgi")
    XBGI_SRC_DIR = path.join(XBGI_DIR, "sources")

    includedirs {
        path.join(XBGI_SRC_DIR, "common"),
        path.join(XBGI_SRC_DIR, "misc"),
        path.join(XBGI_SRC_DIR, "ps"),
        path.join(XBGI_SRC_DIR, "x11"),
    }

    files {
        path.join(XBGI_SRC_DIR, "common/**"),
        path.join(XBGI_SRC_DIR, "misc/**"),
        -- path.join(XBGI_SRC_DIR, "ps/**"),
        path.join(XBGI_SRC_DIR, "x11/**"),
    }

    excludes {
        path.join(XBGI_SRC_DIR, "demo.c"),
        path.join(XBGI_SRC_DIR, "usleep.c"),
    }

    buildoptions_c {
        "-std=c99",
    }

