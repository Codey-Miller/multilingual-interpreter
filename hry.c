#include <stdio.h>
#include <string.h>
typedef enum{false,true} bool;
typedef char* str;
char character;
FILE *file;
int x = 0;
char scan[10];
char vartypes[128][16];
char varvalues[128][16];
char varnames[128][16];
int addint;
int intvalues[128];
char addvarvalue[16];
char found[128];
int match(char first[],char second[]){
	if(strlen(first)!=strlen(second)){
		return false;
	}
	int pos=0;
	while(pos<strlen(first)){
		if(first[pos]!=second[pos]){
			return false;
		}
	}
	return true;
}
int add(){
	character=fgetc(file);
	if(scan[9]==0){
		x=0;
		while(scan[x]!=0){
			x++;
		}
		scan[x]=character;
	} else {
		x=0;
		for(x=0;x<10;x++){
			scan[x]=scan[x+1];
		}
		scan[9]=character;
	}
}
char characters(){
	if(character=='\\'){
		add();
		if(character=='n'){
			return '\n';
		} else if(character=='t'){
			return '\t';
		} else if(character=='v'){
			return '\v';
		} else if(character=='b'){
			return '\b';
		} else if(character=='r'){
			return '\r';
		} else if(character=='f'){
			return '\f';
		} else if(character=='a'){
			return '\a';
		} else {
			return character;
		}
	} else {
		return character;
	}
	return 0;
}
int variableset(){
	int pos=0;
	int letter=0;
	int charac=0;
	while(varvalues[pos][0]!=0){
		pos++;
	}
	for(letter;letter<strlen(found);letter++){
		vartypes[pos][letter]=found[pos];
	}
	letter=0;
	while(character!=EOF){
		add();
		if(character=='='||character=='\n'||character==';'){
			break;
		}
		addvarvalue[letter]=character;
		letter++;
	}
	letter=0;
	if(character!=EOF){
		while(addvarvalue[letter]!=' '){
			letter++;
		}
		while(letter<16){
			varvalues[pos][charac]=addvarvalue[letter];
			charac++;
			letter++;
		}
	}
	while(character!=EOF){
		if(character==';'||character=='\n'){
			break;
		} else if(character>='0'&&character<='9'){
			while(character>='0'&&character<='9'){
				intvalues[pos]=intvalues[pos]*10+(character-48);
				add();
			}
		} else {

		}
		add();
	}
	return 0;
}
int print(){
	while(character!=EOF){
		add();
		if(character=='('){
			while(character!=')'){
				if(character==EOF){
					break;
				}
				add();
				if(character=='\"'||character=='\''){
					add();
					while(character!='\"'&&character!='\''){
						if(character==EOF){
							break;
						}
						printf("%c",characters());
						add();
					}
				} else {
					//variableget();
				}
			}
		} else {
			if(character=='\"'||character=='\''){
				add();
				while(character!='\"'&&character!='\''){
					if(character==EOF){
						break;
					}
					printf("%c",characters());
					add();
				}
			}
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
	int pos=0;
	for(pos;pos<strlen(check);pos++){
		found[pos]=check[pos];
	}
	return true;
}
FILE *open(str filename){
	return fopen(filename, "r");
}
int lex(){
	add();
	while(character!=EOF){
		if(check("print")||check("write")||check("echo")||check("put")||check("display")||check("show")||check("say")){
			print();
		} else if(check("var")||check("int")||check("bool")||check("char")||check("str")||check("string")){
			variableset();
		}
		add();
	}
}
int main(){
	char filename[50]="hry.hry";
	//scanf("%s",filename);
	file=open(filename);
	lex();
	getchar();
	return 0;
}