# 1 编译

cd 到根目录下
配置环境
```shell
 source build/envsetup.sh
```
选择编译的版本
```shell
lunch
```
一般编译的版本是merlin-userdebug  //一般找这个然后将序列号49输入
编译

```shell
./prebuilts/build-tools/linux-x86/bin/ninja -f out/combined-merlin.ninja libmtkcam_3rdparty.customer
```
经常使用的是这个.so，单独编译它

输出库的路径

~/Code/out/target/product/merlin/vendor/lib64$ 

# 2 ADB
```shell
adb root
adb reboot
cd out/target/product/merlin/vendor/lib64
#手机系统更改只读，只读无法adb push
adb disable-verity   
#重新挂载
adb remount			　
#推送到手机上
adb push libmtkcam_3rdparty.customer.so vendor/lib64
#杀掉手机摄像头进程,若多次重启相机后，相机仍然故障无法使用，原因是版本太新需要将新版本的so库都push进去,新建一个临时文件，将新生成的so都复制过去，然后执行adb push *.so vendor/lib64 或者直接adb reboot重新启动
adb shell pkill camera*　
```
adb配置缓冲空间打印log
```shell
adb logcat -G 6M
adb logcat
#adb logcat | grep "switched"
```


用如何内容打印

ALOGD("Ming:mAlgoFlag=0x%x",mAlgoFlag);



adb logcat |grep "Ming"



app 下发的指令

mAlgoFlag

美颜下发的指令

ALGO_FACEBEAUTY_PREVIEW

0x205　

0x201 美颜关闭