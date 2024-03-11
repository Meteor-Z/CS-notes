# Wsl

- 众所周知，windows是linux最好的发行版，wsl可以满足基本可以满足我所有的开发需求了，以下是wsl的相关配置
- 因为 ubuntu 22.04 上的软件太老了，最终换成了 openSUSE 风滚草版本
- openSUSE风滚草的版本的软件更新很好，需要版本都是最新的，而不是Ubuntu一样，太老了

## zsh

```shell
sh -c "$(curl -fsSL https://gitee.com/Devkings/oh_my_zsh_install/raw/master/install.sh)"
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting
git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions
plugins=(git zsh-syntax-highlighting zsh-autosuggestions sudo)
```

## 软件

```shell
sudo zypper update # 更新软件
sudo zypper se xxx # 搜索软件
sudo zypper rm xxx # 删除软件
sudo zypper install xxx # 安装软件

sudo zypper install zsh
sudo zypper install neofetch # 装逼
sudo zypper install gcc
sudo zypper install gcc-c++ # g++，恶臭的名字
sudo zypper install gdb
sudo zypper install cmake
sudo zypper install clang
sudo zypper install clang-format
sudo zypper install man-pages man-pages-zh_CN man-pages-posix # 中文man以及相关的 page
sudo zypper install valgrind # 内存泄漏检测工具
sudo zypper install btop # 终端管理
sudo zypper install perf # 性能分析
sudo zypper install ripgrep # 捕捉
```
