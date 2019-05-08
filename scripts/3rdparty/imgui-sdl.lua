imgui =  dependency(nil, "imgui_sdl")
  	kind "StaticLib"
    defines {
    }

    IMGUI_SDL_DIR = path.join(PROJECT_DIR, "3rdparty/imgui-sdl")

    includedirs {
        path.join(PROJECT_DIR, "3rdparty"),
        path.join(PROJECT_DIR, "include"),
        IMGUI_SDL_DIR,
        IMGUI_DIR,
    }

    files {
        path.join(IMGUI_SDL_DIR, "**.cpp"),
        path.join(IMGUI_SDL_DIR, "**.h"),
    }

    excludes {
        path.join(IMGUI_SDL_DIR, "example.cpp"),
    }
