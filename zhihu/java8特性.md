#! https://zhuanlan.zhihu.com/p/599318787
# Java8 新特性

## Java 8 Stream
不知道大家学过 Linux 下的 管道 没有, 这个相当于一个重定向的玩意,可以实现将一个内容的输入传输到另一个内容里面, A --> B , 关键符号是 `|`;以下是 linux 下的一个简单例子~.

```shell
echo "Arch Linux" | cowsay | lolcat
```
>上述代码的大致意思就是输出一个`Arch Linux`,然后通过 管道 将这句话传输到 cowsay里面,cowsay 可以将这句话以牛的形式输出出来,然后将这个句话(包括牛) 传输到 lolcat 里面,而lolcat 就可以直接将这些东西全部以彩色的形式传输出来,于是就是下面的图片了~.
![](https://cdn.jsdelivr.net/gh/Meteor-Z/blog-image/shell%E5%9B%BE%E5%83%8F)


所以说:所有的数据在管道里面传输,然后将最终信息显示在终端中 这就是管道.而 Stream 也是如此.

Stream, 流, java中的集合在流中流动,然后进行封装加工,将其加工之后的数据传输到一个最终的集合里面,不关心其中数据的变化(也就是函数式编程),只看最终结果,所以说`Stream`流很方便快捷.我们直接通过例子来看一下~~.

### 某学校的 java考试题
>题目大意:有一个 Teach类, 然后将若干个老师将如到集合里面,获取里面的薪资最高的老师的姓名和工号![Teach类](https://cdn.jsdelivr.net/gh/Meteor-Z/blog-image/Teacher%E7%B1%BB.png)

我们可以使用`stream()`方法来获取一个集合的`Stream`流,然后对这个流进行操作,我们可以直接调用`max()`来获取其中的最大值,其中我们直接使用`Lambda`表达式来返回薪资最大,然后返回的是一个`Optional`类,(容我之后研究研究),然后调用`ifPresent()`来判断这个对象是否存在,然后直接调用`Lambda`输出出来这个对象的内容~

![Teacher类中Stream流的使用](https://cdn.jsdelivr.net/gh/Meteor-Z/blog-image/Teacher%20Stream%E6%B5%81%E7%9A%84%E4%BD%BF%E7%94%A8.png)

### 完全平方数
> 将一个集合里面的完全平方数得到,然后将重复的数字剔除,然后进行排序,然后返回一个集合

我们直接通过代码来看一下~
![完全平方数](https://cdn.jsdelivr.net/gh/Meteor-Z/blog-image/%E5%AE%8C%E5%85%A8%E5%B9%B3%E6%96%B9%E6%95%B0%E7%9A%84%E8%BF%87%E6%BB%A4.png)

首先通过`stream()`获取`stream`流,然后对流进行操作,`map()`的意思就是进行匹配`映射`,里面`i`就表示将`i`变成`i * i`,其实就是完全平方数,然后`distinct()`就是去除掉相同的元素,之后`sorted()`进行排序,`collect(Collectors.toList())`来最终返回一个集合,这样这个集合就得到了~~,返回的数值是以下内容
```in
1 4 9 16 81 2916 4225
```
是不是很方便!,是不是很简单!~  
其他的想到啥再写(  
我们不关心数据在其过程中的变化,只关心数据的最终变化,这就是`Stream`流.

希望对您有所帮助~~