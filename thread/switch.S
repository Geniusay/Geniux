[bits 32]
section .text
global switch_to
switch_to:

	;保存内核栈
	push esi
	push edi
	push ebx
	push ebp

	;得到栈中参数
	mov eax,[esp+20]	;获取cur，将cur的esp指针保存在self_kstack中
	mov [eax],esp

	;上半部分是保护cur线程的栈数据，下半部分是恢复next的栈数据
	mov eax,[esp+24]	;得到next参数
	mov esp,[eax]		;pcb的第一个成员self_kstack

	pop ebp
	pop ebx
	pop edi
	pop esi
	ret		;  此时的ret执行的是栈顶的kernel_thread