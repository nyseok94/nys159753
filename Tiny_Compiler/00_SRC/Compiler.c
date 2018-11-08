#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Linked_list.h"

#define buf_size 2000
#define var_size 100
#define op_size 500

void initbuf(char *buf) {
    int i = 0;
    for ( i = 0; i < buf_size; i++) {
        buf[i] = '\0';
    }
}    

void *append(char *a, char b) {
    char *p;
    int i;
    p = (char*)malloc(sizeof(char) * buf_size);
    for ( i = 0; i < buf_size; i++) {
        p[i] = '\0';
    }
    strcpy(p, a);

    i = 0;
    while (p[i] != '\0') {
        i++;
    }
    p[i] = b;

    return p;
}    

char *buf;
char syntax_list[buf_size][10];
char buffer[buf_size];
char var[var_size][10];

typedef struct op {

	char operator;
	int index;
} OP;	

OP operate[op_size];

//return var_index  if there is no var return -1
int var_index(char *ch) {

	int i;
	for(i = 0; i<var_size; i++) {
		if(strcmp(ch,var[i])==0) return i;
	}
	return -1;
}

int main(){

    FILE *fin, *fout;
    int i, a, j, cnt_int, cnt, va, tem_va;
	int temp = 0;
	// create linked list
	LIST* L1 = create_list();

    buf = (char*)malloc(sizeof(char) * buf_size);
    initbuf(buf);

    fin = fopen("in.txt", "r");
    if ( fin == 0 ) {
        printf("eroor1\n");
        exit(0);
    }
    
    fout = fopen("out.txt", "w");
    if ( fout == 0 ) {
        printf("error2\n");
        exit(0);
    }    
    
    for(i=0; (i < sizeof(buffer) - 1) && ((a = fgetc(fin)) != EOF); i++) {
		
		if ((a == '\t') || (a == '\n')) i--;
        else buffer[i] = a;
    
	}
    buffer[i] = '\0';
  
    printf("\n\n%s\n", buffer);

	for(i = 0, j= 0; buffer[i]; i++) {
		if((buffer[i] == '{')) {
			buf = append(buf, buffer[i]);
			strcpy(syntax_list[j], buf);
			j++;
			initbuf(buf);
		}

		else if((buffer[i] != ';') && (buffer[i] != ' ') && (buffer[i] != ',') ) {
			buf = append(buf, buffer[i]);
		}

		else {
			strcpy(syntax_list[j], buf);
			j++;
			initbuf(buf);
		}

	}
	strcpy(syntax_list[j], buf);
	strcpy(syntax_list[++j],"#");
	
	initbuf(buf);

	printf("      j is syntax_list`s last index : %d\n", j);	
	// j is syntax_list's last index
	/////////////
	//syntax_list print

	printf("\n");
	for(i = 0; i <= j; i++) {
		printf("  %3d  %s\n", i, syntax_list[i]);
	}
	/////////////////////////////
	cnt_int = 3;

	for(i = 1; i <= j; i++) {
		buf = syntax_list[i];
		for(cnt = 0; cnt < i; cnt++) {
			if(strcmp(buf, syntax_list[cnt]) == 0){
				temp = i; 
				break;
			}	
		}
		if(temp!=0) break;
	}
	//temp => start operation
	printf("\n\n%d\n\n", temp);

	for(i = cnt_int; i < temp; i++) {
		strcpy(var[i - cnt_int], syntax_list[i]);
	}

	// var[] print
	//  variable usage check!

	for(i = 0; var[i][0]; i++) {
		add_list(L1, var[i]);
		for(cnt = temp; cnt <j; cnt++) {
			if(strcmp(var[i], syntax_list[cnt]) == 0){
				(L1->last->usage)++;
			}
		}	
		printf("\nvar[%d] : %s  list_cnt : %d  usage : %d\n\n",i, var[i], L1->count, L1->last->usage);
	}	

	for(i = 0, cnt = 0; i<=j; i++){
		if(strcmp(syntax_list[i], "=") == 0){
			operate[cnt].operator = '=';
			operate[cnt].index = i;
			cnt++;
		}
		else if(strcmp(syntax_list[i], "+") == 0){
			operate[cnt].operator = '+';
			operate[cnt].index = i;
			cnt++;
		}
		else if(strcmp(syntax_list[i], "-") == 0){
			operate[cnt].operator = '-';
			operate[cnt].index = i;
			cnt++;
		}	
		
	}

	//operate[].operator  ,  operate[].index  print
	/*
	for(i = 0; operate[i].index ; i++) {
		printf("\n  %c %d\n", operate[i].operator, operate[i].index);
	}	

	printf("\n");
	*/


	// code generate
	for(i = 0; operate[i].index; i++){
		
		if(operate[i].operator == '=') {
			// check if code is MOV series
			if(operate[i+1].operator == '='){
				//check direct or indirect	
				tem_va = var_index(syntax_list[operate[i].index + 1]);
				// MOV0 code(direct to register) generate
				if(tem_va == -1){
					va = var_index(syntax_list[operate[i].index - 1]);
					fprintf(fout,"MOV3 R%d, #%d\n", va, atoi(syntax_list[operate[i].index + 1]));
				}
			}

			// ADD code generate
			else if(operate[i+1].operator == '+'){
				va = var_index(syntax_list[operate[i].index - 1]);
				fprintf(fout, "MOV4 R%d, ", va);
				temp = va;
				va = var_index(syntax_list[operate[i].index + 1]);
				fprintf(fout, "R%d\n", va);
				va = var_index(syntax_list[operate[i].index + 3]);
				fprintf(fout, "ADD R%d, R%d\n", temp, va);
			}
			// SUB code generate
			else if(operate[i+1].operator == '-') {
				va = var_index(syntax_list[operate[i].index - 1]);
				fprintf(fout, "MOV4 R%d, ", va);
				temp = va;
				va = var_index(syntax_list[operate[i].index + 1]);
				fprintf(fout, "R%d\n", va);
				va = var_index(syntax_list[operate[i].index + 3]);
				fprintf(fout, "SUB R%d, R%d\n", temp, va);
			}	
		}
	}	
}




