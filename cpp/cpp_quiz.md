# cpp quiz

## 1

```c++
template <class T> void f(T &i) { std::cout << 1; }

template <> void f(const int &i) { std::cout << 2; }

int main() {
  int i = 42;
  f(i);
}
```

答案： 输出 1
这里进行了模板特化，但是int进行匹配的时候，优先考虑匹配最接近的，所以匹配的时候选择1

## 2

```c++
#include <iostream>
#include <string>

void f(const std::string &) { std::cout << 1; }

void f(const void *) { std::cout << 2; }

int main() {
  f("foo");
  const char *bar = "bar";
  f(bar);
}
```

答案：输出 22
虽然在调用的时候使用`const std::string&` 确实是可以将一个字符串字面量绑定到这个上面，但是根据字符串字面量其实是`const char []`, 更容易绑定到 `const void*`上，这样可以不需要转换，如果想要绑定到`const std::string&`，那么需要进行转换。

## 3

```c++
#include <iostream>

void f(int) { std::cout << 1; }
void f(unsigned) { std::cout << 2; }

int main() {
  f(-2.5);
}
```

答案 报错
double是不可以直接转换成int和unsigned的，需要强制类型转换，`浮点数无法自动转换为整数或无符号整数类型`

## 30

```c++
#include <iostream>
struct X {
  X() { std::cout << "X"; }
};

int main() { X x(); }
```

答案 无输出
`当一个东西能被看作一个声明或者一个定义的时候，优先看作成一个声明，所以这里`, 这里`X X();`的实际意义是声明一个函数，这个函数会返回类型为X的结构体。

## 32

```c++
#include <iostream>

struct X {
  X() { std::cout << "a"; }
  X(const X &x) { std::cout << "b"; }
  const X &operator=(const X &x) {
    std::cout << "c";
    return *this;
  }
};

int main() {
  X x; // 1
  X y(x); // 2
  X z = y; // 3
  z = x; // 4
}
```

答案： 输出 abbc
很简单，了解初始化和赋值就知道了。1 2 3 都是初始化，但是 1 是无参初始化,2 3 长得不一样，但是调用的都是`X (const X& x)`,4是赋值，调用的是 `operator =`.

## 163

