# 用户(组)管理
新建用户：useradd 用户名
查看用户：id 用户名 ||  tail /etc/passwd
切换用户：su - 用户名
删除用户：userdel -r 用户名
修改用户密码：passwd 用户名
修改用户属性：usermod     chage

添加用户组：groupadd group1  ||   useradd -g group1 user1
添加用户组：groupdel

# 网络管理
## 网络状态查看
ifconfig vs ip

## 网络配置

## 路由命令

## 网络故障排除

## 网络服务管理

## 常用网络配置文件


# 磁盘管理

# 进程管理
# 内存管理



# 常用命令
## 终端利用ssh登录远程服务器
安装ssh：`yum install ssh`
启动ssh：`service sshd start`
登录远程服务器：`ssh -p 50022 my@127.0.0.1`-p后面是端口 my是服务器用户名 127.0.0.1是服务器ip
输入密码：`my@127.0.0.1:`
回车输入密码即可登录
## 磁盘管理
`df -h /etc`

## yum命令
1. 列出所有可更新的软件清单命令：`yum check-update`
2. 更新所有软件命令：`yum update`
3. 仅安装指定的软件命令：`yum install <package_name>`
4. 仅更新指定的软件命令：`yum update <package_name>`
5. 列出所有可安裝的软件清单命令：`yum list`
6. 删除软件包命令：`yum remove <package_name>`
7. 查找软件包 命令：`yum search <keyword>`
8. 清除缓存命令:
清除缓存目录下的软件包`yum clean packages`
清除缓存目录下的 headers`yum clean headers`
清除缓存目录下旧的 headers `yum clean oldheaders`
清除缓存目录下的软件包及旧的headers `yum clean, yum clean all (= yum clean packages; yum clean oldheaders)`

## 数据库

## shell makefile


# GDB调试
`gdb -g text.c`
l,b(N,function),n,p,

# 多进程编写
消息队列：
共享内存：
信号量：

# 多线程编写

# TCP网络编写

# 查找、排序、二叉树递归算法

# 实现一个String类
