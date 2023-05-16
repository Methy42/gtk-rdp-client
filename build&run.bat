@echo off

REM 删除当前目录中的build目录
rmdir /s /q build

REM 创建一个新的build目录并进入
mkdir build && cd build

REM 设置PKG_CONFIG_PATH环境变量，以便CMake能够找到librdkafka的配置文件
set PKG_CONFIG_PATH=C:\msys64\mingw64\include\;C:\msys64\mingw64\lib\;C:\msys64\share\;C:\msys64\mingw64\share\pkgconfig\;C:\msys64\mingw64\lib\pkgconfig;%PKG_CONFIG_PATH%

REM 使用CMake生成Visual Studio工程文件
cmake -G "Visual Studio 17 2022" ..

REM 使用MSBuild编译程序
msbuild ALL_BUILD.vcxproj /p:Configuration=Release

REM 运行程序
rdp-client.exe

cd ..