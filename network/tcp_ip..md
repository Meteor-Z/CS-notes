# TCP_IP

所有代码基本上都是在`Arch Linux`上运行，并且使用的版本是`gcc 13.1`最新版本。

## 客户端和服务端

对于服务端 编译命令 `g++ server.cpp -o server -std=c++23`
```c++
#include <cstring>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <format>
#include <unistd.h>

void error_handing(const std::string& err_message)
{
    std::cout << err_message << std::endl;
    exit(1);
}
int main(int argc, char* argv[]) 
{
    // C++ style 一定要保证初始化为0
    int server_sock {0};
    int client_sock {0};
    
    sockaddr_in server_addr {0};
    sockaddr_in client_addr {0};
    socklen_t client_addr_size {0};

    std::string message = "Hello World!";
    if (argc != 2) 
    {
        std::cout << std::format("Usage : {} <port>\n", argv[0]);
        exit(1);
    }
    
    server_sock = socket(PF_INET, SOCK_STREAM, 0); // 创建一个套接字， 表示使用的这个协议
    if (server_sock == -1) 
    {
        error_handing("socker() error");      
    }
    

    // 设置这个服务器的端口号和使用的协议
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));

    if (bind(server_sock, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) // 分配ip地址和端口号
    {
        error_handing("bind() error");
    }

    if (listen(server_sock, 5) == -1)
    {
        error_handing("listen() error");
    }
    
    client_addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (sockaddr*)&client_addr, &client_addr_size); // 返回接收过来的信息
    
    if (client_sock == -1) 
    {
        error_handing("accept_error");
    }
    write(client_sock, message.c_str(), sizeof(message));
    std::cout << "信息已经发送！" << std::endl;
    
    close(client_sock);
    close(server_sock);

    return 0;
}
```

对于客户端

```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <format>

void err_handing(const std::string& message) 
{
    std::cout << message << std::endl;
    exit(1);
}

int main(int argc, char* argv[]) 
{
    // c++ style 风格
    int sock = {0};
    sockaddr_in server_addr = {0};
    int str_len = {0};
    char message[30] = {0};
    if (argc != 3)
    {
        std::cout << std::format("Usage : {} <IP>  <port>\n", argv[0]);
        exit(1);
    }
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)   
    {
        err_handing("socket_ error");
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));
    
    if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) 
    {
        err_handing("connect() error");
    }
    str_len = read(sock, message, sizeof(message) -1 );

    if (str_len == -1) 
    {
        err_handing("read() error");
    }
    std::cout << message << std::endl;
    std::cout << std::format("Message, from server {} \n", message) << std::endl;
    close(sock);
    return 0;
    
} 
```


`linux`平台上和`windows`平台上，没有进行统一,`std::net`在`C++26` 或者`C++29` 才会加入到标准库里面，我哭死。

文件句柄/描述符：是为了称呼操作系统所创建的文件或者套接字罢了。

不过`c++` 在文件上还会做到了统一，不需要进行底层处理。

## 套接字类型和协议设置

一般采用`IPV4`这个协议。当然还有`IPV6`，不过还是建议用`IPV4`这个协议吧 （4字节协议），IPV6(16字节协议)

对于`UDP`或者`TCP`，网络现在很好，基本上都使用`TCP`.


## 地址与数据序列

不是很懂网络地址分类，这个A类，B类，C类，

端口号区别应用程序，一般是`0~65536`,`0~1023`是分配到知名应用端口，有特定的用处，`TCP`和`UDP`可以公用一个端口号。


`struct sockaddr_in`就是保存这些信息的，（IP地址+端口号）

### 网络字节序与地址变换

在`csapp`上可以知道，对于一个32位的整数来说，一个数字1 可以有两种表示方法，大端法和小端法。
咱们用的就是大端法。 网络序列-> 大端序

```in
00000000 00000000 00000000 00000001
00000001 00000000 00000000 00000000
```

```c++
#include <iostream>
#include <arpa/inet.h>

int main()
{
    unsigned short host_port = 0x1234;
    unsigned short net_port = htons(host_port);
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr = htonl(host_addr);

    printf("%#x \n",host_port);
    printf("%#x \n",net_port);
    printf("%#lx \n",host_addr);
    printf("%#lx \n",net_addr);
}
```

会发生转化，在一些机子上不会发生改变。