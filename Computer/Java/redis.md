# redis 入门

## 五种常用数据类型

- 字符串
- 哈希 (存储对象)
- 列表 (list) 按照插入顺序连接, (可以实现任务队列 ? )
- 集合(set) 没有重复元素
- 有序集合 (sorted set) 有序集合, 没有重复元素

## redis 常用命令

### 字符串 string 操作命令

- `SET key value `: 设置指定`key` 的值
- `GET key`:获取`key`值
- `SETEX key seconds value`:多了一个设置值的过期时间
- `SETNX key value`key不在的时候设置key的值为`value` (防止覆盖)
- 注意事项:
  - `SET` 都是字符串操作


## 哈希 hash 

与`map`差不多

## 列表 list

这不是 栈么 ????

这样插入的  -------- >> 往右边插入

可以用于信息队列来使用



这其实是一个双向列表,呜呜呜 就是一个`deque`

## 集合 set 

跟`set`没啥两样

## 有序集合 sorted set

其实就是`unordered_set`

每一个元素关联一个`double` score 的分数进行排序

两个`set`都不允许重复元素



[redis 中文网](http://www.redis.cn)



