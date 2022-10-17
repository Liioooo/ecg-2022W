cmake_minimum_required(VERSION 3.22)
set(Header_Files
    "src/INIReader.h"
    "src/Utils.h"
    "src/OpenGLDebug.h"
    "src/Shader.h"
    "src/Drawable.h"
    "src/CamaraSystem.h"
    "src/InputManager.h"
    "src/Teapot.h"
)
source_group("Header Files" FILES ${Header_Files})
set(Source_Files
    "src/Main.cpp"
    "src/Shader.cpp"
    "src/Drawable.cpp"
    "src/CamaraSystem.cpp"
    "src/InputManager.cpp"
)
source_group("Source Files" FILES ${Source_Files})
set(All_Sources ${Header_Files} ${Source_Files})
