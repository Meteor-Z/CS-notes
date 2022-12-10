 # Mysql

mysql主要是数据库管理系统

## Mysql 的安装

- 安装Mysql

```bash
sudo pacman -S mysql
```

- 卸载Mysql

```bash
sudo pacman -Rs mysql
```

- 初始化

```bash
sudo mysqld --initialize --user=mysql --basedir=/usr --datadir=/var/lib/mysql
```

-  设置开机自启

```ba
sudo systemctl enable mysqld.service
```

- 启动Mysql

```bash
sudo systemctl start mysqld.service
```

- 查看Mysql服务

```bash
systemctl status mysqld.service
```

- 连接Mysql

```bash
mysql -uroot -p
```

- 修改密码

```bash
ALTER user 'root'@'localhost' IDENTIFIED BY '新密码';
```

## 数据模型

- 关系型数据库
  - 建立在关系模型基础上，由多张相互连接的二维表组成的数据库

## SQL

### Sql通用语法

- Sql语句可以单行或者多行，分号结尾
- SQL语句可以使用空格/缩进来增强语句的可读性
- MySQL数据库的SQL语句不分大小写，但是关键字还是建议用大写

### SQL分类

- `DDL`:数据定义语言
- `DML`:数据操作语言
- `DQL`:数据查询语言
- `DCL`:数据控制语言

### 数据类型

- 数值类型：`INT` `LONG` `DOUBLE`和前面+`UNSIGNED` 如果省内存的话上网搜

- 字符串：
  - `VARCHAR()`：普通的字符串 （不建议用`CHAR`吧？ 建议用`VARCHAR`）
  - `BLOB`:二进制数据 （字节）
  - `TEXT`:文本数据 （字符）
- 日期类型：
  - `DATA`:日期值 `YYYY-MM-DD`
  - `TIME`: 时间值 `HH:MM:SS`
  - `DATATIME`:日期时间 `YYYY-MM-DD HH:MM:SS`
  - 

### 数据库操作

- 查询：
  - 查询所有数据库：`SHOW DATABASES;`
  - 查询我现在在哪一个数据库：`SELECT DATABASE();`
- 创建： `CREATE DATABASE [IF NOT EXISTS] 数据库名` [DEFAULT CHARSET 字符集] (指定使用什么字符集)
- 删除：`DROP DATABASE [IF EXISTS] 数据库名`
- 使用：`USE 数据库名`

### 表操作

- 查询
  - 查询当前数据库中的所有表：`SHOW TABLES;`
  - 查询表结构：`DESC 表名`
- 修改：
  - 添加字段:`ALTER TABLE 表名` ADD `字段名` 类型 [COMMENT 注释] [约束];
  - 修改数据类型：`ALTER TABLE 表名 MODIFY 字段名 新数据结(长度)`
  - 修改字段名和字符类型：`ALTER TABLE `旧表名 新表名` 类型（长度） [COMMENT 注释] [约束]
  - 删除字段：`ALTER TABLE 表名 DROP 字段名`
  - 修改表名：`ALTER TABLE 表名 RENAME TO 新表名`
  - 删除表明：`DROP TABLE [IF EXISTS] 表名`
  - 删除表名并且创建改表：`TRUNCATE TABLE 表名`





