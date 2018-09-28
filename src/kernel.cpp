#include "types.h"
#include "port.h"
#include "gdt.h"
#include "interrupts.h"

// This section is needed for the linker to enable OOP
typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors(){
	for(constructor*i = &start_ctors; i != &end_ctors ; i++)
		(*i)();
}

void print(char*);

extern "C" void kernelMain(	void* multiboot_structure,\
							uint32_t magicnumber){
	char text[80]= "Hello kernel";
	
	GlobalDescriptorTable gdt;
	InterruptManager interrupts(0x20,&gdt);
	interrupts.activateInterruptorFlag();

	print(text);
	while(1);
}

void print(char* string){
    //Video Memory is hard coded at 0xb8000
    static uint16_t* videoMemory = ( uint16_t* )0xb8000;
    static uint8_t x = 0, y = 0;
	uint16_t highByte, offset;

    for(int16_t i=0 ; string[i] != '\0' && string[i] != '\n'; ++i, x++){
		offset =  80 * y + x ;
		highByte = videoMemory[offset] & 0xFF00;
		videoMemory[offset] = highByte | string[i];
	}
 }
