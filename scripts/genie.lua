solution "platchamer_sln"

	configurations {
		"Debug",
		"Release",
	}
	platforms {
		"x64",
	}

	language "C++"
	-- flags {
	-- 	"RTTI",
	-- }


PROJECT_DIR = path.getabsolute("..")
BUILD_DIR = path.join(PROJECT_DIR, "build")
GAME_3RDPARTY_DIR = path.join(PROJECT_DIR, "3rdparty")

ENTCOSY_3RDPARTY_DIR = path.join(PROJECT_DIR, 'src/libs/entcosy/3rdparty')
BGFX_DIR = path.join(GAME_3RDPARTY_DIR, "bgfx")
BX_DIR = path.join(GAME_3RDPARTY_DIR, "bx")
BIMG_DIR = path.join(GAME_3RDPARTY_DIR, "bimg")

dofile "options.lua"
dofile "toolchain.lua"
toolchain(BUILD_DIR, GAME_3RDPARTY_DIR)
dofile "utils/module.lua"

group "bin"
dofile "game.lua"

