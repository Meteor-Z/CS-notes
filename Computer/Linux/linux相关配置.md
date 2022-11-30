# Linux相关软件的配置

## pacman相关操作

- 更新所有软件和系统： `sudo pacman -Syyu`
- 查找软件：`pacman -Ss "XXX"`
- 安装软件：`sudo pacman -S XXXX`
- 卸载软件：`sudo pacman -Rs XXX`

## vim  相关配置的列表

配置列表在`/etc/vimrc目录下`

```bash
"  设置缩进的代码
set ts=4
set softtabstop=4
set shiftwidth=4
set expandtab
set autoindent

" 设置显示行号
set nu

" 设置括号自动补全
inoremap ( ()<ESC>i
inoremap [ []<ESC>i
inoremap { {}<ESC>i

" 设置大括号自动缩进
imap {<CR> {<CR>}<ESC>O
```



## Java/IDEA的相关配置

1. 下载`JDK`和IDEA : 直接使用`pacman`进行安装

2. JVM会安装到`/usr/lib目录里面，`

3. 在`/etc/prpfile`中添加以下进行配置（这是永久有效的）

```bash
export JAVA_HOME=/usr/lib/jvm/java-8u73-sun   # 自己的java的路径
export JRE_HOME=${JAVA_HOME}/jre   
export CLASSPATH=.:${JAVA_HOME}/lib:${JRE_HOME}/lib   
export PATH=${JAVA_HOME}/bin:$PATH 
```

4. 是使用命令`source /etc/profile`进行加载配置 (如果启动不了 就要每次source一下？)  (注销再登录或者重启就可以了)

## Clash For Window 的配置代理

分别在`/etc/profile`和`~/.zshrc`中输入以下内容

```bash
export https_proxy=http://127.0.0.1:7890
export http_proxy=http://127.0.0.1:7890
export all_proxy=socks5://127.0.0.1:7890
```

并在clash中的`port`改成7890,并且`manjaro`中将网络代理设置成自动代理，并且设置成以下格式

![代理-聚合图床](https://pic.imgdb.cn/item/6387727416f2c2beb1ed0cd6.png) 



