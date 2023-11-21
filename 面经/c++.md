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

`std::move()`和`std::forward<T>()`仅仅是将将其进行左值变成右值，但是并没有进行移动。参数永远是左值。

### C++三种继承？ ： 就是 public protected private, private 可以用空基类优化？(protected可以避免将子类变成父类传参?，然后可以配合空基类优化)

`请使用public`进行继承，EBO可以节省一些空间。

### new一个对象在多线程的情况下是安全的么？new(delete)的底层是什么？

1. 调用 `operator() new`进行构造一个空的地方
2. 调用构造函数进行赋值
3. 指针传给调用者

析构函数是反过来的

### 单例模式？

[更好的单例模式](https://zhuanlan.zhihu.com/p/651173499)

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
- const_cast
  - 不是很懂
- static_cast
  - 用于像c一样的隐藏转换。
- reinterpret_cast
  - 二进制直接转换，没用过
  
### STL底层的数据结构都是什么数据结构？ 有序的和无序的都是什么？

- 对于有序，都是红黑树
- 对于无序，都是哈希表

### sizeof运算符是什么阶段生效的，里面的函数会发生实际作用吗？

注意：sizeof就像+号一样是运算符，是在编译期就能算出来的，里面的函数不会执行。

### std::move(a),这样会发生一个移动么？实际上发生了什么？

上面有，仅仅是将一个值类别转换成一个右值，并不会发生移动，移动是移动构造的时候才会发生移动
`std::move`并没有发生，`std::forward<T>()`也没有进行引用，

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

越低级的库应该放在约后面进行链接，减少编译的大小和时间。

### std::enable_shared_from_this是干什么的？(在tiny_rpc项目里面写有)

注意：这个函数只能从一个`std::shared_ptr`里面进行返回，否则直接寄

### 序列化和反序列化是什么？（可能在redis上进行实现）

TODO!

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
    }); // right 会进行匹配。（绑定到std::function上了）
    
    std::cout << pos << std::endl;
}
```

lambda是lambda, std::function 是 std::function,两者之间是完全不同的东西，一般运的时候只是将lambda绑定到到了一个std::function上了，但是这两个之间是不能相互转换的。

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

### 什么是复杂均衡

### 浮点数存储原理

### epoll的堵塞？

## 设计模式

- 什么是生产者-消费者模式
