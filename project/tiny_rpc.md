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

安装:

```shell
git clone https://github.com/fmtlib/fmt.git
cd fmt
mkdir build
cmake ..
make 
sudo make install # 将头文件和链接文件放在/usr/local/include 或者 /usr/local/lib/
```

使用

```shell
g++ main.cpp /usr/local/lib/libfmt.a # 这样就可以链接成功了
```

1. 配合cmake使用

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

这里相关的信息可以直接使用C++20的`std::soruce_location`,通过设置缺省值来获得

### 日志器

1. 提供输出日志的方法

## EventLoop

事件循环队列

## 定时器

对于一个调用，那么如果没有完成，还要处理其他的任务

1. 指定的时间点 arrive_time (其实就是一个时间戳)
2. interval, ms 间隔
3. is_repeated 是否是一个重复性的任务
4. is_cancel : 取消
5. task

### 方法

`cancel()`
`cancel_repeated()`

## Timer

定时器: 是一个TimerEvent的集合
Timer继承自FdEvent

```c++
add_time_event(); 
delete_time_event();
on_time() // 当发任务的时候，要转型的方法
```

## IO线程

IO线程能帮助我们干什么

1. 创建一个新线程
2. 在新线程中创建一个EventLoop, 完成初始化
3. 开启loop

## TcpBuffer

- 方便处理数据，特别是应用层的包组装而后拆解
- 方便异步的发送（塞到缓冲区里面，等待epoll异步发送）
- 提高发送效率，多个包一起发送

读到一般的数据，将数据放到一个缓冲区里面，然后再读取。

## 遇到的问题

### 队列未锁导致多次 pop

```c++
    // std::lock_guard<std::mutex> guard { mtx }; 应加上这句代码
    while (!m_buffer.empty()) {
            std::cout << m_buffer.front() << std::endl;
            m_buffer.pop();
        }
```

原本这样的代码如果多个线程同时同时争抢这个资源的话,就会发生多次pop导致段错误.使用`valgrind --tool=memcheck --leak-check=full  ./a.out`诊断出来的问题

### 多次锁住同一把锁，导致锁死

代码就是函数调用的时候，一层函数用了std::mutex，第二层函数也用std::mutex,直接就寄了。

### cmake链接的时候因为链接顺序导致出错

妈的，这错误太简单了，但是因为这个简单错误，导致找了最起码3小时错误。。

```cmake
target_link_libraries(io_thread_test PRIVATE io_thread_libs)
target_link_libraries(io_thread_test PRIVATE ${TINYXML})
target_link_libraries(io_thread_test PRIVATE ${LIBFMT})
```

`越基础的库应该越放在后面`，具体的可以看操作系统中关于链接的定义。如果上面的因为链接的顺序颠倒，就直接寄了。。 

### shared_from_this的问题

构造的时候，乱用 shared_from_this()导致 导致寄寄寄。
对于一下的代码就是错误的。

```c++
#include <memory>
#include <iostream>

class Node {
public:
    Node() { std::cout << "Widget constructor run" << std::endl; }
    ~Node() { std::cout << "Widget destructor run" << std::endl; }
    std::shared_ptr<Node> get_shared_object() { return std::shared_ptr<Node>(this); }
};

int main() {
    std::shared_ptr<Node> a = std::make_shared<Node>();
    std::shared_ptr<Node> b = a->get_shared_object();

    std::cout << a.use_count() << std::endl;
    std::cout << b.use_count() << std::endl;
    return 0;
}
```

上面的代码就是错误的代码，需要使用`std::shared_from_this()`。

可以看出

1. 智能共享指针不能够直接从this对象进行构造（这个太重要了）
2. 只允许在shared_ptr所管理的对象上调用shared_from_this()

```c++
#include <memory>

struct Node: public std::enable_shared_from_this<Node> { };

int main() {
    std::shared_ptr<Node> a = std::make_shared<Node>();
    std::shared_ptr<Node> b = a.share_+from_this();
    return 0;
}
```

那我直接调用构造的有什么区别呢？
