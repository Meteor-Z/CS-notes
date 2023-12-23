# CRTP

实现编译器多态的。

- `Curiously Recurring Template Pattern`,通过将子类类型作为参数,传递给基类模板,可以实现编译期多态.
- 因为模板会根据<>里面的内容进行初始化,编译出很多类型的代码,那么我们就可以使用这个特性,来进行编译期的多态
- 如果说在运行期间的多态,那么会查找虚函数表,会浪费时间,但是编译期多态就不会进行查表,节约时间.

```c++
#include <iostream>

struct Base {
    virtual void foo() = 0;
    virtual ~Base(){}
};

struct A : public Base {
    void foo() {
        std::cout << "A Derived" << std::endl;
    }
};

struct B : public Base {
    void foo() {
        std::cout << "B Derived" << std::endl;
    }
};

int main() {
    Base* derived_a = new A();
    Base* derived_b = new B();
    derived_a->foo();
    derived_b->foo();
    delete derived_a;
    delete derived_b;
}
```

这里发生了多态,而且是运行期多态,会进行虚函数查表,运行效率比较低,通过CTRP,可以实现编译期的多态

```c++
#include <iostream>

template <typename T>
struct Base {
    void foo() {
        T& derived = static_cast<T&>(*this);
        derived.foo();
    }
};

struct A : Base<A> {
    void foo() {
        std::cout << "Derived A" << std::endl;
    }
};

struct B : Base<B> {
    void foo() {
        std::cout << "Derived B" << std::endl;
    }
};

int main() {
    Base<A>* p1 = new A{};
    p1->foo();
    Base<B>* p2 = new B{};
    p2->foo();
    delete p2;
    p2 = new B();
    p2->foo();
    delete p1;
    delete p2;
}
```

这里只需要进行一个`static_cast`转换，就可以使用了。
