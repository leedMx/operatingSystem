#ifndef __GDT_H
#define __GDT_H

#include "types.h"

class GlobalDescriptorTable{

	public:
	GlobalDescriptorTable();
	~GlobalDescriptorTable();
	uint16_t get_DataSegmentSelector();
	uint16_t get_CodeSegmentSelector();

	class SegmentDescriptor	{
		public:
		SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
		uint32_t getBase();
		uint32_t getLimit();

		private:
		uint16_t limit_lo;
		uint16_t base_lo;
		uint8_t base_hi;
		uint8_t type;
		uint8_t flags_limit_hi;
		uint8_t base_vhi;
	}__attribute((packed));//byte perfect

	private:
	SegmentDescriptor nullSegmentSelector;
	SegmentDescriptor unusedSegmentSelector;
	SegmentDescriptor codeSegmentSelector;
	SegmentDescriptor dataSegmentSelector;

};

#endif
