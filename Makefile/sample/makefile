
#自定义变量，变量引用为$(变量)
EXE = test			
SRC = test.c

#预定义变量
CC = gcc			#C 语言编译程序
CFLAGS = -g			#传递给 CC 程序的标志
LDFLAGS = -L -lFOO	#传递给链接程序的标志

#makefile规则，第一个目标文件为make默认的执行目标
all:test.o		
	gcc -o test test.c
	
exe1:$(SRC)			#输入make exe1执行特定的目标规则
	$(CC) $(LDFLAGS) -o $(EXE) $(SRC)
	
exe2:$(SRC)
	$(CC) -o $(EXE) $^	#$^包含所有的依赖文件

.PHONY:clean		#将目标文件clean设置为伪目标，该目标的规则被执行后不产生文件
clean:				#makefile规则
	rm -f $(EXE) *.o	#*.o是指任意.o文件