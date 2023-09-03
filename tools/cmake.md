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

```

如果是添加一个动态库，那么如果将那个生成的`.so`文件删除掉，那么那个代码就执行不下去了，跟 windows 上缺少
dll 文件不能执行是一样的道理。(windows 上推荐一定要安装 msvc 运行库哦～)

`#include "xxx"`和 `#include <xxx>` 这样的`“”`这样的优先从本目录中可以找，如果找不到，在linux上是从`/usr/include/`这里面开始找，而`<>`只在`/usr/include`中找，不会在本目录中开始找。


