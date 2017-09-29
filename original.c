#include <stdio.h>
#include <string.h>
typedef enum{false,true} bool;
typedef char * str;
char character;
FILE *file;
int x = 0;
char scan[10]={0,0,0,0,0,0,0,0,0,0};
char varvalues[128][16];
char varnames[128][16];
int variableset(){
	int pos=0;
	int letter=0;
	while(varvalues[pos][0]!=0){
		pos++;
	}
	while((character=fgetc(file))!='='){
		if(character==' '){}
		else{varnames[pos][letter]=character;
		letter++;}
	}
	letter=0;
	while((character=fgetc(file))!='\n'){
		if(character==';'){
			ungetc(character,file);
			break;
		} else if(character==EOF){break;}
		else if(character>='0'&&character<='9'){
			ungetc(character,file);
			while((character=fgetc(file))!='\n'){
				if(character<='0'||character>='9'){
					break;
				}
				varvalues[pos][letter]=character;
				letter++;
			}
			break;
		} else if(character=='\"'||character=='\''){
			while((character=fgetc(file))!='\n'){
				if(character=='\"'||character=='\''){
					break;
				}
				varvalues[pos][letter]=character;
				letter++;
			}
			break;
		} else if(character==' '){letter--;}
		letter++;
	}
	return 0;
}
int printing(){
	if(character=='\\'){
		character=fgetc(file);
		if(character=='\''||character=='\"'||character=='\\'){
			printf("%c",character);
		} else if(character=='n'){
			printf("\n");
		} else if(character=='r'){
			printf("\r");
		} else if(character=='t'){
			printf("\t");
		} else if(character=='b'){
			printf("\b");
		} else if(character=='f'){
			printf("\f");
		} else if(character=='0'){
			printf("\0");
		} else {
			printf("%c",character);
		}
	} else {
		printf("%c",character);
	}
	return 0;
}
bool match(char first[], char second[]){
	int loop=0;
	while(loop<strlen(first)){
		if(second[loop]!=first[loop]){
			return false;
		}
		loop++;
	}
	return true;
}
int variableget(){
	char varname[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int pos;
	while((character=fgetc(file))!=EOF){
		if(character==')'||character=='\"'||character=='\''){
			ungetc(character,file);
			break;
		}
		pos=0;
		while(varname[pos]!=0){
			pos++;
		}
		varname[pos]=character;
	}
	pos=0;
	while(varname[pos]==' '){
		while(pos<strlen(varname)){
			varname[pos]=varname[pos+1];
			pos++;
		}
		pos=0;
	}
	int loop=0;
	while(varnames[loop]!=varname){
		if(loop>128||varnames[loop][0]==0){
			break;
		}
		if(match(varnames[loop],varname)){
			printf("%s",varvalues[loop]);
		}
		loop++;
	}
	return 0;
}
int print(){
	while((character=fgetc(file))!=EOF){
		if(character=='\"'){
			while((character=fgetc(file))!='\"'){
				printing();
			}
			while((character=fgetc(file))==' '){}
			if(character=='+'||character=='&'){}else{ungetc(character,file);return 0;}
		}
		if(character=='\''){
			while((character=fgetc(file))!='\''){
				printing();
			}
			return 0;
		}
		if(character=='('){
			while((character=fgetc(file))!=')'){
				if(character=='\"'){
					while((character=fgetc(file))!='\"'){
						printing();
					}
				} else if(character=='\''){
					while((character=fgetc(file))!='\''){
						printing();
					}
				} else {
					ungetc(character,file);
					variableget();
				}
			}
			return 0;
		}
	}
	return 0;
}
bool check(char check[]){
	int loop=0;
	while(loop<strlen(check)){
		if(scan[strlen(scan)-(strlen(check)-loop)]!=check[loop]){
			return false;
		}
		loop++;
	}
	return true;
}
int add(){
	if(scan[9]==0){
		x=0;
		while(scan[x]!=0){
			x++;
		}
		if(character>='A'&&character<='Z'){
			character=character+32;
		}
		scan[x]=character;
	} else {
		x=0;
		for(x=0;x<10;x++){
			scan[x]=scan[x+1];
		}
		if(character>='A'&&character<='Z'){
			character=character+32;
		}
		scan[9]=character;
	}
	if(check("print")||check("write")||check("echo")||check("put")||check("display")||check("show")){
		print();
	} else if(check("var")||check("int")||check("bool")||check("char")||check("str")||check("string")){
		variableset();
	}
	return 0;
}
FILE *open(str filename){
	return fopen(filename, "r");
}
int lex(){
	int place;
	while((character=fgetc(file))!=EOF){
		add();
	}
	return 0;
}
int main(){
	char filename[50]="hry.hry";
	//scanf("%s",filename);
	file=open(filename);
	lex();
	getchar();
	getchar();
	return 0;
}