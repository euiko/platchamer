sdl_bgi =  dependency(nil, "sdl_bgi")
  	language "C"
  	kind "StaticLib"
    
    SDL_BGI_DIR = path.join(GAME_3RDPARTY_DIR, "sdl_bgi")

    local _files = os.matchfiles(path.join(SDL_BGI_DIR, "src/SDL_bgi.h"))
    local inc_dir = include_files(sdl_bgi, os.matchfiles(path.join(SDL_BGI_DIR, "src/graphics.h")))
    inc_dir = include_files("SDL2", _files)
    includedirs {
        inc_dir,
        path.join(SDL_BGI_DIR, "src"),
    }

    files {
        path.join(SDL_BGI_DIR, "src/SDL_bgi.c"),
    }

    buildoptions_c {
        "-std=c11",
    }

