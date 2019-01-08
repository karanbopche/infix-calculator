#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int calculator(char* str);
int isOperand(const char* item);
void toPostfix(char * equation);
int operatorIndex(char a);

int main(int argc, char* argv[])
{
    int result;
    char equation[60];
    ///test equation char equation[] =  "24 * 15 * 06 - 19 * 95 / 14 / 2 + 12 - 19";
    if(argc < 2)
    {
        printf("Enter the equation with space separated elements.\n");
        gets(equation);
    }
    else
        strcpy(equation, argv[1]); /// get equation from argument........

    printf("entered equation %s\n", equation);
    toPostfix(equation);
    ///printf("postfix string is %s\n", equation);
    result = calculator(equation);
    printf("result of calculation is : %d\n", result);
    return 0;
}
void toPostfix(char * equation)
{
    char stack[10];
    int top=0;
    int size = strlen(equation)+1;
    char postfix[size];
    postfix[0] = '\0';
    char *item = strtok(equation, " "); /// delimit for each element.......
    while(item) {
        if(isOperand(item)){ /// operands add to postfix equations directly....
            strcat(postfix, item);
            strcat(postfix, " "); /// operator delimiter.........
        }
        else {
            if(top > 0){    /// only if stack is not empty........
                if(operatorIndex(stack[top-1]) < operatorIndex(*item)){ /// if current operator is of higher precedences than previous.
                    stack[top++] = *item;       /// put on stack and check for next operator....
                }
                else {
                    char buffer[] = "  ";   /// temporary buffer for strings...
                    buffer[0] = stack[--top];   /// put operator from top of stack into equation...
                    strcat(postfix, buffer);
                    stack[top++] = *item;       /// put current operator on stack for further....
                }
            }
            else    /// stack is empty....
                stack[top++] = *item;       /// first operand.......
        }
        item = strtok(NULL, " ");   /// check for next element in equation........
    }
    while(top > 0){         /// put all the remaining operators from stack to equations.....
        char buffer[3] = "  ";
        buffer[0] = stack[--top];
        strcat(postfix, buffer);
    }
    strcpy(equation, postfix);
}
/// function for checking operator precedence.........
int operatorIndex(char a) {
    int ret = 0;
    switch (a)
    {
        case '+' : ret = 1; break;
        case '-' : ret = 1; break;
        case '*' : ret = 2; break;
        case '/' : ret = 2; break;
        case '%' : ret = 2; break;
        case '(' : ret = -1; break;
    }
    return ret;

}
/// check if current equation item is an operator or not.......
int isOperand(const char* item) {
    while(*item) {
        if(!isdigit(*item))
            return 0;
        item++;
    }
    return 1;
}
/// solve the postfix equation..........
int calculator(char* str) {
    int stack[10], top = 0;
    const char* item = strtok(str, " ");
    int operator1, operator2, result=0;
    while(item != NULL)
    {
        if(isOperand(item))     /// if current item is operator (number) put it on stack.....
            stack[top++] = atoi(item);
        else    /// current operator is an operator......
        {
            if(top < 2) {   /// failed equation.......
                printf("Wrong equation.\n");
                return 0;
            }
            operator1 = stack[--top];   /// take out two operands
            operator2 = stack[--top];
            if(*item=='+') {
            result = operator1 + operator2;
            }
            else if(*item=='-') {
                result = operator2 - operator1;
            }
            else if(*item=='*') {
                result = operator1 * operator2;
            }
            else if(*item=='/') {
                result = operator2 / operator1;
            }
            else if(*item == '%') {
                result = operator2 % operator1;
            }
            else    /// unknown operator......
                printf("can't solve operation.\n");
            stack[top++] = result;
        }
        item = strtok(NULL, " ");
    }
    if(top == 1)
        return stack[--top];
    else
        printf("wrong equation\n");
    return 0;
}
