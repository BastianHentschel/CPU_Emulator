#include <iostream>
#include "main.h"

using namespace std;



struct Memory {
    static constexpr uint32_t MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];

    void init() {
        for (unsigned char &i : Data)
            i = 0;
    }

    Byte &operator[](uint32_t index) {
        return Data[index];
    }
};


struct CPU {
    Memory &memory;
    Word PC = 0xFFFC; //Program Counter
    Byte SP = 0xFF; //Stack Pointer

    //Registers
    Register8 A = 0x00;
    Register8 X = 0x00;
    Register8 Y = 0x00;

    Byte C: 1 = 0; //Carry
    Byte Z: 1 = 0; //Zero
    Byte I: 1 = 0; //Interrupt Disable
    Byte D: 1 = 0; //Decimal Mode
    Byte B: 1 = 0; //Break Command
    Byte V: 1 = 0; //Overflow
    Byte N: 1 = 0; //Negative

    void reset() {
        PC = 0xFFFC;
        SP = 0xFF;
        C = Z = I = D = B = V = N = 0;
        A = X = Y = 0;

        memory.init();
    }

    Byte fetch() {
        return memory[PC++];
    }

    bool execute() {
        Byte opcode = fetch();
        switch (opcode) {
            //REGISTER A
            case LDA_IMM: //LDA Immediate
                A = fetch();
                break;
            case LDA_ABS: //LDA Absolute
                A = memory[(fetch() << 8) + fetch()];
                break;
            case STA: //STA
                memory[(fetch() << 8) + fetch()] = A;
                break;
            case PLA: //PLA
                A = memory[0x0100 + ++SP];
                break;
            case PHA: //PHA
                memory[0x0100 + SP--] = A;
                break;
            case INA:
                A++;
                break;
            case DEA:
                A--;
                break;
            case CMP:
                C = A >= fetch();
                PC--;
                Z = A == fetch();
                PC--;
                N = fetch()>>7;

            //REGISTER X
            case LDX_IMM:
                X = fetch();
                break;
            case LDX_ABS:
                X = memory[(fetch() << 8) + fetch()];
                break;
            case STX:
                memory[(fetch() << 8) + fetch()] = X;
                break;
            case PLX:
                X = memory[0x0100 + ++SP];
                break;
            case PHX:
                memory[0x0100 + SP--] = X;
                break;
            case INX:
                X++;
                break;
            case DEX:
                X--;
                break;
            //REGISTER Y
            case LDY_IMM:
                Y = memory[PC++];
                break;
            case LDY_ABS:
                Y = memory[(fetch() << 8) + fetch()];
                break;
            case STY:
                memory[(fetch() << 8) + fetch()] = Y;
                break;
            case PLY:
                Y = memory[0x0100 + ++SP];
                break;
            case PHY:
                memory[0x0100 + SP--] = Y;
                break;
            case INY:
                Y++;
                break;
            case DEY:
                Y--;
                break;
            //MEMORY-INCREMENTS/DECREMENTS
            case INC:
                memory[(fetch()<<8)+fetch()]++;
                break;
            case DEC:
                Z = !--memory[(fetch()<<8)+fetch()];
                break;
            //SPECIALS
            case ADD:
                A += memory[(fetch() << 8) + fetch()];
                break;
            case JMP:
                PC = (fetch() << 8) + fetch();
                break;
            case PRC:
                cout << memory[0x0100 + ++SP];
                break;
            case PRD:
                cout << memory[0x0100 + ++SP] + 0x30;
                break;
            case PRN:
                cout << endl;
                break;
            case PRH:
                cout << HEX[memory[0x0100 + ++SP] >> 4] << HEX[memory[0x0100 + SP] & 0xF];
                break;

            case BEQ:
                if (Z) {
                    PC+=fetch();
                } else fetch();
                break;
            case ZRO:
                C = Z = I = D = B = V = N = 0;
                A = X = Y = 0;
                break;
            case STP:
                return false;
            default:
                exit(1);

        }
        return true;
    }

};


void load_fibonacci(Memory &memory, Word &program_counter) {
    //ZERO PROCESSOR FLAGS AND REGISTERS
    memory[program_counter++] = ZRO;
    //INIT COUNTER TO 10
    memory[program_counter++] = LDA_IMM;
    memory[program_counter++] = 10;
    memory[program_counter++] = STA;
    memory[program_counter++] = 0x04;
    memory[program_counter++] = 0x00;
    // INIT A WITH 1
    memory[program_counter++] = LDA_IMM;
    memory[program_counter++] = 0x01;


    //PUSH AND PRINT
    const Byte LOOPL = program_counter>>8;
    const Byte LOOPR = program_counter&0xFF;
    memory[program_counter++] = PHX;
    memory[program_counter++] = PRH;
    memory[program_counter++] = LDY_IMM; //SET Y TO 0x20
    memory[program_counter++] = 0x20;
    memory[program_counter++] = PHY;
    memory[program_counter++] = PRC;
    memory[program_counter++] = PRN;
    //PUSH A
    memory[program_counter++] = PHA;
    //STORE X
    memory[program_counter++] = STX;
    memory[program_counter++] = 0x10;
    memory[program_counter++] = 0x10;
    //ADD MEMORY
    memory[program_counter++] = ADD;
    memory[program_counter++] = 0x10;
    memory[program_counter++] = 0x10;
    // PULL X
    memory[program_counter++] = PLX;
    //Branch if counter zero
    memory[program_counter++] = DEC;
    memory[program_counter++] = 0x04;
    memory[program_counter++] = 0x00;
    memory[program_counter++] = BEQ;
    memory[program_counter++] = 0x03;

    //JMP
    memory[program_counter++] = JMP;
    memory[program_counter++] = LOOPL;
    memory[program_counter++] = LOOPR;
}

int main() {
    Memory memory{};
    CPU cpu{memory};
    cpu.reset();

    //JMP to start of memory (start of program)
    memory[0xFFFC] = JMP;
    Word program_counter = 0x0200;
    memory[0xFFFD] = program_counter>>8;
    memory[0xFFFE] = program_counter&0xFF;

    load_fibonacci(memory, program_counter);
    load_fibonacci(memory, program_counter);


    while (true) {
        if (!cpu.execute()) break;
    }

}
