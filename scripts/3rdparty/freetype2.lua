imgui =  dependency(nil, "freetype2")
  	kind "StaticLib"
    defines {
    --   "STB_RECT_PACK_IMPLEMENTATION=1",
      -- "STB_TRUETYPE_IMPLEMENTATION=1",
      -- "STB_TEXTEDIT_IMPLEMENTATION=1",
      -- "IMGUI_USER_CONFIG=\"../../src/config/imgui_config.h\"",
    }

    FREETYPE2_DIR = path.join(PROJECT_DIR, "3rdparty/libfreetype2")
    FREETYPE2_SRC_DIR = path.join(FREETYPE2_DIR, "freetype2/src")
    FREETYPE2_INC_DIR = path.join(FREETYPE2_DIR, "freetype2/include")

    includedirs {
        path.join(PROJECT_DIR, "3rdparty"),
        FREETYPE2_INC_DIR,
        FREETYPE2_SRC_DIR,
    }

    files {
        path.join(FREETYPE2_SRC_DIR, "**.cpp"),
        path.join(FREETYPE2_SRC_DIR, "**.h"),
    }

    excludes {
        path.join(FREETYPE2_DIR, "examples/**"),
    }
