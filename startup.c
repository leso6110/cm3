#include <stdint.h>

/*
 * The reset handler is the first executable code to run after
 * startup. It is defined at the end of the file, and performs
 * basic memory initialization, then calls the main() function.
 */
void reset_handler();

/*
 * main() is defined in main.c. This is analogous to main() in 
 * a desktop C program, and is called/ran within the reset handler.
 */
extern int main();

/*
 * This is the default handler for all interrupts the processor
 * may receive. See the implementation below for more explanation.
 */
void default_handler();

/*
 * These variables are defined in the linker script (gcc_arm.ld).
 * They are the addresses of code sections created once the final program
 * is compiled, and are used by the reset handler below.
 */
extern uint32_t _etext;		// address of the end of .text section
extern uint32_t _sdata;		// address of the start of .data section
extern uint32_t _edata;		// address of the end of .data section
extern uint32_t _sbss;		// address of the start of .bss section
extern uint32_t _ebss;		// address of the end of .bss section

/*
 * Top of our stack. We tell the processor to start the stack at the 
 * end of SRAM1 (which is 0x20017FFF), and the processor will automatically
 * grow the stack downwards (towards 0x00000000).
 */
#define STACK_TOP	0x2000FFFF /*lm3s6965evb*/

/*
 * Vector table. A vector is nothing more than the address of a function, and
 * this table stores addresses to these functions such that when an interrupt
 * occurs, the hardware itself looks at the function address associated within
 * the interrupt and jumps to that code. Note that the attribute given to 
 * this array places it into its own section, such that it can be placed it at 
 * whichever address we want to in the linker script.
 */
uint32_t _vectors[] __attribute__ ((section(".vectors"))) = {
	
	// processor exceptions
	(uint32_t)STACK_TOP,		   // 	stack top
	(uint32_t)&reset_handler,	   // 	reset handler
    (uint32_t)&default_handler,    //	NMI_Handler
	(uint32_t)&default_handler,    //	HardFault_Handler
	(uint32_t)&default_handler,    //	MemManage_Handler
	(uint32_t)&default_handler,    //	BusFault_Handler
	(uint32_t)&default_handler,    //	UsageFault_Handler
	0,
	0,
	0,
	0,
	(uint32_t)&default_handler,    //	SVC_Handler
	(uint32_t)&default_handler,    //	DebugMon_Handler
	0,
	(uint32_t)&default_handler,    //	PendSV_Handler
	(uint32_t)&default_handler,    //	SysTick_Handler
	
	// interrupts
	(uint32_t)&default_handler,    //	WWDG_IRQHandler
	(uint32_t)&default_handler,    //	PVD_PVM_IRQHandler
	(uint32_t)&default_handler,    //	TAMP_STAMP_IRQHandler
	(uint32_t)&default_handler,    //	RTC_WKUP_IRQHandler
	(uint32_t)&default_handler,    //	FLASH_IRQHandler
	(uint32_t)&default_handler,    //	RCC_IRQHandler
	(uint32_t)&default_handler,    //	EXTI0_IRQHandler
	(uint32_t)&default_handler,    //	EXTI1_IRQHandler
	(uint32_t)&default_handler,    //	EXTI2_IRQHandler
	(uint32_t)&default_handler,    //	EXTI3_IRQHandler
	(uint32_t)&default_handler,    //	EXTI4_IRQHandler
	(uint32_t)&default_handler,    //	DMA1_Channel1_IRQHandler
	(uint32_t)&default_handler,    //	DMA1_Channel2_IRQHandler
	(uint32_t)&default_handler,    //	DMA1_Channel3_IRQHandler
	(uint32_t)&default_handler,    //	DMA1_Channel4_IRQHandler
	(uint32_t)&default_handler,    //	DMA1_Channel5_IRQHandler
	(uint32_t)&default_handler,    //	DMA1_Channel6_IRQHandler
	(uint32_t)&default_handler,    //	DMA1_Channel7_IRQHandler
	(uint32_t)&default_handler,    //	ADC1_2_IRQHandler
	(uint32_t)&default_handler,    //	CAN1_TX_IRQHandler
	(uint32_t)&default_handler,    //	CAN1_RX0_IRQHandler
	(uint32_t)&default_handler,    //	CAN1_RX1_IRQHandler
	(uint32_t)&default_handler,    //	CAN1_SCE_IRQHandler
	(uint32_t)&default_handler,    //	EXTI9_5_IRQHandler
	(uint32_t)&default_handler,    //	TIM1_BRK_TIM15_IRQHandler
	(uint32_t)&default_handler,    //	TIM1_UP_TIM16_IRQHandler
	(uint32_t)&default_handler,    //	TIM1_TRG_COM_TIM17_IRQHandler
	(uint32_t)&default_handler,    //	TIM1_CC_IRQHandler
	(uint32_t)&default_handler,    //	TIM2_IRQHandler
	(uint32_t)&default_handler,    //	TIM3_IRQHandler
	(uint32_t)&default_handler,    //	TIM4_IRQHandler
	(uint32_t)&default_handler,    //	I2C1_EV_IRQHandler
	(uint32_t)&default_handler,    //	I2C1_ER_IRQHandler
	(uint32_t)&default_handler,    //	I2C2_EV_IRQHandler
	(uint32_t)&default_handler,    //	I2C2_ER_IRQHandler
	(uint32_t)&default_handler,    //	SPI1_IRQHandler
	(uint32_t)&default_handler,    //	SPI2_IRQHandler
	(uint32_t)&default_handler,    //	USART1_IRQHandler
	(uint32_t)&default_handler,    //	USART2_IRQHandler
	(uint32_t)&default_handler,    //	USART3_IRQHandler
	(uint32_t)&default_handler,    //	EXTI15_10_IRQHandler
	(uint32_t)&default_handler,    //	RTC_Alarm_IRQHandler
	(uint32_t)&default_handler,    //	DFSDM1_FLT3_IRQHandler
	(uint32_t)&default_handler,    //	TIM8_BRK_IRQHandler
	(uint32_t)&default_handler,    //	TIM8_UP_IRQHandler
	(uint32_t)&default_handler,    //	TIM8_TRG_COM_IRQHandler
	(uint32_t)&default_handler,    //	TIM8_CC_IRQHandler
	(uint32_t)&default_handler,    //	ADC3_IRQHandler
	(uint32_t)&default_handler,    //	FMC_IRQHandler
	(uint32_t)&default_handler,    //	SDMMC1_IRQHandler
	(uint32_t)&default_handler,    //	TIM5_IRQHandler
	(uint32_t)&default_handler,    //	SPI3_IRQHandler
	(uint32_t)&default_handler,    //	UART4_IRQHandler
	(uint32_t)&default_handler,    //	UART5_IRQHandler
	(uint32_t)&default_handler,    //	TIM6_DAC_IRQHandler
	(uint32_t)&default_handler,    //	TIM7_IRQHandler
	(uint32_t)&default_handler,    //	DMA2_Channel1_IRQHandler
	(uint32_t)&default_handler,    //	DMA2_Channel2_IRQHandler
	(uint32_t)&default_handler,    //	DMA2_Channel3_IRQHandler
	(uint32_t)&default_handler,    //	DMA2_Channel4_IRQHandler
	(uint32_t)&default_handler,    //	DMA2_Channel5_IRQHandler
	(uint32_t)&default_handler,    //	DFSDM1_FLT0_IRQHandler
	(uint32_t)&default_handler,    //	DFSDM1_FLT1_IRQHandler
	(uint32_t)&default_handler,    //	DFSDM1_FLT2_IRQHandler
	(uint32_t)&default_handler,    //	COMP_IRQHandler
	(uint32_t)&default_handler,    //	LPTIM1_IRQHandler
	(uint32_t)&default_handler,    //	LPTIM2_IRQHandler
	(uint32_t)&default_handler,    //	OTG_FS_IRQHandler
	(uint32_t)&default_handler,    //	DMA2_Channel6_IRQHandler
	(uint32_t)&default_handler,    //	DMA2_Channel7_IRQHandler
	(uint32_t)&default_handler,    //	LPUART1_IRQHandler
	(uint32_t)&default_handler,    //	QUADSPI_IRQHandler
	(uint32_t)&default_handler,    //	I2C3_EV_IRQHandler
	(uint32_t)&default_handler,    //	I2C3_ER_IRQHandler
	(uint32_t)&default_handler,    //	SAI1_IRQHandler
	(uint32_t)&default_handler,    //	SAI2_IRQHandler
	(uint32_t)&default_handler,    //	SWPMI1_IRQHandler
	(uint32_t)&default_handler,    //	TSC_IRQHandler
	(uint32_t)&default_handler,    //	LCD_IRQHandler
	0,
	(uint32_t)&default_handler,    //	RNG_IRQHandler
	(uint32_t)&default_handler 	   //	FPU_IRQHandler

};

/*
 * Reset handler implementation, the first and only piece of code the hardware itself
 * automatically calls on bootup.
 */
void reset_handler()
{
	/*
	 * We first want to copy the values in .data to RAM, as that
	 * is where we told our code to look for them in the linker 
	 * script. 
	 */
	uint32_t* psrc = &_etext;	// start at the end of .text, where .data is loaded in flash
	uint32_t* pdest = &_sdata;	// copy to start of .data, where it is linked to in ram
	
	while (pdest < &_edata) {
		// copy the value from flash to ram
		*pdest = *psrc;
		++psrc; 
		++pdest;
	}
	
	
	/*
	 * Next set the values in the .bss section in ram to zeros. Some standard somewhere
	 * guarantees this section to be zeros, thus we will oblige without confrontation.
	 */
	pdest = &_sbss;		// start at the beginning of .bss in ram
	while (pdest < &_ebss)
	{
		// set each value to zero
		*pdest = 0x0;
		++pdest;
	}
	
	/*
	 * Finally, call main so we can run all our actual code. If we didn't
	 * call main, because this is the only actual code the hardware itself 
	 * calls, our program would just stop here.
	 */
	main();
}

/*
 * Our default handler (the handler all interrupts run at this point) does
 * nothing more than stall the processor in an infinite loop. If you are 
 * looking to implement a specific interrupt, then create a new function and 
 * point to it in the corresponding row in the vector table. However, the 
 * processor will boot just fine as is.
 */
void default_handler()
{
	while(1) {
		;
	}
}




