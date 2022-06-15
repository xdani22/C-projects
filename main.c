#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define S 4
#define C 8
#define ATT 10
#define MAXPOINTS 100

int verifyCode (int secretCode[S], int attempt[S+2]);
void displayBoard (int board[ATT][S+2],int secretcode[], int nRows, int score);
void generateSecretCode (int secretCode[S]);
void scanVector (int v[], int t);
int calculateScore (int attempts);
void printVector (int v[],int t);

int main(void) {
	
	int secretCode[S],attempt[S+2],board[ATT][S+2]; int i=0; int j,p; unsigned seed;
	int score;
	
	srand(time(NULL));
	generateSecretCode(secretCode);
	//printVector(secretCode,S);
	
	printf("WELCOME TO myMASTERMIND. Enter your guess(no repeated numbers), you have %i tries to beat the computer:\n",ATT);
	
	do {
		scanVector(attempt,S);
		
		verifyCode(secretCode,attempt);
		
		for (p=0;p<S+2;p++){
			board[i][p]=attempt[p];
		}
		printf("Attempt %i: ",i+1);
		printVector(attempt,S);
		
		if (attempt[S]!=4){
			printf(" Black pegs:%i",attempt[S]);
			printf(" White pegs:%i",attempt[S+1]);
			printf(" You have %i attempts left\n",ATT-i-1);
		}
		i=i+1;
	
		} while ((i<ATT)&&(attempt[S]!=4));
	
	score=calculateScore(i);
	displayBoard(board,secretCode,i,score);
	return 0;
}


void displayBoard (int board[ATT][S+2],int secretCode[S], int nRows,int score){
int j,i;
	printf("\nResume chart:\n");
	
	for (i=0;i<nRows;i++){
		printf("Attempt %i:",i+1);
		for (j=0;j<S+2;j++){
			switch (j){
			case 0: case 1: case 2: case 3:
				printf("%i",board[i][j]);
				break;
					case 4:
						printf(" Black pegs:%i ",board[i][j]);
						break;
							case 5:
								printf(" White pegs:%i \n ",board[i][j]);
								break;
			}
		}
	}
	printf("\n-------------------------------------\n");
	if (ATT>=nRows){
	if (score!=0){
		printf("\n-Congrats, you won. Your score is %i-",score);
	}
	else {
		printf("\n-You lost :(                        -");
	}
	printf("\n-------------------------------------\n");
	}
		return;
}

void generateSecretCode (int secretCode[]){
	int num; int i,j; 
for(i=0; i<S; i++){
        secretCode[i] = rand()%C;
        for(j=0; j<=(i-1); ++j){
            if (secretCode[i] != secretCode[j]) {
                continue;
            }
            else {
            	secretCode[i] = rand()%C;
            }
        }
}//auxiliary LOOPS to ensure that numbers are not repeated.
	return;
}



int verifyCode (int secretCode[S],int attempt[S+2]){
	
	int i,j; int b=0; int w=0; //black and white pegs

	for (i=0;i<S;i++){
		if (secretCode[i]==attempt[i]){
		b=b+1;
		}
		for (j=0;j<S;j++) {
			if (secretCode[i]==attempt[j]){
			w=w+1;
			}
		}
	}
	w=w-b;
	attempt[S]=b; attempt[S+1]=w;
	return (attempt[S+2]);
}

void scanVector (int v[], int t){
	// reads a vector of size t
	int i;
	for (i=0; i<t; i++){
		scanf("%i",&v[i]);
	}
	return;
}


int calculateScore (int attempts) {
	int i; int score=10*ATT;
	for (i=0;i<attempts;i++){
		score=score-10;
	}
	return (score);
}

void printVector (int v[],int t){
	int p;
		for (p=0;p<t;p++){
    	printf("%i",v[p]);
		}
}




