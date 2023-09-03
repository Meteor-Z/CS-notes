# tiny_rpc


## 安装依赖

一个项目有头文件和具体的函数实现来决定，其中如果可以使用包管理安装的话，

- 头文件：`/usr/include/`下
- 库文件：`/usr/lib/`下

如果是自己安装的话，建议放在

- 头文件： `/usr/local/include/`下
- 库文件： `/usr/local/lib/`下

以上文件目录都已经在环境变量中了，所以可以直接使用，具体库文件是否可以直接链接，对于标准库，不需要手动链接，但是对于非标准库的链接，则需要手动连接，一下是`fmt`库的下载和使用

### fmt库的安装使用

1. 安装
```shell
git clone https://github.com/fmtlib/fmt.git
cd fmt
mkdir build
cmake ..
make 
sudo make install # 将头文件和链接文件放在/usr/local/include 或者 /usr/local/lib/
```
2. 使用
```shell
g++ main.cpp /usr/local/lib/libfmt.a # 这样就可以链接成功了
```
3. 配合cmake使用

```cmake
cmake_minimum_required(VERSION 3.22.1)

project(test_c++)

add_executable(test_c++ main.cpp)

target_link_libraries(test_c++ "/usr/local/lib/libfmt.a")
```


## 日志

要实现的功能

1. 日志级别
2. 打印到文件中，日期命名，日志滚动
3. c/c++风格希望都能全部支持
4. 线程是安全的

### 日志级别

1. Debug
2. Info
3. Error

### 日志内容

1. 文件名称
2. 行号
3. 序列号
4. 进程号 线程号
5. 时间，日期 (要精确到毫秒)
6. 自定义消息

日志格式
```c++
// 最终结果大概是这样的形势:[INFO][2023年9月3日16时21分37秒][文件名:/home/lzc/test_c++/main.cpp 行号 10]
```

2. 设置日志输出的路径
### 日志器

1. 提供输出日志的方法