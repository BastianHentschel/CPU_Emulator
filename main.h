//
// Created by basti on 05/05/2021.
//

#ifndef CPU_EMULATOR_MAIN_H
#define CPU_EMULATOR_MAIN_H

typedef uint8_t Byte;
typedef uint16_t Word;
typedef uint64_t Register64;
typedef uint64_t Register8;

constexpr Byte LDA_IMM = 0x01;
constexpr Byte LDA_ABS = 0x02;
constexpr Byte STA = 0x03;
constexpr Byte PLA = 0x04;
constexpr Byte PHA = 0x05;
constexpr Byte INA = 0x06;
constexpr Byte DEA = 0x07;
constexpr Byte CMP = 0x08;

constexpr Byte LDX_IMM = 0x11;
constexpr Byte LDX_ABS = 0x12;
constexpr Byte STX = 0x13;
constexpr Byte PLX = 0x14;
constexpr Byte PHX = 0x15;
constexpr Byte INX = 0x16;
constexpr Byte DEX = 0x17;
constexpr Byte CPX = 0x18;

constexpr Byte LDY_IMM = 0x21;
constexpr Byte LDY_ABS = 0x22;
constexpr Byte STY = 0x23;
constexpr Byte PLY = 0x24;
constexpr Byte PHY = 0x25;
constexpr Byte INY = 0x26;
constexpr Byte DEY = 0x27;
constexpr Byte CPY = 0x28;

constexpr Byte INC = 0x36;
constexpr Byte DEC = 0x37;

constexpr Byte ADD = 0xA0;


constexpr Byte PRC = 0xB0;
constexpr Byte PRD = 0xB1;
constexpr Byte PRN = 0xB2;
constexpr Byte PRH = 0xB3;


constexpr Byte BEQ = 0xC1;

constexpr Byte JMP = 0xF0;

constexpr Byte ZRO = 0xF1; //Zeroes Flags and Registers
constexpr Byte STP = 0x00;

constexpr char *HEX = (char *) "0123456789ABCDEF";

#endif //CPU_EMULATOR_MAIN_H
