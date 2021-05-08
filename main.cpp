#include <iostream>
#include <fstream>
#include "main.h"

using namespace std;


struct Memory {
    static constexpr uint32_t MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];

    void init() {
        for (Byte &i : Data)
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

    Byte &fetchMemory() {
        return memory[(fetch() << 8) + fetch()];
    }

    Byte &fetchOffset() {
        return memory[PC + (char) fetch()];
    }

    bool execute() {
        Byte opcode = fetch();
        switch (opcode) {
            //REGISTER A
            case LDA_IMM: //LDA Immediate
                A = fetch();
                break;
            case LDA_ABS: //LDA Absolute
                A = fetchMemory();
                break;
            case LDA_REL: //LDA Absolute
                A = fetchOffset();
                break;
            case STA: //STA
                fetchMemory() = A;
                break;
            case STA_REL: //STA
                fetchOffset() = A;
                break;
            case PLA: //PLA
                A = memory[0x0100 + ++SP];
                break;
            case PHA: //PHA
                memory[0x0100 + SP--] = A;
                break;
            case INA:
                Z = !++A;
                N = A >> 7;
                break;
            case DEA:
                Z = !--A;
                N = A >> 7;
                break;
            case CMP_IMM:
                C = A >= fetch();
                PC--;
                Z = A == fetch();
                PC--;
                N = fetch() >> 7;
                break;
            case CMP_ABS:
                C = A >= fetchMemory();
                PC -= 2;
                Z = A == fetchMemory();
                PC -= 2;
                N = fetchMemory() >> 7;
                break;
            case CMP_REL:
                C = A >= fetchOffset();
                PC--;
                Z = A == fetchOffset();
                PC--;
                N = fetchOffset() >> 7;
                break;
                //REGISTER X
            case LDX_IMM:
                X = fetch();
                break;
            case LDX_ABS:
                X = fetchMemory();
                break;
            case LDX_REL:
                X = fetchOffset();
                break;
            case STX:
                fetchMemory() = X;
                break;
            case STX_REL:
                fetchOffset() = X;
                break;
            case PLX:
                X = memory[0x0100 + ++SP];
                break;
            case PHX:
                memory[0x0100 + SP--] = X;
                break;
            case INX:
                Z = !++X;
                N = X >> 7;
                break;
            case DEX:
                Z = !--X;
                N = X >> 7;
                break;
            case CMX_IMM:
                C = X >= fetch();
                PC--;
                Z = X == fetch();
                PC--;
                N = fetch() >> 7;
                break;
            case CMX_ABS:
                C = X >= fetchMemory();
                PC -= 2;
                Z = X == fetchMemory();
                PC -= 2;
                N = fetchMemory() >> 7;
                break;
            case CMX_REL:
                C = X >= fetchOffset();
                PC--;
                Z = X == fetchOffset();
                PC--;
                N = fetchOffset() >> 7;
                break;
                //REGISTER Y
            case LDY_IMM:
                Y = memory[PC++];
                break;
            case LDY_ABS:
                Y = fetchMemory();
                break;
            case LDY_REL:
                Y = fetchOffset();
                break;
            case STY:
                fetchMemory() = Y;
                break;
            case STY_REL:
                fetchOffset() = Y;
                break;
            case PLY:
                Y = memory[0x0100 + ++SP];
                break;
            case PHY:
                memory[0x0100 + SP--] = Y;
                break;
            case INY:
                Z = !++Y;
                N = Y >> 7;
                break;
            case DEY:
                Z = !--Y;
                N = Y >> 7;
                break;
            case CMY_IMM:
                C = Y >= fetch();
                PC--;
                Z = Y == fetch();
                PC--;
                N = fetch() >> 7;
                break;
            case CMY_ABS:
                C = Y >= fetchMemory();
                PC -= 2;
                Z = Y == fetchMemory();
                PC -= 2;
                N = fetchMemory() >> 7;
                break;
            case CMY_REL:
                C = Y >= fetchOffset();
                PC -= 2;
                Z = Y == fetchOffset();
                PC -= 2;
                N = fetchOffset() >> 7;
                break;
                //MEMORY-INCREMENTS/DECREMENTS
            case INC:
                Z = !++fetchMemory();
                PC -= 2;
                N = fetchMemory() >> 7;
                break;
            case INC_REL:
                Z = !++fetchOffset();
                PC--;
                N = fetchOffset() >> 7;
                break;
            case DEC:
                Z = !--fetchMemory();
                PC -= 2;
                N = fetchMemory() >> 7;
                break;
            case DEC_REL:
                Z = !--fetchOffset();
                PC--;
                N = fetchOffset() >> 7;
                break;
                //SPECIALS
            case ADD_IMM:
                A += fetch();
                break;
            case ADD_ABS:
                A += fetchMemory();
                break;
            case ADD_REL:
                A += fetchOffset();
                break;
            case JMP:
                PC = (fetch() << 8) + fetch();
                break;
            case PRC:
                cout << memory[0x0100 + ++SP] << flush;
                break;
            case PRD:
                cout << memory[0x0100 + ++SP] + 0x30 << flush;
                break;
            case PRN:
                cout << endl;
                break;
            case PRH:
                cout << HEX[memory[0x0100 + ++SP] >> 4] << HEX[memory[0x0100 + SP] & 0xF] << flush;
                break;

            case BEQ_IMM:
                if (Z) {
                    PC += (signed char) fetch();
                } else fetch();
                break;
            case BEQ_ABS:
                if (Z) {
                    PC += (signed char) fetchMemory();
                } else fetchMemory();
                break;
            case BEQ_REL:
                if (Z) {
                    PC += (signed char) fetchOffset();
                } else fetchOffset();
                break;
            case BNE_IMM:
                if (!Z)
                    PC += (signed char) fetch()-1;
                else fetch();
                break;
            case BNE_ABS:
                if (!Z)
                    PC += (signed char) fetchMemory()-1;
                else fetchMemory();
                break;
            case BNE_REL:
                if (!Z)
                    PC += (signed char) fetchOffset()-1;
                else fetchOffset();
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


void load_file(const string &filename, Memory &memory, Word &position);


int main(int argc, char *argv[]) {
    Memory memory{};
    CPU cpu{memory};
    cpu.reset();

    //JMP to start of memory (start of program)
    memory[0xFFFC] = JMP;
    Word program_counter = 0x0200;
    memory[0xFFFD] = program_counter >> 8;
    memory[0xFFFE] = program_counter & 0xFF;
    for (int i = 1; i < argc; ++i) {
        load_file(argv[i], memory, program_counter);
    }

    while (true) {
        if (!cpu.execute()) break;
    }
}

void load_file(const string &filename, Memory &memory, Word &position) {
    ifstream file(filename, ios::binary);
    for (int i = 0; file; ++i) {
        char chr = file.get();
        memory[position + i] = chr;
    }
}
