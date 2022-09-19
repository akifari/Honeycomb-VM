#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "inst.h"
int input();
int files();
int num;

void print_stack() {
    for (int i = 0; i < SP; i++) {
        printf("0x%04d ", stack[i]);
        if ((i + 1) % 4 == 0) { printf("\n"); }
    }
    if (SP != 0) { printf("\n"); }
}

void print_registers() {
    printf("Register Dump:\n");
    for (int i = 0; i < REGISTER_SIZE; i++) {
        printf("%04d ", registers[i]);
        if ((i + 1) % 4 == 0) { printf("\n"); }
    }
}

int find_empty_register() {
    for (int i = 0; i < REGISTER_SIZE; i++) {
        if (i != registers[EX] && i != registers[EXA]) { return i; }
    }
    return EX;
}

void eval(int instr) {
    is_jmp = false;
    switch (instr) {
        case HLT: {
            running = false;
            printf("Finished Execution\n");
            // print_stack(0, 16);
            // print_registers();
            break;
        }
        case PSH: {
            SP = SP + 1;
            IP = IP + 1;
            stack[SP] = instructions[IP];
            break;
        }
        case POP: {
            SP = SP - 1;
            break;
        }
        case ADD: {
            registers[A] = stack[SP];
            SP = SP - 1;

            registers[B] = stack[SP];
            /* SP = SP - 1; */

            registers[C] = registers[B] + registers[A];

            /* SP = SP + 1; */
            stack[SP] = registers[C];
            printf("%d + %d = %d\n", registers[B], registers[A], registers[C]);
            break;
        }
        case MUL: {
            registers[A] = stack[SP];
            SP = SP - 1;

            registers[B] = stack[SP];
            /*SP = SP - 1;*/

            registers[C] = registers[B] * registers[A];

            /*SP = SP + 1;*/
            stack[SP] = registers[C];
            printf("%d * %d = %d\n", registers[B], registers[A], registers[C]);
            break;
        }
        case DIV: {
            registers[A] = stack[SP];
            SP = SP - 1;

            registers[B] = stack[SP];
            /* SP = SP - 1;*/

            registers[C] = registers[B] / registers[A];

            /* SP = SP + 1; */
            stack[SP] = registers[C];
            printf("%d / %d = %d\n", registers[B], registers[A], registers[C]);
            break;
        }
        case SUB: {
            registers[A] = stack[SP];
            SP = SP - 1;

            registers[B] = stack[SP];
            /* SP = SP - 1; */

            registers[C] = registers[B] - registers[A];

            /* SP = SP + 1; */
            stack[SP] = registers[C];
            printf("%d - %d = %d\n", registers[B], registers[A], registers[C]);
            break;
        }
        case SLT: {
            SP = SP - 1;
            stack[SP] = stack[SP+1] < stack[SP];
            break;
        }
        case MOV: {
            registers[instructions[IP + 2]] = registers[instructions[IP + 1]];
            IP = IP + 2;
            break;
        }
        case SET: {
            registers[instructions[IP + 1]] = instructions[IP + 2];
            IP = IP + 2;
            break;
        }
        case LOG: {
            printf("%d\n", registers[instructions[IP + 1]]);
            IP = IP + 1;
            break;
        }
        case IF: {
            if (registers[instructions[IP + 1]] == instructions[IP + 2]) {
                IP = instructions[IP + 3];
                is_jmp = true;
            }
            else{
                IP = IP + 3;
            }
            break;
        }
        case IFN: {
            if (registers[instructions[IP + 1]] != instructions[IP + 2]) {
                IP = instructions[IP + 3];
                is_jmp = true;
            }
            else {
                IP = IP + 3;
            }
            break;
        }
        case GLD: {
            SP = SP + 1;
            IP = IP + 1;
            stack[SP] = registers[instructions[IP]];
            break;
        }
        case GPT: {
            registers[instructions[IP + 1]] = stack[SP];
            IP = IP + 1;
            break;
        }
        case NOP: {
            printf("Do Nothing\n");
            break;
        }
        default: {
            printf("Unknown Instruction %d\n", instr);
            break;
        }
    }
}

int main(int argc, char** argv) {
    

    int files() {
    
    FILE *file;
    char fnamer[100]="";
    char *filename = argv[1] = fnamer;
    

    printf("Input file name\n");
    scanf("%s",&fnamer);
    

    file = fopen(filename, "r");
    if (!file) {
        printf("error: could not read file `%s`\n", filename);
        return -1;
    }

    instructions = malloc(sizeof(*instructions) * instruction_space);
    
    int num;
    int i = 0;
    while (fscanf(file, "%d", &num) > 0) {
        instructions[i] = num;
       
        i++;
        if (i >= instruction_space) {
            instruction_space *= 2;
            instructions = realloc(instructions, sizeof(*instructions) * instruction_space); // double size
        }
    }
    
   

    // set 'instruction_count' to number of instructions read
    instruction_count = i;

    // close the file
    fclose(file);

    // initialize stack pointer
    SP = -1;
    // loop through program, but don't
    // go out of the programs bounds
    while (running && IP < instruction_count) {
        eval(FETCH);
        if(!is_jmp){
            IP = IP + 1;
        }
    }

    // clean up instructions
    free(instructions);

    }
    
    
    int input(){

    // allocate space for instructions
    instructions = malloc(sizeof(*instructions) * instruction_space); // 4 instructions
   
   
    int i = 0;
    while (scanf("%d", &num) > 0) {
        instructions[i] = num;
       // printf("%d\n", instructions[i]);
        i++;
    
        if (i >= instruction_space) {
            instruction_space *= 2;
            instructions = realloc(instructions, sizeof(*instructions) * instruction_space); // double size
        }
        
    }
    
        instruction_count = i;

        SP = -1;


        while (running && IP < instruction_count) {
        eval(FETCH);
        if(!is_jmp){
            IP = IP + 1;
        } 
    }

        free(instructions);
    }



    int choose;
    int options;
    
    while(options){
    
    
    
     printf ("***       *****      *****    **** ********\n");
     printf ("***        *****      *****    **** ********\n");

     printf("                             /  \n");
     printf("WELCOME TO HONEYCOMBVM     -(): \n");
     printf("                            / \n");

     printf ("Make your choice\n");
     printf ("Instructions   -->>> 0 \n");
     printf ("Give input     -->>> 1 \n");
     printf ("Read from file  -->> 2 \n");
     printf ("Exit           -->>> 3 \n");

     printf ("***       *****      *****    **** ********\n");
     printf ("***        *****      *****    **** ********\n");
     scanf("%d", &choose);
    
    
    switch (choose)
    {

        
    case 0:
     printf ("Instructions\n");
    printf ("  0      hlt 	 			halts program\n"
            "  1      psh val  			pushes <val> to stack\n"
            "  2      pop 	 			pops value from stack\n"
            "  3      add 	 			adds top two vals on stack\n"
            "  4      mul 	 			multiplies top two vals on stack\n"
            "  5      div 	 			divides top two vals on stack\n"
            "  6      sub 	 			subtracts top two vals on stack\n"
            "  7      mov reg        	movs the value in reg_a to reg_b \n"
            "  8      set reg    		sets the reg to value\n"
            "  9      Print       			prints out a\n"
            "  10     JMP          	    if the register == val branch to the ip\n"
            "  11     JMP  		        if the register != val branch to the ip\n"
            "  10     gld reg 			loads a register to the stack\n"
            "  11     gpt reg 			pushes top of stack to the given register\n"
            "  12     nop 				nothing\n");
            break;

    case 1:
    options = 0;
    input();
   
            break;

    case 2:
    files();
            break;

    case 3:
            return 0;
    
        
             
    }
    fflush (stdin);
        printf ("Continue or Exit(Type 0 or 1)?\n");
        scanf    ("%d", &options);
    }
    EndWhile: ;
    // set 'instruction_count' to number of instructions read

    // close the file
    

    // initialize stack pointer
    

    // loop through program, but don't
    // go out of the programs bounds
    

    return 0;
}