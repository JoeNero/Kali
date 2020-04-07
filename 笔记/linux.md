# 1 vim

vim 配置

vim .vimrc

以下配置满足日常使用，

```shell
set nu                                                           
syntax on
set showcmd
set encoding=utf-8
set autoindent
set tabstop=2
set shiftwidth=4
set cursorline
set cursorcolumn
```
快捷键:
ctrl +d :下翻一页
ctrl + u: 上翻一页
gg  /   ctrl+g 　文件末尾

ifconfig
ip地址

![image-20200328153351613](/home/xtt/.config/Typora/typora-user-images/image-20200328153351613.png)



# ln

# grep

# mv

移动命令

# ps
可通过ps 来查看，通过参数 -o 来查看,只能静态显示

```shell
ps -eo pid,tty,user,comm,lstart,etime | grep redis
```

# VSCode

ctrl + k ctrl + 0 折叠所有的代码

ctrl + k  ctrl +j 展开所有的代码