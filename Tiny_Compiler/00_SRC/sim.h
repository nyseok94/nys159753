
#ifndef SIM
#define SIM

using namespace std;
#include <iostream>



enum { MOV0, MOV1, MOV2, MOV3, ADD, SUB, JZ, MOV4 };

typedef struct {
	int OPCODE;
	int OP1;
	int OP2;
} instruction;

static const unsigned int prog_size = 1024;
static const unsigned int mem_size = 256;
static const unsigned int regs = 16;

//memory
instruction program[prog_size];
int memory[mem_size] = {0};

//function decleration
int decode(ifstream& infile, int num, int val);
int run_program( int size);
void on_chip_debug( int pc );
void timer(long sec);
void report_profile( int freq[], int clks[], int size );
void transform(char* a, int size, FILE* fout);
void binary(int n, int size, FILE* fout);
int ch(char* a);

#endif
