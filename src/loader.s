#hex magic number 0x1badb002 is necessary for GRUB to know it is a kernel
.set MAGIC, 0x1badb002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC+FLAGS)

.section .multiboot #this section only loads the variables
	.long MAGIC
	.long FLAGS
	.long CHECKSUM
	
.section .text
.extern kernelMain
.extern callConstructors
.global loader

loader:
	mov $kernel_stack, %esp
	#at this point GRUB has
	#pushed pointer for multiboot info into eax
	#pushed MAGIC number into ebx
	call callConstructors
	
	push %eax
	push %ebx
	#now we have such pointers on top of stack before calling kernel
	call kernelMain
    
_stop:
	cli
	hlt
	jmp _stop
    
.section .bss
.space 2*1024*1024 #2Mib of space to avoid overwriting with stack pointer
kernel_stack:
