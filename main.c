#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LONG_STRING 250 // Maximum length of the strings.
#define ALT 4 //Number of possible answers (alternatives)
#define MAX_QUESTIONS 30 //Maximum number of questions in the pool.
#define NUM_TEST_QUESTIONS 10 //Maximum number of questions in the test.
#define MAX_EXAMS 10//max num of exams

typedef struct {
	char stem [LONG_STRING];
	char alternatives [ALT][LONG_STRING];
	int difficulty;
	int correctAnswer;
} typeQuestion;

void manageQuestionPool(typeQuestion questionPool[],int *questionPoolSize);
void displayQuestionsList(typeQuestion questionPool[],int questionPoolSize);
void displayMenu1();
void displayMenu2();
void displayMenu3();
void displayMenu4();
void displayQuestion (typeQuestion question);
typeQuestion readQuestion (void);
void modifyQuestion(typeQuestion *question);
void removeQuestion (int p,typeQuestion questionPool[]);
void manageTests(typeQuestion questionPool[],int questionPoolSize);
void displayExam(typeQuestion exams[]);
void displayQuestion2 (typeQuestion question);
void setOrder(int v[]);
void shuffleAnswers (typeQuestion *question);
void checkLastOption(typeQuestion *question);
void generateTest(typeQuestion questionSelection[],typeQuestion testQuestions[]);
void checkLastOption(typeQuestion *question);
void sortVector(typeQuestion questionPool[],int questionPoolSize);
void copyVector (typeQuestion questionPool[],typeQuestion questionPoolAux[],int questionPoolSize);


int main(void) {
	
	typeQuestion questionPool[MAX_QUESTIONS];
	int questionPoolSize=0;initializePool(questionPool);//It is initialized to the number of questions given by initializePool
	int m1;int i=1;
	
	while (i!=0){
		
	 	displayMenu1();
		scanf("%i",&m1);
		
		switch (m1){
			
			case 1:
				
				manageQuestionPool(questionPool,&questionPoolSize);
				
				break;
				
					case 2:
						
						manageTests(questionPool,questionPoolSize);
						
					break;
		}
		
		printf("If you want to end the EXAM MANAGING SOFTWARE, press 0:");
		scanf("%i",&i);
	}
	
	return;
}

int initializePool (typeQuestion questionPool[]){
	// Version 3.0 04/12/2019
	// Last update: answers of the type ?All of the above? ?None of the above? have been added on 4/12

	// Parameters
	// questionPool: vector of Questions
	// questionPoolSize: number of questions
	// Action
	// This function generates n questions, stores them in questionPool
	// and returns questionPoolSize


	char auxstr[3], auxstr2[3];
	int i,j,n;
	n=16; // I want to generate 16 questions, change n if you want more (or less)
	
	for (i=0;i<n; i++){
		strcpy(questionPool[i].stem , "This is the stem for question ");
		sprintf(auxstr,"%i",i+1);
		strcat(questionPool[i].stem, auxstr);
		for (j=0;j<ALT; j++){
			strcpy(questionPool[i].alternatives[j] , "This alternative ");
			strcat(questionPool[i].alternatives[j], auxstr);
			strcat(questionPool[i].alternatives[j], " ");
			sprintf(auxstr2,"%i",j+1);
			strcat(questionPool[i].alternatives[j], auxstr2);
		}
		questionPool[i].difficulty=i%10+1;
		questionPool[i].correctAnswer=i%4+1; // For questions 1,5,9,.. correct answer is 1 ...
	}
	
	// Add three answers that are "All of the above" or "None of the above" 
	strcpy(questionPool[0].alternatives[3] , "All of the above");
	strcpy(questionPool[1].alternatives[3] ,"All of the above");
	strcpy(questionPool[2].alternatives[3] , "None of the above");


	return(n); // n is the number of questions generated
}

void displayMenu2(){
	
	printf("*****************************************\n");
	printf("MANAGEMENT OF THE POOL OF QUESTIONS      \n");
	printf("*****************************************\n");
	printf("\n1. Add new question to the pool\n");
	printf("2. Modify a question\n");
	printf("3. Remove a question\n");	
	printf("4. List all questions\n");
	printf("5. Show questions sorted by difficulty\n");
	printf("6. Show the most difficult questions\n");
	printf("0. Come back to main menu\n");
	return;
	
}

void displayMenu3(typeQuestion question){
	
	printf("***********************************\n");
	printf("           MODIFY QUESTION         \n");
	printf("***********************************\n");
	displayQuestion((question));
	printf("If you want to modify the statement, press 0. If you want to change the\n");
	printf("right answer, press 5. If you want to set a new difficulty level, press 6.\n");
	printf("If you want to alter any of the possible answers, please indicate which one [1-4].\n");
	printf("If you want to stop editing, press 7\n");
	return;
	
}

void displayMenu4() {
	
	printf("*****************************************\n");
	printf("MANAGEMENT OF THE EXAMS                  \n");
	printf("*****************************************\n");
	printf("1. Choose questions\n");
	printf("2. Show selection\n");
	printf("3. Generate test\n");
	printf("4. Display test");
	return;

}

void displayQuestion (typeQuestion question){
	
	int i;
	
		printf("Question:%s\n", question.stem);
		
		for (i=0;i<ALT;i++){
			
			if (i==question.correctAnswer-1){
				printf("[X] %s\n", question.alternatives[i]);
			}
			
			else {
				printf("-   %s\n", question.alternatives[i]);
			}
		}
		
		printf("DIFFICULTY:%i\n", question.difficulty);
		
	return;
}

void displayMenu1(){
	
	printf("*****************************************");
	printf("\nWelcome to the Exams Management Software:\n");
	printf("*****************************************\n");
	printf("\n1. MANAGE THE POOL OF QUESTIONS\n");
	printf("2. MANAGE EXAMS\n");
	printf("0. Exit\n");
	return;
}

typeQuestion readQuestion (void){
	
	int i,b;
	typeQuestion question;
	
		printf("Statement of the question:");
		fflush(stdin);
		scanf("%[^\n]", question.stem);
		
		printf("Alternatives:\n");
		for(i=0;i<ALT;i++){
			printf("%i)",i+1);
			fflush(stdin);
			scanf("%[^\n]", question.alternatives[i]);
			
		}
		
		printf("Right answer?(1-4):");
		scanf("%i",&question.correctAnswer);
		
		question.difficulty=((rand()%10)+1);
	
	return(question);
}

void modifyQuestion(typeQuestion *question){
	
	int opt,b; int i=1;
	displayMenu3(*question);
	scanf("%i",&opt);
	
	while (opt!=7){
		
		switch (opt){
			case 0:
				
				printf("Please write a new statement:");
				fflush(stdin);
				scanf("%[^\n]", (*question).stem);
				opt=8;
				break;
				
					case 1: case 2: case 3: case 4:
						printf("Please write a new answer:");
						fflush(stdin);
						scanf("%[^\n]", (*question).alternatives[opt-1]);
						opt=8;
						break;
						
							case 5:
								printf("Right answer?:");
								scanf("%i",&(*question).correctAnswer);
								opt=8;
								break;
								
									case 6:
										printf("Introduce the difficulty level:");
										scanf("%i",&(*question).difficulty);
										opt=8;
										break;
										
											case 8:
											displayMenu3(*question);
											scanf("%i",&opt);
											break;
		}
	}
	
	return;
	}
	
void removeQuestion (int p,typeQuestion questionPool[]){
	
    int i;
    
  	for (i=p;i<MAX_QUESTIONS-p;i++){
  		
  		questionPool[i]=questionPool[i+1];
  		
	  }
	  
    return;
}

void displayQuestionsList(typeQuestion questionPool[],int questionPoolSize){
	
	int i;
	
	for (i=0;i<questionPoolSize;i++){
		
		displayQuestion (questionPool[i]);
		printf("\n");
		
	}
	
	return;
}

void manageQuestionPool(typeQuestion questionPool[],int *questionPoolSize){
	
	int j,a,m2;
	displayMenu2();
	scanf("%i",&m2);
	typeQuestion questionPoolAux[MAX_QUESTIONS];
	
	switch (m2){
		
		case 0:
			
			system("cls");
			
			break;
			
				case 1:
					if (*questionPoolSize<MAX_QUESTIONS){
						printf("How many questions do you want to add?");
						scanf("%i",&j);
						
						for (a=0;a<j;a++){
							
							questionPool[*questionPoolSize]=readQuestion();
							*questionPoolSize=*questionPoolSize+1;
							
						}
					}
					else {
						printf("Warning, the maximum number of questions has been reached");
					}
					break;
					
					case 2:
						
							printf("\nQuestion to modify:");
							scanf("%i",&a);
							modifyQuestion(&questionPool[a]);
							
						break;
						
						case 3:	
						
							printf("Question to erase:");
							scanf("%i",&a);
							displayQuestion(questionPool[a-1]);
							printf("Type 1 to procced to deleting the question:");
							scanf("%i",&j);
							
							if (j==1){
								
								removeQuestion(a-1,questionPool);
								*questionPoolSize=*questionPoolSize-1;
								
							}
							else {
								
								printf("Removal Cancelled");
								
							}
							
							break;
							
								case 4:
									
									displayQuestionsList(questionPool,*questionPoolSize);
																	
								break;
								
									case 5://show questions sorted by difficulty
									
										copyVector (questionPool,questionPoolAux,*questionPoolSize);
										sortVector(questionPool,*questionPoolSize);
										displayQuestionsList(questionPool,*questionPoolSize);
										
										break;
										
											case 6://show most difficult questions
											
												printf("How many questions do you want to see?");
												scanf("%i",&j);
												copyVector (questionPool,questionPoolAux,*questionPoolSize);
												sortVector(questionPool,*questionPoolSize);
												displayQuestionsList(questionPool,j);
												
											break;
											
												default:
													printf("Introduce a valid number please");
													break;
													
	return;
	}
}

void displayQuestion2 (typeQuestion question){//function to display questions in displayExam
	
	int i;
	printf("Question:%s\n", question.stem);
	
	for (i=0;i<ALT;i++){
	printf("-   %s\n", question.alternatives[i]);
		}
	
	printf("DIFFICULTY:%i\n", question.difficulty);
	return;
}

void displayExam(typeQuestion questionSelection[]){//Function to display a real exam, calculating the punctuation, etc.
	
	int i,ans;int mark=0;int a=NUM_TEST_QUESTIONS;
	
	for (i=0;i<NUM_TEST_QUESTIONS;i++){
		
		displayQuestion2(questionSelection[i]);
		printf("Answer?:");
		scanf("%i",&ans);
		
		if (ans==questionSelection[i].correctAnswer){
			mark++;
		}
		
		system("cls");
		displayQuestion(questionSelection[i]);
		
	}
	
	printf("You finished the exam,your mark was of %i\n",mark);
	
	return;
}

void chooseQuestions(typeQuestion questionPool[], typeQuestion questionSelection[], int questionPoolSize){
	
	int usedQuest[MAX_QUESTIONS],i,a; unsigned seed;
	
	for (i=0;i<MAX_QUESTIONS;i++){
		usedQuest[i]=0;
	}
	
	srand(time(NULL));
	a=rand()%NUM_TEST_QUESTIONS;
	
	for (i=0;i<NUM_TEST_QUESTIONS;i++){
		while (usedQuest[a]==1){
			a=rand()%NUM_TEST_QUESTIONS;
		}
		
		questionSelection[i]=questionPool[a];
		usedQuest[a]=1;
	}
	
	return;
}

void setOrder(int v[]){
	int n1,n2,aux;
	n1=rand()%ALT;
	n2=rand()%ALT;
	
	do{
		n2=rand()%ALT;
	} while (n1==n2);
	
	aux=v[n1];
	v[n1]=v[n2];
	v[n2]=aux;	
	n1=rand()%ALT;
	n2=rand()%ALT;
	
	do{
		n2=rand()%ALT;
	} while (n1==n2);
	
	aux=v[n1];
	v[n1]=v[n2];
	v[n2]=aux;	
	
	return;
}

void shuffleAnswers (typeQuestion *question){
	
	int i,newCorrect; char aux[ALT][LONG_STRING];
	int v[ALT]={1,2,3,4};
	
	setOrder(v);
	
	for (i=0;i<ALT;i++){
		strcpy(aux[i], (*question).alternatives[i]);
	}
	
	for (i=0;i<ALT;i++){
		strcpy((*question).alternatives[i], aux[v[i]-1]);
			if ((*question).correctAnswer==i+1){
			newCorrect=v[i];
		}
	}
	
	(*question).correctAnswer=newCorrect;
	
	return;
}

void checkLastOption(typeQuestion *question){
	
	int i;int newCorrect=(*question).correctAnswer;
	char a[]="All of the above";
	char b[]="None of the above";
	char alt[ALT][LONG_STRING];
	
	for (i=0;i<ALT;i++){
		strcpy(alt[i], (*question).alternatives[i]);
	}
	
	for (i=0;i<ALT;i++){
		if ((strcmp(((*question).alternatives[i]), a)==0)||((strcmp((*question).alternatives[i], b))==0)){
			strcpy((*question).alternatives[3], alt[i]);
			strcpy((*question).alternatives[i], alt[3]);
			if (i+1==(*question).correctAnswer){
					newCorrect=4;
			}
			else if (4==(*question).correctAnswer){
				newCorrect=i+1;
			}
		}
	}
	
	(*question).correctAnswer=newCorrect;
	
	return;
}

void generateTest(typeQuestion questionSelection[],typeQuestion testQuestions[]){
	
	int i;
	
	for (i=0;i<NUM_TEST_QUESTIONS;i++){
		testQuestions[i]=questionSelection[i];
	}
	
	for (i=0;i<NUM_TEST_QUESTIONS;i++){
		shuffleAnswers(&testQuestions[i]);
		checkLastOption(&testQuestions[i]);
	}
	
	return;
}

void manageTests(typeQuestion questionPool[],int questionPoolSize){
	typeQuestion questionSelAux[NUM_TEST_QUESTIONS];//it happens that the first vector declared has some characters in it, so i declared one to avoid possible problems.
	typeQuestion questionSel[NUM_TEST_QUESTIONS];	
	typeQuestion testQuestions[NUM_TEST_QUESTIONS];

	
	int i=0;int p;
	displayMenu4();
	scanf("%i",&p);
	
	switch(p){
		case 1:
			chooseQuestions(questionPool,questionSel,questionPoolSize);
			break;
			
			case 2:
			
			displayQuestionsList(questionSelAux,NUM_TEST_QUESTIONS);
			
			break;
			
				case 3:
					generateTest(questionSel,testQuestions);
				break;
				
					case 4:
						//displayExam(testQuestions); this function asks the user for an answer and corrects the exam.
						//It uses another displayQuestion(2)
						displayQuestionsList(testQuestions,NUM_TEST_QUESTIONS); 
					break;
					
	}
	return;
}

void sortVector(typeQuestion questionPool[],int questionPoolSize){//bubblesort baby
	int i,j,aux;
	for (i=1; i<=questionPoolSize-1; i++) {
		for(j=0; j < questionPoolSize-i; j++) {
			if(questionPool[j].difficulty>questionPool[j+1].difficulty) {
			 	aux=questionPool[j].difficulty;
				questionPool[j].difficulty=questionPool[j+1].difficulty;
				questionPool[j+1].difficulty=aux;
			}
		}
	}
	return;	
}

void copyVector (typeQuestion questionPool[],typeQuestion questionPoolAux[],int questionPoolSize){
	int i;
	for (i=0;i<questionPoolSize;i++){
		questionPoolAux[i]=questionPool[i];
	}
return;
}

