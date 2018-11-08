#include <iostream>
#include <fstream>
#include <cstdlib>
#include "sim.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define DEBUG
#define DIS

#define MOV0 0
#define MOV1 1
#define MOV2 2
#define MOV3 3
#define ADD 4
#define SUB 5
#define JZ 6
#define MOV4 7

typedef struct {
	char OPCODE[5];
	char OP1[5];
	char OP2[6];

} inst;

inst buf;

int main(int argc, char *argv[]) {

	FILE *fin, *fout;
	int line, cnt, temp;

	fin = fopen("out.txt", "r");
	if(fin == 0) {
		printf("error\n");
		exit(0);
	}
	fout = fopen("asm.out", "w");
	if(fout == 0) {
		printf("error1\n");
		exit(0);
	}
//	assert((fin != NULL) && (fout != NULL));

	line = atoi( argv[1] );

	for(cnt = 0; cnt < line; cnt++){

		fscanf(fin, "%s %s %s", buf.OPCODE, buf.OP1, buf.OP2);
		temp = ch(buf.OPCODE);

		switch( temp ) {
	
			case MOV0:
				fprintf(fout, "0000");
				transform(buf.OP1, 4, fout);
				transform(buf.OP2, 8, fout);
				break;
			case MOV1:
				fprintf(fout, "0001");
				transform(buf.OP2, 4, fout);
				transform(buf.OP1, 8, fout);
				break;
			case MOV2:
				fprintf(fout, "0010");
				transform(buf.OP1, 4, fout );
				transform(buf.OP2, 4, fout );
				fprintf(fout, "0000");
			case MOV3:
				fprintf(fout, "0011");
				transform(buf.OP1, 4, fout);
				transform(buf.OP2, 8, fout);
				break;
			case ADD:
				fprintf(fout, "0100");
				transform(buf.OP1, 4, fout);
				transform(buf.OP2, 4, fout);
				fprintf(fout, "0000");
				break;
			case SUB:
				fprintf(fout, "0101");
				transform(buf.OP1, 4, fout);
				transform(buf.OP2, 4, fout);
				fprintf(fout, "0000");
				break;
			case JZ:
				fprintf(fout, "0110");
				transform(buf.OP1, 4, fout);
				transform(buf.OP2, 8, fout);
				break;
			case MOV4:
				fprintf(fout, "0111");
				transform(buf.OP1, 4, fout);
				transform(buf.OP2, 4, fout);
				fprintf(fout, "0000");
				break;
		}

		fprintf(fout, "\n");

	}

	fclose(fin);
	fclose(fout);

	exit(0);

}

void transform(char* a, int size, FILE* fout){

	int cnt;
	int num;

	if((a[0] == 'R')|| (a[0] == '#')) {
		if(a[0] == 'R') a = strtok(a, ",");
		num = atoi(a+1);
	}
	else {
		a = strtok(a, ",");
		num = atoi(a);
	}
	binary(num, size, fout);
}

void binary(int n, int size, FILE* fout) {
	
	int i, p;
	
	if(size == 4) p = 0x08;
	else p = 0x80;
	
	for( i = 0; i < size; i++ ) {

		if ( p & n ) fprintf(fout, "1");
		else fprintf(fout, "0");

		p >>= 1;

	}
}

int ch(char* a){ //a = buf.OPCODE

	if(strcmp(a, "MOV0")==0) return 0;
	else if(strcmp(a, "MOV1")==0) return 1;
	else if(strcmp(a , "MOV2")==0) return 2;
	else if(strcmp(a , "MOV3")==0) return 3;
	else if(strcmp(a , "ADD")==0) return 4;
	else if(strcmp(a , "SUB")==0) return 5;
	else if(strcmp(a , "JZ")==0) return 6;
	else if(strcmp(a , "MOV4")==0) return 7;
	else return 8;
}
