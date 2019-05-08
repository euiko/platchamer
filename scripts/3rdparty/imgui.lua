imgui =  dependency(nil, "imgui")
  	kind "StaticLib"
    defines {
    --   "STB_RECT_PACK_IMPLEMENTATION=1",
      -- "STB_TRUETYPE_IMPLEMENTATION=1",
      -- "STB_TEXTEDIT_IMPLEMENTATION=1",
      "IMGUI_USER_CONFIG=\"../../src/config/imgui_config.h\"",
    }

    IMGUI_DIR = path.join(PROJECT_DIR, "3rdparty/imgui")

    includedirs {
        path.join(PROJECT_DIR, "3rdparty"),
        IMGUI_DIR,
        FREETYPE2_INC_DIR,
    }

    files {
        path.join(IMGUI_DIR, "**.cpp"),
        path.join(IMGUI_DIR, "**.h"),
    }

    excludes {
        path.join(IMGUI_DIR, "examples/**"),
    }
