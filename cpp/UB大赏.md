# UB大赏

## 有符号整型溢出是UB，无符号整型不是UB

这里代码就会因为UB,导致无限循环

```c++
void test() {
    for (int i = 3; i > 2; i++) {
        cnt++;
    }
    std::cout << cnt << std::endl;
}
```

## 局部变量没有初始化，导致UB

```c++
void test() {
 int a;
if (a)
	a = 0;
}
```
没有初始化，就是ub，导致错误。


