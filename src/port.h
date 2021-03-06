#ifndef __PORT_H
#define __PORT_H

#include "types.h"

class Port{
	public:
		Port(uint16_t);
		~Port();
	protected:
		uint16_t portNumber;
};

class Port8Bits : public Port{
	public:
		Port8Bits(uint16_t);
		~Port8Bits();

		void write(uint8_t);
		uint8_t read();
};

class Port8BitsSlow : public Port8Bits{
	public:
	Port8BitsSlow(uint16_t);
	~Port8BitsSlow();
	void write(uint8_t);

	protected:
	inline void writeSlow(uint8_t _data){
		asm ("outb %1 " : : "a" (_data), "Nd" (portNumber) );
		asm volatile("jmp 1f;1:jmp 1f; 1:");
	}

};

#endif
