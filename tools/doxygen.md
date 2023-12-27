# doxygen

这玩意真的强，呜呜呜，羡慕死了

## 安装

```shell
sudo apt intall doxygen # 
sudo apt install graphviz # 图形化调用需要使用
```

## 生成

```shell
# 生成 Doxyfile
doxygen -g 
# 生成网页
doxygen Doxyfile
```

## 文档描述

这个文档太多了，直接在放file里面了, 之后直接复制这个doxygen的文档就好了

## 代码参考

根据这个类的相关注释来生成相关的doxygen

```c++
/**
 * @file main.cpp
 * @author lzc (xxxxx@qq.com)
 * @brief 测试doxygen的文件
 * @version 0.1
 * @date 2023-12-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <bits/stdc++.h>
#include <functional>
#include <iostream>

using ll = long long; ///< 名称替换 long long -> ll

/**
 * @brief 这是一些类型
 *
 */
enum class Type {
    TypeONE = 1,   ///< 类型1
    TypeTwo = 2,   ///< 类型2
    TypeThree = 3, ///< 类型3
};

/**
 * @brief Person类
 *
 */
class Person {
public:
    /**
     * @brief Construct a new Person object
     *
     * @param name 姓名
     * @param age 年龄
     * @param height 身高
     */
    Person(const std::string& name, int age, double height)
        : m_name(name), m_age(age), m_height(height) {}
    /**
     * @brief 输出这个人的成员变量的参数
     *
     */
    void show_data() {
        std::cout << m_name << ' ' << m_age << ' ' << m_height << std::endl;
    }
    /**
     * @brief 一个人说了某一段话
     *
     * @param message 说的信息
     */
    void talk(std::string message) {
        std::cout << m_name << ": " << message << std::endl;
    }

public:
    std::string m_name; ///< 人的姓名
    int m_age;          ///< 人的年龄
    double m_height;    ///< 人的升高
};

/**
 * @brief 主函数
 *
 * @return int 返回给系统的
 */
int main() {}
```