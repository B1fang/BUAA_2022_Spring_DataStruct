#include<stdio.h>

/*
    使用了递归下降的思路对表达式进行解析
    注意！！这段代码没有实现空格的消除，且没有经过评测机测试
*/

int parseTerm(char* term){ // 这里需要注意term可能的三种形式：数字，连乘，连除，具体解决思路依然是parseExpr的递归下降的思路
    char* termPtr = term;
    int digit = 0;
    while(*termPtr != '\0' && *termPtr != '*' && *termPtr != '/'){
        digit = digit*10 + *termPtr - '0';
        termPtr ++;
    }
    char opSym = *termPtr;
    termPtr ++;
    if(opSym == '*'){
        return digit * parseTerm(termPtr);
    }
    else if(opSym == '/'){
        return digit / parseTerm(termPtr);
    }
    else{
        return digit;
    }
}

int parseExpr(char* expr){
    char* exprPtr = expr;
    while(*exprPtr != '\0' && *exprPtr != '+' && *exprPtr != '-'){ // 跳出循环只有两种可能性：第一是遍历到字符串尾部，第二是遇到了加减分隔符
        exprPtr ++;
    }
    char opSym = *exprPtr;
    *exprPtr = '\0';
    exprPtr ++;
    if(opSym == '+'){
        return parseTerm(expr) + parseExpr(exprPtr);
    }
    else if(opSym == '-'){
        return parseTerm(expr) - parseExpr(exprPtr);
    }
    else{
        return parseTerm(expr);
    }
}

int main(){
    char a[10000] = {};
    scanf("%s", a);
    int res = parseExpr(a);
    printf("%d", res);
    return 0;
}
