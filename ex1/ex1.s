        .syntax unified
	
	      .include "efm32gg.s"

	/////////////////////////////////////////////////////////////////////////////
	//
  // Exception vector table
  // This table contains addresses for all exception handlers
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .section .vectors
	
	      .long   stack_top               /* Top of Stack                 */
	      .long   _reset                  /* Reset Handler                */
	      .long   dummy_handler           /* NMI Handler                  */
	      .long   dummy_handler           /* Hard Fault Handler           */
	      .long   dummy_handler           /* MPU Fault Handler            */
	      .long   dummy_handler           /* Bus Fault Handler            */
	      .long   dummy_handler           /* Usage Fault Handler          */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* SVCall Handler               */
	      .long   dummy_handler           /* Debug Monitor Handler        */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* PendSV Handler               */
	      .long   dummy_handler           /* SysTick Handler              */

	      /* External Interrupts */
	      .long   dummy_handler
	      .long   gpio_handler            /* GPIO even handler */
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   gpio_handler            /* GPIO odd handler */
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler

	      .section .text

	/////////////////////////////////////////////////////////////////////////////
	//
	// Reset handler
  // The CPU will start executing here after a reset
	//
	/////////////////////////////////////////////////////////////////////////////

	      .globl  _reset
	      .type   _reset, %function
        .thumb_func
_reset:
    // load all pointers. these are constants. do not change!
	// Also renambed to aliases
    ldr r0, =GPIO_BASE//gpio_base_addr
	GPIO .req r0
	
    ldr r1, =GPIO_PA_BASE//gpio_pa_base_addr
	GPIO_A .req r1
	
    ldr r2, =GPIO_PC_BASE//gpio_pc_base_addr
	GPIO_C .req r2
	
    ldr r3, =ISER0//iser0_addr
	ISER0 .req r3
	
    ldr r4, =SCR//scr_addr
	SCR .req r4
	
	ldr r5, =EMU_BASE//emu_addr
    EMU .req r5
	
	ldr r6, =CMU_BASE//cmu_base_addr
	CMU .req r6
	
	mov r7, #0xff // constant stored to be used in interrupt handler.
    Cff .req r7
	
	mov r11, #0 // constant stored to be used in interrupt handler
	C0 .req r11
	
    // set GPIO CLOCK
    mov r8, #1
    lsl r8, r8, #CMU_HFPERCLKEN0_GPIO
    ldr r9, [r6, #CMU_HFPERCLKEN0]
    orr r9, r9, r8
    str r9, [r6, #CMU_HFPERCLKEN0]

    // GPIO output
    // high drive strength:
    mov r8, #0x2
    str r8, [r1, #GPIO_CTRL]
    
    // set to output
    mov r8, #0x55555555
    str r8, [r1, #GPIO_MODEH]

    // GPIO output
    // set to input
    mov r8, #0x33333333
    str r8, [r2, #GPIO_MODEL]
    // enable internal pull-up
    str r7, [r2, #GPIO_DOUT]

    // setup interrupts
    mov r8, #0x22222222
    str r8, [r0, #GPIO_EXTIPSELL]
    str r7, [r0, #GPIO_EXTIRISE]    //enable rising edge
    str r7, [r0, #GPIO_EXTIFALL]     //enable falling edge
    str r7, [r0, #GPIO_IEN]         //enable interruts
    ldr r9, =#0x802
    str r9, [r3]                    //enable interrupt handling
    bx lr
	/////////////////////////////////////////////////////////////////////////////
	//
  // GPIO handler
  // The CPU will jump here when there is a GPIO interrupt
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
gpio_handler:
    str r7, [r0, #GPIO_IFC]     // write 0xff to IFC to clear the interrupt flag
    ldr r8, [r2, #GPIO_DIN]     // get input
    lsl r8, r8, #8              // left shift to get right pins
    eor r8, r8, r11
    str r8, [r1, #GPIO_DOUT]    // write back to leds
    bx lr
	
	/////////////////////////////////////////////////////////////////////////////

        .thumb_func
dummy_handler:  
    bx lr  // do nothing
/*
cmu_base_addr:
    .long CMU_BASE

gpio_base_addr:
    .long GPIO_BASE

gpio_pa_base_addr:
    .long GPIO_PA_BASE

gpio_pc_base_addr:
    .long GPIO_PC_BASE

iser0_addr:
    .long ISER0

emu_addr:
    .long EMU_BASE

scr_addr:
    .long SCR
    */
