#include <stdbool.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

  
// Returns 'true' if the character is a DELIMITER. 
bool isDelimiter(char ch) 
{ 
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||  
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||  
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||  
        ch == '[' || ch == ']' || ch == '{' || ch == '}') 
        return (true); 
    return (false); 
} 

bool isDigit(int c){
    if(c>=48 && c<=57){
        return true;
    }
    return false;
}


bool isNumber(char* str){
    enum state {Comeco=0,Q1=1,Q2=2,Q3=3,Q4=4,End=5,Error=6}; // 0 = start , 1 = Q1 , 2 = 
    enum state atual = Comeco;
    int character = *str;

    while (atual != End && atual != Error){
        switch(atual){
            case Comeco:
                character = *str;
                if(isDigit(character))
                    atual = Q2;
                else if(character==45 || character==43)
                    atual = Q1;
                else{
                    atual = Error;
                    
                }
                    
                str++;
                character = *str;
            break;
            case Q1: 
                if(isDigit(character))
                    atual=Q2;
                else
                    atual = Error;
                str++;
                character = *str;
            break;
            case Q2: 
                if( character==46 )
                    atual=Q3;   
                else if(!isDigit(character) && !isDelimiter(*str)){
                    atual = Error;
                    str--;
                    character=*str;
                }
                str++;
                character = *str;
            break;
            case Q3: 
                if(isDigit(character)){
                    str++;
                    character = *str;
                    atual=Q4;
                }else
                    atual = Error;
            break;
            case Q4:
                if(isDigit(character))
                    str++;    
                else{
                    str--;
                    atual = End;
                }
                character = *str;
            break;
            case End:
                return true;
            break;
            case Error:
                return false;
            break;
        }
    }
    
    if(atual == End)
        return true;
    else 
        return false;
    
}


// Returns 'true' if the character is an OPERATOR. 
bool isOperator(char ch) 
{ 
    if (ch == '+' || ch == '-' || ch == '*' ||  
        ch == '/' || ch == '>' || ch == '<' ||  
        ch == '=') 
        return (true); 
    return (false); 
} 

// Returns 'true' if the string is a VALID IDENTIFIER. 

bool validIdentifier(char* str) 
{ 
    int character = str[0];
    if( (character>=48 && character<=57) || isDelimiter(str[0])==true )
        return false;
    return (true); 
} 

// Returns 'true' if the string is a KEYWORD. 
bool isKeyword(char* str) 
{ 
    if (!strcmp(str, "if") || !strcmp(str, "else") || 
        !strcmp(str, "while") || !strcmp(str, "do") ||  
        !strcmp(str, "break") ||  
         !strcmp(str, "continue") || !strcmp(str, "int") 
        || !strcmp(str, "double") || !strcmp(str, "float") 
        || !strcmp(str, "return") || !strcmp(str, "char") 
        || !strcmp(str, "case") || !strcmp(str, "char") 
        || !strcmp(str, "sizeof") || !strcmp(str, "long") 
        || !strcmp(str, "short") || !strcmp(str, "typedef") 
        || !strcmp(str, "switch") || !strcmp(str, "unsigned") 
        || !strcmp(str, "void") || !strcmp(str, "static") 
        || !strcmp(str, "struct") || !strcmp(str, "goto")) 
        return (true); 
    return (false); 
} 
  
// // Returns 'true' if the string is an INTEGER. 
// bool isInteger(char* str) 
// { 
//     int i, len = strlen(str); 
  
//     if (len == 0) 
//         return (false); 
//     for (i = 0; i < len; i++) { 
//         if (str[i] != '0' && str[i] != '1' && str[i] != '2'
//             && str[i] != '3' && str[i] != '4' && str[i] != '5'
//             && str[i] != '6' && str[i] != '7' && str[i] != '8'
//             && str[i] != '9' || (str[i] == '-' && i > 0)) 
//             return (false); 
//     } 
//     return (true); 
// } 
  
// // Returns 'true' if the string is a REAL NUMBER. 
// bool isRealNumber(char* str) 
// { 
//     int i, len = strlen(str); 
//     bool hasDecimal = false; 
  
//     if (len == 0) 
//         return (false); 
//     for (i = 0; i < len; i++) { 
//         if (str[i] != '0' && str[i] != '1' && str[i] != '2'
//             && str[i] != '3' && str[i] != '4' && str[i] != '5'
//             && str[i] != '6' && str[i] != '7' && str[i] != '8'
//             && str[i] != '9' && str[i] != '.' ||  
//             (str[i] == '-' && i > 0)) 
//             return (false); 
//         if (str[i] == '.') 
//             hasDecimal = true; 
//     } 
//     return (hasDecimal); 
// } 
  
// Extracts the SUBSTRING. 
char* subString(char* str, int left, int right) 
{ 
    int i; 
    char* subStr = (char*)malloc( 
                  sizeof(char) * (right - left + 2)); 
  
    for (i = left; i <= right; i++) 
        subStr[i - left] = str[i]; 
    subStr[right - left + 1] = '\0'; 
    return (subStr); 
} 
  
// Parsing the input STRING. 
void parse(char* str) 
{ 
    int left = 0, right = 0; 
    int len = strlen(str); 
  
    while (right <= len && left <= right) { 
        if (isDelimiter(str[right]) == false) //  delimitadores-->   = , ; ,  , + , - , * , / , , , < , > , [ , ] , ( , ) , { , } 
            right++; 
  
        if (isDelimiter(str[right]) == true && left == right) { 
            if (isOperator(str[right]) == true) 
                printf("'%c' IS AN OPERATOR\n", str[right]); 
  
            right++; 
            left = right; 
        } else if (isDelimiter(str[right]) == true && left != right 
                   || (right == len && left != right)) { 
            char* subStr = subString(str, left, right - 1); 
  
            if (isKeyword(subStr) == true) 
                printf("'%s' IS A KEYWORD\n", subStr); 
  
            // else if (isInteger(subStr) == true) 
            //     printf("'%s' IS AN INTEGER\n", subStr); 
  
            // else if (isRealNumber(subStr) == true) 
            //     printf("'%s' IS A REAL NUMBER\n", subStr); 
            else if(isNumber(subStr))
                printf("'%s' IS A NUMBER\n",subStr );

            else if (validIdentifier(subStr) == true
                     && isDelimiter(str[right - 1]) == false) 
                printf("'%s' IS A VALID IDENTIFIER\n", subStr); 
  
            else if (validIdentifier(subStr) == false
                     && isDelimiter(str[right - 1]) == false) 
                printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr); 
            left = right; 
        } 
    } 
    return; 
} 
  
// DRIVER FUNCTION 
int main() 
{ 
     // maximum legth of string is 100 here  
    char str[100] = "if( variavel ) { float forc2 = variavel / ( 4.8 + 3a4 ); } else { char /etra = outrav2riavel;} "; 
  
    parse(str); // calling the parse function 
  
    return (0); 
} 