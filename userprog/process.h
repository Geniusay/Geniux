#ifndef _USERPROG_PROCESS_H
#define _USERPROG_PROCESS_H

#define USER_VADDR_START 0x8048000

void page_dir_activate(struct task_struct* pthread);
void start_process(void* filename_);
void process_activate(struct task_struct* pthread);
uint32_t* create_page_dir(void);
void create_user_vaddr_bitmap(struct task_struct* user_prog);
void process_execute(void* filename, char* name);
#endif // !_USERPROG_PROCESS_H