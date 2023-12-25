# redis

多个客户端和服务端，客户端发送TCP请求，发送给服务端，然后服务端进行请求

## 数据结构

### 哈希表

链式哈希表和开放寻址哈希表，这里使用的是链式哈希表，实现在相关库里面 

### 侵入时数据结构

平常的数据结构是非侵入式数据结构

```c++
template<typename T>
struct ListNode {
    ListNode* prev;
    ListNode* next;
    T value;
}
```

侵入时的数据结构是这样的，`对象的内部状态由外部对象管理`

```c++
struct ListNode {
    ListNode* prev;
    ListNode* next;
}

template<typename T>
struct Data {
    ListNode list;
    T value;
}
```

每一个节点都包含指向下一节点的指针，并且连接关系由节点本身来决定，在访问链表的时候，客户端必须要入侵到数据结构内部的对象里面才能管理对象。

### 序列化

将对象序列化成一个个的字节序，然后将字节序通过网络传输传输到另一个网络上，之后再进行反序列化，解析到正确的数据。
类型-长度-值 （什么类型的，长度是多少，值是多少）
