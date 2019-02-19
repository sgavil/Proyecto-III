rem Ramón Arjona Quiñones, 2019
rem Script de compilación para ProyectoIII que crea la solución de VS con CMake, compila Ogre y mueve los dll necesarios para la ejecución del mismo
@echo on

rem 4.Movemos los dll necesarios a nuestra carpeta Exes
if exist "exes\" (
	rmdir /s /q exes\
)
mkdir exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\debug\plugins_d.cfg exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\release\plugins.cfg exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\debug\OgreMain_d.dll exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\release\OgreMain.dll exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\debug\RenderSystem_GL_d.dll exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\release\RenderSystem_GL.dll exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\release\zlib.dll exes

