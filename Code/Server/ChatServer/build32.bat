mkdir Build64Bat
cd Build64Bat
cmake .. -G "Visual Studio 15 2017 Win64"
MSBuild.exe Project.sln -property:Configuration=Debug
pause
