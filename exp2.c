#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char label[20];
    int addr;
} Symbol;

Symbol symtab[MAX];
int count = 0;

void add_symbol(const char *label, int addr) {
    // Avoid duplicate entries
    for (int i = 0; i < count; i++) {
        if (strcmp(symtab[i].label, label) == 0) {
            return;
        }
    }
    strcpy(symtab[count].label, label);
    symtab[count].addr   = addr;
    count++;
}

void show_table() {
    printf("\nSymbol Table:\n");
    printf("%-10s | %s\n", "Symbol", "Address");
    for (int i = 0; i < count; i++) {
        printf("%-10s | %d\n", symtab[i].label, symtab[i].addr);
    }
}

int main() {
    const char *code[7][3] = {
        { "",    "START", "200" },
        { "LOOP","LDA",   "A"   },
        { "",    "ADD",   "ONE" },
        { "",    "STA",   "A"   },
        { "A",   "DB",    "5"   },
        { "ONE", "DB",    "1"   },
        { "",    "END",   ""    }
    };

    for (int loc = 199, i = 0; i < 7; i++, loc++) {
        if (strlen(code[i][0]) > 0) {
            add_symbol(code[i][0], loc);
        }
    }

    show_table();
    return 0;
}
