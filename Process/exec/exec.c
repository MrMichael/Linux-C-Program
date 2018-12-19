#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

char *const ps_argv[] = {"ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL};
char *const ps_envp[] = {"PATH=/bin:/usr/bin", "TERM=console", NULL};

int main(void)
{
	//ps是linux自带的应用程序
	//"ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL 都是命令行参数
	//这相当于在bash命令行输入：ps -o pid,ppid,pgrp,session,tpgid,comm
	
	//execl("/bin/ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);
	
	//execlp("ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);
	
	//execle("/bin/ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL, ps_envp);
	
	//这个函数在ubuntu中不存在
	//execlpe("ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL, ps_envp);
	
	//execv("/bin/ps", ps_argv);
	
	//execvp("ps", ps_argv);
	
	execve("/bin/ps", ps_argv, ps_envp);
	
	
	//由于exec函数只有错误返回值，只要返回了一定是出错
	//所以不需要判断它的返回值，直接在后面调用perror即可。
	perror("exec ps");
	exit(1);
	
	return 0;
}