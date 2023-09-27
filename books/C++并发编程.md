# C++并发编程

## 线程管控

传入线程的参数，一般都会以右值的形式，也就是会拷贝一份进行传入参数，如果函数中是`no-const-reference`，就会出现报错，这时候就需要`std::ref()`参数进行保证引用。这里其实是一个包装类，进行封装了
注意，传入指针的时候，有可能会导致悬垂引用，这时候一定要划分粒度，将其拷贝一份，比如直接传入一个 char* 的 buff,这时候buff就有可能因为析构导致寄了，但是还没有进入线程中进行赋值，所以这里更加推荐使用`std::string(buff)`这样进行初始化。

```c++
#include <iostream>
#include <thread>

int a = 0;
int b = 1;
int c = 2;

void do_something(int& a,int& b, int& c)
{
    a++;
    b++;
    c++;
}
int main()
{
    std::thread t1(do_something, std::ref(a), std::ref(b), std::ref(c)); 
    t1.join();
    std::cout << a << ' ' << b << ' ' << c << std::endl; // 1 2 3
}
```

如果要调用类或者结构体的函数，那么要传递多个参数,实现线程池的地方有写到

```c++
#include <iostream>
#include <thread>

class Node
{
public:
    void do_something() { std::cout << "yes" << std::endl; }
} temp;

int main()
{   // 当于传入一个参数，这个参数是函数的自己，我学过哦~，还是看过深入探索c++对象模型的
    std::thread t1(&Node::do_something, temp); // yes
}
```

## 防止死锁

1. 避免嵌套锁，
   1. 尤其是那种一个类中使用多少个函数，如果多个函数共同要抢夺一把锁，那么要避免嵌套。
2. 持有锁之后，避免调用由用户提供的程序接口
3. 固定顺序获取锁
   1. 选择`std::scoped_lock<std::mutex, std::mutex> lock { m1, m2 }`,scooped_lock来同时获取锁
   2. 按照地址的高低来获取锁，避免一个抢A，一个抢B
   3.