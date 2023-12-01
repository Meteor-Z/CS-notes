# mmap

## 传统读入

1. 将文件读入到内存中
2. 修改内存中的内容
3. 内存内容写入到文件中

`read()`:已从从磁盘拷贝到`page cache`，一次是从`page cache`拷贝到用户态内存
但是这里修改的时候有用户态和内核态的区分，内存中的内容首先会放到内核态上，如果要修改，那么就要将这些文件再搬到用户态，

这里就需要多次拷贝

1. 数据从硬盘搬运到内核态，
2. 如果要修改数据，那么就要将其文件再次发送到用户态。这里还有一次拷贝
3. 如果要保存，那么还要保存到用户态，然后再保存到内核态
4. 内核态中的数据还要再次写入到硬盘上

这里就经过了很多次拷贝，这时候，如果说你要读取一个文件，然后将这个文件发送到另一个文件的手上，

1. 将A在内核态的文件读取到用户态
2. 将用户态的文件写入到B文件的用户态上
3. 然后用户态的文件还要写回到内核态

这里都要经过两次无用的操作，拷贝到用户态

## 零拷贝

文件在内核态就不需要拷贝到用户态了，直接从内核态到内核态。

其中有`mmap`和`sendfile`，一次函数调用会有两次上下文切换，mmap通过映射可以减少将文件copy到用户空间里面，
`mmap配合write:`一共四次上下文切换，3次拷贝
`sendfile`:一共两次上下文切换，3次拷贝（如果更高级一点，就是两次拷贝了，不需要经过socket缓冲区。

### 差别

`mmap对于用户和内核，映射了物理磁盘和虚拟地址`，因为要进行映射，所以需要的内存就要比较大，如果是大文件，找不到一个非常大的连续空间去映射，那么就急了，但是sendfile就没有这个问题。

sendfile