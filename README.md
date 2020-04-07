**开发的本职工作永远是完成迭代需求，修复bug，研究新框架新组件这类工作。**
------
# GitHelp
## git初始化
1. git安装：`$ sudo apt-get install git`
2. 配置用户名邮箱：`$ git config --global user.name "lxr"   $ git config --global user.email "980436373@qq.com"`
3. 查看配置：`$ git config --list

## 提交
+ git是对比仓库内外文件状态，只要git commit那仓库内外文件即一致
+ git add filename 后悔了 在git commit之前 git reset filename
+ 觉得新版本不好想回退到之前版本，git reset <commitID>(commitID通过git log查询)
   +（默认） --mixed 保留仓库外变更且处于modified（方便改写）
      + --soft 保留仓库外变更且处于staged(没啥用)
      + --hard 不保留仓库外变更（自己的改动都不要了，和仓库一致）
+ 觉得旧版本不好又想回到新版本，git reset <commitID>(commitID通过git reflog查询)，如果是回到最新版本 git pull

## 分支
1. 创建依据旧分支新分支 `$ git checkout -b <branchname>(新分支名字) <template>(依据分支，没有则以当前所在分支为模板)`
2. 查看所有分支 `$ git branch`        切换分支 `$ git checkout <branchname>`

## 合并
合并分支的**变更**而不是分支的**内容**
每次变更都生成新的commit，合并即是把这些变更(commit)整合在一块`$ git merge <branchname>`
1. master完成框架开发，吩咐小A和小B各自完成模块a、b开发
2. 小A以master为模板开辟新分支xiaoAworks，并完成模块a开发
3. 小B以master为模板开辟新分支xiaoBworks，并完成模块b开发
4. master合并小A和小B的分支，`$ git merge xiaoAworks` `$ git merge xiaoBworks`
5. 解决冲突

## 远端仓库
1. `$ git clone` 小A和小B都下载远端仓库
2. 小A开发模块本地分支xiaoAworks推送至远端仓库 `$ git push`
   + 第一次会提示远端没有你的分支，可以在远端设置新分支并提交 `$ git push --set-upstream origin <branchname>`也可以用这种方法提交到新仓库新分支(git remote查看连接到的远程分支，git branch -a查看所有分支)
3. 组长拉取远程仓库信息 `$ git fetch`
   + 发现新增分支xiaoAworks，于是 `$ git checkout -b xiaoAworks origin xiaoAworks`
   + 再次发现此分支变更时直接 `$ git pull`

## 变基
1. 组长给小A和小B分配了任务，同时自己也在master上开发，当组长merge小A小B分支时，会把AB的commitID添加到自己新增的commit后面
`$ git rebase master`
2. 会发生冲突，解决完后 `$ git add .`放入staged区，然后继续下一个节点的rebase `$ git rebase --continue`

## 创建SSH密钥并更新至Github
前文我们已经讲过了如何在本地上使用Git，但是Git最厉害的地方并不在于从本地使用，而是在于其支持协同工作，以及Github的简单上传和下载。
初次使用Git来配置密钥一般需要三步：
1. 生成密钥：生成密钥的语句如下`$ ssh-keygen -t rsa -C "email@youremail.com"` `vim ~/.ssh/id_rsa.pub`
2. 设置远程仓库的密钥：登录Github，点击右上角头像旁边的倒三角选择其中的Settings，在左边的项目栏里选择SSH and GPG keys，点击New SSH keys把刚才复制下来的sSSH keys粘贴进去即可，title写不写都行。
3. 在设置好了之后，我们检擦一下密钥有没有生效：`$ ssh -T git@github.com`
4. 修改git的remote url：git remote -v 查看远程地址，`$ git remote set-url origin git@github.com:account/project.git`
5. Git与Github：添加远程库从Github中下载文件
```
$ git remote add origin(自命名) git@github.com:.../first_git.git  #连接远程库和版本库
$ git push origin master    #将版本库的内容推到远程库    
$ git clone git@github.com:.../learngit.git  #从远程库中克隆
```
下载库的时候只下载最新的那个库，可以使用这个命令：
`$ git clone git仓库地址 --depth=1`
这样就只下载到最新版本，而不是带有全部历史版本的仓库。


