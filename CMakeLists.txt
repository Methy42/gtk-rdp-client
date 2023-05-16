cmake_minimum_required(VERSION 3.0)
project(rdp_client)

# 用来配置pkgConfig找include的代码，可根据环境更改
set(PKG_CONFIG_PATH C:\\msys64\\mingw64\\include\\;C:\\msys64\\mingw64\\lib;C:\\msys64\\share;C:\\msys64\\mingw64\\share\\pkgconfig\\;C:\\msys64\\mingw64\\lib\\pkgconfig)
message("PKG_CONFIG_PATH: ${PKG_CONFIG_PATH}")

# 寻找gtk库
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# 设置头文件目录
include_directories(src/include)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

# 将源代码添加到可执行文件中
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp")
add_executable(rdp_client ${SOURCES})

# 链接gtk库
target_link_libraries(rdp_client ${GTK3_LIBRARIES} uv crypto ssl)

# 将 assets 目录中的所有文件添加到构建目标中
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})