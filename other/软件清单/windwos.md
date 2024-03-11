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
- office: 我校的2021年的office LTS版本，免费，而且不花钱
- 发送请求：postman
- 视频播放器: vlc
- 音乐软件：网易云音乐（可能这就是习惯的力量罢了

## scoop

一些专业软件还是用scoop安装比较方便

### 安装scoop

```shell
set-executionpolicy remotesigned -scope currentuser
iex (new-object net.webclient).downloadstring('https://get.scoop.sh')
```

### scoop软件

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

### 油猴

- [油猴刷课脚本](https://greasyfork.org/zh-CN/scripts/462748-%E8%B6%85%E6%98%9F%E5%AD%A6%E4%B9%A0%E9%80%9A%E5%B0%8F%E5%8A%A9%E6%89%8B-%E6%AD%A3%E5%88%99%E6%94%B9-%E5%AE%8C%E5%85%A8%E5%85%8D%E8%B4%B9-%E8%A7%86%E9%A2%91-%E7%AB%A0%E8%8A%82%E6%B5%8B%E8%AF%95-%E8%87%AA%E5%8A%A8%E6%8C%82%E6%9C%BA-%E9%98%B2%E6%B8%85%E8%BF%9B%E5%BA%A6-%E4%B8%8D%E5%8D%A0%E8%B5%84%E6%BA%90)
