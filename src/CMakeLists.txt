

# 子项目处理头文件，添加头文件搜索路径，，或者在父级CMakeLists.txt链接头文件（用target_include_directories）(一般是include)
# include_directories("/home/zzy/Desktop/zzy_stduy/my_project_test1/3rdparty/hello/lib")

# 子项目处理/链接文件，链接库文件，，或者在父级CMakeLists.txt链接库文件（用target_link_libraries）
# link_libraries("/home/zzy/Desktop/zzy_stduy/my_project_test1/3rdparty/hello/lib")

# opencv头文件搜索路径
include_directories("/home/zzy/Desktop/zzy_stduy/my_project_test1/3rdparty/opencv/include/opencv4/") 
# gtest头文件搜索路径
include_directories("/home/zzy/Desktop/zzy_stduy/my_project_test1/3rdparty/googletest/googletest/include")
# 该项头文件搜索路径
include_directories("/home/zzy/Desktop/zzy_stduy/my_project_test1/include")


# 链接opencv库文件
find_package(OpenCV REQUIRED)
link_libraries(${OpenCV_LIBS})

# 链接gtest库文件，及其所需的线程库
file(GLOB gtestlib ../3rdparty/googletest/lib/*)
link_libraries(${gtestlib} pthread)


file(GLOB_RECURSE srcs CONFIGURE_DEPENDS ./*.cpp ../include/*.h)
message("111111111111111 ${srcs}")
add_executable(hello ${srcs})

