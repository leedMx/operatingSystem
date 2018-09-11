#ifndef __GDT_H
#define __GDT_H

#include "types.h"

	class GlobalDescriptorTable
	{
		public:
			/*this is made because Global descriptor tables
			are scrambled to provide backwards compatibility, 
			so we need to create a template to be able
			to provide desriptor information
			and have it translated to a segment descriptor*/
			class SegmentDescriptor
			{
				private:
					uint16_t limit_lo;
					uint16_t base_lo;
					uint8_t base_hi;
					uint8_t type;
					uint8_t flags_limit_hi;
					uint8_t base_vhi;
				public:
				SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
				uint32_t Base();
				uint32_t Limit();
			}__attribute((packed));//required to prevent compiler from scambling info and have it byte perfect


	private:
	SegmentDescriptor nullSegmentSelector;
	SegmentDescriptor unusedSegmentSelector;
	SegmentDescriptor codeSegmentSelector;
	SegmentDescriptor dataSegmentSelector;

	public:
	GlobalDescriptorTable();
	~GlobalDescriptorTable();

	uint16_t DataSegmentSelector();
	uint16_t CodeSegmentSelector();
	};



#endif
