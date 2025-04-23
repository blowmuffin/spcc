#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char symbol[20];
    int address;
} Symbol;

typedef struct {
    char literal[20];
    int address;
} Literal;

typedef struct {
    char mnemonic[20];
    int opcode;
} Mnemonic;

// Sample code lines
static const char *code[] = {
    "START 100",
    "X LDA 200",
    "STA Z",
    "ADD -20",
    "MUL -30",
    "END"
};

static Mnemonic mTab[] = {
    { "START", 0 }, { "LDA", 1 }, { "STA", 2 },
    { "ADD",   3 }, { "SUB", 4 }, { "MUL", 5 },
    { "DIV",   6 }, { "END", 7 }
};

static Symbol sym[MAX];
static Literal lit[MAX];
static int symCount = 0, litCount = 0;
static int locTable[MAX], locIndex = 0;

// Check if token is a mnemonic
static int isMnemonic(const char *token) {
    for (int i = 0; i < (int)(sizeof(mTab)/sizeof(mTab[0])); i++) {
        if (strcmp(mTab[i].mnemonic, token) == 0) {
            return 1;
        }
    }
    return 0;
}

// First pass: record symbols and literals
void firstPass(void) {
    int loc = 0;
    for (int i = 0; i < 6; i++) {
        char w1[20] = "", w2[20] = "", w3[20] = "";
        int n = sscanf(code[i], "%19s %19s %19s", w1, w2, w3);

        // Handle START directive
        if (strcmp(w1, "START") == 0 || strcmp(w2, "START") == 0) {
            sscanf((n == 2 ? w2 : w3), "%d", &loc);
            continue;
        }

        // If first token is not mnemonic, treat as symbol
        if (!isMnemonic(w1)) {
            strcpy(sym[symCount].symbol, w1);
            sym[symCount].address = loc;
            symCount++;
        }

        // Detect literal (negative operand)
        const char *operand = (n == 2 ? w2 : w3);
        if (operand[0] == '-') {
            int exists = 0;
            for (int j = 0; j < litCount; j++) {
                if (strcmp(lit[j].literal, operand) == 0) {
                    exists = 1;
                    break;
                }
            }
            if (!exists) {
                strcpy(lit[litCount].literal, operand);
                lit[litCount].address = -1;  // To assign later
                litCount++;
            }
        }

        locTable[locIndex++] = loc++;
    }
}

// Second pass: assign addresses to literals
void secondPass(void) {
    int nextAddr = locTable[locIndex - 1] + 1;
    for (int i = 0; i < litCount; i++) {
        if (lit[i].address == -1) {
            lit[i].address = nextAddr++;
        }
    }
}

// Print all tables
void printTables(void) {
    printf("\nSymbol Table:\n");
    for (int i = 0; i < symCount; i++) {
        printf("%s : %d\n", sym[i].symbol, sym[i].address);
    }

    printf("\nLiteral Table:\n");
    for (int i = 0; i < litCount; i++) {
        printf("%s : %d\n", lit[i].literal, lit[i].address);
    }

    printf("\nLocation Counter Table:\n");
    for (int i = 0; i < locIndex; i++) {
        printf("Line %d : %d\n", i + 1, locTable[i]);
    }

    printf("\nMnemonic Table:\n");
    for (int i = 0; i < (int)(sizeof(mTab)/sizeof(mTab[0])); i++) {
        printf("%s : %d\n", mTab[i].mnemonic, mTab[i].opcode);
    }
}

int main(void) {
    firstPass();
    secondPass();
    printTables();
    return 0;
}