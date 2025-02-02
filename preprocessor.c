#include "P_header.h"
int count = 0;
void declare(char* line, FILE *file) {
    printf("Parsing line (declare): %s\n", line); // Debug statement
    
    if (sscanf(line, "@int %[^()](%[^,],%[^)])", AT[aCount].name, AT[aCount].size1, AT[aCount].size2) == 3) {
        AT[aCount].dim = 2;
        fprintf(file, "int %s[%s][%s];\n", AT[aCount].name, AT[aCount].size1, AT[aCount].size2);
        aCount++;
    } else if (sscanf(line, "@int %[^()](%[^)])", AT[aCount].name, AT[aCount].size1) == 2) {
        AT[aCount].dim = 1;
        fprintf(file, "int %s[%s];\n", AT[aCount].name, AT[aCount].size1);
        aCount++;
    } else {
        printf("Error parsing declare line: %s\n", line); // Debug statement
    }
}

void read(char* line,FILE *file)
{
    sscanf(line,"@%s %s < %s",PT.oper,PT.lhs,PT.rhs1); //@read B < f1

    int k;
    int i = 0;
    while(i < aCount)
    {
        if(!strcmp(PT.lhs,AT[i].name))
        {
            k = i;
            break;
        }
        i++;
    }
    if(AT[k].dim == 1)
    {
        fprintf(file,"int size%d = sizeof(%s) / sizeof(%s[0]);\nFILE *file = fopen(\"%s\", \"r\");\nfor(int i = 0;i < size%d;i++)\n{\n\tfscanf(file,\"%%d\",&%s[i]);\n}\n",count,PT.lhs,PT.lhs,PT.rhs1,count,PT.lhs);
        count++;
    }
    else
    {
        fprintf(file,"int sizeRows%d = sizeof(%s) / sizeof(%s[0]);\nint sizeCols%d = sizeof(%s[0]) / sizeof(%s[0][0]);\nFILE *file = fopen(\"%s\", \"r\");\nfor(int i = 0;i < sizeRows%d;i++)\n{\n\tfor(int j = 0;j < sizeCols%d;j++);\n\t{\n\t\tfscanf(file,\"%%d\",&%s[i][j]);\n\t}\n}\n",count,PT.lhs,PT.lhs,count,PT.lhs,PT.lhs,PT.rhs1,count,count,PT.lhs);
        count++;
    }
}
void copy(char* line,FILE *file)
{
    sscanf(line,"@%s %s = %s",PT.oper,PT.lhs,PT.rhs1);
    int curDim;
    int k;
    int i = 0;
    while(i < aCount)
    {
        if(!strcmp(PT.lhs,AT[i].name))
        {
            k = i;
            break;
        }
        i++;
    }
    if(AT[k].dim == 2)
    {
        fprintf(file,"int sizeRows%d = sizeof(%s) / sizeof(%s[0]);\nint sizeCols%d = sizeof(%s[0]) / sizeof(%s[0][0]);\nfor(int i = 0;i < sizeRows%d;i++)\n{\n\tfor(int j = 0;j<sizeCols%d;j++)\n\t{\n\t\t%s[i][j] = %s[i][j];\n\t}\n}\n",count,PT.lhs,PT.lhs,count,PT.lhs,PT.lhs,count,count,PT.lhs,PT.rhs1);
        count++;
    }
    else
    {
        fprintf(file,"int size%d = sizeof(%s) / sizeof(%s[0]);\nfor(int i = 0;i < size%d;i++)\n{\n\t%s[i] = %s[i];\n}\n",count,PT.lhs,PT.lhs,count,PT.lhs,PT.rhs1);
        count++;
    }
}
void initialize(char* line, FILE* file) {
    sscanf(line, "@%s %s = %s", PT.oper, PT.lhs, PT.rhs1);
    int k;
    int i = 0;
    while(i < aCount)
    {
        if(!strcmp(PT.lhs,AT[i].name))
        {
            k = i;
            break;
        }
        i++;
    }
    
    
    if (AT[k].dim == 2) {
        fprintf(file, "int sizeRows%d = sizeof(%s) / sizeof(%s[0]);\nint sizeCols%d = sizeof(%s[0]) / sizeof(%s[0][0]);\n",count, PT.lhs, PT.lhs,count, PT.lhs, PT.lhs);
        fprintf(file, "for(int i = 0; i < sizeRows%d; i++) {\n\tfor(int j = 0; j < sizeCols%d; j++) {\n\t\t%s[i][j] = %s;\n\t}\n}\n",count,count, PT.lhs, PT.rhs1);
        count++;
    } else {
        fprintf(file, "int size%d = sizeof(%s) / sizeof(%s[0]);\n",count, PT.lhs, PT.lhs);
        fprintf(file, "for(int i = 0; i < size%d; i++) {\n\t%s[i] = %s;\n}\n",count, PT.lhs, PT.rhs1);
        count++;
    }
}

void print(char *line,FILE *file)
{
    sscanf(line, "@%s %s", PT.oper, PT.lhs);

    int k;
    int i = 0;
    while(i < aCount)
    {
        if(!strcmp(PT.lhs, AT[i].name))
        {
            k = i;
            break;
        }
        i++;
    }
    if(AT[k].dim == 2){
        fprintf(file,"int sizeRows%d = sizeof(%s) / sizeof(%s[0]);\nint sizeCols%d = sizeof(%s[0]) / sizeof(%s[0][0]);\nfor(int i = 0; i < sizeRows%d; i++) {\n\tfor(int j = 0; j < sizeCols%d; j++) {\n\t\tprintf(\"%%d \",%s[i][j]);\n\t}\n\tprintf(\"\\n\");\n}\n",count,PT.lhs,PT.lhs,count,PT.lhs,PT.lhs,count,count,PT.lhs);
        count++;
    }
    else{
        fprintf(file,"int size%d = sizeof(%s) / sizeof(%s[0]);\nfor(int i = 0; i < size%d; i++) {\n\tprintf(\"%%d \",%s[i]);\n}\n",count,PT.lhs,PT.lhs,count,PT.lhs);
        count++;
    }
}
void dotp(char *line,FILE *file)
{
    sscanf(line,"@%s %s = %s . %s",PT.oper,PT.lhs,PT.rhs1,PT.rhs2);
    fprintf(file,"int size%d = sizeof(%s) / sizeof(%s[0]);\nfor(int i = 0;i < size%d;i++)\n{\n\t%s[i] = %s[i]*%s[i];\n}\n",count,PT.lhs,PT.lhs,count,PT.lhs,PT.rhs1,PT.rhs2);
    count++;
} 
void add(char *line,FILE *file){
    sscanf(line,"@%s %s = %s + %s",PT.oper,PT.lhs,PT.rhs1,PT.rhs2);
    int i = 0;
    while(i < aCount){
        if(!strcmp(PT.lhs,AT[i].name)){
            if(AT[i].dim == 1){
                fprintf(file,"int size%d = sizeof(%s) / sizeof(%s[0]);\nfor(int i = 0;i < size%d,i++)\n{\n\t%s[i] = %s[i]+%s[i];\n}\n",count,PT.lhs,PT.lhs,count,PT.lhs,PT.rhs1,PT.rhs2);
                count++;
            }
            else{
                fprintf(file,"int sizeRows%d = sizeof(%s) / sizeof(%s[0]);\nint sizeCols%d = sizeof(%s[0]) / sizeof(%s[0][0]);\nfor(int i = 0;i < sizeRows%d;i++)\n\tfor(int j = 0;j < sizeCols%d;j++)\n\t\t%s[i][j] = %s[i][j]+%s[i][j];\n",count,PT.lhs,PT.lhs,count,PT.lhs,PT.lhs,count,count,PT.lhs,PT.rhs1,PT.rhs2);
                count++;
            }
            break;
        }
        i++;
    }
}
void mmult(char *line,FILE *file){
    sscanf(line,"@%s %s = %s * %s",PT.oper,PT.lhs,PT.rhs1,PT.rhs2);
    fprintf(file,"int sizeRows%d = sizeof(%s) / sizeof(%s[0]);\nint sizeCols%d = sizeof(%s[0]) / sizeof(%s[0][0]);\nfor(int i = 0;i < sizeRows%d;i++)\n\tfor(int j = 0; j < 2; ++j)\n\t\tfor(int k = 0; k < 2; ++k)\n\t\t\t%s[i][j] += %s[i][k] * %s[k][j];\n",count,PT.lhs,PT.lhs,count,PT.lhs,PT.lhs,count,PT.lhs,PT.rhs1,PT.rhs2);
    count++;
}
void sum(char *line,FILE *file){
    sscanf(line,"@%s %s",PT.oper,PT.lhs);
    int k;
    int i = 0;
    while(i < aCount)
    {
        if(!strcmp(PT.lhs, AT[i].name))
        {
            k = i;
            break;
        }
        i++;
    }
    if(AT[k].dim == 1){
    fprintf(file,"int sum%d = 0;\nint size = sizeof(%s) / sizeof(%s[0]);\nfor(int i = 0;i < size%d;i++)\n\tsum%d += %s[i];\nP_sum = sum%d;\n",count,PT.lhs,PT.lhs,count,count,PT.lhs,count);
    count++;
    }
    else{
    fprintf(file,"int sum%d = 0;\nint sizeRows%d = sizeof(%s) / sizeof(%s[0]);\nint sizeCols%d = sizeof(%s[0]) / sizeof(%s[0][0]);\nfor(int i = 0;i < sizeRows%d;i++)\n\tfor(int j = 0;j < sizeCols%d;j++)\n\t\tsum%d += %s[i][j];\n\tP_sum = sum%d;\n",count,count,PT.lhs,PT.lhs,count,PT.lhs,PT.lhs,count,count,count,PT.lhs,count);
    count++;
    }
}
void aver(char *line,FILE *file){
    sscanf(line,"@%s %s",PT.oper,PT.lhs);
    int k;
    int i = 0;
    while(i < aCount)
    {
        if(!strcmp(PT.lhs, AT[i].name))
        {
            k = i;
            break;
        }
        i++;
    }
    if(AT[k].dim == 1){
    fprintf(file,"double average%d = 0;\nint size%d = sizeof(%s) / sizeof(%s[0]);\nfor(int i = 0;i < size%d;i++)\n\taverage%d += %s[i];\nP_aver = average%d / size%d;\n",count,count,PT.lhs,PT.lhs,count,count,PT.lhs,count,count);
    count++;
    }  
    else{
    fprintf(file,"double average%d = 0;\nint sizeRows%d = sizeof(%s) / sizeof(%s[0]);\nint sizeCols%d = sizeof(%s[0]) / sizeof(%s[0][0]);\nfor(int i = 0;i < sizeRows%d;i++)\n\tfor(int j = 0;j < sizeCols%d;j++)\n\t\taverage%d += %s[i][j];\nP_aver = average%d / size%d;\n",count,count,PT.lhs,PT.lhs,count,PT.lhs,PT.lhs,count,count,count,PT.lhs,count,count);
    count++;
    }
}
void parse(FILE *in, FILE *out) {
    char line[150];
    
    while (fgets(line, sizeof(line), in)) {
        int i = 0;
        while (isspace((unsigned char)line[i]) && line[i] != '\0') {
            i++;
        }
        strcpy(line, line + i);
        
        if (line[0] == '@') {
            sscanf(line, "@%s", PT.oper);
            
            if (strcmp(PT.oper, "int") == 0) {
                declare(line, out);
            } else if (strcmp(PT.oper, "read") == 0) {
                read(line, out);
            } else if (strcmp(PT.oper, "copy") == 0) {
                copy(line, out);
            } else if (strcmp(PT.oper, "init") == 0) {
                initialize(line, out);
            } else if (strcmp(PT.oper, "print") == 0) {
                print(line, out);
            } else if (strcmp(PT.oper, "dotp") == 0) {
                dotp(line, out);
            } else if (strcmp(PT.oper, "add") == 0) {
                add(line, out);
            } else if (strcmp(PT.oper, "mmult") == 0) {
                mmult(line, out);
            } else if (strcmp(PT.oper, "sum") == 0) {
                sum(line, out);
            } else if (strcmp(PT.oper, "aver") == 0) {
                aver(line, out);
            } else {
                printf("Error: Unknown operation in line: %s\n", line); // Debug statement
            }
        } else {
            fprintf(out, "%s", line);
        }
    }
}


int main(int argc, char *argv[]) {
    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen("expanded.c", "w");
    

    parse(inputFile,outputFile);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

