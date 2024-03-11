# CS-notes

这个是我的学习笔记，以前叫做`university-study`,但是跟着[zwx](https://github.com/zweix123/CS-notes)的博客，遂改成了`CS-notes`,他的博客对我帮助很大，十分感谢他。下面的文章具体可以访问我的个人网站：[liuzecehn.top](https://liuzechen.top/)

## 提问的艺术

我觉得在学习计算机专业的过程中，提问是一件非常重要的事情，所以说有提问的艺术，以下是我看相关的文章，总结的几点

- 在询问之前要在网络上进行搜索相关的问题，看自己能不能解决掉。
- SSCCE: Short, Self Contained, Compilable, Example：代码要简短，并且可以完整运行
- 将代码粘贴到相关网站上进行发送，相关信息也要发送，不要使用手机拍照，不要进行截图。
- 告知相关平台，并且如果有错误信息，也应该贴出来，

## 书籍

这些书我觉得挺好的。目前也在读这些书，做相关笔记，有些书籍真的是再看一遍，都有不同的收获

- 深入理解操作系统(csapp)
  - 基本快读完了，但是还需要平时看看，
- 操作系统导论(ostep)
  - 文件系统里面不是很清楚，前面还行
- 程序员的自我修养(链接，装载和库)
  - 光看了前半部分
- 计算机网络(自顶向下方法)
  - 目前正在看
- 数据库系统实现
  - 目前正在看
- [EffectivModernCpp](https://github.com/CnTransGroup/EffectiveModernCppChinese/tree/master/src) 
  - 可以反复读
- 现代cpu性能优化与分析 
  - 只有200页，但是信息量巨大
- Linux多线程服务端编程：使用muduo C++网络库 
  - 陈硕的，非常不错

## 视频

- [性能优化 往数组里写入0为何比写入1更快？详解缓存的工作机制](https://www.bilibili.com/video/BV1gu41117bW)
- [git成熟项目的工作流](https://www.bilibili.com/video/BV19e4y1q7JJ/)
- [内存泄漏，以及为什么不要继承STL](https://www.youtube.com/watch?v=LKKmPAQFNgE)
- [https的原理，CA机构](https://www.bilibili.com/video/BV1uY4y1D7Ng)
- [UB行为以及相关后果](https://www.bilibili.com/video/BV1iF4m1L7MB)

## 文章

- [What every programmer should know about memory](https://zhuanlan.zhihu.com/p/611133924)（每一个程序员应该知道的内存知识）
- [C++服务编译耗时优化原理及实践](https://tech.meituan.com/2020/12/10/apache-kylin-practice-in-meituan.html)
- [git merge 和 rebase 的 区别](https://www.cnblogs.com/FraserYu/p/11192840.html)
- [for循环的时候要使用auto遍历的原因](https://www.zhihu.com/question/355171938/answer/899154458)
- [浮点数误差](https://zhuanlan.zhihu.com/p/673320830)  
- [markdown中mermaid的用法](https://soft.xiaoshujiang.com/docs/grammar/feature/mermaid/#e59bbee8a1a8e696b9e59091_7)
- [提问的艺术](https://zhuanlan.zhihu.com/p/20752519)
- [什么时候使用const_cast](http://blog.hostilefork.com/when-should-one-use-const-cast/)
- [为什么std::vector比std::list快](https://stackoverflow.com/questions/238008/relative-performance-of-stdvector-vs-stdlist-vs-stdslist)
- [加入const为什么可以优化代码(取模运算)](https://zhuanlan.zhihu.com/p/151038723)
- [测试oj网站的cpu, 好有趣](https://zhuanlan.zhihu.com/p/28322626)
- [gdb的实现原理](https://linux.cn/article-8943-1.html)
- [看懂火焰图，火焰图基本入门](https://www.ruanyifeng.com/blog/2017/09/flame-graph.html)
- [内存模型](https://zhuanlan.zhihu.com/p/382372072)
- [volatile和atomic的区别，以及volatile的应用](https://github.com/CnTransGroup/EffectiveModernCppChinese/blob/master/src/7.TheConcurrencyAPI/item40.md)

## 博主

平时看看，可以爆一爆他的金币

- [陈硕](https://www.zhihu.com/people/giantchen) 博客好多东西，我都不懂，希望有懂得一天
- [zwx](https://github.com/zweix123/CS-notes)
- [韦易笑](https://www.zhihu.com/people/skywind3000)
- [双笙子佯谬](https://space.bilibili.com/263032155) 讲解c++视频的

## 网站

好用的网站都放在这了

- 绘图网站:
  - [Graph Editor](https://csacademy.com/app/graph_editor)
  - [draw.io](https://draw.io)
- 剪切板：
  - [godbolt](https://godbolt.org)
  - [在线剪切板](https://paste.nugine.xyz)
- c++
  - [cppreference](https://zh.cppreference.com/w/%E9%A6%96%E9%A1%B5) 手册
  - [cppinsights](https://cppinsights.io) 解糖用的
- [知乎](https://www.zhihu.com)
- [IEEE754计算](http://weitz.de/ieee)

## 第三方库

- [backward-cpp](https://github.com/bombela/backward-cpp): 相当于gdb中的bt指令，可以在代码出现问题的时候打印出调用栈
- [fmt](https://github.com/fmtlib/fmt): 现代的C++格式化库，进入C++20标准里面了
- [compiledb](https://github.com/nickdiego/compiledb): 生成非cmake的clangd的json信息的
- [googletest](https://github.com/google/googletest): google的测试工具
- [benchmark](https://github.com/google/benchmark): 测试相关速度的
- [protobuf](https://github.com/protocolbuffers/protobuf): 传输序列化的