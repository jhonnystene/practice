/*
 * Practice Virtual Machine
 * By Johnny Stene
 * 
 * See README for information.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define NOP 00
#define OUT 01
#define JMP 02
#define JEZ 03
#define STA 04
#define LDB 05
#define SWP 06
#define ADD 07

uint8_t ROM[256];
uint8_t PC;
uint8_t A;
uint8_t B;

int main(int argc, char** argv) {
	if(argc != 2) {
		printf("Usage: %s <ROM file>\n", argv[0]);
		return -1;
	}

	// Load ROM file
	FILE *romptr;
	romptr = fopen(argv[1], "r");
	if(romptr == NULL) {
		printf("Unable to open file %s.\n", argv[1]);
		return -2;
	}
	fgets((char*) ROM, 256, romptr);
	fclose(romptr);
	printf("ROM file loaded.\n");

	// Execute ROM
	for(;PC < 256;) {
		uint8_t instruction = ROM[PC];

		if(instruction == NOP) {
			PC++;
		} else if(instruction == OUT) {
			printf("%c", A);
			PC++;
		} else if(instruction == JMP) {
			if(PC == ROM[PC + 1]) {
				printf("\nCaught infinite loop at address %x. Emulation halted.\n", PC);
				return -4;
			}
			
			PC = ROM[PC + 1];
		} else if(instruction == JEZ) {
			if(A == 0) PC = ROM[PC + 1];
			else PC += 2;
		} else if(instruction == STA) {
			A = ROM[PC + 1];
			PC += 2;
		} else if(instruction == LDB) {
			B = ROM[A];
			PC++;
		} else if(instruction == SWP) {
			uint8_t C = B;
			B = A;
			A = C;
			PC++;
		} else if(instruction == ADD) {
			A += B;
			PC++;
		} else {
			printf("Illegal instruction. Emulation halted.\n");
			return -3;
		}
	}	

	printf("\nEmulation finished.\n");
	return 0;
}
