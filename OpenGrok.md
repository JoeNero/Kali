```shell
sudo add-apt-repository ppa:webupd8team/java
```

oracle
user  526988861@qq.com
passwd 1997225XTTxtt

opengrok

```shell
    sudo python3 bin/deploy.py -c etc/configuration.xml -D lib/source.war /var/lib/tomcat8/webapps


```

```shell
sudo apt-get update

vi /etc/profile

JAVA_HOME=/usr/jdk
CLASSPATH=$JAVA_HOME/lib/
PATH=$PATH:$JAVA_HOME/bin
export PATH JAVA_HOME CLASSPATH

source /etc/profile
```



运行脚本open.sh

```shell
sudo bash run.sh
```



创建索引脚本
```shell
#****************************************************************#
# ScriptName: opengrok_indexing.sh
# Author: zhongxiao.yzx
# Create Date: 2018-08-22
#***************************************************************#

opengrok_path="/home/xtt/OpenGrok/opengrok-1.3.11"
source_root="${opengrok_path}/source/mychain"
indexing_root="${opengrok_path}/source/indexing"

# indexing for the source code
# 1. remove the old indexing if exist
if [ -d ${indexing_root}/ ];then
    rm -rf ${indexing_root}/
fi
mkdir -p ${indexing_root}

# 2. export the OpenGrok environment variables
export OPENGROK_TOMCAT_BASE=/home/xtt/OpenGrok/apache-tomcat-9.0.33
export OPENGROK_INSTANCE_BASE=opengrok

export JAVA_OPTS="-Xmx1024m"
# java -jar ${opengrok_path}/lib/opengrok.jar for command help
java $JAVA_OPTS -jar ${opengrok_path}/lib/opengrok.jar -P -S -v \
-s ${source_root} \
-d ${indexing_root} \
-W ${indexing_root}/configuration.xml \
-w opengrok # webapp-context  ${OPENGROK_TOMCAT_BASE}/webapps/webapp-context 
```


新配置的vim使用
ctrl + q 进入命令行

sudo apt-get install tomcat8 
sudo /etc/init.d/tomcat8 restart 