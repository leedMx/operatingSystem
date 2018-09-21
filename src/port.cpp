#include "port.h"

Port::Port(uint16_t portNumber){
    this->portNumber = portNumber;
}

Port8Bits::Port8Bits(uint16_t portnumber)
:Port(portnumber)
{
}

inline void Port8Bits::write(uint8_t data){
    asm volatile("outb %0 %1\n\t" : : "a" (data), "Nd" (portNumber) );
}

inline uint8_t Port8Bits::read(){
	uint8_t readData;
    asm volatile("inb %1 %0\n\t" : "=a" (readData) : "Nd" (portNumber) );
    return readData;
}

inline void Port8Bits::writeAndWait(uint8_t data){
    asm volatile("outb %0 %1\n\t" : : "a" (data), "Nd" (portNumber) );
    asm volatile("jmp 1f;1:jmp 1f; 1:");
}
