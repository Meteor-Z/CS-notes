 # Java Web

`B/S`架构: 浏览器/服务器模式，两者之间直接把这个信息进行处理就可以了，易于维护和升级

## HTTP

HTTP：规定了浏览器和服务器之间的数据传输的规则

- 基于`TCP`协议，面向连接，十分安全
  - 每次请求是独立的，所有不能共享，但是速度更快 （使用`Cookie`,`Session`来解决此缺点）

### 常见的数据格式

- 数据分成三部分

  - 请求行：第一行，其中`GET`表示的是请求方式/表示请求资源的路径,还有请求协议
  - 请求头，第二行开始，格式是`key:value`的格式
  - 请求体：`POST`请求的最后一部分，存放的是请求参数

- 响应数据的格式

  - 响应行：响应的状态，200 就是OK，
  - 响应头：`key:value`的值
  - 响应体：存放着响应数据

- 状态码：

  - `1xx`:响应中，临时状态吗，
  - `2xx`:都表示成功，处理已经完成
  - `3xx`：重定向到了其他地方
  - `4xx`:客户端错误
  - `5xx`:服务器发生错

  

  

  

## 创建`maven`项目

### 项目构造

1. 对于开发中的项目
   - hello
     - src
       - main
         - java
         - resources
         - webapp
           - html （外界能访问的）
           - WEB-INF (WEB的配置文件)
             - web.xml
     - pom.xml

2. 部署的`JavaWeb`项目构造：

   - hello
     - html
     - WEB-INF
       - classes (java字节码文件)
       - lib（项目所需要的jar包）
         - web.xml （web项目配置文件）

   



### 请求转发

一种在服务器内部发生资源跳转的方式

`request.getRequestDispatcher("/demo02").forward(request,response);`

同时，我们可以将资源放在request里面。然后进行转发

- `setAttribute` ：设置域

- `getAttribute`：根据key,来获取

- `removeAttribute`

重定向：我自己处理不了，我302了，现在需要你照其他人，然后我会给你一个地址。就是响应头`location:XXXX`

特点：

- 地址栏会发生变化，但是请求转发的话不会发生改变
- 可以重定向向很多位置，其他网站也可以了的

路径问题：

- 浏览器使用：不需要加虚拟路径（就是不加项目访问路径）
- 服务端使用：不需要加虚拟路径（自己使用就可以了）
- 练习：
  - `<a>`:浏览器使用，所以要加上虚拟路径
  - `<form>`：浏览器使用，加上虚拟路径
  - 转发：不需要加虚拟路径
  - 重定向：需要加上虚拟路径

### response

- 响应行： `setSatus(int sc)`:设置状态码
- 响应头： `set Header(String name,String value)`： 设置响应键值对
- 响应体: 通过流的形式将输入输出流输出到界面就行了





