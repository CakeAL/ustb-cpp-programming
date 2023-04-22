cmake_minimum_required(VERSION 3.23)
project(Cpp_Programming)

set(CMAKE_CXX_STANDARD 14)

#递归遍历所有的cpp文件
file (GLOB_RECURSE files *.cpp)
#将所有的cpp文件单独生成可执行文件
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    add_executable (${exe} ${file})
    message (\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()


#F:\programs\c_pro\Cpp_Programming\exercise5
