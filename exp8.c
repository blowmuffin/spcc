#include <stdio.h>
#include <string.h>

#define MAX_RULES 10

typedef struct {
    char left[10];
    char right[10];
} Rule;

int main(void) {
    int n;
    char input[50], stack[50] = "", tmp[20], *sub;
    Rule rules[MAX_RULES];

    printf("Enter number of rules: ");
    scanf("%d", &n);
    getchar();  // consume newline

    printf("Enter rules in format X->Y (no spaces):\n");
    for (int j = 0; j < n; j++) {
        fgets(tmp, sizeof(tmp), stdin);
        tmp[strcspn(tmp, "\n")] = '\0';

        char *l = strtok(tmp, "->");
        char *r = strtok(NULL, "->");
        if (l && r) {
            strcpy(rules[j].left, l);
            strcpy(rules[j].right, r);
        } else {
            printf("Invalid format. Use A->aB\n");
            j--;  // retry
        }
    }

    printf("Enter input: ");
    scanf("%49s", input);

    int i = 0;
    while (i <= (int)strlen(input)) {
        // SHIFT
        if (i < (int)strlen(input)) {
            int len = strlen(stack);
            stack[len] = input[i];
            stack[len + 1] = '�';
            printf("%s\t%s\tShift %c\n", stack, &input[i + 1], input[i]);
            i++;
        }
        // REDUCE
        int reduced = 0;
        for (int j = 0; j < n; j++) {
            sub = strstr(stack, rules[j].right);
            if (sub) {
                int pos = sub - stack;
                stack[pos] = '�';
                strcat(stack, rules[j].left);
                printf("%s\t%s\tReduce %s->%s\n", stack, &input[i], rules[j].left, rules[j].right);
                reduced = 1;
                break;
            }
        }
        if (reduced) continue;

        // FINAL CHECK
        if (i == (int)strlen(input)) {
            if (strcmp(stack, rules[0].left) == 0) {
                printf("\nAccepted\n");
            } else {
                printf("\nNot Accepted\n");
            }
            break;
        }
    }

    return 0;
}