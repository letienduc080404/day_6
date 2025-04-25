
#include <stdint.h>

// Định nghĩa địa chỉ cơ sở của ngoại vi RCC và GPIO

#define RCC_BASE_ADDR							0x40023800UL
#define RCC_CFGR_REG_OFFSET						0x08UL
#define RCC_CFGR_REG_ADDR						(RCC_BASE_ADDR  +  RCC_CFGR_REG_OFFSET)
#define GPIOA_BASE_ADDR							0x40020000UL

int main(void)
{

	uint32_t *pRccCfgrReg =  (uint32_t *) RCC_CFGR_REG_ADDR;

	// Khai báo con trỏ đến thanh ghi cấu hình RCC

			*pRccCfgrReg &= ~(0x3 << 21); // Xóa bit 21 và 22
	// Cài đặt hệ số chia (prescaler)

			*pRccCfgrReg |= ( 1 << 25);
			*pRccCfgrReg |= ( 1 << 26);

	// a) Bật clock cho ngoại vi GPIOA
	uint32_t *pRccAhb1Enr = (uint32_t *)(RCC_CFGR_REG_ADDR + 0x3);

			*pRccAhb1Enr |= ( 1 << 0); // Bật clock cho GPIOA

	// b) Cấu hình chế độ của chân GPIOA pin 8 thành chế độ chức năng thay thế (alternate function mode)

	uint32_t *pGPIOAModeReg = (uint32_t*)(GPIOA_BASE_ADDR + 00);

			*pGPIOAModeReg &= ~( 0x3 << 16); // Xóa các bit cấu hình
			*pGPIOAModeReg |= ( 0x2 << 16);  // Thiết lập chế độ alternate function

	// c) Cấu hình thanh ghi chức năng thay thế để thiết lập chế độ 0 cho chân PA8

	uint32_t *pGPIOAAltFunHighReg = (uint32_t*)(GPIOA_BASE_ADDR + 0x24);
			*pGPIOAAltFunHighReg &= ~( 0xf << 0);

	for(;;);
}
