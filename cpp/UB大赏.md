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

