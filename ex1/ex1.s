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
    BL setup_gpio_clock
    
    //power saving
    ldr r1, =CMU_BASE
    mov r5, #0
    str r5, [r1, #CMU_LFCLKSEL]

    ldr r4, =EMU_BASE
    str r5, [r4, #EMU_CTRL]
    
    // disable ram
    mov r5, #0
    str r5, [r4, #EMU_MEMCTRL]
    
    //tune clock
    ldr r1, =CMU_BASE
    mov r5, #0
    str r5, [r1, #CMU_LFRCOCTRL]
    str r5, [r1, #CMU_HFRCOCTRL]


    ldr r1, =SCR
    mov r2, #6
    str r2, [r1]
    BL setup_buttons
    BL setup_LED
    BL setup_interrupts
    wfi 
    
    
/////////////////////////////////////////////////////////////////////////////
    //
  // GPIO handler
  // The CPU will jump here when there is a GPIO interrupt
    //
    /////////////////////////////////////////////////////////////////////////////
    
    .thumb_func
setup_buttons:
    ldr r1, =GPIO_PC_BASE
    
    mov r2, #0x33333333
    str r2, [r1, #GPIO_MODEL]
    // enable internal pull-up
    mov r2, #0xff
    str r2, [r1, #GPIO_DOUT]
    bx lr 
    
    .thumb_func
gpio_handler:
    
    // clear the interrupt
    ldr r1, =GPIO_BASE
    ldr r2, [r1, #GPIO_IF]
    str r2, [r1, #GPIO_IFC]
    
    ldr r1, =GPIO_PC_BASE   // location if buttons in memory
    ldr r2, =GPIO_PA_BASE   // location of LEDs in memory
    
    //debug
    //mov r4, #0x88
    //str r4, [r1, #GPIO_DOUT]

    
    // take input from GPIO_DIN, left shift them 8 places
    // and write that to output GPIO_DOUT
    ldr r3, [r1, #GPIO_DIN]
    lsl r3, r3, #8
    mov r5, #0
    eor r3, r3, r5
    str r3, [r1, #GPIO_DOUT]
    
    bx lr         
          
    
    /////////////////////////////////////////////////////////////////////////////
    
    .thumb_func
dummy_handler:  
        bx lr  // do nothing


    .thumb_func
setup_interrupts:
    // 
    ldr r1, =GPIO_BASE              // load pointer to GPIO BASE to r1
    mov r2, #0x22222222             // load value 0x22222222 to r2
    str r2, [r1, #GPIO_EXTIPSELL]   // write r2 to GPIO_EXTIPSELL
    
    // generate interrupts on 1->0 transition
    mov r2, #0xff                   // load 0xff to r2
    str r2, [r1, #GPIO_EXTIFALL]    // store r2 in GPIO_EXTIFALL
    
    // generate interrupts on 0->1 transition
    mov r2, #0xff                   
    str r2, [r1, #GPIO_EXTIRISE]
    
    // eneble interrupt generation
    mov r2, #0xff
    str r2, [r1, #GPIO_IEN]
    
    // enable interrupt handling
    ldr r1, =ISER0
    ldr r2, =#0x802
    str r2, [r1]
    
    //return
    bx lr
    
    .thumb_func
setup_gpio_clock:

    ldr r1, =CMU_BASE
    ldr r2, [r1, #CMU_HFPERCLKEN0]
    
    mov r3, #1
    lsl r3, r3, #CMU_HFPERCLKEN0_GPIO
    orr r2, r2, r3
    
    str r2, [r1, #CMU_HFPERCLKEN0]
    bx lr
 
    .thumb_func
setup_LED:
    // set high drive strength
    mov r1, #0x2
    ldr r2, =GPIO_PA_BASE
    str r1, [r2, #GPIO_CTRL]
    
    //set pins 8-15 to output
    mov r1, #0x55555555
    ldr r2, =GPIO_PA_BASE
    str r1, [r2, #GPIO_MODEH]
    bx lr

