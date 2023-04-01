#ifndef _KERNEL_MEMORY_H
#define _KERNEL_MEMORY_H
#include "stdint.h"
#include "bitmap.h"
#include "list.h"
/* 内存池标记 */
enum pool_flags {
	PF_KERNEL = 1,
	PF_USER = 2
};

struct virtual_addr {
	struct bitmap vaddr_bitmap;
	uint32_t vaddr_start;		//管理的虚拟位置的起始
};

struct mem_block {
	struct list_elem free_elem;
};

struct mem_block_desc {
	uint32_t block_size;	  //内存块大小
	uint32_t block_per_arena; //本arena中可容纳此mem_block的数量
	struct list free_list;	 // arena链表
};


#define DESC_CNT 7
#define PG_P_1 1
#define PG_P_0 0
#define PG_RW_R 0
#define PG_RW_W 2
#define PG_US_S 0
#define PG_US_U 4
extern struct pool kernel_pool, user_pool;
void mem_init(void);
void* palloc(struct pool*  m_pool);
void* get_kernel_pages(uint32_t pg_cnt);
uint32_t addr_v2p(uint32_t vaddr);
void* get_a_page(enum pool_flags pf, uint32_t vaddr);
void* malloc_page(enum pool_flags pf, uint32_t pg_cnt);
uint32_t* pde_ptr(uint32_t vaddr);
uint32_t* pte_ptr(uint32_t vaddr);
void block_desc_init(struct mem_block_desc* desc_array);
void* sys_malloc(uint32_t size);
void sys_free(void* ptr);
#endif
