# banben1
1.设置一下用户名和邮箱
    $ git config --global user.name "your name"
    $ git config --global user.email "your mailbox"
  1.1版本库也叫仓库，英文是repository

2.工作区和版本库
    在Git中，有两个工作的部分：
    第一个部分叫工作区，也就是从目录打开的部分；
    第二个部分叫做版本库，也就是在工作区中有一个 .git 的目录，这个目录正常是隐藏的。
    在版本库中还有两个部分，第一部分叫 Stage，也就是暂存区，第二部分是 Git 为我们创造的 Master 目录。
  2.1用 git status 查看一下状态；
       使用 git add 将其添加到版本库中的 Stage 暂存区；
       最后我们在使用 git commit（-m ''方便 git log），一个文件才正式地进入版本库。
  2.2用 git diff 的方式来查看版本库中的文件和工作区中的文件是否有不同

3.我们开始修改文件，展示 Git 管理文件的强大之处
    git log（--pretty=oneline）：由近到远的显示我们的修改
    git reset --hard comment_id：回退到任一版本（回到过去）
    gir reflog：查找所有版本，方便从过去到未来

4.创建SSH密钥并更新至Github
    前文我们已经讲过了如何在本地上使用Git，但是Git最厉害的地方并不在于从本地使用，而是在于其支持协同工作，以及Github的简单上传和下载。
  4.1初次使用Git来配置密钥一般需要三步：
      生成密钥：生成密钥的语句如下$ ssh-keygen -t rsa -C "email@youremail.com"；vi ~/.ssh/id_rsa.pub
      设置远程仓库的密钥：登录
Github，点击右上角头像旁边的倒三角
选择其中的Settings
，在左边的项目栏里选择SSH and GPG keys，
点击New SSH              keys
把刚才复制下来的sSSH keys粘贴进去即可，title写不写都行，在设置好了之后，我们检擦一下密钥有没有生效。

$ ssh -T git@github.com
      修改git的remote url：git remote -v 查看远程地址，$ git remote set-url origin git@github.com:account/project.git

5.Git与Github：添加远程库从Github中下载文件


    $ git remote add origin git@github.com:.../first_git.git  #连接远程库和版本库
1
    $ git push origin master    #将版本库的内容推到远程库

    
$ git clone git@github.com:.../learngit.git  #从远程库中克隆
————————————————

载库的时候只下载最新的那个库，可以使用这个命令：
git clone git仓库地址 --depth=1
这样就只下载到最新版本，而不是带有全部历史版本的仓库。

海军上将光之翼
