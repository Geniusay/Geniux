#include "string.h"
#include "global.h"
#include "debug.h"

/*将dst_地址起始的后size位置为value*/
void memset(void *dst_, uint8_t value, uint32_t size) {
	ASSERT(dst_ != NULL);
	uint8_t* dst = (uint8_t*)dst_;
	while (size-- > 0) {
		*(dst++) = value;
	}
}

/*将src_地址后size位的值复制到dst_中*/
void memcpy(void *dst_, const void *src_, uint32_t size) {
	ASSERT(dst_ != NULL);
	ASSERT(src_ != NULL);
	uint8_t* dst = dst_;
	const uint8_t* src = src_;
	while (size-- > 0) {
		*(dst++) = *(src++);
	}
}

/*比较，如果相等则为0，a>b为1，a<b为-1*/
int memcmp(const void* a_, const void* b_, uint32_t size) {
	const char* a = a_;
	const char* b = b_;
	ASSERT(a != NULL || b != NULL);
	while (size-- > 0) {
		if (*a > *b) {
			return 1;
		}
		else if (*a < *b) {
			return -1;
		}
		a++;
		b++;
	}
	return 0;
}

/*字符串从src_复制到dst_*/
char* strcpy(char* dst_, const char* src_) {
	ASSERT(dst_ != NULL && src_ != NULL);
	char* dst = dst_;
	while ((*(dst_++) = *(src_++)));
	return dst;
}

/*返回字符串长度*/
uint32_t strlen(const char* str_) {
	ASSERT(str_ != NULL);
	const char* p = str_;
	while (*(p++));
	return p - str_ - 1;
}

/*比较两个字符串,a=b返回0,a>b返回1,a<b返回-1*/
int8_t strcmp(const char* a, const char* b) {
	ASSERT(a != NULL && b != NULL);
	while (*a != 0 && *a == *b) {
		a++;
		b++;
	}
	return *a<*b ? -1 : *a>*b;
}

/*从前往后找到ch在str中首次出现的位置*/
char* strch(const char* str, const uint8_t ch) {
	ASSERT(str != NULL);
	while (*str!=0)
	{
		if (*str == ch) {
			return (char*)str;
		}
		str++;
	}
	return NULL;
}

/*从后往前找到ch在str中首次出现的位置*/
char* strrch(const char* str, const uint8_t ch) {
	ASSERT(str != NULL);
	const char* chr = NULL;

	while (*str != 0) {
		if (*str == ch) {
			chr = str;
		}
		str++;
	}
	return (char*)chr;
}

/*将字符串src_拼接到dst后*/
char* strcat(char* dst_, const char* src_) {
	ASSERT(dst_ != NULL && src_ != NULL);
	char* dst = dst_;
	while (*(dst_++));
	--dst_;
	while ((*(dst_++) = *(src_++)));
	return dst;
}

/*解决内存覆盖问题，将拼接的字符串重新分配一个地址*/
char* newstrcat(char* dst_, const char* src_) {
	ASSERT(dst_ != NULL && src_ != NULL);
	char* dst = "";
	char* p = dst;
	while (*(p++)=*(dst_++));
	--p;
	while ((*(p++) = *(src_++)));
	return dst;
}

/*在字符串str中查找字符ch出现的次数*/
uint32_t strchrs(const char* str, uint8_t ch) {
	ASSERT(str != NULL);
	uint32_t count = 0;
	while (*str != 0) {
		if (*(str++) == ch) {
			count++;
		}
	}
	return count;
}