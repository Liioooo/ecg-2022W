cmake_minimum_required(VERSION 3.22)
set(Header_Files
    "src/INIReader.h"
    "src/Utils.h"
    "src/OpenGLDebug.h"
    "src/Shader.h"
    "src/Drawable.h"
    "src/DrawableMesh.h"
    "src/CamaraSystem.h"
    "src/InputManager.h"
    "src/Teapot.h"
    "src/Box.h"
    "src/Cylinder.h"
    "src/Sphere.h"
    "src/Torus.h"
    "src/Window.h"
    "src/Renderer.h"
    "src/OrbitCamara.h"
)
source_group("Header Files" FILES ${Header_Files})
set(Source_Files
    "src/Main.cpp"
    "src/Shader.cpp"
    "src/Drawable.cpp"
    "src/DrawableMesh.cpp"
    "src/InputManager.cpp"
    "src/Window.cpp"
    "src/Renderer.cpp"
    "src/OrbitCamara.cpp"
)
source_group("Source Files" FILES ${Source_Files})
set(All_Sources ${Header_Files} ${Source_Files})
