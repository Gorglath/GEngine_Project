# GEngine

GEngine is a custom built game engine which uses Ogre3d-Next. <br />

## Usage
Currently GEngine is still a work in progress and is bound to changes. <br />

## Dependencies

GEngine dependencies at the moment are Ogre3d-Next and SDL2 (which ogre3d uses but must be included as well). <br />
<br />
Make sure that you download and build Ogre3d-Next : (https://github.com/OGRECave/ogre-next) <br />
And download SDL2 : (https://www.libsdl.org/download-2.0.php) <br />

## Linking

The path mentioned before should lead to the include directories on your computer, make sure to include the full paths. <br />
Note: out\build is a directory in which the Ogre3d-next and it's dependencies are built, it won't show unless you built Ogre3d-next or his dependencies. <br />
<br />
In project settings -> C/C++ -> General -> Additional include directories: <br />
<br />
..\SDL\SDL2\SDL2-2.0.16\include <br />
..\Ogre3d_Next\Ogre_Next\Components\Hlms\Common\include <br />
..\Ogre3d_Next\Ogre_Next\Components\Hlms\Pbs\include <br />
..\Ogre3d_Next\Ogre_Next\Components\Hlms\Unlit\include <br />
..\Ogre3d_Next\Dep\out\build\ogredeps\include  <br />
..\Ogre3d_Next\Ogre_Next\OgreMain\include <br />
..\Ogre3d_Next\Ogre_Next\out\build\include <br />
<br />
In project settings -> Linker -> General -> Additional library directories: <br />
<br />
..\SDL\SDL2\SDL2-2.0.16\lib\x64 <br />
..\Ogre3d_Next\Ogre_Next\out\build\lib\Release <br />
<br />
In projcet settings -> Linker -> Input -> Additional dependencies: <br />
<br />
OgreOverlay.lib <br />
OgreMain.lib <br />
OgreSamplesCommon.lib <br />
OgreHlmsPbs.lib <br />
OgreHlmsUnlit.lib <br />
SDL2.lib <br />
SDL2main.lib <br />
<br />
