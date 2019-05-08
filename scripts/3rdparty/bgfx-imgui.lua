imgui =  dependency(nil, "bgfx-imgui")
  	kind "StaticLib"
    defines {
    --   "STB_RECT_PACK_IMPLEMENTATION=1",
      -- "STB_TRUETYPE_IMPLEMENTATION=1",
      -- "STB_TEXTEDIT_IMPLEMENTATION=1",
        "IMGUI_USER_CONFIG=\"../../../../src/config/imgui_config.h\"",
    }

    BGFX_IMGUI_DIR = path.join(BGFX_DIR, "3rdparty/dear-imgui")
    BGFX_STB_DIR = path.join(BGFX_DIR, "3rdparty/stb")

    includedirs {
        path.join(BX_DIR,   "include"),
        path.join(BIMG_DIR, "include"),
        path.join(BGFX_DIR, "include"),
        path.join(BGFX_DIR, "3rdparty"),
        path.join(BGFX_DIR, "examples"),
        path.join(PROJECT_DIR, "src"),
        BGFX_IMGUI_DIR,
        BGFX_STB_DIR,
    }

    print(path.join(BGFX_IMGUI_DIR, "**.cpp"))

    files {
        path.join(BGFX_IMGUI_DIR, "**.cpp"),
        path.join(BGFX_IMGUI_DIR, "**.h"),
        path.join(BGFX_STB_DIR, "**.h"),
        path.join(BGFX_DIR, "examples/common/imgui/**.cpp"),
        path.join(BGFX_DIR, "examples/common/imgui/**.h"),
    }
