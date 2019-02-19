#!/bin/bash

:<<EOF
算术运算
原生bash不支持简单的数学运算，但是可以通过其他命令来实现，例如 awk 和 expr。
EOF
val=`expr 2 + 6`	#使用反引号而不是单引号,运算符之间必须用空格隔开
val=`expr 2 \* 6`
val=`expr 12 / 3`
val=`expr 13 % 3`
val=`expr 3 == 3`
echo "sum is : $val"

#关系运算符
echo "关系运算符"
a=10
b=20
#中括号两边必须有空格
if [ $a -eq $b ]	#等于
then
	echo "result is true"
else
	echo "result is false"
fi

if [ $a -ne $b ]	#不等于
then
	echo "result is true"
else
	echo "result is false"
fi

if [ $a -gt $b ]	#大于
then
	echo "result is true"
else
	echo "result is false"
fi

if [ $a -lt $b ]	#小于
then
	echo "result is true"
else
	echo "result is false"
fi

if [ $a -ge $b ]	#大于等于
then
	echo "result is true"
else
	echo "result is false"
fi

if [ $a -le $b ]	#小于等于
then
	echo "result is true"
else
	echo "result is false"
fi

#布尔运算符	且或非
echo "布尔运算符"
if [ $a -eq $b -o $a -lt $b ]	#或
then
	echo "result is true"
else
	echo "result is false"
fi

if [ $a == 10 -a $a -lt $b ]	#且
then
	echo "result is true"
else
	echo "result is false"
fi

if [ ! $a -ne $b ]				#非
then
	echo "result is true"
else
	echo "result is false"
fi

#字符串运算符
:<<EOF
=	检测两个字符串是否相等
!=	检测两个字符串是否不相等
-z	检测字符串长度是否为0
-n	检测字符串长度是否不为0
$	检测字符串是否为空
EOF
echo "字符串运算符"
c="abc"
d="abc"
if [ $c = $d ]		#用==也可以		
then
	echo "result is true"
else
	echo "result is false"
fi

if [ -z $c ]		
then
	echo "result is true"
else
	echo "result is false"
fi










