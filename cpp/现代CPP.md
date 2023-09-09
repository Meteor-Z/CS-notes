# 现代CPP 要点

这里是关于现代 C/C++ 的一些总结，仅作总结

## consteper-if

可以代替以前通过宏定义的形式来生成配置文件等。其所有的判断其实是编译期的时候就直接完成的。

```cpp
template<typename T>
auto get_val(T t)
{
    if constexpr (std::is_pointer_v<T>) return *t;
    else if constexpr (std::is_same_v<T, int>)
    {
        return std::string("hello");
    } else return t;
}

int main()
{
    std::cout << get_val(1) << std::endl;
    std::cout << get_val(new int(1)) << std::endl;
    return 0;
}
```

`std::is_pointer_v<T>，std::is_same_v<T,int>` 可以在编译期就可以判断这个数值是否是指针和是否是和int是一个类型，所以说可以得到这个数值，尽管好像是返回多个个数值，但是这其实在编译期就完成了这些操作，所以其实就返回了一个数值.
