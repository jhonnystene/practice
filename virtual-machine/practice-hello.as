00	04 0D	STA #HELLO ; Store address of HELLO in A register
02	05	#LOOP LDB ; Load current char into B register
03	06	SWP ; Swap current char into A register
04	03 0C	JEZ #END ; Jump to end if we're at the end of the string
06	01	OUT ; Output current character
07	04 01	STA 1 ; Increment A register
09	07	ADD
0A	02 02	JMP #LOOP
0C	02 0C	#END JMP #END
0D	48 65	#HELLO DB "Hello, World!"
	6C 6C
	6F 2C
	20 57
	6F 72
	6C 64
	21 00
