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

		void writeAndWait(uint8_t);
		void write(uint8_t);
		uint8_t read();
};

#endif
