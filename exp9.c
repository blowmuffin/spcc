#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Return operator precedence
static int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Convert infix to postfix
static void infixToPostfix(const char *infix, char *postfix) {
    char stack[100];
    int top = -1, k = 0;
    for (int i = 0; infix[i]; i++) {
        char ch = infix[i];
        if (isalnum((unsigned char)ch)) {
            postfix[k++] = ch;
        } else if (ch == '(') {
            stack[++top] = ch;
        } else if (ch == ')') {
            while (top >= 0 && stack[top] != '(') {
                postfix[k++] = stack[top--];
            }
            top--;
        } else {
            while (top >= 0 && precedence(stack[top]) >= precedence(ch)) {
                postfix[k++] = stack[top--];
            }
            stack[++top] = ch;
        }
    }
    while (top >= 0) {
        postfix[k++] = stack[top--];
    }
    postfix[k] = '\0';
}

// Generate Three Address Code from postfix
static void generateTAC(const char *postfix) {
    char stk[100][10];
    int top = -1, temp = 1;
    for (int i = 0; postfix[i]; i++) {
        char ch = postfix[i];
        if (isalnum((unsigned char)ch)) {
            char op[2] = { ch, '\0' };
            strcpy(stk[++top], op);
        } else {
            char arg2[10], arg1[10], res[10];
            strcpy(arg2, stk[top--]);
            strcpy(arg1, stk[top--]);
            sprintf(res, "t%d", temp++);
            printf("%s = %s %c %s\n", res, arg1, ch, arg2);
            strcpy(stk[++top], res);
        }
    }
}

int main(void) {
    char expr[100], postfix[100];
    printf("Enter an expression: ");
    scanf("%99s", expr);
    infixToPostfix(expr, postfix);
    printf("\nThree Address Code:\n");
    generateTAC(postfix);
    return 0;
}