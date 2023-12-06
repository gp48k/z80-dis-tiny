# z80-dis-tiny
Searching for the world's smallest Z-80 disassembler.

Started with the results of the [trs8bit newsletter](https://trs-80.org.uk/downloads.html)'s 
[2023 competition](http://48k.ca/comp2023.html), this repository tracks the progress of various
attempts at the smallest Z-80 disassembler.

The current best is: [peter-1](src/peter-1/1040) at 1040 bytes.

To make the variants comperable and have at least a modicum of practicality they all have the
same interaface and restrictions on operation.  They must:

* Have a subroutine called `z80dis`
* Disassemble the instruction pointed to by `HL` register.
* HL points to the next instruction upon return.
* Put the nul terminated disassembly into a buffer pointed to by `DE` register.
* Support all documented Z-80 instructions.
* Behave reasonably on undocumented instructions (i.e., don't crash, don't output more than 16 bytes to the buffer or put non-ASCII into the buffer).
* Put a single space between the mnemonic and arguments.
* Not output a space after the mnemonic if there are no arguments.
* Output in upper case ASCII.
* Output all numbers in hexadecimal with a $ prefix.
* Use zero-padded, 2 digit hex numbers for 8 bit values.
* Use zero-padded, 4 digit hex numbers for 16 bit values and addresses.
* Show relative branch destinations as addresses.
* Output IX and IY offsets as signed numbers from (IX-$80) to (IX+$7F).
* Use the standard Zilog mnemonics and format for instructions.
* Use V and NV for the P/V flag tests (e.g., opcode $E8 is "RET V").
* Emit RST instructions as "RST $00" through "RST $38".

The size is the sum of both the code and data (initialized or not) and the stack space usage.  The subroutine can occupy at most two contiguous regions of memory.
