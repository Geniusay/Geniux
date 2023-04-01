#include "bitmap.h"
#include "string.h"
#include "debug.h"

/*初始化bitmap*/
void bitmap_init(struct bitmap* btmp) {
	memset(btmp->bits, 0, btmp->btmp_bytes_len);
}

/*判断 bit_idx位是否为1，为1则返回1，否则返回0*/
bool bitmap_scan_test(struct bitmap* btmp, uint32_t bit_idx) {
	uint32_t arr_index = bit_idx / 8;//在bits的数组索引
	uint32_t arr_member_index = bit_idx % 8;//在bits的数组元素中的索引

	return (btmp->bits[arr_index]) & (BITMAP_MASK << arr_member_index);
}

/*在位图中申请连续cnt个位，成功返回下标，失败返回-1*/
int bitmap_scan(struct bitmap* btmp, uint32_t cnt) {
	int arr_index = 0;

	while ((0xff == btmp->bits[arr_index]) && arr_index < btmp->btmp_bytes_len) {
		arr_index++;
	}

	ASSERT(arr_index < btmp->btmp_bytes_len);
	if (arr_index == btmp->btmp_bytes_len) {
		return -1;
	}

	int arr_member_index = 0;
	while ((btmp->bits[arr_index])&(BITMAP_MASK << arr_member_index)) {
		arr_member_index++;
	}

	int bit_idx_start = arr_index * 8 + arr_member_index;
	if (cnt == 1) {
		return bit_idx_start;
	}

	int bits_left = btmp->btmp_bytes_len * 8 - bit_idx_start;
	int count = 1;
	int next_bit = bit_idx_start + 1;

	bit_idx_start = -1;
	while (bits_left--) {
		if (!(bitmap_scan_test(btmp, next_bit))) {
			count++;
		}
		else {
			count = 0;
		}

		if (count == cnt) {
			bit_idx_start = next_bit - cnt + 1;
			break;
		}
		next_bit++;
	}
	return bit_idx_start;
}


void bitmap_set(struct bitmap* btmp, uint32_t bit_idx, int8_t value) {
	ASSERT((value == 0) || (value == 1));
	uint32_t arr_index = bit_idx / 8;//在bits的数组索引
	uint32_t arr_member_index = bit_idx % 8;//在bits的数组元素中的索引
	if (value) {
		btmp->bits[arr_index] |= (value << arr_member_index);
	}
	else {
		btmp->bits[arr_index] &= ~(value << arr_member_index);
	}
	
}