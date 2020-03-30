#***************************************************************#
#ScriptName: opengrok_indexing.sh
# Author: zhongxiao.yzx
# Create Date: 2018-08-22
#***************************************************************#

opengrok_path="/home/hoperun/opengrok/opengrok"
source_root="/home/hoperun/opengrok/src"
indexing_root="/home/hoperun/opengrok/index"

# indexing for the source code
# 1. remove the old indexing if exist
if [ -d ${indexing_root}/ ];then
    rm -rf ${indexing_root}/
	fi
	mkdir -p ${indexing_root}

	# 2. export the OpenGrok environment variables
	export OPENGROK_TOMCAT_BASE=/home/hoperun/opengrok/tomcat
	export OPENGROK_INSTANCE_BASE=opengrok

	export JAVA_OPTS="-Xmx1024m"
	# java -jar ${opengrok_path}/lib/opengrok.jar for command help
	java $JAVA_OPTS -jar ${opengrok_path}/lib/opengrok.jar -P -S -v \
	-s ${source_root} \
	-d ${indexing_root} \
	-W ${indexing_root}/configuration.xml \
	-w opengrok # webapp-context  ${OPENGROK_TOMCAT_BASE}/webapps/webapp-context 
