#!/bin/bash  

# 多行注释
:<<EOF
# #! 是一个约定的标记，它告诉系统这个脚本需要什么解释器来执行，即使用哪一种 Shell。
# 首次运行出错运行：sed -i -e 's/\r$//' xxx.sh
EOF

echo "hello shell"
echo "hello world"

#变量
name="michael"	#变量名和等号之间不能有空格		!!!
echo ${name}	#调用变量:$变量名 或 ${变量名}
readonly name	#设置为只读变量
echo "My name is $name"
unset name		#删除变量，不能删除只读变量

#字符串
str='this is a string "name" $name'	#单引号字符串中的变量是无效的
str2="this is a string \"name\" $name"	#双引号里可以有变量和转义字符
echo $str
echo $str2
#拼接字符串
str3='hello,'$str''
str4="hello,$str2"
echo $str3
echo $str4
#获取字符串长度
echo ${#name}
#提取子字符串
str5=${str4:0:5}	#第0个字符开始截取5个字符
echo $str5

:<<EOF
数组
bash支持一维数组（不支持多维数组），并且没有限定数组的大小。
EOF
num=(1 2 3 4 5)	#用括号来表示数组，数组元素用"空格"符号分割开
students=("jack" "tom" "mike" "sherry" "ming")
echo ${num[0]}
echo ${students[0]}
# 获取数组所有元素
echo "array:,${students[*]}"
# 获取数组元素的个数
echo "length of array:,${#students[*]}"
# 取得数组单个元素的长度
echo "length of array element:,${#students[0]}"



