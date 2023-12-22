# Wsl

众所周知，windwos是linux最好的发行版，wsl可以满足基本可以满足我所有的开发需求了，一下是wsl的相关配置

## 换源

```shell
sudo sed -i 's@//.*archive.ubuntu.com@//mirrors.ustc.edu.cn@g' /etc/apt/sources.list
```

## zsh

```shell
sh -c "$(curl -fsSL https://gitee.com/Devkings/oh_my_zsh_install/raw/master/install.sh)"
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting
git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions
plugins=(git zsh-syntax-highlighting zsh-autosuggestions sudo)
```

## 软件

```shell
sudo sed -i 's@//.*archive.ubuntu.com@//mirrors.ustc.edu.cn@g' /etc/apt/sources.list # 换成中科大的源
sudo apt update
sudo apt upgrade
sudo apt install zsh
sudo apt install gcc
sudo apt install g++
sudo apt install gdb
sudo apt install cmake
sudo apt install clangd 
sudo apt install clang-format
sudo apt install manpages-zh # 中文man
sudo apt install language-pack-zh-hans # 汉字显示
sudo apt install libboost-all-dev # boost库
sudo apt install libprotobuf-dev protobuf-compiler # protobuf
sudo apt install valgrind # 内存泄漏检测工具
sudo apt install cppcheck # 简单的静态cpp检测  cppcheck xxx.cpp 即可
sudo apt install fonts-jetbrains-mono # 字体
sudo apt install docker.io # docker的配置
```
