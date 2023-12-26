
project(HELLO)

# 设置目录文件为SOURCES变量
set(SOURCES ./lib/hello.cpp ./lib/hello.h)

# 生成静态库helloa
add_library(helloa STATIC ${SOURCES})
# 修改静态库名称为hello
set_target_properties(helloa PROPERTIES OUTPUT_NAME "hello")
# 防止清理hello
set_target_properties(helloa PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# 生成静态库helloso
add_library(helloso SHARED ${SOURCES})
# 修改静态库名称为hello
set_target_properties(helloso PROPERTIES OUTPUT_NAME "hello")
# 防止清理hello
set_target_properties(helloso PROPERTIES CLEAN_DIRECT_OUTPUT 1)



# add_executable(hello main.cpp)


