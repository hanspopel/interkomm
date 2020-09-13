# OSC

Quick installation guide OSX & Windows:

OSX creates the VST3/AU Plugin and Server App including Controlsurface scipts for Logic and Live
Requires XCode 9 or higher.


Windows creates the VST3 Plugin and Server App including Controlssurface scipts for Live
Requires VS 2015 or higher



1. clone the OSC .git to any folder on your disk:

'cd any_parent_path'
'git clone git@github.com:WavesDev/OSC.git'


2. Enter this folder and check out submodule 'zdb' to this location

'cd OSC' 
'git clone git@github.com:cblomert/zdb.git'

You will require access to the zdb github (cblomert will invite you if necessary)


3. run the build & deploy script

!!!! Always Make sure to run the scripts directly from the root directory OSC !!!!


on OSX: 

'./build.sh -args'

Possible arguments on OSX: 

-all (cleans everything, then builds and deploys all targets)
-allr (builds and deploys all targets)

-osx (cleans osx build folder and osx products then builds / deploys all osx targets)
-osxr (builds / deploys all osx targets)

-clean (cleans all build folders and all products)

-gen (generates XCode Projects)

-update (updates sources)



on WIN: 
'build -args'

Possible arguments on WIN: 
-all (cleans everything, then builds and deploys all targets)
-allr (builds and deploys all targets)

-clean (cleans build folder and all products)

-update (updates sources)

-gen (generates VS Projects)



You can also add several commands, as in: 
./build.sh -update -clean -server
(this will update the sources, clean everything, then build the Win/OSX server)

If specified, any update & clean operations are done first.


5. deployed products (installer for OSX/Win) can be found in /products

6. built compoponents (Plugins/Server/Controlsurfaces) can be found here:

on OSX:
Plugins: build/plugins/VST3/<Config>/
Controlsurface Logic: build/controlsurfaces/logic/<Config>/
Controlsurface Live: build/controlsurfaces/live/Release/
Server: build/osx/server/<Config>/

on Win:
Plugins: build/win/plugins/VST3/<Config>/
Controlsurface Live: build/win/controlsurfaces/live/Release/
Server: build/win/server/<Config>/

7. A Logfile is created in the root directory 'build.log' that will contain the complete bash/cmd output including output from cmake & all build operations

There are some Warnings & safety checks in place to make sure the script runs safely. 
Only call the ./build.sh & build.bat directly from the main OSC folder - Don't call any of the subscripts directly. 


