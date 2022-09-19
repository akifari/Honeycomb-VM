typedef enum {
    HLT, // 0  -- hlt              :: stop the program "halts the central processing unit (CPU) until the next external interrupt is fired."
    PSH, // 1  -- psh val          :: pushes <val> to stack
    POP, // 2  -- pop              :: pops value from stack
    ADD, // 3  -- add              :: adds top two vals on stack
    MUL, // 4  -- mul              :: multiplies top two vals on stack
    DIV, // 5  -- div              :: divides top two vals on stack
    SUB, // 6  -- sub              :: subtracts top two vals on stack
    SLT, // 7  -- slt reg_a, reg_b :: pushes (reg_a < reg_b) to stack "Set if less than"
    MOV, // 8  -- mov reg_a, reg_b :: move the value in reg_a to reg_b
    SET, // 9  -- set reg, val     :: sets the register to value
    LOG, // 10 -- log a            :: prints out a
    IF,  // 11 -- if reg val ip    :: if the register == val branch to the ip
    IFN, // 12 -- ifn reg val ip   :: if the register != val branch to the ip
    GLD, // 13 -- gld reg          :: loads a register to the stack
    GPT, // 14 -- gpt reg          :: pushes top of stack to the given register
    NOP // 15 -- nop             :: nothing
    
} Instructions;

/** Registers */
typedef enum {
    A, B, C, D, E, F, I, J, // GENERAL PURPOSE
    EX,                     // EXCESS
    EXA,                    // MORE EXCESS
    IP,                     // INSTRUCTION POINTER
    SP,                     // STACK POINTER
    REGISTER_SIZE
} Registers;

static int registers[REGISTER_SIZE];

// instructions array
int *instructions;

// how many instructions to do
int instruction_count = 0;

// how much space is allocated for the instructions
// 4 instructions by default
int instruction_space = 4;

/** if the program is running */
static bool running = true;

/** if the IP is assigned by jmp instructions(such as IF,IFN),it should not increase 1 any more **/
bool is_jmp = false;
#define STACK_SIZE 256
static int stack[STACK_SIZE];

/** quick ways to get SP and IP */
#define SP (registers[SP])
#define IP (registers[IP])

/** fetch current instruction set */
// #define FETCH (test_a[IP])
// #define FETCH (test_b[IP])
#define FETCH (instructions[IP])
