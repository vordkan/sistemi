/* SCRIVERE UN PROGRAMMA C CHE */
#include
#define BUFFSIZE 15
int main(){
	char op1[BUFFSIZE]
	char op2[BUFFSIZE]
	char output[BUFFSIZE]
	do{
		if(read(STDIN_FILENO, op1, 2) < 0){
			perror("Errore su read: ");
			exit(-1)
		}
		if(atoi(op1) == 1)
			exit(0);
		if(read(STDIN_FILENO, op2, 2) < 0{
			perror("Errore su read: ");
			exit(-1);
		}
		sprint(output, "%d + %d = %d\n", atoi
	}
}
