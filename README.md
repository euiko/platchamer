<h1 align="center">Platchamer</h1>
A platformer game that used as academic project on creating games on top of BGI(Borland Graphic Interface) with minimal dependency

## Dependencies
- [RTTR](https://github.com/rttrorg/rttr) Reflection library, used as in game editor
- [Dear ImGui](https://github.com/ocornut/imgui) GUI Interface, for ui in game editor
- [SDL_bgi](http://libxbgi.sourceforge.net/) Old Borland Graphic Interface based on cross platform Multimedia Library (Graphic, Input, etc)
- [SDL2](http://hg.libsdl.org/SDL) Simple DirectMedia Layer as a rendering and input handler
- [ImGui-SDL](https://github.com/Tyyppi77/imgui_sdl) SDL ImGui rendering backend, modified to adopt the project
- [libfreetype2](https://github.com/servo/libfreetype2) Library that provide font loading
- [cereal](https://github.com/USCiLab/cereal.git) For serialization/deserialization with C++11 compatible
- [GENie](https://github.com/bkaradzic/GENie) as project generator tool

## How To Run (Tested on Linux only)
- Initialize all submodule using `git submodule init`
- Fetch and update submodule with `git submodule update` 
- Run GENie project generator in the bin directory to generate project for your platform as of `bin/linux/genie --gcc=linux-clang gmake`, see help, community, or official resource for more detail
- Change directory to generated project (Makefile, Ninja, VStudio, FASTBuild, Xcode) in the **build/projects/*your_configuration*/**
- Open project for VStudio and XCode, then build.
- Build project if generated as Ninja, Makefiles, FASTBuild
- Open the build directory on the **build/*your_platform*/[bin|obj]**
- Run the executable on the bin directory
