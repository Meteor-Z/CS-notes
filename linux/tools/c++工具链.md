# c++ 工具链

操作系统：Arch
编辑器：vscode
编译器：clang
辅助工具：clangd + clang-format + clang-tidy

## 注意事项

### 生成compile_command.json

clangd 进行lsp服务，需要使用 compile_command.json 进行识别,cmake可以生成这个文件，在cmake顶层文件加入这段话。

```cmake
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
```

### clang-format

clang-format的放在项目目录中使用`.clang-format`即可生成。

## 编译代码

- 开启编译选项：`g++ main.cpp -std=c++20 -Wall -Wextra -Wconversion -Wshadow -Werror -o main`
  - `-Wall -Wextra -Wconversion -Wshadow`:基本上就开启了所有警告
  - `Werror`:将警告变成错误
