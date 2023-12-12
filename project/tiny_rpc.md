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

## TcpConnection

read() -> excute() -> write() -> read() ->exute() -> write() ....

read():读取客户端的请求,组装称rpc请求
excute():将rpc请求入参数,执行业务逻辑得到rpc响应
write():将RPC相应发送到客户端。

### InBuffer

服务端调用read成功从socket缓冲区读数据,然后学入到InBuffer里面
服务端从InBuffer前面读取数据,进行解码得到请求.

### OutBuffer

服务端向发送数据,会将数据编码之后放入到OutBuffer后面
服务端在fd可用的情况下,调用write将OutBuffer里面的数据全部发送出去.

上述的都是从Buffer上构建的.

## TcpClient

connect() -> write() -> read()

connect(): 连接对端机器  
write(): 将rpc相应发送给客户端  
read(): 读取客户端发来的请求，组成rpc请求

### 非堵塞 connect

- 返回0, 表示连接成功
- 返回 -1, 但是 errno == EINPROGRESS, ，表示连接正在建立，可以添加 epoll 去监听可写事件，等待时间就绪之后，调用 getsockopt获取fd的错误，错误为0就表示连接建立成功。
- 其他errno就是直接报错

## protobuf的问题

将信息转化成二进制数据在网络中传输，但是还要自定义协议格式，因为数据在Tcp传输上是面向字节的，所以需要设计一个协议。

## 字节序

使用大端存储（网络序）

开始符 - 整包长度（四字节，包含开始符和结束符） - reqid长度 - reqid - 方法名长度 - 方法名 - 错误码 - 错误信息长度 - 错误信息 - protobuf序列化数据 - 校验码（我觉得应该使用md5）- 结束符

## 分发器

read() -> decode() -> dispatcher() -> encode() -> wirte()

dispatcher() 是分发器，将请求的东西进行分发

```protubuf
service OrderService {
    rpc make_order(makeOrderRequest) returns (OrderResponse);
    rpc query_order(queryOrderRequest) returns (queryOrderResponse);
}
```

### RPC服务端的流程（从protubuf中读取数据）

1. 注册一个 OrderService 对象
2. 从OrderService 对象中得到 service.method_name， 根据这个name，从中 找到方法   func
3. 找到对应的 request type 以及 response type
4. 将请求体李米娜 pb_data 反序列化为 request type 对象，声明一个空的 response type 的对象
5. func(request, response)
6. 将 response 对象序列化成 pb_data, 做encode 然后塞入buffer里面，就会发送回包了。

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
    std::shared_ptr<Node> b = a.share_from_this();
    return 0;
}
```

那我直接调用构造的有什么区别呢？

### 程序有时候非正常断开，绑定了同一个端口，但是重启，我的端口还是占用，这是怎么回事？

端口处于`time_wait`状态, 就是计网里面四次挥手的最后`Time_wait`，linux上大约是是2个msl,也就是2 * 30 ms = 1min 的时间，处于这个状态，于是就不能连接了。
