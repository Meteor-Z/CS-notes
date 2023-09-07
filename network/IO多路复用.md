# IO多路复用

一个网络服务器如何要接收多个来自不同ip的请求，这时候可以开启很多的线程来接收这个请求，但是开辟线程的性能消耗是很大的，所以有了IO复用。

## select函数

- 将多个文件描述符集中在一起然后一起统一监视，select函数需要接收一个集合,表示有没有这个描述符，但是C没有`std::set`,于是就有一个fd_set数组来表示有没有这个文件描述符，如果有的话，设为1，如果没有的话，设置为0
- 同样，select函数是非堵塞/堵塞函数,主要看最后一个超出时间的失效性.

### 优点/缺点

- 优点：服务器介入者少, 程序具有兼容性。
- 缺点：每次调用之后都会对所有的文件描述符进行循环,性能肯定是不行的，每次还要将监控信息进行传来传去(传给os)，(这个是最耗费时间的)

如何将这个进行弥补呢？ -> epoll (仅向操作系统传递一次监视对象,监视范围或者内容变化只通知发生变化的事项。)

## epoll函数

1. 无需编写以监视状态为目的的针对所有文件描述符？
2. epoll_wait()函数不需要每次都传递监视对象信息

>现在epoll_create(int size);中的size已经可以完全忽略掉，操作系统会自行控制其例程

### 函数说明

```c++
int epoll_create(int size); // 创建一个epoll，存储在epoll例程中，返回的是一个 fd, 文件描述符
int epoll_ctl(int epfd, int op, int fd, struct epoll_event* event); // 在内部注册监视对象描述符
// epfd 是 epoll_create()创建的文件描述符, op 是对于这个对象是添加，还是删除
// fd是注册对象的文件描述符，event是监视对象的事件类型
// int 为返回值，成功就是0，失败就是-1
// eg
epoll_ctl(A, EPOLL_CTL_ADD, B, C); // 在A中注册B，主要监视参数C中的事件
epoll_ctl(A, EPOLL_CTL_DEL, B, nullptr); // 在 A 中删除 B

int epoll_wait(int efpd, struct epoll_event* events, int maxevents, int timeout);
// epf是epoll文件描述符， events是保存文件描述符结构体地址值， maxevents是保存的最大事件数， 后面是截止时间







```