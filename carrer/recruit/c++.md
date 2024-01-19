# c++ 面经

## 基础知识

### 一句话总结多态的概念

为不同的数据类型提供一个统一的数据接口。（用统一的符号来表示多个不同的类型）

### 结构体对齐讲一讲？然后int double int是多大？(24) (结构体对齐的规则有两条)

cpu读取的时候按照4k的粒度进行读取，所以结构体对齐的时候不是按照正常的排列进行的。  

对齐规则

  1. 自身对其的整数倍数的大小上，
  2. 考虑多个数组同时出现的时候，后面的也要进行考虑

### 什么时候是万能引用，什么时候是右值引用？

都是`&&`,但是还是有不同

1. 如果有类型推倒，那么才会有万能引用（universal references）
2. 如果吗没有类型推倒，那么就不是万能引用。

带入到代码中，就是 `模板`和`auto`有类型推倒  
并且必须是：`auto&&` 和 `f(T&& val)`的形式

```c++
#include <iostream>
struct Node {
    int a;
    double b;
    double c;
};
int main() {
    Node a = { 1, 2, 3 };
    Node&& b = std::move(a); // 右值引用 -> 右值
    auto&& c = a; // 万能引用 ->  左值
    auto&& d = std::move(a); // 万能引用 -> 右值
}
```

### 什么是万能引用？引用折叠是什么？完美转发是什么，参数是左值还是右值？

- `std::move()`和`std::forward<T>()`仅仅是将将其进行左值变成右值，但是并没有进行移动。参数永远是左值。
- 并且这个T是`类型&`这样才会起作用，因为推导的时候`<typename T>`中的T遇见左值是不同的，会推导出带有引用的类型

### C++三种继承？ ： 就是 public protected private, private 可以用空基类优化？(protected可以避免将子类变成父类传参?，然后可以配合空基类优化)

`请使用public`进行继承，EBO可以节省一些空间。

### new一个对象在多线程的情况下是安全的么？new(delete)的底层是什么？

1. 调用 `operator() new`进行构造一个空的地方
2. 调用构造函数进行赋值
3. 指针传给调用者

析构函数是反过来的

### 单例模式？

[更好的单例模式](https://zhuanlan.zhihu.com/p/651173499)

- 在c++中，单例模式其实就是全局变量呗，在其他语言中，不能使用全局

### 智能指针是线程安全的么？为什么更推荐使用make_unique/shared() ?

是线程安全的。
C++并没有规定函数调用的时候，参数的访问求值等顺序，这个是未定义的，编译器可以随便进行优化
如何使用`new T`的形式进行初始化，那么就有可能出现内存泄漏
这两个函数可以保证使用前就可以将内存分配等隐藏在这个函数里面，就不会发生内存泄漏了qwq.

### namespace {} 这样是干什么的 (就是没有名字的namespace)

相当于在本作用域里面使用，每一个都加上了`static`关键字

### 虚函数存放在哪里？虚函数表存放在哪里？（elf文件里面想）

函数的东西肯定是放在了`.text`里面，然后虚函数表是放在了`.rodata`里面

### 虚函数表是在什么时候生成的? (编译期？运行期？)

编译期，直接生成在`.rodata`段里面。

### 构造函数为什么不能是虚函数？

[知乎](https://www.zhihu.com/question/35632207)  

虚函数调用的时候只要知道部分信息，但是构造函数调用的时候需要尽可能知道所有的信息，很显然是悖论。 

### shared_ptr也有什么样的缺点（延长生命周期方面）

如果很多指针在多个`std::shared_ptr`里面，那么这个对象就不会发生析构，导致内存增大。

### 什么是RAII

`资源获取即初始化`  
每一个明确的资源配置动作（new）都应该在`单一语句`中执行，并且立即将获得的资源交给handle对象(智能指针)

### 指针和引用有什么区别？类中可以直接使用引用么？推荐使用？ 什么时候用指针，什么时候用引用 ？（延迟初始化）

指针是指针，引用是引用，引用相当于起别名，类中不推荐使用引用，因为引用相当于起别名，要直接进行初始化，不如指针。  

### TCP连接的时候什么时候才会触发三次握手？

### C++中四种cast是什么?

- dynamic_cast 转换失败会干什么？ 两种情况？ 依赖与什么？有性能损耗么？和static_cast有什么区别？
  - 对于引用和指针有不同的情况，因为引用不不能为空，所以这时候抛出去的是异常，指针则是`nullptr`,
  - 派生类转向基类的时候，`static_cast`和`dynamic_cast`都安全
  - 但是返的话，那么`dynamic_cast`比较安全。
  - 运行期间进行转换，上行转化是安全的，但是下行转化`dynamic_cast`就比较安全，因为会返回 nullptr
- const_cast
  - 不是很懂
- static_cast
  - 用于像c一样的隐藏转换。
  - 不能转换掉cv运算符
  - 在编译期就可以直接转换了
- reinterpret_cast
  - 二进制直接转换，没用过
  
### C++ STL 中的数据结构的底层都是什么？

- vector
  - 底层: 数组
- deque
  - 底层: 数个缓冲区相接，由一个中央控制器管理
- 关联容器
  - 底层: 均是红黑树
  - eg: set, map, multimap, multiset
  - 迭代器kv结构是 std::map<const k, v>这样的结构
    - 所以说要在遍历的时候要使用`auto&`或者将const补全，否则会进行复制，产生额外的开销
- 无序关联容器
  - 底层:均为哈希表
  - eg: unordered_map, unordered_set, unordered_multiset, unordered_multimap
- stack, deque
  - 底层: deque
- priority_queue
  - 底层: vector

### sizeof运算符是什么阶段生效的，里面的函数会发生实际作用吗？

注意：sizeof就像+号一样是运算符，是在编译期就能算出来的，里面的函数不会执行。

### std::move(a),这样会发生一个移动么？实际上发生了什么？

上面有，仅仅是将一个值类别转换成一个右值，并不会发生移动，移动是移动构造的时候才会发生移动
`std::move`并没有移动，`std::forward<T>()`也不一定完美

### 为什么单例模式需要通过静态函数创建实例 不能直接一个全局变量或者全部静态方法静态变量？ （链接顺序，已经初始化，空间占用）

对于不同编译单元的全局变量的初始化C++并没有进行规定，所以这个是UB,推荐使用函数的方式进行初始化

```c++
void get_some() {
  if (!ptr) {
    ptr = new ptr();
  }
  return ptr;
}
```

### 为什么链接的时候需要保证初始化顺序（在操作系统里面有写到）

越低级的库应该放在越后面进行链接，减少编译的大小和时间。（算是遗留下来的问题吧）

### std::enable_shared_from_this是干什么的？(在tiny_rpc项目里面写有)

注意：这个函数只能从一个`std::shared_ptr`里面进行返回，否则直接寄

### 序列化和反序列化是什么？（可能在redis上进行实现）

序列化是将数据变成字节流在网络上进行传播
反序列化是将在网络上传播的字节流转化成数据

### 为什么这个模板不能直接转换？

```c++
#include <bits/stdc++.h>

template <typename T>
T BinarySearch(T l, T r, const std::function<bool(T)>& f) {
    while(l < r) {
        T mid = (l + r) >> 1;
        if (f(mid)) l = mid + 1;
        else r= mid;
    }
    return l;
}

int main() {
    int n, x;
    std::cin >> n >> x;
    int pos = BinarySearch(1, n, [&](int y) {
        return y > x;
    }); // wrong

    int pos = BinarySearch<int>(1, n, [&](int y) {
        return y > x;
    }); // right
    
    std::cout << pos << std::endl;
}
```

lambda是lambda, std::function 是 std::function,两者之间是完全不同的东西，一般用的时候只是将lambda绑定到到了一个std::function上了，但是这两个之间是不能相互转换的。

lambda相当于一个匿名函数，大致相当于一个struct/class的一个operator()

```c++
auto foo = [](int i) {
    std::cout << i << std::endl;
};

struct __anonymous__type__you__cannot__name__ {
  void operator()(int i) { 
    std::cout << i << std::endl;
  }
};

__anonymous__type__you__cannot__name__ foo;

foo();
```

因此这两个是完全不相干的东西，lambda不会推断`std::function`的模板参数，不会尝试任何形式的转换。

### 为什么要用varint代替union

union不允许内部含有非POD对象，但是variant却可以，因为union不能保证调用正确的析构函数，会导致错误。

### noexpect关键字一般在哪一个地方使用？

参考这个例子

```c++
// 如果将 noexpect去掉的话，那么下面的emplace_back()就不会调用 移动构造函数。
class A {
public:
    A(int) { cout << "A(int)" << endl; }
    A(const A&) { cout << "A(const A&)" << endl; }
    A(const A&&) noexcept { cout << "A(const A&&)" << endl; }
    ~A() { cout << "~S()" << endl; }
};
int main() {
    vector<A> a;
    cout << a.capacity() << endl;
    a.emplace_back(1);
    cout << a.capacity() << endl;
    a.emplace_back(2);
    cout << a.capacity() << endl;
    return 0;
}
```

般情况下，移动构造函数与移动赋值函数均应手动添加 noexcept 声明，原因在于 vector 等有强异常安全保证的 STL 容器面对移动构造函数不是 noexcept 的情况会优先考虑使用复制构造函数。也就是说，不加 noexcept，很多情况下移动构造等于白写。

`强异常安全`：即使发生了内存泄漏，也不会产生任何的副作用。

### 有关static关键字的作用？用法，注意点？

- static修饰的变量初始化完成之后，在整个程序运行期间内存都不会释放。
- 像局部静态变量在初始化的时候，会初始化出数值，等到再次调用的时候，不会再次初始化，保留了最后一次函数调用的数值
- 静态局部变量和普通全局变量以及静态全局变量在编译器的时候就会分配地址
- 静态变量存储在数据段和.bss段，c语言因为是平凡类型，在编译期就初始化了，但是c++因为引入了对象，要调用构造函数才能初始化，c++规定全局或或者静态对象当且仅当对象首次调用时候才会进行构造。
- c++只规定了全局变量会在`main`函数之前就初始化完毕，但是之前的全局变量并没有进行相关的规定,执行顺序是UB的。

### STL中迭代器什么时候会失效？

想象一下，迭代器就像一个指针在~内存~上进行进行游走，那么如果你在遍历的时候，加入了一些元素，或者删除一些元素（导致内存变化）就有可能出现迭代器失效，导致直接爆炸的例子。

1. 内存变化，导致迭代器失效，插入，删除等
2. 删除迭代器，这个指针没了，所以迭代器就失效了

### 什么是复杂均衡

问了一下，nginx可以进行反向代理，访问一个端口，可以进行端口转发，那么多个人群如果要访问同一个服务器的话，nginx就可以进行将这些流量转发到后面的服务器里面，避免其他人员进行Ddos攻击等，如果流量比较多，就需要要将流量分到各个服务器，进行负载均衡

### 浮点数存储原理

- 哎，考机组考了，这个是IEEE 754的相关存储方式，浮点数都基本上是使用这个进行计算的
- 考虑32位浮点数，就是1位表示正负数，8位表示阶码，其他位数表示数字，然后加上偏移量等计算出这个数字

## 设计模式

- 什么是生产者-消费者模式

### 返回 T&& 和 std::move() 都有什么危害？

- return T&& 是返回了一个右值的悬垂引用，那么当这个右值直接消失的话，那么就造成了悬垂引用了
- std::move() 是因为RVO(返回值优化) 可能是劣化，还不是优化

## shared_ptr是如何实现的，并且和weak_ptr的关系？

- shared_ptr中是有一个指针的，里面存放的是两个引用常量，一个shared_ptr的，一个weak_ptr弱引用的数量，两个都为空，才会`真正地`释放资源。
- shared_ptr如何和weak_ptr都指向同一个资源的时候，共享的是同一个资源块，然后那个资源块，当weak_ptr全部寄了之后才会释放。
- 因为weak_ptr会进行提权，就是lock()进行提权，所以说等到全部寄了，才会真正的释放

