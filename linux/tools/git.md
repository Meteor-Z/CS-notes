# git

基础的指令就不介绍了，一下主要是实际应用中使用的

## 中文乱码解决

```shell
git config --global core.quotepath false
```

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

### `借鉴`别人的提交记录（例子）

我借鉴了几位（很多位的例子的github提交记录，如zwxgg,u姐姐等  

- `vault backup + 时间`： 保存，备份，（好像没什么内容
- `fix: do not allow creating nightly github release without binary`: 修复bug
- `doc：fix wrong layout`：修复错误的格式
- `ci: update docker build arguments`: ci,测试环境，修复build的arguments
- `feat: add xxx`: 增加了什么新特性

## 如何撤销commit

```shell
git add file
git commit -m '修改原因'
git reset --soft HEAD^ #撤销了 commit
git reset --hard HEAD^ # 连着add也撤销掉 或者后面跟上那个哈希值
# 这些是我在branch上进行开发进行实现的

# 撤销多个commit 然后恢复成一个
git reset HEAD~5 # revert the last 5 commits
git add .
git commit -m "xxxxx"
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

- rebase是变基，从原来的基变成现在的基。因为主分支有可能出现新的增长，这时候就需要变基

## 如何提交一个pr

注意，提交的时候是提交一个branch上去，。然后将branch合并上去

1. 将项目fork到本地，然后拉去过来: `这个在github上进行操作`
2. 本地开一个新的branch,在branch上进行开发新玩意:`git checkout -b feat-xxxx`
3. 将branch提交到github上: `git push origin feat-xxxx`
4. 然后用branch提交一下对面main里面: `在github上提交branch`
5. 然后将代码同步一下（github只能自动更新）然后删除branch:`将本地的分支删除，然后重新拉取分支`

## 修改默认编辑器为 nvim

- 修改默认编辑器为vim：`git config core.editor nvim`

## 添加和删除本地第三方库

```shell
# 添加
git submodule add http链接 ./third_party/xxx
# 删除


```