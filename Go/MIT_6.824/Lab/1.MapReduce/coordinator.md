# 该解析对应src/mr/coordinator.go

Source Code:
```go
package mr
//调度进程的入口
import "log"
import "net"
import "os"
import "net/rpc"
import "net/http"


type Coordinator struct {
	// Your definitions here.

}

// Your code here -- RPC handlers for the worker to call.

//
// an example RPC handler.
//
// the RPC argument and reply types are defined in rpc.go.
//
func (c *Coordinator) Example(args *ExampleArgs, reply *ExampleReply) error {
	reply.Y = args.X + 1
	return nil
}


//
// start a thread that listens for RPCs from worker.go
//
func (c *Coordinator) server() {
	rpc.Register(c)
	rpc.HandleHTTP()
	//l, e := net.Listen("tcp", ":1234")
	sockname := coordinatorSock()
	os.Remove(sockname)
	l, e := net.Listen("unix", sockname)
	if e != nil {
		log.Fatal("listen error:", e)
	}
	go http.Serve(l, nil)
}

//
// main/mrcoordinator.go calls Done() periodically to find out
// if the entire job has finished.
//
func (c *Coordinator) Done() bool {
	ret := false

	// Your code here.


	return ret
}

//
// create a Coordinator.
// main/mrcoordinator.go calls this function.
// nReduce is the number of reduce tasks to use.
//
func MakeCoordinator(files []string, nReduce int) *Coordinator {
	c := Coordinator{}

	// Your code here.


	c.server()
	return &c
}

```
```go
type Coordinator struct {

}
```
留存的Coordinator struct

接下来定义rpc调用的函数，并且演示了一个rpc函数调用的事例

```go
// Your code here -- RPC handlers for the worker to call.

//
// an example RPC handler.
//
// the RPC argument and reply types are defined in rpc.go.
//
func (c *Coordinator) Example(args *ExampleArgs, reply *ExampleReply) error {
	reply.Y = args.X + 1
	return nil
}   
```

接下来展示在go中起一个线程监听来自worker.go的rpc请求？（待定）
```go
//
// start a thread that listens for RPCs from worker.go
//
func (c *Coordinator) server() {
	rpc.Register(c)
	rpc.HandleHTTP()
	//l, e := net.Listen("tcp", ":1234")
	sockname := coordinatorSock()
	os.Remove(sockname)
	l, e := net.Listen("unix", sockname)
	if e != nil {
		log.Fatal("listen error:", e)
	}
	go http.Serve(l, nil)
}
```

- 对于*__rpc.Register(c)__*的解析：
    rpc.Register()是go语言库中的一个函数，用于在rpc服务器上注册一个对象，进行网络调用。
    rpc.Register()函数用于将一个对象注册到rpc服务器上，以便可以通过网络进行远程调用，对于上文的rpc.Register(c)意味着注册Coordinator类的实例c到rpc服务器，在这里coordinator是由自己定义。

    下文是一段简单的代码演示如何注册一个对象并且启动rpc服务器
    ```go
    import (
        "log"
        "net"
        "net/rpc"
    )

    type MyService struct {
        // 定义RPC服务方法的结构体
    }

    func (s *MyService) MyMethod(args ArgsType, reply *ReplyType) error {
        // 实现RPC服务方法的逻辑
        return nil
    }

    func main() {
        myService := new(MyService) //new方法创建出一个MyService对象
        rpc.Register(myService)     //rpc注册myService

        listener, err := net.Listen("tcp", ":1234") //启用net服务监听tcp 端口1234 监听完成的成功对象放入了listener 抛出错误放err
        if err != nil {                             //异常处理  
            log.Fatal("Listen error:", err)
        }

        for {                                       //无限循环等待accept
            conn, err := listener.Accept()          //accept方法 成功后的对象放入conn
            if err != nil {                         //异常处理
                log.Fatal("Accept error:", err)
            }

            go rpc.ServeConn(conn)                  //ServeConn连接先前初始化完成的conn实例
        }                                           //该方法从conn中读取RPC请求，解析请求，提取请求的方法名、参数。根据方法名找到register了的RPC服务对象，调用相应的RPC服务方法，将请求的参数传递给该方法。RPC服务方法执行相应的逻辑，生成结果。并且封装成RPC响应，通过网络连接发送给调用对象
    }
    ```

- 对于rpc.HandleHTTP()的解析：
    HandleHTTP是go中用于将rpc服务器注册到http服务器的函数，以便通过http协议调用rpc服务，当调用rpc.HandleHTTP时，它会将默认的RPC处理程序注册到http服务路由器上。这样你就可以通过HTTP协议调用、访问注册的RPC服务。

    rpc.HandleHTTP()执行：
    1. 创建一个默认的rpc处理程序
    2. 注册rpc处理程序到http默认的服务路由器上
    3. 为rpc服务提供一个http路径（默认为/rpc）
    4. 当在http请求到达，请求被转发到rpc处理程序中，实现http协议调用rpc服务
    
    ```go
    type MyService struct {
    // 实现RPC服务接口的结构体
    }

    func (s *MyService) MyMethod(args ArgsType, reply *ReplyType) error {
        // 实现RPC服务方法的逻辑
        return nil
    }

    func main() {
        myService := new(MyService)
        rpc.Register(myService)

        rpc.HandleHTTP()

        err := http.ListenAndServe(":8080", nil)        //http监听8080端口
        if err != nil {
            log.Fatal("ListenAndServe error:", err)
        }
    }

    ```

- 对于net.Listen()的解析：
    是go语言用于创建Unix套接字的函数，该函数会创建一个Unix域套接字，绑定到一个指定文件路径（这里的sockname入参即为保存的路径）。这样你可以使用Unix域套接字来进行本地进程间通信。

    下面是一段简单示例：
    ```go
    package main

    import (
        "log"
        "net"
        "os"
    )

    func main() {
        sockname := "/tmp/mysocket.sock"

        // 删除已存在的套接字文件
        os.Remove(sockname)

        // 创建Unix域套接字
        listener, err := net.Listen("unix", sockname)
        if err != nil {
            log.Fatal("Listen error:", err)
        }
        defer listener.Close()      //defer关键字用于延迟函数，为了在程序发生Listen error时，Log.Fatal()抛异常终止的时候，仍然能调用Listener.Close(),停止监听

        log.Println("Listening on", sockname)   //打印log

        // 接受连接请求
        for {
            conn, err := listener.Accept()
            if err != nil {
                log.Fatal("Accept error:", err)
            }

            // 处理连接
            go handleConnection(conn)   //处理业务
        }
    }

    func handleConnection(conn net.Conn) {
        defer conn.Close()

        // 处理连接逻辑
        // ...
    }
    ```
- 对于http.Serve()的解析:
    go语言使用这个函数启动http服务器并且监听指定地址的函数调用，在源代码中l是一个Listener对象，它在net.Listen()中初始化。后面的nil参数代表，使用默认的http请求处理器。

- 对于coordinator.go中的Done()方法，如果实体的工作完成，调用Done()方法 ？ （待定）

- 对于coordinator.go中的MakeCoordinator()方法，它将在main/mrcoordinator.go中被调用，它将用来创建一个Coordinator对象，而这个对象由你自己定义。

以上为对于coordinator.go原始代码的解析。

---

具体实现思路跳转 [Lab-1-Fxzbed](./Lab-1-Fxzbed.md)
任务简介跳转    [Lab-1-MapReduce](./MapReduce.md)