# makefile

## 编译静态库

```shell
g++ add.cpp minus.cpp -c # -c是分别生成了 add.o minus.o文件
ar -r lib.a add.o minus.o # 将add.o 和 minus.o 合并成一个lib.a这个库
g++ main.cpp lib.a -o main.out # 丽链接成main.out文件
```

## 编译动态库

```shell
# -fPIC是位置无关代码，本来是绝对位置，现在变成相对位置了
g++ -shared -fPIC add.cpp minus.cpp -o libyes.so
# 注意这里lib开头，并且链接的时候是-lyes, 后面的rpath是告诉运行的时候去寻找哪一个链接库，
g++ main.cpp -lyes -L/home/lzc/code/temp -Wl,-rpath=/home/lzc/code/temp -o main.out
```
