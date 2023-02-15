/*
 * MEMORY defines flash and ram locations. Doing this is not necessary,
 * but makes it easier to load and link the final code to specific locations.
 *
 * Important note: "loading" code refers to the physical location where code 
 * is placed onto the microcontroller. "Linking" code refers to where the instructions
 * actually look for the code when the code is ran. For example, you might load a 
 * section of code into one address but tell the instructions to look for 
 * it at a different address (thus link it to a different address). See the README 
 * for more info on why this is necessary sometimes.
 *
 * On the stm32l476rg, flash starts at 0x00000000 and goes to 0x000FFFFF. Flash should
 * only be read and executed, thus given the attribute (rx). Similar story for ram, 
 * but given (rwx) for read, write, execute. Refer to your datasheet for specific
 * ORIGIN and LENGTH values.
 */
 
 /* leso, this memory is ment for lm3s6965evb which is the default cortex-m debug target in vscode.*/
MEMORY
{
	FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 0x0003FFFF
	RAM (rwx) : ORIGIN = 0x20000000, LENGTH =  0x0000FFFF
} 

/* This is where the picture is painted on where each section is to be placed
 * in memory. You can imagine the SECTIONS block as an actual vague memory map of the
 * final program, with the start of SECTIONS as address 0x00 and the end
 * being our final address. */
SECTIONS
{
	/* First we define the .text section in the final program */
	.text : 
	{
	
		/* Because the hardware reads the vector table from address 0x00, it 
		 * must be placed first in the final output program. This is followed by 
		 * the .text sections that should be placed right after .vectors 
		 */
		*(.vectors)
		*(.text)
		
		/* This is the variable used in startup.c to know where the end of
		 * .text is. "." refers to the current address SECTIONS is at.
		 */
		_etext = .;	
		
	} > FLASH	/* Link this code into flash */
	
	/* Next is the .data section. AT means load this code at this address. Thus,
	 * the code is loaded onto the microcontroller at the end of .text. See the
	 * README for why this is necessary. However, this section is linked into RAM
	 * as that is where it is copied to in the startup code so that these variables
	 * can be read AND written to.
	 */
	.data : AT (_etext)
	{
		_sdata = .;
		*(.data)
		_edata = .;
	} > RAM
	
	/* Lastly the .bss section. These are uninitialized variables, and therefore do
	 * not need to be specified where they are loaded to. It does need to be specified 
	 * however that they are linked in RAM so the executable code in flash knows where to
	 * look for them.
	 */
	.bss :
	{
		_sbss = .;
		*(.bss)
		_ebss = .;
	} > RAM
}
