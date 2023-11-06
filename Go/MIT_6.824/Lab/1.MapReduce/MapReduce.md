## Lab-1 MapReduce

> 任务难度：中等偏上

- 实现一个分布式的MapReduce应用，包含两个程序，调度程序（coordinator）和工作程序（worker）。程序运行时将有一个调度进程和一个或多个并行的工作进程。在现实中，我们期望工作进程运行在不同的机器上，但在本实验中它们将运行在你的同一台机器上，通过进程通信模拟分布式程序。工作进程通过RPC和调度进程通信。每一个工作进程都会向调度进程请求一个任务，从一个或多个文件中读取任务所需的数据，执行这个任务，然后将输入写入一个或多个文件。如果一个工作进程没能在一个合理的时间（本实验设置为10s）内完成任务，调度进程应该将该进程视为故障并发现它，并把相同的任务交给另一个工作进程。

- 调度进程和工作进程的入口分别在 <mark> main/mrcoodinator.go </mark> 和 <mark> main/mrwork.go  </mark> 中，不要修改它们。请在<mark>mr/coordinator.go</mark>、<mark>mr/worker.go</mark>和<mark>mr/rpc.go</mark>中完成你的实现

---

运行你的代码，确保单词计数插件已经build（在main目录下执行）:
```
go build -race -buildmode=plugin ../mrapps/wc.go
```

运行调度进程
```
go run -race maroordinator.go pg-*.txt
```

pg开头的txt文件是mrcoordinator.go程序的入参，每个文件后面都有一个分隔符，并且是一个map任务的入参。在一个或多个命令窗口执行工作进程：

```
go run -race mrworker.go wc.so
```

当工作进程和调度进程结束，在mr-out-开头的文件查看结果。如果你完成了代码，将结果折合排序，应该和顺序执行得到相同的结果
```
cat mr-out* | sort | more
```

测试脚本 main/test-mr.sh 这些测试检查了单词技术器和文本检索器在输入pg开头的文件时是否产生了正确的输出。测试Map Reduce任务是否是并发的，任务崩溃容错性

如果你执行这个脚本，它会挂起，因为调度进程永远不会结束：
```
bash test-mr.sh
```

你可以修改mr/coordinator.go中的Done()函数，把ret:=false改成ret:=true，这样的话，调度进程会立即结束。再执行上面的脚本，你会发现测试失败了。

这个测试脚本希望看到以mr-out-x命名的文件，它们是由Reduce任务产生的。而mr/coordinator.go和mr/worker.go空的实现不会产生这些文件，所以测试失败了。

跳转：</p>
[coordinator解析](./coordinator.md)

[worker解析](./worker.md)

[设计思路跳转](./Lab-1-Fxzbed.md)