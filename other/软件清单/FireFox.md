# FireFox

firefoex需要以下设置, 否则进入全屏播放的时候比较慢

- 视频加载的缓冲不需要设置成0
  - 地址栏输入 about:config，回车进入配置页面。分别搜索下面三项，功能看注释
  - full-screen-api.warning.timeout 双击设置为 0 //关闭视频进入全屏时的提示
  - full-screen-api.transition-duration.enter 双击设置为 ‘0 0’ // 去除全屏模式的过渡动画–进入
  - full-screen-api.transition-duration.leave 双击设置为 ‘0 0’ // 去除全屏模式的过渡动画–退出

## 油猴

- [油猴刷课脚本](https://greasyfork.org/zh-CN/scripts/462748-%E8%B6%85%E6%98%9F%E5%AD%A6%E4%B9%A0%E9%80%9A%E5%B0%8F%E5%8A%A9%E6%89%8B-%E6%AD%A3%E5%88%99%E6%94%B9-%E5%AE%8C%E5%85%A8%E5%85%8D%E8%B4%B9-%E8%A7%86%E9%A2%91-%E7%AB%A0%E8%8A%82%E6%B5%8B%E8%AF%95-%E8%87%AA%E5%8A%A8%E6%8C%82%E6%9C%BA-%E9%98%B2%E6%B8%85%E8%BF%9B%E5%BA%A6-%E4%B8%8D%E5%8D%A0%E8%B5%84%E6%BA%90)
