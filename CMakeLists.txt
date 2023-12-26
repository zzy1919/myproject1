
set(CMAKE_CXX_STANDARD 14)

# project(HELLO)
# 设置允许链接未在当前目录的项目
cmake_policy(SET CMP0079 NEW)


add_subdirectory(src bin) # 关联子目录的src的CMakeList.txt ,生产的可执行文件放到bin目录（不存在会自动生成）

# 查找hello静态库文件
file(GLOB hello_a 3rdparty/hello/lib/*.a)
# 查找hello动态库文件
file(GLOB hello_so 3rdparty/hello/lib/*.so)

# 链接/处理 头文件
target_include_directories(hello PUBLIC "/home/zzy/Desktop/zzy_stduy/my_project_test1/3rdparty/hello/lib")

# target_include_directories(hello PUBLIC "/home/zzy/Desktop/zzy_stduy/my_project_test1/3rdparty/googletest/googletest/include")

# 链接/处理 库文件（静态库、动态库）
target_link_libraries(hello ${hello_a} ${hello_so})

