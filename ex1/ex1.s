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
    // set GPIO CLOCK
    mov r0, #1
    lsl r0, r0, #CMU_HFPERCLKEN0_GPIO
    ldr r1, =CMU_BASE
    ldr r2, [r1, #CMU_HFPERCLKEN0]
    orr r2, r2, r0
    str r2, [r1, #CMU_HFPERCLKEN0]

    // GPIO output
    // high drive strength:
    ldr r0, =GPIO_PA_BASE
    mov r1, #0x2
    str r1, [r0, #GPIO_CTRL]
    
    // set to output
    mov r1, #0x55555555
    str r1, [r0, #GPIO_MODEH]

    // GPIO output
    // set to input
    ldr r0, =GPIO_PC_BASE
    mov r1, #0x33333333
    str r1, [r0, #GPIO_MODEL]
    // enable internal pull-up
    mov r1, 0xff
    str r1, [r0, #GPIO_DOUT]
    
    
    
    // setup interrupts
    ldr r0, =GPIO_BASE
    mov r1, #0x22222222
    str r1, [r0, #GPIO_EXTIPSELL]
    mov r1, #0xff
    str r1, [r0, #GPIO_EXTIRISE]    //enable rising edge
    str r1, [r0, #GPIO_EXTIFALL]     //enable falling edge
    str r1, [r0, #GPIO_IEN]         //enable interruts
    ldr r1, =#0x802
    ldr r0, =ISER0
    str r1, [r0]                    //enable interrupt handling
    bx lr
	/////////////////////////////////////////////////////////////////////////////
	//
  // GPIO handler
  // The CPU will jump here when there is a GPIO interrupt
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
gpio_handler:
    ldr r0, =GPIO_BASE
    ldr r1, =GPIO_PA_BASE
    ldr r2, =GPIO_PC_BASE
    //clear interrupt flag
    ldr r3, [r0, #GPIO_IF]
    str r3, [r0, #GPIO_IFC]
    
    //read input, process it and write to output
    ldr r3, [r2, #GPIO_DIN]     // get input
    lsl r3, r3, #8              // left shift to get right pins
    eor r3, r3, #0
    str r3, [r1, #GPIO_DOUT]    // write back to leds
    bx lr
	
	/////////////////////////////////////////////////////////////////////////////

        .thumb_func
dummy_handler:  
    bx lr  // do nothing
