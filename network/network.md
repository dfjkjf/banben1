[TOC]
#TCP/IP
一种通信协议，*源地址IP*和*目的地址IP*：找到两台网络设备；
*源程序端口*和*目的程序端口*：确定网络设备中的哪个进程

+ 建立TCP连接，三次握手：
*在socket编程中，这一过程由客户端执行connect来触发*
A与B建立TCP连接时：首先A向B发SYN（同步请求），然后B回复SYN+ACK（同步请求应答），最后A回复ACK确认。
若在握手过程中某个阶段莫名中断，TCP 协议会再次以相同的顺序发送相同的数据包。
+ 断开TCP连接，四次挥手：
*在socket编程中，这一过程由客户端或服务端任一方执行close来触发，整个流程如下*
首先A向B发FIN（关闭请求）同时进入FIN_WAIT_1状态，
然后B回复ACK（同意A关闭）同时进入CLOSE_WAIT状态，
接着B向A发FIN（关闭请求，因为TCP连接是全双工）同时进入LAST_WAIT状态，
最后A回复ACK（同意B关闭），B收到ACK后关闭连接，A等待2MSL后依然没有收到回复，则证明B已正常关闭，那A也可以关闭连接

#面试常问
1. 为什么要三次握手而不是两次？
为了防止已失效的连接请求报文段突然又传送到了服务端，占用服务端资源。
2. 为什么关闭连接是四次挥手？
TCP是全双工模式，当A向B发送FIN时A还可以接受B的数据
3. TCP如何保证可靠传输
TCP是字节流传输协议，发送消息前的三次握手，发送过程中的顺序编号，确认应答(ACK)机制，开启时钟计时，客户端超时重传，服务端的差错检测(检验和)等。
4. 如何建立可靠的UDP连接
UDP要想可靠，就要接收方收到UDP之后回复个确认包，发送方有个机制，收不到确认包就要重新发送，每个包有递增的序号，接收方发现中间丢了包就要发重传请求。当网络太差时候频繁丢包，防止越丢包越重传的恶性循环，要有个发送窗口的限制，发送窗口的大小根据网络传输情况调整，调整算法要有一定自适应性。
5. 粘包问题如何处理？
粘包和TCP没关系，要建立健壮的应用层协议。
+ 尾部标记序列。通过特殊标识符表示数据包的边界，例如\n\r，\t，或者一些隐藏字符。
+ 头部标记分步接收。在TCP报文的头部加上表示数据长度。
+ 应用层发送数据时定长发送。


如果又要利用udp的快速响应优点，又想可靠传输，那么只能考上层应用自己制定规则了。
常见的使用udp的例子：ICQ,QQ的聊天模块。
以qq为例的一个说明：
登陆采用TCP协议和HTTP协议，你和好友之间发送消息，主要采用UDP协议，内网传文件采用了P2P技术。总来的说：
1.登陆过程，客户端client 采用TCP协议向服务器server发送信息，HTTP协议下载信息。登陆之后，会有一个TCP连接来保持在线状态。
2.和好友发消息，客户端client采用UDP协议，但是需要通过服务器转发。腾讯为了确保传输消息的可靠，采用上层协议来保证可靠传输。如果消息发送失败，客户端会提示消息发送失败，并可重新发送。
3.如果是在内网里面的两个客户端传文件，QQ采用的是P2P技术，不需要服务器中转。


#DNS
DNS（Domain Name System）服务是和 HTTP 协议一样位于应用层的协议。它提供域名到 IP 地址之间的解析服务。
用户通常使用主机名或域名来访问对方的计算机，而不是直接通过 IP地址访问。如：baidu.com
DNS 协议提供通过域名查找 IP 地址，或逆向从 IP 地址反查域名的服务。

#socket编码实例
服务端：
服务器端先初始化socket，然后与端口绑定，对端口进行监听，调用accept阻塞，等待客户端连接。
`socket() -> bind() -> listen() -> accept()`
客户端：
客户端先初始化socket，然后与服务端连接，服务端监听成功则连接建立完成
`socket() -> connect()`
完成上面的步骤后即可以开始数据的传输了，数据传输结束后再调用close关闭连接，服务端还要关闭监听。

