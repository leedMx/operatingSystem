.set IRQ_BASE, 0x20

.section .data
	interruptnumber:.byte 0

.section .text

.extern _ZN16InterruptManager15handleInterruptEhj

.macro HandleInterruptRequest num 
.global _ZN16InterruptManager19handleInterrupt\num\()Ev
_ZN16InterruptManager19handleInterrupt\num\()Ev:
	movb $\num + IRQ_BASE, (interruptnumber)
	jmp int_bottom

.endm

.global _ZN16InterruptManager6ignoreEv
_ZN16InterruptManager6ignoreEv:
	iret

#Declarations using macro

HandleInterruptRequest 0x00
HandleInterruptRequest 0x01

int_bottom:
	pusha		#save all registers, to prevent process corruption
	pushl %ds	#data segment
	pushl %es	#?
	pushl %fs	#frame pointer?
	pushl %gs	#?

	pushl %esp				#2nd Parameter: esp
	push (interruptnumber)	#1st parameter: interrupt

	call _ZN16InterruptManager15handleInterruptEhj

	movl %eax,%esp			#returned esp; restore it
	
	popl %gs	#restoring values after handling interrupt
	popl %fs
	popl %es
	popl %ds
	popa		


