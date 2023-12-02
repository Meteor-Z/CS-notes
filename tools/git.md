# git

基础的指令就不介绍了，一下主要是实际应用中使用的

## 如何将

## 提交术语

commit内容是 type: short summary

## Type

- build: 影响构建系统或外部依赖项的更改（example scopes：gulp，broccoli，npm）
- ci: CI 配置文件和脚本发生了变化（example scopes：Travis、Circle、BrowserStack、SauceLabs）。
- docs: 仅对文档进行了修改
- feat: 增加新的特征
- fix: 修复 bug
- perf: 提高性能的代码更改
- refactor: 既不是修复 bug 也不是添加特征的代码重构
- style: 不影响代码含义的修改，比如空格、格式化、缺失的分号等
- test: 增加确实的测试或者矫正已存在的测试

## 如何撤销commit

```shell
git add file
git commit -m '修改原因'
git reset --soft HEAD^ #撤销了 commit
git reset --hard HEAD^ # 连着add也撤销掉
# 这些是我在branch上进行开发进行实现的

# 撤销多个commit 然后恢复成一个
git reset HEAD~5 # revert the last 5 commits
git add .
git commit -m "xxxxx"
```

## 中文乱码解决

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
# 将分支推送到远程仓库
git push origin feature/new-feature
# git checkout feature/new-feature
git merge feature/new-feature # 注意实在主分支上merge副分支


git branch -d feature/new-feature # 删除本地的这个分支
git push origin --delete feature/new-feature # 删除远程分支
```

## merge 和 rebase 的区别

merge我认为是是直接合并到主分支，好像就是head头直接平移到branch上面的一样，  
但是rebase不一样，开一个新branch之后，rebase像是从旧main上然后迁移到新main上，然后再提交上去。

## 如何提交一个pr

注意，提交的时候是提交一个branch上去，。然后将branch合并上去

1. 将项目fork到本地，然后拉去过来，
2. 本地开一个新的branch,在branch上进行开发新玩意
3. 将branch提交到github上
4. 然后用branch提交一下对面main里面
5. 然后将代码同步一下（github只能自动更新）然后删除branch