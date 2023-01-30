SECTION MBR vstart=0x7c00    ;告诉编译器我的起始编译地址是 0x7c00
	
;利用cs(因为jmp 0:0x7c00，所以一开始是0) 来初始化ax,ds,es,ss,fs,gs,这类sreg寄存器是无法直接存储立即数的即直接赋值,所以需要通过cs来转移
	mov ax,cs				
	mov ds,ax
	mov es,ax
	mov ss,ax
	mov fs,ax
	mov sp,0x7c00 ;初始化栈指针，mbr是程序，程序就要用到栈
;利用0x06功能号进行清屏 INT 0x10  ah = 0x06 BIOS在运行过程中会有一些输出，这样子是为了更好看到我们的字符
	mov ax,0x600     ;ah = 0x06 al = 0代表全部
	mov bx,0x700	 ;BH = 上卷行属性
	mov cx,0		 ;(CL,CH) = 窗口左上角 (x,y)
	mov	dx,0x184f    ;(DL,DH) = 窗口右下角 (x,y) (0x18=24,0x4f=79) VGA文本一行只容纳 80个字符，25行
	int 0x10
;获取光标位置，在光标处打印字符
	mov ah,3         ; 3号功能即获取光标位置
	mov bh,0		 ; 存储带获取光标页号,第0页
	int 0x10		 
;打印字符串
	mov ax,message
	mov bp,ax		; es:bp 为串首地址，es此时同cs一致
	mov cx,6		; cx 为串长度，不包括结束符0的字符个数
	mov ax,0x1301	;子功能号 13 显示字符及属性，要存入 ah 寄存器，
					; al 设置写字符方式 ah=0 ：显示字符串，光标跟随移动
	mov bx,0x2		; bh 存储要显示的页号，此处是第
					; bl 中是字符属性，属性黑底绿字（bl = 02h) 
	int 0x10		; 执行 BIOS Ox10 号中
	
	
	jmp $
	message db "Geniux"
	times 510-($-$$) db 0  ;510 - 当前行号 - setcion行号得到剩余位置并填0
	db 0x55,0xaa
