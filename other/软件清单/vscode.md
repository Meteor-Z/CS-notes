# vscode

vscode是我使用最多的编辑器，除了写java, 我感觉它什么都可以干。以下是我的一些配置  
vscode的配置一般是`json`文件，使用json文件进行配置

## 插件

常用的插件，非常好用, 额，我的插件怎么感觉有点少（？

- c++插件
  - clangd: 在linux上要下载东西使用
  - c/c++: 微软的，需要调试，记得关闭提示，让`clangd`进行调试
- 远程：remote ssh 相关插件
- 格式化：clang-format
- cmake: cmake tools
- Markdown: Markdown All in One
- 注释：doxygen 这玩意真的太好用了

## 调试

我发现和gdb调试起来，还是vscode的配置比较爽一点,以下是相关配置  

- `tasks.json`：生成目标文件的，我不需要，因为工程文件是cmake生成的
- `launch.json`：进行debug生成好的目标文件的，需要的是这个

下面的的这个就是`launch.json`文件，

```json
{
    // 使用 IntelliSense 了解相关属性。 
    // 悬停以查看现有属性的描述。
    // 欲了解更多信息，请访问: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    // 调试参数
    "configurations": [
        {
            // 生成的信息
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
        //   调试哪一个程序，使用cmake生成之后，要进行调试的。
        // 好像和 cmake 插件配合的很好，能直接生成调试哪一个
            "program": "${workspaceRoot}/OUT/${fileBasenameNoExtension}.out",
            // "program": "${workspaceRoot}/OUT/a.out",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            // false 表示不会有独立的黑框
            "externalConsole": false,
            "MIMode": "gdb",
            // 调试器的位置
            "miDebuggerPath": "/usr/bin/gdb",
            "preLaunchTask": "C/C++: g++ 生成活动文件",
            "miDebuggerArgs": "-q -ex quit; wait() { fg >/dev/null; }; /usr/bin/gdb -q --interpreter=mi",
            "setupCommands": [
                {
                    "description": "为 gdb 启用整齐打印",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
```

## c++ 工具链

vscode可以配合相关插件进行代码开发

### 生成compile_command.json

clangd 进行lsp服务，需要使用 `compile_command.json` 进行识别,cmake可以生成这个文件，在cmake顶层文件加入这段话。

```cmake
# 生成对应的 compile_command
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# 指定一定要使用这个标准
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
```

### clang-format

clang-format的放在项目目录中使用`.clang-format`即可生成。



