    .syntax unified
    .arch armv7-m
    .cpu cortex-m3

    .section .stack
    .align 3
#ifdef __STACK_SIZE
    .equ    Stack_Size, __STACK_SIZE
#else
    .equ    Stack_Size, 0x400
#endif
    .globl    __StackTop
    .globl    __StackLimit
__StackLimit:
    .space    Stack_Size
    .size __StackLimit, . - __StackLimit
__StackTop:
    .size __StackTop, . - __StackTop

    .section .heap
    .align 3
#ifdef __HEAP_SIZE
    .equ    Heap_Size, __HEAP_SIZE
#else
    .equ    Heap_Size, 0xC00
#endif
    .globl    __HeapBase
    .globl    __HeapLimit
__HeapBase:
    .if    Heap_Size
    .space    Heap_Size
    .endif
    .size __HeapBase, . - __HeapBase
__HeapLimit:
    .size __HeapLimit, . - __HeapLimit
    .section .isr_vector
    .align 2
    .globl __isr_vector
__isr_vector:
    .long    __StackTop            /* Top of Stack */
    .long    Reset_Handler         /* Reset Handler */
    .long    NMI_Handler           /* NMI Handler */
    .long    HardFault_Handler     /* Hard Fault Handler */
    .long    MemManage_Handler     /* MPU Fault Handler */
    .long    BusFault_Handler      /* Bus Fault Handler */
    .long    UsageFault_Handler    /* Usage Fault Handler */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    SVC_Handler           /* SVCall Handler */
    .long    DebugMon_Handler      /* Debug Monitor Handler */
    .long    0                     /* Reserved */
    .long    PendSV_Handler        /* PendSV Handler */
    .long    SysTick_Handler       /* SysTick Handler */

	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler
	.long    UnknownInt_Handler

    .size    __isr_vector, . - __isr_vector

    .text
    .thumb
    .thumb_func
    .align 2
    .globl    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
    ldr    r1, =__etext
    ldr    r2, =__data_start__
    ldr    r3, =__data_end__

.flash_to_ram_loop:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt    .flash_to_ram_loop
    ldr    r0, =_start
    bx    r0
    .pool
    .size Reset_Handler, . - Reset_Handler
    .align 1
    .thumb_func
    .weak _start
    .type _start, %function

_start:
    /* Zero fill the bss segment. */
    ldr   r1, = __bss_start__
    ldr   r2, = __bss_end__
    movs  r3, #0
    b  .fill_zero_bss
.loop_zero_bss:
    str  r3, [r1], #4

.fill_zero_bss:
	cmp  r1, r2
	bcc  .loop_zero_bss

    /* Jump to our kmain */
    bl kmain
    b .
    .size    _start, . - _start

	

                    //  Referance Paper:
                    //  http://www.sersc.org/journals/IJSH/vol9_no2_2015/10.pdf
                    //  http://www.cncdesigner.com/wordpress/?p=3102
                    .text

                    .global SysTick_Handler
                    .type SysTick_Handler, %function

SysTick_Handler:    ldr       R0,=0xE000E000

                    ldr       R1,[R0,#0x010]      // System Tick Flagi silelim
                    bic       R1,#0x00010000
                    str       R1,[R0,#0x010]

                    ldr       R0,=0xE000E000
                    ldr       R1,=0X10000000
                    str       R1,[R0,#0xD04]      // PendSV tetikleyelim
                    bx          lr


                    .global PendSV_Handler
                    .type PendSV_Handler, %function
PendSV_Handler:     push    {r4 - r11, lr}
                    mrs     r0,msp
                    bl      __scheduler
                    msr     msp, r0
                    pop     {r4 - r11, lr}
                    bx      lr

                    .global OS_Start
                    .type OS_Start, %function
OS_Start:           msr     msp, r0

                    ldr     R0,=0xE000ED20      // SCB_SHPR3
                    ldr     R1,=0x00FF0000
                    str     R1,[R0]             // PendSV onceligini SVC ile esit yaptik

                    // 168E6/1000/2=168000 TICK TIME 1MS
                    ldr     r0,=0xE000E014
                    ldr     r1,=0x00014820
                    str     r1,[r0]

                    // Count Flagi silelim
                    ldr     r1,=0xE000E010
                    ldr     r0,[r1]
                    ldr     r1,=0xFFFEFFFF
                    and     r0,r0,r1
                    ldr     r1, =0x00000007
                    orr     r0,r0,r1
                    ldr     r1,=0xE000E010
                    str     r0,[r1]

                    pop     {r4 - r11, lr}
                    pop     {r0}
                    pop     {r1}
                    pop     {r2}
                    pop     {r3}
                    pop     {r12}
                    pop     {lr}
                    pop     {pc}
                   @pop     {psr}


                    .global SVC_Handler
                    .type SVC_Handler,%function
SVC_Handler:        add r7,sp,#24
                    ldr r7,[r7]
                    sub r7,r7,#2
                    ldrb r7,[r7]
                    mov r8,#4
                    mul r7,r7,r8
                    ldr r8,=sysVector
                    add r7,r8,r7
                    ldr r7,[r7]
                    bx  r7
                    
                    


                    .file	"cm3-c.c"
                    .comm	sysVector,40,4
                    .comm	iterProcess,4,4
                    .comm	lastProcess,4,4
                    .text
                    .align	1
                    .global	__schedulerInitStack
                    .syntax unified
                    .thumb
                    .thumb_func
                    .fpu fpv4-sp-d16
                    .type	__schedulerInitStack, %function
__schedulerInitStack:
                    @ args = 0, pretend = 0, frame = 16
                    @ frame_needed = 1, uses_anonymous_args = 0
                    push	{r7, lr}
                    sub	sp, sp, #16
                    add	r7, sp, #0
                    str	r0, [r7, #4]
                    str	r1, [r7]
                    ldr	r3, [r7]
                    subs	r3, r3, #32
                    mov	r0, r3
                    bl	malloc
                    mov	r3, r0
                    str	r3, [r7, #12]
                    ldr	r2, [r7, #4]
                    ldr	r3, [r7, #12]
                    str	r2, [r3, #24]
                    ldr	r3, [r7, #12]
                    mov	r2, #16777216
                    str	r2, [r3, #28]
                    ldr	r2, .L3
                    ldr	r3, [r7, #12]
                    str	r2, [r3, #20]
                    ldr	r3, [r7, #12]
                    subs	r3, r3, #36
                    str	r3, [r7, #8]
                    ldr	r3, [r7, #8]
                    mvn	r2, #6
                    str	r2, [r3, #32]
                    ldr	r3, [r7, #12]
                    subs	r3, r3, #36
                    mov	r0, r3
                    adds	r7, r7, #16
                    mov	sp, r7
                    @ sp needed
                    pop	{r7, pc}
.L4:
                    .align	2
.L3:
                    .word	__exit
                    .size	__schedulerInitStack, .-__schedulerInitStack
                    .ident	"GCC: (Arch Repository) 7.1.0"
                

                    

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro    def_irq_handler    handler_name
    .align 1
    .thumb_func
    .weak    \handler_name
    .type    \handler_name, %function
\handler_name :
    b    .
    .size    \handler_name, . - \handler_name
    .endm

	def_irq_handler	UnknownInt_Handler

    def_irq_handler    NMI_Handler
    def_irq_handler    HardFault_Handler
    def_irq_handler    MemManage_Handler
    def_irq_handler    BusFault_Handler
    def_irq_handler    UsageFault_Handler
//    def_irq_handler    SVC_Handler
    def_irq_handler    DebugMon_Handler
//    def_irq_handler    PendSV_Handler
//    def_irq_handler    SysTick_Handler
    def_irq_handler    Default_Handler
/*
                // External Interrupts
    def_irq_handler    WWDG_IRQHandler                   // Window WatchDog
    def_irq_handler    PVD_IRQHandler                    // PVD through EXTI Line detection
    def_irq_handler    TAMP_STAMP_IRQHandler             // Tamper and TimeStamps through the EXTI line
    def_irq_handler    RTC_WKUP_IRQHandler               // RTC Wakeup through the EXTI line
    def_irq_handler    FLASH_IRQHandler                  // FLASH
    def_irq_handler    RCC_IRQHandler                    // RCC
    def_irq_handler    EXTI0_IRQHandler                  // EXTI Line0
    def_irq_handler    EXTI1_IRQHandler                  // EXTI Line1
    def_irq_handler    EXTI2_IRQHandler                  // EXTI Line2
    def_irq_handler    EXTI3_IRQHandler                  // EXTI Line3
    def_irq_handler    EXTI4_IRQHandler                  // EXTI Line4
    def_irq_handler    DMA1_Stream0_IRQHandler           // DMA1 Stream 0
    def_irq_handler    DMA1_Stream1_IRQHandler           // DMA1 Stream 1
    def_irq_handler    DMA1_Stream2_IRQHandler           // DMA1 Stream 2
    def_irq_handler    DMA1_Stream3_IRQHandler           // DMA1 Stream 3
    def_irq_handler    DMA1_Stream4_IRQHandler           // DMA1 Stream 4
    def_irq_handler    DMA1_Stream5_IRQHandler           // DMA1 Stream 5
    def_irq_handler    DMA1_Stream6_IRQHandler           // DMA1 Stream 6
    def_irq_handler    ADC_IRQHandler                    // ADC1, ADC2 and ADC3s
    def_irq_handler    CAN1_TX_IRQHandler                // CAN1 TX
    def_irq_handler    CAN1_RX0_IRQHandler               // CAN1 RX0
    def_irq_handler    CAN1_RX1_IRQHandler               // CAN1 RX1
    def_irq_handler    CAN1_SCE_IRQHandler               // CAN1 SCE
    def_irq_handler    EXTI9_5_IRQHandler                // External Line[9:5]s
    def_irq_handler    TIM1_BRK_TIM9_IRQHandler          // TIM1 Break and TIM9
    def_irq_handler    TIM1_UP_TIM10_IRQHandler          // TIM1 Update and TIM10
    def_irq_handler    TIM1_TRG_COM_TIM11_IRQHandler     // TIM1 Trigger and Commutation and TIM11
    def_irq_handler    TIM1_CC_IRQHandler                // TIM1 Capture Compare
    def_irq_handler    TIM2_IRQHandler                   // TIM2
    def_irq_handler    TIM3_IRQHandler                   // TIM3
    def_irq_handler    TIM4_IRQHandler                   // TIM4
    def_irq_handler    I2C1_EV_IRQHandler                // I2C1 Event
    def_irq_handler    I2C1_ER_IRQHandler                // I2C1 Error
    def_irq_handler    I2C2_EV_IRQHandler                // I2C2 Event
    def_irq_handler    I2C2_ER_IRQHandler                // I2C2 Error
    def_irq_handler    SPI1_IRQHandler                   // SPI1
    def_irq_handler    SPI2_IRQHandler                   // SPI2
    def_irq_handler    USART1_IRQHandler                 // USART1
    def_irq_handler    USART2_IRQHandler                 // USART2
    def_irq_handler    USART3_IRQHandler                 // USART3
    def_irq_handler    EXTI15_10_IRQHandler              // External Line[15:10]s
    def_irq_handler    RTC_Alarm_IRQHandler              // RTC Alarm (A and B) through EXTI Line
    def_irq_handler    OTG_FS_WKUP_IRQHandler            // USB OTG FS Wakeup through EXTI line
    def_irq_handler    TIM8_BRK_TIM12_IRQHandler         // TIM8 Break and TIM12
    def_irq_handler    TIM8_UP_TIM13_IRQHandler          // TIM8 Update and TIM13
    def_irq_handler    TIM8_TRG_COM_TIM14_IRQHandler     // TIM8 Trigger and Commutation and TIM14
    def_irq_handler    TIM8_CC_IRQHandler                // TIM8 Capture Compare
    def_irq_handler    DMA1_Stream7_IRQHandler           // DMA1 Stream7
    def_irq_handler    FSMC_IRQHandler                   // FSMC
    def_irq_handler    SDIO_IRQHandler                   // SDIO
    def_irq_handler    TIM5_IRQHandler                   // TIM5
    def_irq_handler    SPI3_IRQHandler                   // SPI3
    def_irq_handler    UART4_IRQHandler                  // UART4
    def_irq_handler    UART5_IRQHandler                  // UART5
    def_irq_handler    TIM6_DAC_IRQHandler               // TIM6 and DAC1&2 underrun errors
    def_irq_handler    TIM7_IRQHandler                   // TIM7
    def_irq_handler    DMA2_Stream0_IRQHandler           // DMA2 Stream 0
    def_irq_handler    DMA2_Stream1_IRQHandler           // DMA2 Stream 1
    def_irq_handler    DMA2_Stream2_IRQHandler           // DMA2 Stream 2
    def_irq_handler    DMA2_Stream3_IRQHandler           // DMA2 Stream 3
    def_irq_handler    DMA2_Stream4_IRQHandler           // DMA2 Stream 4
    def_irq_handler    ETH_IRQHandler                    // Ethernet
    def_irq_handler    ETH_WKUP_IRQHandler               // Ethernet Wakeup through EXTI line
    def_irq_handler    CAN2_TX_IRQHandler                // CAN2 TX
    def_irq_handler    CAN2_RX0_IRQHandler               // CAN2 RX0
    def_irq_handler    CAN2_RX1_IRQHandler               // CAN2 RX1
    def_irq_handler    CAN2_SCE_IRQHandler               // CAN2 SCE
    def_irq_handler    OTG_FS_IRQHandler                 // USB OTG FS
    def_irq_handler    DMA2_Stream5_IRQHandler           // DMA2 Stream 5
    def_irq_handler    DMA2_Stream6_IRQHandler           // DMA2 Stream 6
    def_irq_handler    DMA2_Stream7_IRQHandler           // DMA2 Stream 7
    def_irq_handler    USART6_IRQHandler                 // USART6
    def_irq_handler    I2C3_EV_IRQHandler                // I2C3 event
    def_irq_handler    I2C3_ER_IRQHandler                // I2C3 error
    def_irq_handler    OTG_HS_EP1_OUT_IRQHandler         // USB OTG HS End Point 1 Out
    def_irq_handler    OTG_HS_EP1_IN_IRQHandler          // USB OTG HS End Point 1 In
    def_irq_handler    OTG_HS_WKUP_IRQHandler            // USB OTG HS Wakeup through EXTI
    def_irq_handler    OTG_HS_IRQHandler                 // USB OTG HS
    def_irq_handler    DCMI_IRQHandler                   // DCMI
    def_irq_handler    CRYP_IRQHandler                   // CRYP crypto
    def_irq_handler    HASH_RNG_IRQHandler               // Hash and Rng
    def_irq_handler    FPU_IRQHandler                    // FPU

*/
.end


