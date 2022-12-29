cmake_minimum_required(VERSION 3.22)
set(Header_Files
    "src/INIReader.h"
    "src/Utils.h"
    "src/OpenGLDebug.h"
    "src/Shader.h"
    "src/drawable/Drawable.h"
    "src/drawable/DrawableMesh.h"
    "src/CamaraSystem.h"
    "src/InputManager.h"
    "src/drawable/objects/Teapot.h"
    "src/drawable/objects/Box.h"
    "src/drawable/objects/Cylinder.h"
    "src/drawable/objects/Sphere.h"
    "src/drawable/objects/Torus.h"
    "src/Window.h"
    "src/Renderer.h"
    "src/OrbitCamara.h"
    "src/lights/Light.h"
    "src/Material.h"
    "src/lights/PointLight.h"
    "src/lights/DirectionalLight.h"
    "src/lights/SpotLight.h"
    "src/Texture.h"
    "src/CubeTexture.h"
)
source_group("Header Files" FILES ${Header_Files})
set(Source_Files
    "src/Main.cpp"
    "src/Shader.cpp"
    "src/drawable/Drawable.cpp"
    "src/drawable/DrawableMesh.cpp"
    "src/InputManager.cpp"
    "src/Window.cpp"
    "src/Renderer.cpp"
    "src/OrbitCamara.cpp"
    "src/Material.cpp"
    "src/Texture.cpp"
    "src/CubeTexture.cpp"
)
source_group("Source Files" FILES ${Source_Files})
set(All_Sources ${Header_Files} ${Source_Files})
