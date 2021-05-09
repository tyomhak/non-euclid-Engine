# Adding required library files #

## GLFW3 ##
1. Add glfw3.lib to the /libs  directory

## ASSIMP ##
1. Add assimp.lib to the /libs directory  
Your file might have a different ending, you can just rename the file if you get cmake error: can't find assimp

2. Add assimp\*.dll file to /libs/dlls  directory (no renaming)





# Generate VS Project #

## CMake ##
1. Create a new folder "build" in the root dir
2. Open CMake GUI
3. Set the root dir as the source dir
4. Set the "non-euclid-Engine/build" folder as the Build ("Browse Build") /
5. Configure (at the bottom)
6. Generate (at the bottom)
7. You should have a .sln file in the build folder
8. Open .sln with Visual Studio
9. Right click NonEuclid -> "Set as Startup Project"
