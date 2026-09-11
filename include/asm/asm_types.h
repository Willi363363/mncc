/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** asm_types
*/

#ifndef ASM_TYPES_H_
    #define ASM_TYPES_H_
    #define REG_VALUE(reg) ((unsigned char)((reg) & 0x7))
    #define REG_REX_VALUE(reg) ((unsigned char)(((reg) >> 3) & 0x1))

    #define REX_BASE 0x40
    #define REX_W 0x08
    #define REX_R 0x04
    #define REX_X 0x02
    #define REX_B 0x01

// Mod types
typedef enum {
    MOD_INDIRECT = 0b00,
    MOD_DISP8 = 0b01,
    MOD_DISP32 = 0b10,
    MOD_DIRECT = 0b11,
} mod_type_t;

// Registers
typedef enum {
    REG_RAX = 0b0000,
    REG_RCX = 0b0001,
    REG_RDX = 0b0010,
    REG_RBX = 0b0011,
    REG_RSP = 0b0100,
    REG_RBP = 0b0101,
    REG_RSI = 0b0110,
    REG_RDI = 0b0111,
    REG_R8 = 0b1000,
    REG_R9 = 0b1001,
    REG_R10 = 0b1010,
    REG_R11 = 0b1011,
    REG_R12 = 0b1100,
    REG_R13 = 0b1101,
    REG_R14 = 0b1110,
    REG_R15 = 0b1111,
} registers_t;

typedef enum {
    OPEXT_ADD = 0b000,
    OPEXT_OR = 0b001,
    OPEXT_ADC = 0b010,
    OPEXT_SBB = 0b011,
    OPEXT_AND = 0b100,
    OPEXT_SUB = 0b101,
    OPEXT_XOR = 0b110,
    OPEXT_CMP = 0b111,
} op_ext_t;

#endif /* !ASM_TYPES_H_ */
