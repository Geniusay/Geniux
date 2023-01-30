#ifndef __KERNEL_DEBUG_H
#define __KERNEL_DEBUG_H
void panic_spin(char* filename, int line, const char* func, const char* condition);
#define PANIC(...) painc_spin(__FILE__,__LINE__,__func__,__VA_ARGS__)  //这里是ansi c中常用的宏，分别是文件地址，代码行数，函数以及变量

#ifdef NDEBUG
	#define ASSERT(CONDITION) ((void)0)
#else
	#define ASSERT(CONDITION)\
			if(CONDTION){}else{\
				PANIC(#CONDITION); \
			}
#endif // NDEBUG

#endif // !__KERNEL_DEBUG_H
