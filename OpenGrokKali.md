安装universal-ctags
卸载exuberant-ctags
```
sudo apt-get purge ctags
```
下载universal-ctags源码
```
git clone https://github.com/universal-ctags/ctags.git
```
编译及安装
```
cd ctags
./autogen.sh 
./configure
make
sudo make install
```
安装pip3
```shell

curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
sudo python3 get-pip.py
```
安装tomcat
```shell
tar zxvf apache-tomcat-8.5.53.tar.gz 
sudo mv apache-tomcat-8.5.53/ /opt/apache-tomcat-8.5.53
sudo ln -s /opt/apache-tomcat-8.5.37/ /opt/tomcat8
/opt/tomcat8/bin/startup.sh

```

安装opengrok
```
sudo tar zxvf opengrok-1.3.11.tar.gz -C /opt
sudo mv opengrok-1.3.11 /opt/opengrok
cd /opt/opengrok/tools

```

配置opengrok

```shell
cd /opt/opengrok
sudo mkdir -p /opt/opengrok/etc         # Opengrok配置文件目录
sudo mkdir -p /index/src                # Opengrok索引代码目录（可以指定任意目录）


```

```shell
sudo cp -rf CLionProjects GOPATH /index/src

```












