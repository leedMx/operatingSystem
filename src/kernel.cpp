#include "types.h"
#include "gdt.h"

//main kernel function
void printf(char* str)
{
    //hard coded Video Memory address
    static uint16_t* VideoMemory = ( uint16_t* )0xb8000;
    static uint8_t x=0,y=0;

    for(int i=0;str[i] !='\0'; ++i)
 	switch(str[i])
	{
		case '\n':
			x=0;//return carriage
			y++;//new line
			break;

		default:
			VideoMemory[80*y+x]= (VideoMemory[80*y+x] & 0xFF00) | str[i];//& 0xFF00 is the bitwise transformation required to add the less significant part of the video mem bytes, meaning the color for background and foreground
			x++;
			break;

	}
	if (x>=80)
	{
		x=0;
		y++;
	}
	if (y>=25)
	{
		//Left this action blank intentionally to come up with a better solution tahns just clearing the screen
	}
 }

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
	for( constructor* i = &start_ctors ; i != &end_ctors ; i++ )
	(*i)();
}

//params accepting values on top of stack
//extern "C" makes function available for linker
extern "C" void kernelMain(void* multiboot_structure, uint32_t magicnumber)
{
  printf("We are now in kernel main\n~");
  printf("We are now in kernel main\n~");
  printf("We are now in kernel main\n~");
  printf("We are now in kernel main\n~");
  printf("We are now in kernel main\n~");
  while(1);
}
