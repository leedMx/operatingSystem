# Quick reminder, since I don't usually use makefiles
#	this: prerequisite1 dependency2
#		commandsRequiredToMakeThis
#		commandsRequiredToMakeThis
# make will execute the commands when you call
#	make this
# By recompiling first the dependencies
# if dependencies prerequisites or dependencies have changed
#
# This has the same syntax as bash (citation required)(lol) so:
#	varNAME = varValue
# You call the value by using:
#	$varNAME 
# Now, for the complex syntax, % is a pattern matching operator, so:	
#	%.o : %.c %1.c 
# Means that when I call
#	make something.o
# will be interpreted as:
#	something.o : something.c something1.c
#
# Also the makefile rule
#	target.a : objects.b
# Can be tought as
#	@ : <
# And referenced in the command as
# 		command $@ $<
# To be interpreted as 
#		command target.a objects.b
# To prevent make from making a file you can use 
#	.PHONY: rulename
#	rulename: [dependencies]
#		commands
# That way you can call make rulename and run commands

GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-leading-underscore -fno-exceptions -fpermissive
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = loader.o kernel.o gdt.o portb.o

%.o: %.cpp
	g++ $(GPPPARAMS) -o $@ -c $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<


kernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

%.iso:kernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo 'menuentry "OS"{' >> iso/boot/grub/grub.cfg
	echo '    multiboot /boot/kernel.bin' >> iso/boot/grub/grub.cfg
	echo '    boot}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=../$@ iso
	rm -rf iso
	rm *.o
