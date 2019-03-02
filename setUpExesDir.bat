rem Ramón Arjona Quiñones, 2019
rem Script de compilación para ProyectoIII que crea la solución de VS con CMake, compila Ogre y mueve los dll necesarios para la ejecución del mismo
@echo on

mkdir tmp
Xcopy exes\*.cfg tmp
del /q exes\*

rem Librerías dinámicas para OGRE
Xcopy Dependencias\ogre-1.11.5\Build\bin\debug\OgreMain_d.dll exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\release\OgreMain.dll exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\debug\RenderSystem_GL_d.dll exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\release\RenderSystem_GL.dll exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\release\zlib.dll exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\debug\Codec_STBI_d.dll exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\release\Codec_STBI.dll exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\debug\OgreTerrain_d.dll exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\release\OgreTerrain.dll exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\debug\OgrePaging_d.dll exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\release\OgrePaging.dll exes
Xcopy Dependencias\ogre-1.11.5\Build\SDL2-build\RelWithDebInfo\SDL2.dll exes

rem Librerías dinámicas para physX
Xcopy Dependencias\physX-3.4\dll\glut32.dll exes
Xcopy Dependencias\physX-3.4\dll\nvToolsExt64_1.dll exes
Xcopy Dependencias\physX-3.4\dll\PhysX3DEBUG_x64.dll exes
Xcopy Dependencias\physX-3.4\dll\PhysX3_x64.dll exes
Xcopy Dependencias\physX-3.4\dll\PxFoundationDEBUG_x64.dll exes
Xcopy Dependencias\physX-3.4\dll\PxFoundation_x64.dll exes
Xcopy Dependencias\physX-3.4\dll\PxPvdSDKDEBUG_x64.dll exes
Xcopy Dependencias\physX-3.4\dll\PxPvdSDK_x64.dll exes


Xcopy tmp\* exes

del /q tmp
rmdir tmp



