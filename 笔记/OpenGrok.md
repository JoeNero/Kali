# 1 下载安装包

先确认电脑系统版本

```shell
uname -a
```

输出打印

```shell
Linux xtt-ThinkCentre-M720t-N000 4.15.0-91-generic #92~16.04.1-Ubuntu SMP Fri Feb 28 14:57:22 UTC 2020 x86_64 x86_64 x86_64 GNU/Linu
```

# ２ctags

查看ctags

```ctags
ctags --version
```

输出打印

```shell
Exuberant Ctags 5.9~svn20110310, Copyright (C) 1996-2009 Darren Hiebert
  Addresses: <dhiebert@users.sourceforge.net>, http://ctags.sourceforge.net
  Optional compiled features: +wildcards, +regex
```

版本是exuberant ctags 5.9 -svn20110310
听说不求行 毕竟那么长时间没更新了
换个版本下载
先卸载ctags
```shell
sudo apt remove exuberant-ctags -y
```
确认卸载
```shell
ctags --version
```
输出打印
```
程序“ctags”尚未安装。 您可以使用以下命令安装：
sudo apt install exuberant-ctags
```

安装新鲜的universal-ctags
universal-ctags是什么？A maintained ctags implementation, https://ctags.io,一个负责的ctags实现，在github上开源并且持续更新和维护。
先安装autoconf
```shell
sudo apt install autoconf
```
私人git ctags源代码
https://github.com/JoeNero/ctags.git

git clone 下到你的目录下

进入目录
```shell
./autogen.sh 
./configure --prefix /home/xtt/OpenGrok/ctags #个人安装路径，文件夹是自己建的
```
进入你ctags的安装目录
cd bin
链接到用户bin下
```shell
sudo ln -s ctags /usr/bin/ctags
```
有的时候链接不行，建议直接move
```shell
sudo mv ctags /usr/bin
```
检查是否安装成功
```shell
ctags --version
```
输出打印
```shell
Universal Ctags 0.0.0(e87283a), Copyright (C) 2015 Universal Ctags Team
Universal Ctags is derived from Exuberant Ctags.
Exuberant Ctags 5.8, Copyright (C) 1996-2009 Darren Hiebert
  Compiled: Mar 30 2020, 13:49:01
  URL: https://ctags.io/
  Optional compiled features: +wildcards, +regex, +iconv, +option-directory, +packcc
```
表示安装成功



# 3 安装tomcat

官网https://tomcat.apache.org/download-90.cgi

下载tar.gz包

解压并重新命名成tomcat
配置环境变量(这是重命名后的tomcat路径)指令pwd查看命令

```shell
vim ~/.bashrc
```

在.bashrc最后一行添加

```shell
export CATALINA_HOME="/home/xtt/OpenGrok/tomcat"
```

进入tomcat的bin目录
运行startup.sh脚本启动tomcat服务
```
sudo sh startup.sh
```
在浏览器中输入
http://localhost:8080/

出现以下内容代表tomcat配置成功，若未出现检查端口和环境配置tomcat路劲是否正确

![tomcat](/home/xtt/README/pic/opengrok/tomcat.png)



# 4 OpenGrok搭建

低版本的下载链接

https://github.com/oracle/opengrok/releases/tag/0.12.1.5

下载tar.gz就可以了

网上说新的版本可能存在各种问题

如下版本存在各自的问题
(1). https://github.com/oracle/opengrok/releases/tag/1.1-rc38 无法完成代码的符号解析
(2). https://github.com/oracle/opengrok/releases/tag/0.12.1.5
(3). https://github.com/oracle/opengrok/releases/tag/0.13-rc10
我反正是下的0.12.1.5

解压就行

配置环境变量
```
vim ~/.bashrc
```
该路径是你opengrok解压后存放的路径
```shell
export OPENGROK_PATH="/home/xtt/OpenGrok/opengrok" 
```

# 5 创建索引

编写脚本
注意: soure_root为你源码存放的路径,不一定和我一样,我是把源码给移到这个文件夹下了
索引同理，自己创建的
另外注意　tomcat 这一行.是你的tomcat存放路径
export OPENGROK_TOMCAT_BASE=/home/xtt/Opengrok/tomcat
```shell
#***************************************************************#
#ScriptName: opengrok_indexing.sh
# Author: xtt
# Create Date: 2018-08-22
#***************************************************************#

opengrok_path="/home/xtt/OpenGrok/opengrok"
source_root="${opengrok_path}/source/src"   		#你源码存放的路径
indexing_root="${opengrok_path}/source/index"		#你索引存放的路径

# indexing for the source code
# 1. remove the old indexing if exist
if [ -d ${indexing_root}/ ];then
rm -rf ${indexing_root}/
fi
mkdir -p ${indexing_root}

# 2. export the OpenGrok environment variables
export OPENGROK_TOMCAT_BASE=/home/xtt/Opengrok/tomcat
export OPENGROK_INSTANCE_BASE=opengrok

export JAVA_OPTS="-Xmx1024m"
# java -jar ${opengrok_path}/lib/opengrok.jar for command help
java $JAVA_OPTS -jar ${opengrok_path}/lib/opengrok.jar -P -S -v \
-s ${source_root} \
-d ${indexing_root} \
-W ${indexing_root}/configuration.xml \
-w opengrok # webapp-context  ${OPENGROK_TOMCAT_BASE}/webapps/webapp-context 

```

# 6 将openGrok部署到Tomcat

进入opengrok的lib路径，将source.war移动到tomcat目录下的webapps,会自动解压成source

进入tomcat/webapps/source/WEB-INF,找到web.xml文件

![索引配置](/home/xtt/README/pic/opengrok/索引配置.jpg)



重新生成索引

运行上面的脚本opengrok_indexing.sh

重新启动tomcat








