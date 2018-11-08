# Compiler in C

![01_agenda](01_figs/01_agenda.png)

## Purpose

![03_purpose](01_figs/03_purpose.png)

## Conditions

Type : int   /  Operation : '+', '-'

Two operand in a line

![02_two_operand](01_figs/02_two_operand.png)

## 1. Lexical analyze / Scan

#### 1. 문자열(input-code)를 의미 있는 token으로 변환.

input code

```c
main() {
    int a,b,c,d;
    
    a = 5;
    b = 3;
    c = 1;
    d = 4;
    
    a = b + c;
    d = b - c;
}
```

#### 2. Output : token, syntax_list.

first, Store input code in buffer[] except 'tab', 'enter'

![04_first_buf](01_figs/04_first_buf.png)

second, Store input-code in buffer[] except ';'  'space'  ','

![05_second_buf](01_figs/05_second_buf.png)

now, we make Tokens!

Then, i manage tokens with syntax_list.

![06_syntax_list](01_figs/06_syntax_list.png)

because list is easy to control for me.

## 2. Syntax analyzing

first, Classifying Variable / Operator like below.

![07_var_op](01_figs/07_var_op.png)

Manage variable in Linked-list, and operator in linear list. Operator is used for code generation, so i use linear list for easy to code generation.

#### Classifying variables

![08_var](01_figs/08_var.png)

So, start index = start / end index = last

```c
for(cnt = start; cnt < last; cnt++){
    Add_list(L1, syntax_list[cnt]);
    for(_cnt = last; syntax_list[_cnt]; _cnt++){
        if(strcmp(syntax_list[cnt], syntax_list[_cnt]) == 0){
            (L1->last->usage)++;
        }
    }
}
```

There is a section to check the usage, which is to give priority.

It is so important to compile, because when the number of registers is fixed and when there are many variables, the priority is determined and the registers are allocated.

So, if there is 16registers, 17st var is in to Memory.

But, there is big Problem.

![09_problem](01_figs/09_problem.png)

So you must control register usage for optimization.

#### Classifying Operator

![10_op](01_figs/10_op.png)



## 3. Code generation

We use Operator list for Code generation.

![11_op(list)](01_figs/11_op(list).png)

#### MOV3

in assembler, MOV3 is register to register.

![12_MOV3](01_figs/12_MOV3.png)

#### MOV4, ADD

I made assembler for two operation, so we make code for assembler.

ADD R0, R1, R2   ->  MOV4 R0, R1 + ADD R0, R2

![13_MOV4,ADD](01_figs/13_MOV4,ADD.png)

#### MOV4, SUB

It is same that add code generation.

![14_SUB](01_figs/14_SUB.png)

## 4. OUTPUT

You can see output like below.

![15_output](01_figs/15_output.png)

then, look at assembler and decoder together.

![16_out2](01_figs/16_out2.png)



