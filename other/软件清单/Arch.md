# Arch

一直以来，如果使用linux的话，那么都是Arch，以下都是Arch的相关配置。

## 驱动

- 每一台电脑的驱动是不一样的，按照当前电脑的驱动进行安装，注意安装cpu和gpu（核显和独显），以下相关网址

- [Arch 简明指南驱动安装](https://arch.icekylin.online/guide/rookie/graphic-driver.html)
- 安装过后可以在firefox浏览器上查看软硬件编解码支持不支持

## 换源头

中科大Archcn源: [网站](https://mirrors.ustc.edu.cn/help/archlinuxcn.html)

## zsh

```shell
sh -c "$(curl -fsSL https://gitee.com/Devkings/oh_my_zsh_install/raw/master/install.sh)"
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting
git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions
plugins=(git zsh-syntax-highlighting zsh-autosuggestions sudo)
```

## 相关软件

```bash
sudo pacman -Syyu # 更新
sudo pacman -S sof-firmware alsa-firmware alsa-ucm-conf # 声音固件
sudo pacman -S archlinuxcn-keyring # 导入GPG key
sudo pacman -S dolphin # 文件浏览
sudo pacman -S konsole # terminal
sudo pacman -S kate # pdf阅读器
sudo pacman -S ark # 压缩
sudo pacman -S gwenview # 图片查看 
sudo pacman -S partitionmanager # 分区用的
sudo pacman -S filelight # 磁盘使用
sudo pacman -S kcalc # 计算器 
sudo pacman -S btop # 管理器之类的
sudo pacman -S okular # pdf阅读器
sudo pacamn -S kfind # 文件查找等
sudo pacman -S spectacle # 截图软件
sudo pacman -S perf # 性能分析工具
sudo pacman -S vlc # 视频播放器
sudo pacman -S firefox # 火狐浏览器 加插件，使用user-agent插件
sudo pacman -S yay # yay 需要Archcn中文源
sudo pacman -S cmake # 构建工具 
sudo pacman -S fzf # 文件搜索
sudo pacman -S ranger # 文件浏览
sudo pacman -S ripgrep # 搜索关键字
# sudo pacman -S benchmark # 测试c++性能代码用的
sudo pacman -S tree # 生成文件的目录层级用的
sudo pacman -S xmake # 构建软件
# sudo pacman -S jdk17-opjdk # java
sudo pacman -S wine # 可能需要一些游戏什么的
sudo pacman -S scrcpy # 安卓投屏， 安卓打开应用开发者模式，然后 adb devices， 然后 scrcpy 即可
sudo pacman -S clion # 构建工具
sudo pacman -S clion-jre # 解决ui界面的问题
sudo pacman -S clang clang-tidy # clang 编译器
sudo pacman -S neofetch # 装逼用
sudo pacman -S fcitx5-im fcitx5-chinese-addons fcitx5-pinyin-zhwiki # 中文输入法
sudo pacman -S zsh # zsh太好用了
sudo pacman -S net-tools dnsutils inetutils iproute2 # 网络相关
# sudo pacman -S obs-studio # obs 直播用的 可以直接去 steam 上进行下载
sudo pacman -S man man-pages-zh_cn # 中文版的man
sudo pacman -S adobe-source-han-serif-cn-fonts wqy-zenhei wqy-microhei # 相关字体
sudo pacman -S noto-fonts noto-fonts-cjk noto-fonts-emoji noto-fonts-extra # 相关字体
# yay -S ttf-ms-win10-auto # win10微软字体 有少许问题。。。
# yay -S ttf-ms-win11-auto # win11微软字体
yay -S linuxqq # qq
yay -S qbittorrent-enhanced # qbittorrent的增强版 下载电影用的，但是构建挺恶心的qwq
yay -S visual-studio-code-bin # vscode
yay -S debtap # 转换 deb包， sudo debtap -u -- debtap xxx.deb  sudo pacman -U xxxx
yay -S flamegraph-git # 生成flamegraph用的。
yay -S wps-office wps-office-mui-zh-cn wps-office-mime-cn wps-office-fonts ttf-ms-fonts ttf-wps-fonts # wps的相关
```

## wps防止爆体

有的字体在linux上是黑乎乎的一片，需要进行下载安装包`freetype2`的旧版安装包进行升级安装  
链接：[freetype2](https://archive.org/download/archlinux_pkg_freetype2/freetype2-2.13.0-1-x86_64.pkg.tar.zst)

下载安装之后，修改在`/usr/share/application/wps-office-wps.desktop`里面的exec就可以了，设置成  `Exec=env LD_LIBRARY_PATH=/path/to/freetype2/usr/lib /usr/bin/wps %U` 即可
