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
  
  

### 插入

- 添加数据
  - 给指定字段添加数据：`INSERT INTO 表名（字段名,字段名2）VALUES(值1，值2)`
  - 全部字段添加数据：`INSERT IN TO 表名 VALUESE(值1，值2，值3)`，
- 修改数据：`UPDATE 表名 SET 字段名1=值1,字段名=值2。。。 [WHERE 条件]`
- 删除数据：`DELETE 表名 [WHERE 条件]` （这个数据就没有了）

### 查询

```sql
SELECT 
	字段列表
FROM 
	表名列表
WHERE
	条件列表
GROUP BY
	分组字段列表
HAVING
	分组后条件列表
ORDER BY
	排序字段列表
LIMIT
	分页参数
```

- 基本查询

  - 查询多个字段：`SELECT 字段1 [AS '别名']，字段2，字段3 FROM 表名；` `SELECT * FROM 表名`
  - 查询多个字段但是要去重: `DISTINCT`
  - 练习

  ```sql
  # 查询年龄等于 88 的员工
  WHERE age = 88;
  
  # 查询年龄小于 20 的员工
  WHERE age < 20;
  
  # 查询年龄大于等于 20 的员工
  WHERE age >= 20;
  
  # 查询没有身份证的员工
  WHERE idcard IS NULL;
  
  # 查询有是身份证的员工
  WHERE idcard IS NOT NULL;
  
  # 查询年龄不等于88的员工
  WHERE age != 88;
  WHERE age <> 88;
  
  # 查询年龄在15到20岁的员工之间的学生
  WHERE 15 <= age && age <= 20;
  WHERE 15 <= agea AND age <= 20; # 推荐用这种形式或者下面这种写法
  WHERE age BETWEEN 15 AND 20; # 不能写反~~
  
  # 查询性别为女并且年龄小于25的员工
  WHERE gener = '女' and age < 25;
  
  # 查询年龄等于18 或者 20 或者40 的员工
  WHERE age = 18 or age = 20 or age = 40;
  WHERE age=18 or age=20 or age=40;
  WHERE age in(18,20,40);
  
  # 查询姓名是两个字的员工
  WHERE age LIKE ‘__’;
  
  # 查询身份证最后一个是X的员工
  WHERE idcard LIKE '%X';
  ```

  - `BETWEEN ---- AND ----`:在某一个范围（包含最小和最大值）
  - `IN(条件1，条件2，条件3)`：只要满足其实一个条件就可以了
  - `LIKE 占位符`：



### 集合函数

- 常见的聚合函数

  - `COUNT`:统计数量  

  - `MAX`:最大值

  - `MIN`:最小值

  - `AVG`：平均值

  - `SUM`:求和

- 语法：`SELECT 聚合函数（字段列表）FROM 表名`

- 练习：

  ```sql
  # 统计所有员工的数量
  SELECT COUNT(id) FROM emp;
  
  # 统计企业员工的平均年龄
  SELECT AVG(age) FROM emp;
  
  # 统计西安的地区年龄之和
  SELECT SUM(age) FROM emp WHERE address = '西安';
  
  ```

- 注意：所有聚合函数中的时候不会统计空值的

###  分组查询

- 语法：`SELECT 字段列表 FROM 表名 [WHERE 条件] GROUP BY 分组字段名 [HAVING 分组过滤条件]`
- 注意：`HAVING`和`WHERE`的区别：
  - 执行时机不同：`WHERE`是分值之前进行过滤,`HAVING`是分组之后进行考虑
  - `判断条件不同`：`WHERE`不能对聚合函数进行判断，`HAVWING`里面可以使用聚合函数
- 练习

```sql
# 根据性别分组，统计男性员工和女性员工的数量
SELECT gender, COUNT(id) FROM emp GROUP BY gender;

# 统计男性员工和女性员工的平均年龄
SELECT gender,avg(age) FROM emp GROUP BY gender;

# 查询年龄小于45的员工的数量，并根据工作地址分组，获取员工数量大于等于3的工作地址
SELECT workarress,COUNT(*) FROM emp WHERE  age < 45 GROUP BY workaddress HAVING count(*) >= 3;
```

###  排序查询

- 语法:`SELECT 字段列表 FROM 表名 ORDER BY 字段1 排序方式1，字段2 排序方式2`;

- 排序方式：

  - `ASC`:升序 (默认值)
  - 'DESC':降序

- 练习：

  ```sql
  # 根据年龄对公司的员工进行升序排序
  SELECT name FROM emp ORDER BY age ASC;
  
  # 根据入职时间，对于员工进行降序排序
  SELECT * FROM emp ORDER BY entrydate DESC;
  
  # 根据年龄对公司的员工进行升序排序，如果相同，再按照入职时间进行降序排序
  SELECT * FROM emp ORDER BY age ASC,entrydate DESC;
  ```

  ### 分页查询

  其实就是第一页，第二页，第三页，第四页那种

  - 语法：`SELECT 字段列表 FROM 表名 LIMIT 起始索引，查询记录数`

  - 练习：

    ```` sql
    # 查询第一页的员工数据，每行展示10条记录
    SELECT * FROM emp LIMIT 0,10;
    
    # 查询第二页员工数据，每行展示10条记录
    SELECT * FROM emp LIMIT 1,10;
    ````

### 总练习

```sql
# 查询年龄为20，21，22，23的女性员工
SELECT * FROM emp WHERE age in(20,21,22,23) AND gender = '女';

# 查询性别是男，并且年龄在20-40岁之间并且姓名是3个字的员工
SELECT * FROM emp WHERE gender = '男' AND age BETWEEN 20 AND 40 AND name LIKE '___';

# 查询员工表中，年龄小于60岁的，男性员工和女性员工的数量
SELECT gender,COUNT(*) FROM emp WHERE age < 60 GROUP BY gender;

# 查询所有年龄小于等于35岁员工的性别和年龄，并且对于结果按照升序排序，如果年龄相同的按照入职时间进行降序
SELECT name AS ‘姓名’,age AS '年龄' FROM temp WHERE age <=35 ORDER BY age ASC,entydate DESC;

# 查询性别是男，并且年龄是在20-40岁之间的前5个员工，对查询的结果按照年龄升序排序，年龄相同按照入职时间升序排序
SELECT * FROM temp WHERE gender = '男' AND age BETWEEN 20 AND 40 ORDER BY age ASC, entrydate DESC LIMIT 0,5;


```

# 用户管理

- 查询用户

  ```mysql
  USE mysql;
  SELECT * FROM user;
  ```

- 创建用户:

  ```mysql
  CREATE USER '用户名' @ '主机名' IDENTIFIED BY ‘密码‘
  ```

- 练习

  ```mysql
  # 创建一个用户 lzc, 只能在当前主机localhost上访问，密码123456
  CREATE USER 'lzc'@'localhost' IDENTIFIED BY '123456';
  
  # 创建一个用户LZC，在任意的的主机都可以访问数据库，密码123456
  CREATE USER 'LZC'@‘%’ IDENTIFIED BY ‘123456’;
  
  # 修改用户密码
  ALTER USER 'lzc'@'localhost' IDENTIFIED  WITH mysql_native_password BY '1234';
  
  # 删除用户
  DROP USER '用户名'@'主机名';
  ```
  

#

### 权限控制

- `ALL,ALL PRIVIEGES`:所有权限
- `SELECT`：查询数据
- `INSERT`:插入数据
- `UPDATE`:修改数据
- `DELETE`:删除数据
- `ALTER`:修改表
- `DROP`:删除数据库/表/视图
- `CREATE`:创建数据库/表



- 查询权限：`SHOW GRANTS FOR ‘用户名@主机名’`;
- 授予权限：`GRANT 权限列表 ON 数据库名.表名 TO ‘用户名’@‘主机名’`；
- 赊销权限：`REVOKE 权限列表 on 数据库名.表名 FROM ‘用户名’@‘主机名’`；
- 



# 函数

感觉没啥用，还不如直接用`JAVA`中的函数了，而且更好些

# 约束

概念：约束是作用于表中字段上的规则，用于限制存储在表中的数据

目的：保证数据库中的数据的正确，有效性和完整性

​	非空约束：`NOT NULL`;

唯一约束：`UNIQUE` 身份证号 手机号 id 什么的

主键约束：`PRIMARY KEY` 一行数据的唯一标识，要求非空且唯一  规范！

默认约束:`DEFAULT`

检查约束：默认状态下这个字段的默认值

外键约束：`FOREIGN KEY` 让两张表之间建立连接，保证数据的一致性和完整性

- 练习

  | 字段名 | 字段含义   | 字段类型    | 约束条                    |
  | ------ | ---------- | ----------- | ------------------------- |
  | id     | ID唯一标识 | int         | 主键，并且自动增长        |
  | name   | 姓名       | varchar(20) | 不为空，并且唯一          |
  | age    | 年龄       | int         | 大于0，并且小于等于120    |
  | status | 状态       | char(1)     | 如果没有指定该值，默认是1 |
  | gender | 性别       | char(1)     | 无                        |

```sql
# SQL 代码实现
CREATE TABLE emp(
    id int PRIMARY KEY AUTO_INCREMENT comment '主键',
    name varchar(10) NOT NULL UNIQUE  COMMENT '姓名',
    age int check ( 0 < age AND age <= 120 ) COMMENT '年龄',
    status char(1) DEFAULT '1' COMMENT '状态',
    gender char(1)  COMMENT '性别'
)comment '用户表';

# 插入
INSERT INTO emp(name,age,status,gender) VALUES('TOM1',18,'1','男');
INSERT INTO emp(name,age,status,gender) VALUES('TOM2',19,'1','女');
INSERT INTO emp(name,age,status,gender) VALUES('TOM3',20,'1','女');
```

## 外键

作用：将两张表的数据之间建立连接，从而保证数据的一致性和完整性

语法与练习：

```sql
# 添加外键
ALTER TABLE 表名 ADD CONSTRAINT 外键名称（随便起） FOREIGN KEY(外键字段名) REFERENCES 主表（主表列表） # 一个表的字段关联到了另一一个表的主键，使得这两个表之间有关联

# 消息
ALTER TABLE emp ADD CONSTRAINT fk_emp_dept_id (dept_id) REFERENCES dept(id);


```







# 注意事项

- 写代码的时候尽量不要写`*`，因为这样不直观
- 规范，每一张表都要有一个主键约束





