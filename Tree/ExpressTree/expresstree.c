#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ETree{
	char ch;
	struct ETree *left;
	struct ETree *right;
};
typedef struct ETree *etlink;

char stack[100];
int sp=-1;
void push_ch(char item){
	stack[++sp]=item;
}
char pop_ch(void){
	return stack[sp--];
}
char top_ch(void){
	return stack[sp];
}
int empty(void){
	return sp==-1;
}
etlink stack_node[30];
void push_node(etlink item){
	stack_node[++sp]=item;
}
etlink pop_node(void){
	return stack_node[sp--];
}

void display_infix(etlink root){
	if(root){
		printf("(");
		display_infix(root->left);
		printf("%c",root->ch);
		display_infix(root->right);
		printf(")");
	}
}

void display_suffix(etlink root){
	if(root){
		display_suffix(root->left);
		display_suffix(root->right);
		printf("%c",root->ch);
	}
}

etlink create_expresstree(char *suffix,int sufsize){
	int i;
	char ch;
	etlink cur=NULL;
	for(i=0;i<sufsize;i++){
		ch=suffix[i];
		cur=malloc(sizeof(struct ETree));
		cur->ch=ch;
		cur->left=cur->right=NULL;
		if(ch=='+' || ch=='-' || ch=='*' || ch=='/'){
			cur->right=pop_node();
			cur->left=pop_node();
		}
		push_node(cur);
	}
	if(!empty())
		cur=pop_node();
	return cur;
}

void infix2suffix(char *infix,int size,char *suffix,int *sufsize){
	int i,cp=0;
	char ch;
	for(i=0;i<size;i++){
		ch=infix[i];
		if(ch=='+' || ch=='-' || ch=='*' || ch=='/'){
			if(empty()){
				push_ch(ch);
			}else if(ch=='+' || ch=='-'){
				while(!empty()){
					if(top_ch()=='(')
						break;
					suffix[cp++]=pop_ch();
				}
				push_ch(ch);
			}else{
				while(!empty()){
					if(top_ch()=='(' || top_ch()=='+' || top_ch()=='-' )
						break;
					suffix[cp++]=pop_ch();
				}
				push_ch(ch);
			}
		}else if(ch=='(' || ch==')'){
			if(ch=='(')
				push_ch(ch);
			else{
				while(!empty()){
					ch=pop_ch();
					if(ch=='(')
						break;
					suffix[cp++]=ch;
				}
			}
		}else
			suffix[cp++]=ch;
	}
	while(!empty())
		suffix[cp++]=pop_ch();
	*sufsize=cp;
}

int main(int argc, char const *argv[])
{
	char *infix="a+b*c+(d*e+f)*g";
	int size=strlen(infix);
	char *suffix=calloc(size,sizeof(char));
	int sufsize;
	infix2suffix(infix,size,suffix,&sufsize);
	printf("%s\n",suffix );
	etlink expresstree=create_expresstree(suffix,sufsize);
	display_infix(expresstree);
	printf("\n");
	display_suffix(expresstree);
	printf("\n");
	return 0;
}