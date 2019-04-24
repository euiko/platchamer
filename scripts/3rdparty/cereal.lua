cereal =  dependency(nil, "cereal")
  	language "C++"
  	kind "StaticLib"
    -- defines {}
    
    CEREAL_DIR = path.join(GAME_3RDPARTY_DIR, "cereal")
    CEREAL_INCLUDE_DIR = path.join(CEREAL_DIR, "include")

    includedirs {
        CEREAL_INCLUDE_DIR,
    }
