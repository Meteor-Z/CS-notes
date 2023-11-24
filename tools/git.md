# git

基础的指令就不介绍了，一下主要是实际应用中使用的

- 如何赊销commit

```c++

```

- 中文乱码解决

```shell
git config --global core.quotepath false
```

## 项目中开发一个新玩意

1. 创建一个新分支

```shell
git checkout -b feature/new-feature # 创建一个新分支并且切换过去

git add .
git commit -m "xxxxx" # 提交上去

git checkout main # 切换到main分支
git pull # 拉取新分支
git checkout feature/new-feature
git merge main # 合并到新分支

# 将分支推送到远程仓库
git push origin feature/new-feature

git branch -d feature/new-feature
git push origin --delete feature/new-feature
```
