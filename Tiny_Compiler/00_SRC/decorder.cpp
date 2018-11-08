#include <iostream>
#include <fstream>
#include <cstdlib>
#include "sim.h"
#include <time.h>

#define DEBUG
#define DIS
#define CLOCK_PER_SEC 100000

int main(int argc, char* argv[]) {

	int size = 0;
	int line;

	if( argc != 3) {
		cout << "iss <input file <line>\n";
		return -1;
	}

	ifstream infile;
	infile.open(argv[1], ios::in);

	line = atoi(argv[2]);

	while ( size < line) {
		if( (unsigned)size>=prog_size){
			cout << "Error: input program is too large to simulate\n";
			return -1;
		}
		program[size].OPCODE = decode(infile, 4, 8);
		program[size].OP1    = decode(infile, 4, 8);
		program[size].OP2    = decode(infile, 8, 128);

		size++;
#ifdef DEBUG 
		cout << "\n";
#endif
	}

	run_program( size );

	infile.close();
	return 0;
}

void timer(long sec) {
	long now;

	now = clock();

	while(clock() - now < sec * CLOCK_PER_SEC);
	
}

int decode(
	ifstream& infile, 
	int num, 
	int val
	) {

	int CODE =0;
	char bit;

	for(int i=0; i<num; i++) {
		infile >> bit;
		if( bit == '1')
			CODE |= (val >> i);
	}

#ifdef DEBUG
	cout << "-" << CODE;
#endif

	return CODE;
}

void twos_complement( int pc ) {
	if( program[pc].OP2 & 128) { // if OP2 is negative
		
		program[pc].OP2 = (~(char)program[pc].OP2 + 1) * -1;
	}
}


int run_program( int size){
	int pc = -1;
	int reg[regs] = {0};
	int rel;
	
	int freq[8] = {0,0,0,0,0,0,0,0};
	int clks[8] = {4,4,8,6,7,7,12,5};

	while (++pc <= size){

#ifdef DIS
	on_chip_debug(pc);
#endif
//		timer(1);			

		switch( program[pc].OPCODE ) {
			
			case MOV0: //MOV Rn, Direct
				reg[program[pc].OP1] = memory[program[pc].OP2];  //Direct access
				freq[MOV0]++;
				break;
			case MOV1: //MOV1 Direct, Rn
				memory[program[pc].OP2] = reg[program[pc].OP1];
				freq[MOV1]++;
				break;
			case MOV2: //MOV2 @Rn, Rm
				memory[ reg[program[pc].OP1] ] = reg[program[pc].OP2>>4];
				freq[MOV2]++;
				break;
			case MOV3: //MOV3 Rn, #immediate  2's complement
				
				twos_complement( pc );
				
				reg[program[pc].OP1] = program[pc].OP2;
				freq[MOV3]++;
				break;
			case ADD: //ADD
				reg[program[pc].OP1] += reg[program[pc].OP2>>4];
				freq[ADD]++;
				break;
			case SUB: //SUB
				reg[program[pc].OP1] -= reg[program[pc].OP2>>4];
				freq[SUB]++;
				break;
			case JZ:  //JZ
				freq[JZ]++;
			/* if(program[pc].OP2>>7 == 1 ){ rel = 0 -(255-(program[pc].OP2 - 1));
				}
				else {
					rel = program[pc].OP2;
				}
				cout << "JZ R["<<program[pc].OP1<<"], "<<rel<<" \n";
			*/
				twos_complement( pc );
				if(reg[program[pc].OP1] == 0) pc += program[pc].OP2;
				break;
			case MOV4:
				reg[program[pc].OP1] = reg[program[pc].OP2>>4];				
				freq[MOV4]++;
				break;
			default:
				cout << "Error: Unknown instruction found at line: " << pc +1 << endl;
			//	break;
				return -1;
		}

	}
	cout<< "===============================================" << endl;
	cout << "\nResult R0: " << reg[0] << endl;

	report_profile( freq, clks, size );

	cout << "\n";
	for(int i=0; i<16; i++){
		cout << "R["<<i<<"] "<<reg[i]<< "\n";
	}
	
	for(int i=0; i<16; i++){
		cout << "mem["<<i<<"] "<<memory[i]<<" ";
	}
	cout << "\n";
	
}

void report_profile(int freq[], int clks[], int size) {
	
	int total = 0;
	int total_clks = 0;

	cout << "\n===============================================" << endl;

	for(int i=0; i<7; i++) {
		total += freq[i];
		total_clks += (freq[i]*clks[i]);
	}

	cout << "\nTotal instructions are executed: " <<total << "times\n";
	cout << "\nTotal Program execution time: " << total_clks << "\n";  // * 100ns;
	cout << "\n===============================================" << endl;
}
		
void on_chip_debug( int pc ) {
	const char ISA[8][5] = {
		"MOV0", "MOV1", "MOV2", "MOV3", "ADD", "SUB", "JZ", "MOV4"		
	};

	for (int j=0; j<4; j++ ) {
		cout << ISA[program[pc].OPCODE][j];
	}

	switch ( program[pc].OPCODE ) {
		case MOV0:
			cout << " R[" << program[pc].OP1 << "], " << program[pc].OP2 << endl;
			break;
		case MOV1:
			cout << " "<<program[pc].OP2<<", R["<<program[pc].OP1<<"]\n";
			break;
		case MOV2:
			cout << " R["<<program[pc].OP1<<"], R["<<(program[pc].OP2>>4)<<"] \n";
			break;
		case MOV3:
			cout << " R["<<program[pc].OP1<<"], #"<<program[pc].OP2<<" \n";
			break;
		case ADD:
			cout << "  R["<<program[pc].OP1<<"], R["<<(program[pc].OP2>>4)<<"] \n";
			break;
		case SUB:
			cout << "  R["<<program[pc].OP1<<"], R["<<(program[pc].OP2>>4)<<"] \n";
			break;
		case JZ:
			twos_complement( pc );
			cout << "   R["<<program[pc].OP1<<"], "<<program[pc].OP2<<" \n";
			break;
		case MOV4:
			cout << " R["<<program[pc].OP1<<"], R["<<(program[pc].OP2>>4)<<"] \n";
			break;
		default:
			cout << "Unrecognized instruction ..."<< endl;
	}

}



