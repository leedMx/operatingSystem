.set MAGIC, 0x1badb002		#info required to identify as kernel
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC+FLAGS)

.section .multiboot 		#this includes the magic number on the bin
	.long MAGIC
	.long FLAGS
	.long CHECKSUM
	
.section .text
.extern kernelMain
.global loader

loader:
	mov $kernel_stack, %esp	#Set the stack pointer 2Mib away

	push %eax				#Parameters sent via stack to kernelMain
	push %ebx				#GRUB provided this information

	call kernelMain
    
_stop: 						#infinite loop just in case we return
	cli
	hlt
	jmp _stop
    
.section .bss

.space 2*1024*1024 

	kernel_stack: 			#stack pointer, 2Mib away
