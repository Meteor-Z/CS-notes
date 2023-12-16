# windwos

我使用Arch使用了一年多了，但是最终还是换成了windwos,很多东西还是windwos上用的比较舒服，当然，我的所有开发环境还是在linux上，就是wsl上，以下是我windwoss上的一些开发环境。不包括wsl

## 软件

对于windwos,我觉得下载软件还是直接去官网上进行下载，不需要包管理工具，因为windwos本身与linux就是不相同的，网上的能直接更新，以下是我常用的工具

- 相关驱动：使用驱动精灵安装，然后使用geek将驱动精灵卸载掉
- 聊天软件：qq 和微信
- 编辑器: vscode
- 浏览器：firefox
- 页面查找：utools + everythings
- 种子下载：qbittorrent-enhanced-edition
- 代理软件：cfw
- 杀毒软件：火绒（虽然我不知道他在干什么）
- 文件解压：bandzip
- office: wps大庆版
- 发送请求：postman
- 视频播放器: vlc

## scoop

一些专业软件还是用scoop安装比较方便

### 安装scoop

```shell
set-executionpolicy remotesigned -scope currentuser
iex (new-object net.webclient).downloadstring('https://get.scoop.sh')
```
### 软件

```shell
scoop install git 
scoop install gcc
```

## Firefox

firefoex需要以下设置, 否则进入全屏播放的时候比较慢

- 视频加载的缓冲不需要设置成0
  - 地址栏输入 about:config，回车进入配置页面。分别搜索下面三项，功能看注释
  - full-screen-api.warning.timeout 双击设置为 0 //关闭视频进入全屏时的提示
  - full-screen-api.transition-duration.enter 双击设置为 ‘0 0’ // 去除全屏模式的过渡动画–进入
  - full-screen-api.transition-duration.leave 双击设置为 ‘0 0’ // 去除全屏模式的过渡动画–退出
