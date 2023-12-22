# Docker

起初是为了部署学校的榜单，所以学习以下 docker, 发现很好用
为了方便以后直接润，或者迁移，都是服务器里面安装`docker`，然后将`docker` 里面安装运行的环境

Dock的官方文档:[Docker](https://docs.docker.com/engine/install/linux-postinstall/)

## 镜像

- `docker pull ununtu:20.04`:拉去一个镜像
- `docker images`:列出本地所有的镜像
- `docker rni 镜像名`：删除这个镜像
- `docker [container] commit CONTAINER_IMAGE_NAME:TAG`:创建某个container的镜像
- `docker save -o ubuntu:20.04.tar ubuntu：20.04` 将镜像导出到本地
- `docker load -i 镜像名`：将这个 镜像从本地加载出来

## eg

```shell
# 执行一个容器，使得在ubuntu22.04下运行这个命令，输出Hello World
docker run ubuntu:22.04 /bin/echo "Hello world"
```
