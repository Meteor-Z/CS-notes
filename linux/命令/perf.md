# perf

linux上的性能分析工具。

一般是来做火焰图的，下面是工具命令

## 工具

```c++
sudo pacman -S perf
yay -S flamegraph-git
```

```shell
# record 表示采集系统事件
# -F 99 表示 每秒采集99次
# -p 2512 表示对于2512这个进程进行分许
# sleep 60 表示持续 60秒
sudo perf record -F 99 -p 2512 -g -- sleep 60 # 生成perf.data

# 进行解析
sudo perf script -i perf.data &> perf.unfold

# 进行折叠
stackcollapse-perf perf.unfold &> perf.folded

# 生成svg图片
flamegraph perf.folded > perf.svg
```

alias 指令

alias getflame="sudo perf script -i perf.data &> perf.unfold && stackcollapse-perf perf.unfold &> perf.folded && flamegraph perf.folded > perf.svg"

