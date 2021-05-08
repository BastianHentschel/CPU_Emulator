//
// Created by basti on 05/05/2021.
//

#ifndef CPU_EMULATOR_MAIN_H
#define CPU_EMULATOR_MAIN_H

#include <map>
#include <vector>

typedef uint8_t Byte;
typedef uint16_t Word;
typedef uint64_t Register64;
typedef uint64_t Register8;

constexpr char LETTERS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


constexpr Byte LDA_IMM = 0x01;
constexpr Byte LDA_ABS = 0x02;
constexpr Byte LDA_REL = 0x03;
constexpr Byte STA = 0x04;
constexpr Byte STA_REL = 0x05;
constexpr Byte PLA = 0x06;
constexpr Byte PHA = 0x07;
constexpr Byte INA = 0x08;
constexpr Byte DEA = 0x09;
constexpr Byte CMP_IMM = 0x0A;
constexpr Byte CMP_ABS = 0x0B;
constexpr Byte CMP_REL = 0x0C;

constexpr Byte LDX_IMM = 0x11;
constexpr Byte LDX_ABS = 0x12;
constexpr Byte LDX_REL = 0x13;
constexpr Byte STX = 0x14;
constexpr Byte STX_REL = 0x15;
constexpr Byte PLX = 0x16;
constexpr Byte PHX = 0x17;
constexpr Byte INX = 0x18;
constexpr Byte DEX = 0x19;
constexpr Byte CMX_IMM = 0x1A;
constexpr Byte CMX_ABS = 0x1B;
constexpr Byte CMX_REL = 0x1C;

constexpr Byte LDY_IMM = 0x21;
constexpr Byte LDY_ABS = 0x22;
constexpr Byte LDY_REL = 0x23;
constexpr Byte STY = 0x24;
constexpr Byte STY_REL = 0x25;
constexpr Byte PLY = 0x26;
constexpr Byte PHY = 0x27;
constexpr Byte INY = 0x28;
constexpr Byte DEY = 0x29;
constexpr Byte CMY_IMM = 0x2A;
constexpr Byte CMY_ABS = 0x2B;
constexpr Byte CMY_REL = 0x2C;

constexpr Byte INC = 0x36;
constexpr Byte INC_REL = 0x37;
constexpr Byte DEC = 0x38;
constexpr Byte DEC_REL = 0x39;

constexpr Byte ADD_IMM = 0xA0;
constexpr Byte ADD_ABS = 0xA1;
constexpr Byte ADD_REL = 0xA2;



constexpr Byte PRC = 0xB0;
constexpr Byte PRD = 0xB1;
constexpr Byte PRN = 0xB2;
constexpr Byte PRH = 0xB3;


constexpr Byte BEQ_ABS = 0xC1;
constexpr Byte BEQ_IMM = 0xC2;
constexpr Byte BEQ_REL = 0xC3;
constexpr Byte BNE_ABS = 0xC4;
constexpr Byte BNE_IMM = 0xC5;
constexpr Byte BNE_REL = 0xC6;

constexpr Byte JMP = 0xF0;

constexpr Byte ZRO = 0xF1; //Zeroes Flags and Registers
constexpr Byte STP = 0x00;

constexpr char *HEX = (char *) "0123456789ABCDEF";

enum DATA_TYPE {
    IMMEDIATE, ABSOLUTE, RELATIVE, VAR
};

enum ASM_MODE {
    DATA, CODE
} mode;

std::map<std::string, std::vector<Word>> data_addresses;
std::map<std::string, Byte> data_values;

std::map<std::string, std::vector<Word>> label_from_addresses;
std::map<std::string, Word> label_addresses;

#endif //CPU_EMULATOR_MAIN_H
