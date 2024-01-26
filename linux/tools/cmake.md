# cmake

```cmake
cmake_minimum_required(VERSION 3.0)  // 要求的版本
project(cpp_study) # 项目名称

set(CMAKE_CXX_STANDARD 20) # cpp 标准

add_library(hello_lib STATIC b.cpp) # 生成一个静态库，然后这个静态库是b.cpp生成的，其实就是.o文件
add_executable(main.out main.cpp a.cpp) # 由 main.cpp 和 a.cpp 生成呢个一个main.out文件

target_link_libraries(main.out hello_lib) # 将生成的 main.out 和这个静态库进行链接
target_link_libraries(tiny_rpc "/usr/local/lib/libfmt.a") # 也可以这样直接链接 libfmt.a

set(CMAKE_CXX_FLAGS "-g") # 可以添加cpp编译选项 这里好像是不可以添加链接的

# 这个意思是在后面这个路径中寻找libtinyxml,注意，这里一定是libtinyxml 是找那个带lib的
find_library(TINYXML tinyxml ${CMAKE_SOURCE_DIR}/third_party/lib/tinyxml)

```

如果是添加一个动态库，那么如果将那个生成的`.so`文件删除掉，那么那个代码就执行不下去了，跟 windows 上缺少
dll 文件不能执行是一样的道理。(windows 上推荐一定要安装 msvc 运行库哦～)

`#include "xxx"`和 `#include <xxx>` 这样的`“”`这样的优先从本目录中可以找，如果找不到，在linux上是从`/usr/include/`这里面开始找，而`<>`只在`/usr/include`中找，不会在本目录中开始找。

## 多目录

很多地方需要父子目录进行协调工作，这时候需要父cmake和子cmake

### 父camke

```cmake
cmake_minimum_required(VERSION 3.22.1)

project(tiny_rpc)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory(test/io_thread_test) # 这个就是加入子目录，其他的不是关键
```

### 子目录

```camke
add_executable(io_thread_test test_io_thread_group.cpp)

include_directories(${CMAKE_SOURCE_DIR}/src/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/include)

# 找到这个库，然后直接安装就行了
find_library(LIBFMT fmt /usr/local/lib)
find_library(TINYXML tinyxml ${CMAKE_SOURCE_DIR}/third_party/lib/tinyxml)

if (LIBFMT)
    message(STATUS "找到了这个库 libfmt: ${LIBFMT}")
else ()
    message(FATAL_ERROR "libfmt not found")
endif ()

if (TINYXML)
    message(STATUS "找到了这个库: ${TINYXML}")
else ()
    message(FATAL_ERROR "这个库没有找到")
endif ()

add_library(io_thread_libs STATIC
    ${CMAKE_SOURCE_DIR}/src/common/config.cpp
    ${CMAKE_SOURCE_DIR}/src/common/log.cpp
    ${CMAKE_SOURCE_DIR}/src/common/utils.cpp
    ${CMAKE_SOURCE_DIR}/src/net/time/time_event.cpp
    ${CMAKE_SOURCE_DIR}/src/net/time/timer.cpp
    ${CMAKE_SOURCE_DIR}/src/net/eventloop.cpp
    ${CMAKE_SOURCE_DIR}/src/net/fd_event.cpp
    ${CMAKE_SOURCE_DIR}/src/net/wakeup_fd_event.cpp
    ${CMAKE_SOURCE_DIR}/src/net/io_thread/io_thread.cpp
    ${CMAKE_SOURCE_DIR}/src/net/io_thread/io_thread_group.cpp
    
)
target_link_libraries(io_thread_test    
    io_thread_libs
    ${TINYXML}
    ${LIBFMT}
    ou 
)

add_test(NAME test COMMAND io_thread_test)
```
## 系统预安装

find_package是系统中预安装的库，是cmake中给你定义好的东西，但是你本地还是要有相关的头文件，应该是这样子的qwq

## 注意事项

- 在链接的时候要格外注意一定要按照顺序进行连接，就是没有依赖的往前面链接，有依赖的往后面链接，否则就会寄了！！
  - 这里如果一个程序依赖A库B库，同时A需要B，那么应该这样写`target_link_libraries(project B A)`,
- 一定要多打日志，就是message()的信息日志
