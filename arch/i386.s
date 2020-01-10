.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM


.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The linker script specifies _start as the entry point to the kernel and the
# bootloader will jump to this position once the kernel has been loaded. It
# doesn't make sense to return from this function as the bootloader is gone.
    .section .text
    .global _start
    .type _start, @function
_start:
	// Protected Mode
	mov %cr0,%eax
	or $1,%eax
	mov %eax,%cr0

	// Set the stack pointer
	mov $stack_top, %esp



	call setColor
	//Set the IVT
	cli
	mov $20,%dx
l0:
	mov %dx,%bx
	shl $2,%bx
	xor %ax,%ax
	mov %ax,%gs
	movw keyhandler,%cx
	movw %cx,%gs:(%bx)
	movw %ds,%gs:2(%bx)
	dec %dx
	jnz l0

	mov %dx,%bx
	shl $2,%bx
	xor %ax,%ax
	mov %ax,%gs
	movw keyhandler,%cx
	movw %cx,%gs:(%bx)
	movw %ds,%gs:2(%bx)

	
	//sti
	//call kmain

	// Halt
	cli
1:	hlt
	jmp 1b


.size _start, . - _start

keyhandler:
	iret

	.type setColor,@function
setColor:
	// Set screen color	
	mov $0x2f,%eax
	mov $0xB8000,%ebx
	mov $2000,%ecx
.ColourOutput:
	movl $0,(%ebx)
	movb %al,1(%ebx)
	add $2,%ebx
	loop .ColourOutput
	ret

// Scheduler API	
	.global __archInitStack
	.type __archInitStack,@function
__archInitStack:

    .global G_ArchInit
    .type G_ArchInit,@function
G_ArchInit:

    .global G_ArchContextSwitch
    .type G_ArchContextSwitch,@function
G_ArchContextSwitch:

    .global __schedulerInitStack
    .type __schedulerInitStack,@function
__schedulerInitStack:

    .global OS_Start
    .type OS_Start,@function
OS_Start:

    .global SysTick_Handler
    .type SysTick_Handler,@function
SysTick_Handler:
