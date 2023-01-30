#include "print.h"
#include "init.h"
void main(void) {
	
	put_str("Hello GeniusOS\n");
	put_int(2023);
	init_all();
	asm volatile("sti");
	while (1) {
		
	}
	return 0;
}