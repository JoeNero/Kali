# 1 连接

输入下列指令，权限配置成root

```shell
adb root
```

可以用下面关机指令测试是否连接成功

```shell
adb reboot
```
或者用查看设备指令来查看设备是否连接
```shell
adb devices
```
若连接失败，插拔手机打开开发者模式和usb调试并且打开文件传输

调试若文件报read:eof相关错误执行以下命令，原因是缓冲空间不足

```shell
adb logcat -G 20M
adb logcat -c
```

# 2 编译调试

一个终端需要执行一次环境变量的配置，若关闭需要重新执行一次

cd 到Code的根目录下
配置环境

```shell
 source build/envsetup.sh
```
选择编译的版本
```shell
lunch
```
一般编译的版本是merlin-userdebug  //一般找这个然后将序列号输入

cd到你需要编译的目录mma

或者
```shell
./prebuilts/build-tools/linux-x86/bin/ninja -f out/combined-merlin.ninja libcam.hal3a.v3 |  tee build.log 
```
merlin.ninja 后面接你要推送的库(你所在项目下的mk文件中告诉你编译生成的动态库)

![生成库](/home/xtt/README/pic/Debug/生成库.png)

项目的根目录下编译(该编译方法，没有变动不会执行)
```shell
./prebuilts/build-tools/linux-x86/bin/ninja -f out/combined-merlin.ninja libmtkcam_3rdparty.customer
```
---
```shell
adb root
adb devices
adb disable-verity   #手机系统更改只读，只读无法adb push
adb remount			　#重新挂载
adb shell logcat|grep -E "onSnapClick|mCaptureStartTime"  #查看摄像头拍照时间
adb push libmtkcam_3rdparty.customer.so vendor/lib64
adb shell pkill camera*　#杀掉手机摄像头进程,若多次重启相机后，相机仍然故障无法使用，原因是版本太新需要将新版本的so库都push进去,新建一个临时文件，将新生成的so都复制过去，然后执行adb push *.so vendor/lib64
```



# 2 压力测试

用下列指令下载测试用的两个apk
```
adb install 
```

# 3 常用adb 命令

adb  reboot
adb  root
adb shell setenforce 0
adb shell setprop vendor.debug.camera.hdr.log 3
adb shell pkill camera*

//开启美颜预览dump 输入输出图
adb  reboot
adb  root
adb shell setenforce 0
adb shell setprop debug.camera.algo.asfb.dump 2

//开启美颜拍照dump 输入输出图
adb  reboot
adb  root
adb shell setenforce 0
adb shell setprop debug.camera.algo.asfb.dump 1

//开MY_LOGD
adb shell setprop persist.vendor.mtk.camera.log_level 3
adb shell setprop vendor.debug.fpipe.force.printio 1
adb shell setprop vendor.debug.tpi.s.log 1

//
开各模块log前，建议先关闭selinux权限，并确定logD是已经有打印的，如果没有打印可以用如下命令开启：
adb root
adb shell setenforce 0
adb shell setprop persist.vendor.mtk.camera.log_level 3  
adb shell pkill camera*

再按以下方法开对应模块的 log：
1. 开MTK Camera2 APP log
adb root
adb shell setprop vendor.debug.mtkcam.loglevel 4  


2. 开camera device hal3 log
log tag: mtkcam-dev3
adb root
adb shell setprop debug.camera.log.CameraDevice3 2


3. 开 AppStreamMgr 的 log
log tag:  mtkcam-AppStreamMgr
adb root
adb shell setprop vendor.debug.camera.log.AppStreamMgr 3
PS:
X>=1, dump per-frame callback image/meta/shutter/error message
X>=2, dump per-frame control metadata
X>=3, dump per-frame result metadata     
打开后，会有关键 log:   mtkcam-AppStreamMgr: [x-CallbackHandler::performCallback]   

4. 开Pipeline log 
log tag: mtkcam-PipelineFrameBuilder
adb root
adb shell setprop persist.vendor.debug.camera.log 3
adb shell pkill camera*
ps:
X>=2, Log every IPipelineFrame settings
X>=3, Log every IPipelineFrame settings and its PipelineContext

打开后，会有关键 log:   mtkcam-PipelineFrameBuilder: App image stream buffers=

5. 开 P1Node log
log tag: MtkCam/P1NodeImp
adb root
adb shell setprop vendor.debug.camera.log.p1node 3

6. 开preview/record 时P2S的log 

开 P2StreamingNode下StreamingFeaturePipe层以上(包括DispatchProcessor/StreamingProcessor)的log：
adb root  
adb shell setprop vendor.debug.mtkcam.p2.log 1

开StreamingFeaturePipe log：
adb root
adb shell setprop vendor.debug.fpipe.force.printio 1
adb shell setprop vendor.debug.tpi.s.log 1

# 4 保存截图

adb shell setenforce 0

adb shell setprop debug.camera.algo.asfb.dump 2