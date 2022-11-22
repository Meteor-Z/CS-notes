# Linux相关软件的配置

## pacman相关操作

- 更新所有软件： `sudo pacman -Syu`
- 查找软件：`pacman -Ss "XXX"`
- 安装软件：`sudo pacman -S XXXX`
- 卸载软件：`sudo pacman -R XXX`
- 

## Java/IDEA的相关配置

1. 下载`JDK`和IDEA : 直接使用`pacman`进行安装是

2. JVM会安装到`/usr/bin目录里面，`

3. 在`/etc/prpfile`中添加以下进行配置（这是永久有效的）

```bash
export JAVA_HOME=/usr/lib/jvm/java-8u73-sun   # 自己的java的路径
export JRE_HOME=${JAVA_HOME}/jre   
export CLASSPATH=.:${JAVA_HOME}/lib:${JRE_HOME}/lib   
export PATH=${JAVA_HOME}/bin:$PATH 
```

4. 是使用命令`source /etc/profile`进行加载配置 (如果启动不了 就要每次source一下？)  很怪，每次都要source一下

## C/C++ VS-code进行配置

只要修改`coder runner` 里面的命令就可以了

