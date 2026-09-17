/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** asm_types
*/

#ifndef ASM_TYPES_H_
    #define ASM_TYPES_H_

    #include <stdbool.h>
    #include <sys/types.h>

    #define REG_VALUE(reg) ((unsigned char)((reg) & 0x7))
    #define REG_REX_VALUE(reg) ((unsigned char)(((reg) >> 3) & 0x1))

    #define REX_BASE 0x40
    #define REX_W 0x08
    #define REX_R 0x04
    #define REX_X 0x02
    #define REX_B 0x01

    #define MAX_TOKENS 8
    #define MAX_TOKEN_LEN 64

    #define CB_BUFFER_CAPACITY (size_t)(2048)
    #define ELFW_VADDR_BASE 0x400000
    #define ELFW_PHDR_ALIGN 0x1000
    #define SYMTAB_DEFAULT_CAP 8
    #define FIXUP_DEFAULT_CAP 8

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

// Op kind enum
typedef enum {
    OPD_NONE,
    OPD_REG,
    OPD_IMM,
    OPD_MEM, // [base_reg ± disp8] -- base_reg n'importe lequel
    OPD_LABEL,
} operand_kind_t;

// CodeBuffer Struct
typedef struct code_buffer_s {
    unsigned char *ptr;
    size_t len;
    size_t tot;
} code_buffer_t;

typedef struct {
    char name[256];
    size_t offset;
    bool defined;
} symbol_t;

typedef struct {
    symbol_t *items;
    size_t len;
    size_t cap;
} symtab_t;

typedef struct {
    size_t patch_offset;
    char symbol[256];
} fixup_t;

typedef struct {
    fixup_t *items;
    size_t len;
    size_t cap;
} fixup_list_t;

// Tout regrouper d'un coup
typedef struct {
    code_buffer_t *cb;
    symtab_t *st;
    fixup_list_t *fl;
} asm_ctx_t;

typedef enum {
    OPEXT_ADD=0b000,
    OPEXT_OR=0b001,
    OPEXT_ADC=0b010,
    OPEXT_SBB=0b011,
    OPEXT_AND=0b100,
    OPEXT_SUB=0b101,
    OPEXT_XOR=0b110,
    OPEXT_CMP=0b111,
} opext_t;

// Encodage d'une instruction
typedef struct {
    operand_kind_t kind;
    registers_t reg; /* OPD_REG, ou registre de BASE pour OPD_MEM */
    int64_t imm; /* OPD_IMM */
    int8_t disp; /* OPD_MEM */
    char label[256]; /* OPD_LABEL */
} operand_t;

// Dictionnaire des formes de chaque keyword
typedef struct {
    const char *mnemonic;
    operand_kind_t op1_kind;
    operand_kind_t op2_kind;
    bool needs_rex_w;
    uint8_t opcode_prefix;
    uint8_t opcode;
    bool plus_reg;
    bool has_modrm;
    int8_t modrm_reg;
    bool reg_is_op1;
    uint8_t imm_size;
    bool is_rel32;
} instr_form_t;

extern const instr_form_t instr_table[];
extern const size_t instr_table_len;

// Contexte d'encodage d'une instruction
typedef struct {
    asm_ctx_t *ctx;
    const instr_form_t *form;
    const operand_t *ops;
    size_t n_ops;
} encode_ctx_t;

// Champs reg/rm résolus pour un octet ModRM
typedef struct {
    registers_t reg_field;
    registers_t rm_reg;
    bool rm_is_mem;
    int8_t mem_disp;
} modrm_info_t;

// Tokenizer ASM
typedef struct {
    char items[MAX_TOKENS][MAX_TOKEN_LEN];
    size_t count;
} token_list_t;

typedef struct {
    const char *name;
    registers_t reg;
} reg_name_entry_t;

#endif /* !ASM_TYPES_H_ */
