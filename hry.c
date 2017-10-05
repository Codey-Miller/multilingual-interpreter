#include <stdio.h>
#include <string.h>
typedef enum{false,true} bool;
typedef char* str;
char character;
FILE *file;
int x=0;
char scan[100];
str vartypes[128];
char varvalues[128][16];
char varnames[128][16];
int intvalues[128];
str found;
str printfun[]={"print","write","echo","put","display","show","say",""};
str variabletypes[]={"var","int","bool","char","str","string",""};
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
	if(scan[99]==0){
		x=0;
		while(scan[x]!=0){
			x++;
		}
		scan[x]=character;
	} else {
		x=0;
		for(x=0;x<100;x++){
			scan[x]=scan[x+1];
		}
		scan[99]=character;
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
	vartypes[pos]=found;
	letter=0;
	add();
	while(character!=' '){
		if(character==EOF){
			break;
		}
		add();
	}
	while(character==' '){
		if(character==EOF){
			break;
		}
		add();
	}
	while(character!=EOF){
		if(character=='='||character=='\n'||character==';'){
			break;
		}
		varnames[pos][letter]=character;
		letter++;
		add();
	}
	int item=127;
	while(varnames[pos][item]==0){
		item--;
	}
	while(varnames[pos][item]==' '){
		varnames[pos][item]=0;
		item--;
	}
	letter=0;
	while(character!=EOF){
		if(character==';'||character=='\n'){
			break;
		} else if(character>='0'&&character<='9'){
			while(character>='0'&&character<='9'){
				intvalues[pos]=intvalues[pos]*10+(character-48);
				add();
			}
			break;
		} else if(character=='\''||character=='\"'){
			add();
			int a = 0;
			while(character!='\''&&character!='\"'){
				varvalues[pos][a]=characters();
				add();
				a++;
			}
			break;
		}
		add();
	}
	return 0;
}
int checkchar(char check[]){
	if(strlen(check)<=strlen(scan)){
		int pos=strlen(scan)-strlen(check);
		int letter=0;
		for(pos;pos<strlen(scan);pos++){
			if(check[letter]!=scan[pos]){
				return false;
			}
			letter++;
		}
	}
	found=check;
	return true;
}
int checkstr(str check[]){
	int item=0;
	int pos;
	bool hit;
	int letter;
	while(strlen(check[item])!=0){
		hit=true;
		pos=0;
		letter=0;
		if(strlen(check[item])<=strlen(scan)){
			pos=strlen(scan)-strlen(check[item]);
			for(pos;pos<strlen(scan);pos++){
				if(check[item][letter]!=scan[pos]){
					hit=false;
				}
				letter++;
			}
			if(hit==true){
				found=check[item];
				return true;
			}
		}
		item++;
	}
	return false;
}
int variableget(){
	int pos=0;
	while(found!=varnames[pos]){
		pos++;
	}
	if(vartypes[pos]=="int"){
		printf("%d",intvalues[pos]);
	} else {
		printf("%s",varvalues[pos]);
	}
	return 0;
}
int printer(){
	int pos;
	while(character!=EOF){
		pos=0;
		if(character==';'||character=='\n'){
			break;
		}
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
		while(strlen(varnames[pos])!=0&&pos<=127){
			if(checkchar(varnames[pos])){
				variableget();
			}
			pos++;
		}
		add();
	}
}
int print(){
	while(character!=EOF){
		if(character=='\n'||character==';'){
			break;
		}
		add();
		if(character=='('){
			while(character!=')'){
				printer();
			}
		} else if(character==' ') {
			printer();
		}
	}
	return 0;
}
/*
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
*/
FILE *open(str filename){
	return fopen(filename, "r");
}
int lex(){
	add();
	while(character!=EOF){
		if(checkstr(printfun)){
			print();
		} else if(checkstr(variabletypes)){
			variableset();
		}
		add();
	}
}
int main(){
	char filename[]="hry.hry";
	file=open(filename);
	lex();
	getchar();
	return 0;
}