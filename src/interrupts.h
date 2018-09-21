#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "types.h"
#include "port.h"
#include "gdt.h"

class InterruptManager{

	public:
	InterruptManager(uint16_t,GlobalDescriptorTable*);
	~InterruptManager();
	
	void activateInterruptorFlag();

	uint16_t get_hardwareInterruptOffset();

	protected:
	static uint32_t handleInterrupt(uint8_t,uint32_t);
		
	static void ignore();
	
	static void handleInterrupt0x00();
	static void handleInterrupt0x01();

	static void setInterruptDescriptorTableEntry(uint8_t,uint16_t,void(*)(),uint8_t,uint8_t);

	struct GateDescriptor{
		uint16_t handlerAddressLowBits;
		uint16_t gdt_codeSegmentSelector;
		uint8_t reserved = 0;
		uint8_t access;
		uint16_t handlerAddressHighBits;
	} __attribute__((packed));

	struct InterruptDescriptorTablePointer{
		uint16_t size;
		uint32_t base;
	} __attribute__((packed));


	static GateDescriptor idt[256];
	uint16_t hardwareInterruptOffset = 0;

	Port8Bits port_PIC_MasterCommand;
	Port8Bits port_PIC_MasterData;
	Port8Bits port_PIC_SlaveCommand;
	Port8Bits port_PIC_SlaveData;
	
	private:
	void setEntries(uint32_t);
	void port_PIC_config();
	void loadInterruptDescriptorTable();

};

#endif
