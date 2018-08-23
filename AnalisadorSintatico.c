#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void criaTabela(int *numToken, char **nomeToken){
    
    int i;
    for(i = 0; i < 17; i++){
        
        switch(numToken[i]){
            
            case 0:
                    nomeToken[0] = "INTEIRO";
                    break;
                    
            case 1:
                    nomeToken[1] = "PONTO_FLUTUANTE";
                    break;
            
            case 2:
                    nomeToken[2] = "STRING";
                    break;
                    
            case 3:
                    nomeToken[3] = "BOOL";
                    break;
                    
            case 4:
                    nomeToken[4] = "IDENTIFICADOR";
                    break;
                    
            case 5:
                    nomeToken[5] = "PALAVRA_RESERVADA";
                    break;
                    
            case 6:
                    nomeToken[6] = "PONTO_VIRGULA";
                    break;
                    
            case 7:
                    nomeToken[7] = "ABRE_PARENTESES";
                    break;
                    
            case 8:
                    nomeToken[8] = "FECHA_PARENTESES";
                    break;
                    
            case 9:
                    nomeToken[9] = "ABRE_CHAVES";
                    break;
                    
            case 10:
                    nomeToken[10] = "FECHA_CHAVES";
                    break;
                    
            case 11:
                    nomeToken[11] = "VIRGULA";
                    break;
                    
            case 12:
                    nomeToken[12] = "ATRIBUICAO";
                    break;
                    
            case 13:
                    nomeToken[13] = "OPERADOR_BOOL";
                    break;
                    
            case 14:
                    nomeToken[14] = "OPERADOR_RELACIONAL";
                    break;
                    
            case 15:
                    nomeToken[15] = "INCREMENTO";
                    break;
                    
            case 16:
                    nomeToken[16] = "ERRO";
                    break;
            
            case 17:
                    nomeToken[17] = "OPERADOR_NUM";
                    break;
                    
             case 18:
                    nomeToken[18] = "PALAVRA_WHILE";
                    break;
            
             case 19:
                    nomeToken[19] = "PALAVRA_IF";
                    break;
            
             case 20:
                    nomeToken[20] = "PALAVRA_ELSE";
                    break;    
            
             case 21:
                    nomeToken[21] = "PALAVRA_RETURN";
                    break;
            
             case 22:
                    nomeToken[22] = "PALAVRA_INT";
                    break;
            
             case 23:
                    nomeToken[23] = "PALAVRA_BOOL";
                    break;
            
             case 24:
                    nomeToken[24] = "PALAVRA_DOUBLE";
                    break;
            
             case 25:
                    nomeToken[25] = "PALAVRA_VOID";
                    break;
            
            
            
        }
    }

}

char *readLexema(int *c, int *n, int *linha, int *coluna, int *token, FILE *file, char *buffer, int *linhasaida, int *colunasaida, char *auxFlutuante){
    
    
    *linhasaida = *linha;
    *colunasaida = *coluna;
    
    if((*n == 0) && (((char) *c == ' ') || ((char) *c == '\n') || ((char) *c == '\t'))){

        if((char) *c == ' '){
            *coluna = *coluna + 1;
        }
        
        else if((char) *c == '\n'){
            *coluna = 1;
            *linha = *linha + 1;
        }
        
        else if((char) *c == '\t'){
            *coluna = *coluna + 4;
        }
        
        if((*c = fgetc(file)) == EOF){
            return buffer;
        }
        
        else{
            buffer = readLexema(c, n, linha, coluna, token, file, buffer, linhasaida, colunasaida, auxFlutuante);
            return buffer;
        }
    }
    
    else if((*n == 0) && (((char) *c == ';') || ((char) *c == '(') || ((char) *c == ')') || ((char) *c == '{') || ((char) *c == '}') || ((char) *c == ',') || ((char) *c == '%'))){

        *token = 6;
        buffer[*n] = (char) *c;
        *n = *n + 1;
        *coluna = *coluna + 1;
        *c = fgetc(file);
        return buffer;
    }
    
    else if(*n == 0 && (char) *c == '"'){         //se for string

        *token = 2;
        buffer[*n] = (char) *c;
        *n = *n + 1;
        *coluna = *coluna + 1;
        int contString = 0, isString = 1;
        char aux;
        
        while(isString == 1 && contString < 201){
            
            if((*c = fgetc(file)) == EOF){
                isString = 0;
                return buffer;
            }
            
            else{
                aux = (char) *c;
                if(aux != '"' && aux != '\n'){
                    buffer[*n] = aux;
                    *n = *n + 1;
                    *coluna = *coluna + 1;
                    contString++;
                }
                
                else if(aux == '"'){
                    buffer[*n] = aux;
                    *n = *n + 1;
                    *coluna = *coluna + 1;
                    *c = fgetc(file);
                    isString = 0;
                    return buffer;
                }
                
                else if(aux == '\n'){
                    *coluna = 1;
                    *linha = *linha + 1;
                    *c = fgetc(file);
                    isString = 0;
                    return buffer;
                }
            }
            
        }
        
        return buffer;
        
    }
    
    else if(*n == 0 && ((*c >= 65 && *c <= 90) || (*c >= 97 && *c <= 122))){     //se for identificador, palavra reservada ou bool
        
        *token = 3;
        int fim = 0, tamanhoId = 0;
        buffer[*n] = (char) *c;
        *n = *n + 1;
        *coluna = *coluna + 1;
        tamanhoId++;
        
        
        while(fim == 0 && tamanhoId < 21){
            
            if((*c = fgetc(file)) == EOF){
                    fim = 1;
                    return buffer;
            }
                
            else{
                if((*c >= 65 && *c <= 90) || (*c >= 97 && *c <= 122) || (*c >= 48 && *c <= 57) || *c == 95){
                    buffer[*n] = (char) *c;
                    *n = *n + 1;
                    *coluna = *coluna + 1;
                    tamanhoId++;
                }
                
                else{
                    
                    fim = 1;
                    return buffer;
                }
                
            }
        }
        
        if(tamanhoId >= 21){
            *c = fgetc(file);
        }
        
        return buffer;
            
    }
    
    else if(*n == 0 && ((*c >= 48 && *c <= 57) || ((char) *c == '.'))){          //se for int ou float

        *token = 0;
        buffer[*n] = (char) *c;
        *n = *n + 1;
        *coluna = *coluna + 1;
        int fim = 0, isFloat = 0, hasExp = 0, hasSignal = 0;
        
        if((char) *c == '.'){
            isFloat = 1;
        }
        
        while(fim == 0){
            
            if((*c = fgetc(file)) == EOF){
                    fim = 1;
                    return buffer;
            }
            
            else{
                
                if(*c >= 48 && *c <= 57){
                    buffer[*n] = (char) *c;
                    *n = *n + 1;
                    *coluna = *coluna + 1;
                }
                
                else if((char) *c == '.' && isFloat == 0){
                    buffer[*n] = (char) *c;
                    *n = *n + 1;
                    *coluna = *coluna + 1;
                    isFloat = 1;
                }
                
                else if((((char) *c == 'e') || ((char) *c == 'E')) && isFloat == 1 && hasExp == 0 && (int)buffer[*n-1] >= 48 && (int)buffer[*n-1] <= 57){
                    buffer[*n] = (char) *c;
                    *n = *n + 1;
                    *coluna = *coluna + 1;
                    hasExp = 1;
                }
                
                else if(((char) *c == '+' || (char) *c == '-') && (buffer[*n-1] == 'E' || buffer[*n-1] == 'e') && hasSignal == 0){
                    buffer[*n] = (char) *c;
                    *n = *n + 1;
                    *coluna = *coluna + 1;
                    hasSignal = 1;
                }
                
                else{
                    
                    fim = 1;
                    
                }
            }
        }
        
        if(!(((int)buffer[*n-1] >= 48) && ((int) buffer[*n-1] <= 57))){             //se tiver ([eE][+-]?) mas não tiver números depois
            
            if(hasExp == 1 && hasSignal == 1){
                
                auxFlutuante[0] = buffer[*n - 2];
                auxFlutuante[1] = buffer[*n - 1];
                buffer[*n - 2] = 0;
                buffer[*n - 1] = 0;
                *n = *n - 2;
                *coluna = *coluna - 2;
            }
            
            else{
                auxFlutuante[0] = buffer[*n - 1];
                buffer[*n - 1] = 0;
                *n = *n - 1;
                *coluna = *coluna - 1;
            }
        }
        
        return buffer;
        
    }
    
    else if((*n == 0) && (((char) *c == '=') || (char) *c == '&' || (char) *c == '|' || (char) *c == '+' || (char) *c == '-' || (char) *c == '*' || (char) *c == '/' || (char) *c == '<' || (char) *c == '>' || (char) *c == '!')){

        *token = 12;
        buffer[*n] = (char) *c;
        *n = *n + 1;
        *coluna = *coluna + 1;
        
        if((*c = fgetc(file)) == EOF){
            return buffer;
        }
        
        else{
            
            if((((char) *c == '=') || (char) *c == '&' || (char) *c == '|' || (char) *c == '+' || (char) *c == '-') && (char) *c == buffer[*n-1]){        //se for ==, &&, ||, ++, --
                buffer[*n] = (char) *c;
                *n = *n + 1;
                *coluna = *coluna + 1;
                *c = fgetc(file);
                return buffer;
            }
            
            else if((char) *c == '=' && ((buffer[*n-1] == '<') || (buffer[*n-1] == '>') || (buffer[*n-1] == '!'))){              //se for !=, <= ou >=
                buffer[*n] = (char) *c;
                *n = *n + 1;
                *coluna = *coluna + 1;
                *c = fgetc(file);
                return buffer;
            
            }
            
            else if((char) *c == '/' && (char) *c == buffer[*n-1]){       //se for comentário simples
                
                int isComment = 1;
                buffer[*n-1] = 0;
                *n = *n - 1;
                *coluna = *coluna + 1;
            
                while(isComment == 1){
                    
                    
                    if((*c = fgetc(file)) == EOF){
                        isComment = 0;
                        return buffer;
                    }
                
                    else{
                        if((char) *c == '\n'){
                            isComment = 0;
                            *linha = *linha + 1;
                            *coluna = 1;
                            *c = fgetc(file);
                        }
                        else if((char) *c == '\t'){
                            *coluna = *coluna + 4;
                        }
                        else{
                            *coluna = *coluna + 1;
                        }
                    }

                }
                
                return buffer;
            }
            
            else if((char) *c == '*' && buffer[*n-1] == '/'){            //se for comentário multiplo
                
                int isComment = 1;
                buffer[*n-1] = 0;
                *n = *n - 1;
                *coluna = *coluna + 1;
                
                while(isComment == 1){
                    
                    if((*c = fgetc(file)) == EOF){
                        isComment = 0;
                        return buffer;
                    }
                    
                    else{
                        if((char) *c == '\n'){
                            *linha = *linha + 1;
                            *coluna = 1;
                        }
                        else{
                            if((char) *c == '\t'){
                                *coluna = *coluna + 4;
                            }
                            else{
                                if((char) *c == '*'){
                                    *c = fgetc(file);
                                    if((char) *c == '/'){
                                        isComment = 0;
                                        *c = fgetc(file);
                                    }
                                    *coluna = *coluna + 1;
                                }

                                *coluna = *coluna + 1;

                            }
                        }
                    }
                }

                return buffer;
            }
            
            else{
                return buffer;
            }
            
        }
    }
    
    else{
        
        *token = 16;
        buffer[*n] = (char) *c;
        *n = *n + 1;
        *coluna = *coluna + 1;
        *c = fgetc(file);
        return buffer;
    }
    
}

int procuraToken(char *buffer, int *token, int *n){
    
    if(*token == 6){
        
        if(strcmp(buffer, "(") == 0){
            *token = 7;
        }
        
        else if(strcmp(buffer, ")") == 0){
            *token = 8;
        }
        
        else if(strcmp(buffer, "{") == 0){
            *token = 9;
        }
        
        else if(strcmp(buffer, "}") == 0){
            *token = 10;
        }
        
        else if(strcmp(buffer, ",") == 0){
            *token = 11;
        }
        
        else if(strcmp(buffer, "%") == 0){
            *token = 13;
        }
        
        
    }
    
    else if(*token == 2){
        
        if(buffer[0] == '"' && buffer[*n-1] != '"' && *n > 1){
            *token = 16;
        }
        
        else if(buffer[0] == '"' && buffer[*n-1] == '"' && *n > 1){
            *token = 2;
        }
        
        else if(buffer[0] == '"' && *n == 1){
            *token = 16;
        }
    }
    
    else if(*token == 3){       //se for identificador, palavra reservada ou bool
        
        if((strcmp(buffer, "true") == 0) || (strcmp(buffer, "false") == 0)){
            *token = 3;
        }
        
       else if ((strcmp(buffer, "while") == 0)){
            *token = 18;
       }
      
       else if ((strcmp(buffer, "if") == 0)){        
            *token = 18;
       }
      
       else if ((strcmp(buffer, "else") == 0)){
            *token = 20;        
       }
        
       else if ((strcmp(buffer, "return") == 0)){
            *token = 21;        
       }
      
       else if ((strcmp(buffer, "int") == 0)){
            *token = 22;        
       } 
      
       else if ((strcmp(buffer, "bool") == 0)){
            *token = 23;        
       } 
      
       else if ((strcmp(buffer, "double") == 0)){
            *token = 24;        
       } 
      
       else if ((strcmp(buffer, "void") == 0)){
            *token = 24;        
       } 
      
      
      
        else{
            *token = 4;
        }
    }
    
    else if(*token == 0){       //se for int ou float
    
        int i;
        
        for(i = 0; i < *n; i++){
            if(buffer[i] == '.'){
                *token = 1;
            }
        }
        
    
    }
    
    else if(*token == 12){          //se for atribuicao, operador, operador relacional ou incremento
        
        if((strcmp(buffer, "=") == 0)){
            *token = 12;
        }
        
        else if((strcmp(buffer, "+") == 0) || (strcmp(buffer, "-") == 0) || (strcmp(buffer, "*") == 0) || (strcmp(buffer, "/") == 0) || (strcmp(buffer, "%") == 0)){
            *token = 17;
        }
      
      else if ((strcmp(buffer, "&&") == 0) || (strcmp(buffer, "||") == 0)){
            *token = 13;
        }        
        
        else if((strcmp(buffer, "==") == 0) || (strcmp(buffer, "<=") == 0) || (strcmp(buffer, ">=") == 0) || (strcmp(buffer, "!=") == 0) || (strcmp(buffer, "<") == 0) || (strcmp(buffer, ">") == 0)){
            *token = 14;
        }
        
        else if((strcmp(buffer, "++") == 0) || (strcmp(buffer, "--") == 0)){
            *token = 15;
        }
    }
    
    
    else if(*token == 16){       //se for token de erro
    }
    

    return *token;
    
}

struct Lexema{
    
    char *token, *lexema;
    int line, column;
};

struct Lexema *criaLexema(char **nomeToken, int auxToken, char *buffer, int *linhasaida, int *colunasaida){
    
    struct Lexema *lex = (struct Lexema*)malloc(sizeof(struct Lexema));
    if(lex != NULL){
        lex->token = nomeToken[auxToken];
        lex->lexema = buffer;
        lex->line = *linhasaida;
        lex->column = *colunasaida;
        
    }
    return lex;
}

void limpaBuffer(char *buffer, int *n){
    
    int i;
    
    for(i = 0; i < *n; i++){
        buffer[i] = 0;
    }
    
    *n = 0;
}

void printLexema(struct Lexema *lex){
    
    printf("%s@", lex->token);
    printf("%s@", lex->lexema);
    printf("%d@", lex->line);
    printf("%d\n", lex->column);
}

int main (int argc, char *argv[ ]){
    
    int *numToken;
    char **nomeToken;
    char *buffer;
    char *auxFlutuante = (char *)calloc(2, sizeof(char));
    size_t bufsize = 202;
    int i, c = 0, n = 0, linha = 1, coluna = 1, token = -1, auxToken, linhasaida = 1, colunasaida = 1;
    struct Lexema *lexema;
    
    numToken = (int*)malloc(17*sizeof(int));
    nomeToken = (char**)malloc(17*(sizeof(char*)));
    for(i = 0; i < 17; i++){
        numToken[i] = i;
        nomeToken[i] = (char*)malloc(19*(sizeof(char)));
    }
    
    criaTabela(numToken, nomeToken);

    buffer = (char *)calloc(bufsize, sizeof(char));
    FILE *file;
    file = fopen(argv[1] , "r");
    c = fgetc(file);
    
    printf("TOKEN@");
    printf("LEXEMA@");
    printf("LINHA@");
    printf("COLUNA\n");
    
    while(c != EOF){
        
        if(auxFlutuante[0] == 'e' || auxFlutuante[0] == 'E' || auxFlutuante[0] == '+' || auxFlutuante[0] == '-'){
            
            buffer[0] = auxFlutuante[0];
            auxFlutuante[0] = auxFlutuante[1];
            auxFlutuante[1] = 0;
        }
        
        else{
            buffer = readLexema(&c, &n, &linha, &coluna, &token, file, buffer, &linhasaida, &colunasaida, auxFlutuante);
        }
        
        if(n > 0){
            auxToken = procuraToken(buffer, &token, &n);
            lexema = criaLexema(nomeToken, auxToken, buffer, &linhasaida, &colunasaida);
            printLexema(lexema);
            limpaBuffer(buffer, &n);
            token = -1;
            free(lexema);
        }
        
    }
    
}