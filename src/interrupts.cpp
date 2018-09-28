#include "interrupts.h"

void print(char*);

InterruptManager::GateDescriptor InterruptManager::idt[256];

InterruptManager::InterruptManager
(uint16_t offset, GlobalDescriptorTable*gdt)
:port_PIC_MasterCommand(0x20),
 port_PIC_MasterData(0x21),
 port_PIC_SlaveCommand(0xA0),
 port_PIC_SlaveData(0xA1)
{
	this->hardwareInterruptOffset = offset;
	uint32_t codeSegment = gdt->get_CodeSegmentSelector();
	
	setEntries(codeSegment);

	port_PIC_config();

	loadInterruptDescriptorTable();
}

void InterruptManager::activateInterruptorFlag(){
	asm("sti");
}

void InterruptManager::port_PIC_config(){
	port_PIC_MasterCommand.write(0x11);
	port_PIC_SlaveCommand.write(0x11);

	port_PIC_MasterData.write(hardwareInterruptOffset);
	port_PIC_SlaveData.write(hardwareInterruptOffset+8);

	port_PIC_MasterData.write(0x04);
	port_PIC_SlaveData.write(0x02);

	port_PIC_MasterData.write(0x01);
	port_PIC_SlaveData.write(0x01);

	port_PIC_MasterData.write(0x00);
	port_PIC_SlaveData.write(0x00);
}

void InterruptManager::loadInterruptDescriptorTable(){
	InterruptDescriptorTablePointer idt_pointer;
	idt_pointer.size = 256*sizeof(GateDescriptor) - 1;
	idt_pointer.base = (uint32_t)idt;
	asm volatile("lidt %0" : :"m"(idt_pointer));

}

void InterruptManager::setEntries(uint32_t codeSegment){
	const uint8_t IDT_INTERRUPT_GATE = 0xE;

	for (int i = 255; i >= 0 ; --i){
	setInterruptDescriptorTableEntry
	(i,codeSegment, &ignore, 0, IDT_INTERRUPT_GATE);
	}

	setInterruptDescriptorTableEntry
	(hardwareInterruptOffset + 0x00, codeSegment, &handleInterrupt0x00, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry
	(hardwareInterruptOffset + 0x01, codeSegment, &handleInterrupt0x01, 0, IDT_INTERRUPT_GATE);
}

void InterruptManager::setInterruptDescriptorTableEntry(
					uint8_t interrupt,
					uint16_t codeSegment,
					void (*handlerFunction)(),
					uint8_t privileges,
					uint8_t type){
	idt[interrupt].handlerAddressLowBits = ((uint32_t)handlerFunction) & 0xFFFF;
	idt[interrupt].handlerAddressHighBits = ((uint32_t)handlerFunction >> 16) & 0xFFFF;
	idt[interrupt].gdt_codeSegmentSelector = codeSegment;

	const uint8_t IDT_DESC_PRESENT = 0x80;
	idt[interrupt].access = IDT_DESC_PRESENT | ((privileges & 3) << 5) | type;
}

extern "C" uint32_t InterruptManager::handleInterrupt
(uint8_t interrupt, uint32_t esp){
	char goodNews[10]="INTERRUPT";
	print(goodNews);
	return esp;
}
