#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

//Assuming the valid word to be no longer 20 continuous valid charactes by default.
#define MAX_VALIDWORD_LENGTH 20

//defining the number of threads
#define NUM_OF_THREADS 2

//This is the list data structure that stores all the valid words
typedef struct validWordList {
	char word[MAX_VALIDWORD_LENGTH];
	int occurences;
	struct validWordList *next;
} validWords;

//This structure is used to provide the start and end addresses of the mmapped file that each thread is support scan
typedef struct chuck{
	char *tstart;
	char *tend;
}chunk;

void addWordToList(char *wstart,char *wend);
validWords * merge(validWords *a, validWords *b);
validWords * mergeSort(validWords *alist);
void split(validWords *alist, validWords **a, validWords **b);
void printList(validWords *alist);
void *runner(chunk *tmem);

//Valid words list being declared as global variable so that all the threads can access it.
validWords *list=NULL;

//mutex initialization
sem_t mutex;

int main(int argc, char **argv){
	clock_t begin, end;
	double timeSpent;
	begin=clock();
	int fd;
	char *fname;
	struct stat finfo;
	char *fdata;
	char *fstart;
	char *fend;
	sem_init(&mutex,0,1);

	//If expected arguments are not provided we throw following error messages
	if(argc<=2){
		if(argc==2){
			printf("Third argument is missing\n");
			exit(-1);
		} else {
			printf("File location not specified\n");
			exit(-1);
		}
	}
	
	//reading file name from command line argument
	fname=argv[1];

	//Open system call will open the file for you. It returns the file descripter
	fd=open(fname, O_RDONLY);
	if(fd<0){
		perror("Opening the file failed");
		exit(-1);
	}

	//initializing fstats with the statistics of the file to retrieve the file size
	if(fstat(fd, &finfo) < 0){
		perror("couldn't fetch the stats of the file");
		exit(-1);
	}
	
	//creating a private memory of size equal to size of the file and mapping it to the address space of this process
	fdata = (char *) mmap(0, finfo.st_size + 1, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if(fdata==MAP_FAILED){
		perror("couldn't map a memory of file content with process address space");
		exit(-1);
	}
	
	fstart=fdata;
	fend=fdata+finfo.st_size;

	//dividing the whole content equally among the threads.
	off_t tchunk = finfo.st_size/NUM_OF_THREADS;
	
	//The next few lines of code performs a domestic check so the chunk divided for each thread does not cut through a valid word at the end. Hence, instead of ending the chunk sharply at fdata+tchunk we increase the boundary to an ' ' or '\n'.
	pthread_t tidArray[NUM_OF_THREADS];
	int i;
	int additionalThreadsRequired=1;
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	for(i=0;i<NUM_OF_THREADS-1;i++){
		char *tfend=fstart+tchunk;
		while(*tfend!=' '&&*tfend!='\n')
			tfend++;
		if(tfend>=fend){
			additionalThreadsRequired=0;
			tfend=fend;
		}
		chunk *tmem = malloc(sizeof(chunk));
		tmem->tstart=fstart;
		tmem->tend=tfend;

		//Thread creation
		if(pthread_create(&tid,&attr,(void *)&runner,tmem)!=0){
			perror("Thread creating failed");
			exit(-1);
		}
		tidArray[i]=tid;
		fstart=tfend+1;
		if(additionalThreadsRequired==0)
			break;
	}
	if(additionalThreadsRequired && fstart<fend){
		chunk *tmem = malloc(sizeof(chunk));
                tmem->tstart=fstart;
                tmem->tend=fend;

		//Last thread created here.
                if(pthread_create(&tid,&attr,(void *)&runner,tmem)!=0){
                        perror("Thread creating failed");
                        exit(-1);
                }
                tidArray[i]=tid;

	}
	for(i=0;i<NUM_OF_THREADS;i++){
		pthread_join(tidArray[i],NULL);
	}
	
	list=mergeSort(list);
	int counter=0;
//	int lines = (int)(argv[2][0] - '0');
	int lines = atoi(argv[2]);
	while(list!=NULL&&counter<lines){
		printf("%s\t%d\n",list->word,list->occurences);
		list=list->next;
		counter++;
	}
	sem_destroy(&mutex);
	end=clock();
	timeSpent=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("execution time : %lf seconds\n",timeSpent);
}

//This method takes a valid word within the boundaries of wstart and wend and adds it to list. If word already in list in increaments the occurrences counter.
void addWordToList(char *wstart, char *wend){
	char *iterator=wstart;
	char validWord[MAX_VALIDWORD_LENGTH];
	int i=0;
	while(iterator<=wend && i<MAX_VALIDWORD_LENGTH){
		validWord[i]=toupper(*iterator);
		iterator++;
		i++;
	}
	validWord[i]='\0';
	if(list==NULL){
		list=malloc(sizeof(validWords));
		strcpy(list->word,validWord);
		list->occurences=1;
		list->next=NULL;
	}else{
		validWords *previous, *current=list;
		do{
			if(strcmp(current->word,validWord)==0){
				current->occurences++;		
				break;
			}
			previous=current;
			current=current->next;
		}while(current!=NULL);
		if(current==NULL){
			current=malloc(sizeof(validWords));
			strcpy(current->word,validWord);
			current->occurences=1;
			current->next=NULL;
			previous->next=current;
		}
	}
	
}

//runner method that is executed by each thread independently
void *runner(chunk *tmem){
	char *fstart=tmem->tstart;
	char *fend=tmem->tend;
	char *fcurrent=fstart;
	
	//Reaching to the first valid word
	while((toupper(*fcurrent)<'A' || toupper(*fcurrent)>'Z') && *fcurrent!='-' && fcurrent<fend){
		fcurrent++;
	}
	char *wordStartChar=fcurrent;
	char *wordEndChar=NULL;
	int isGoodWord=1;
	char c;
	while(fcurrent<fend){
		c = toupper(*fcurrent);
		if((c<'A' || c>'Z') && c!='-' && c!=' ' && c!='\n'){
			isGoodWord=0;
		}else if(c==' ' || c=='\n'){
			if(isGoodWord){
				//add semaphore here
				sem_wait(&mutex);
				addWordToList(wordStartChar, wordEndChar);
				//leaveSemaphore lock here
				sem_post(&mutex);
			}
			while((c<'A' || c>'Z') && c!='-' && fcurrent<fend){
				fcurrent++;
				c = toupper(*fcurrent);
			}
			if(fcurrent>=fend){
				break;
			}else {
				wordStartChar=fcurrent;
			        wordEndChar=NULL;
			        isGoodWord=1;	
			}		
		}
		wordEndChar=fcurrent;		
		fcurrent++;
	}
	pthread_exit(0);
}

//All below methods correspond to sorting. Mergesort algorithm is implemented.
validWords * merge(validWords *a, validWords *b){
	validWords *result=NULL;
	if(a==NULL){
		return b;
	}else if(b==NULL){
		return a;
	}
	if(a->occurences>b->occurences){
		result=a;
		a=a->next;
	}else{
		result=b;
		b=b->next;
	}
	validWords *current=result;
	while(a!=NULL && b!=NULL){
		if(a->occurences>b->occurences){
			current->next=a;
			a=a->next;
			current=current->next;
		}else{
			current->next=b;
                        b=b->next;
                        current=current->next;
		}
	}
	if(a==NULL)
		current->next=b;
	else
		current->next=a;
	return result;
	
} 

validWords * mergeSort(validWords *list){
	if(list->next==NULL)
		return list;
	validWords *a=NULL, *b=NULL;
	split(list,&a,&b);
	a = mergeSort(a);
	b = mergeSort(b);
	return merge(a,b);
}

void split(validWords *list, validWords **a, validWords **b){
	validWords *fast;
	validWords *slow;
	if(list==NULL || list->next==NULL){
		*a=list;
		*b=NULL;
	}else{
		slow=list;
		fast=list->next;
		while(fast!=NULL){
			fast=fast->next;
			if (fast != NULL){
			        slow = slow->next;
			        fast = fast->next;
      			}
		}
		*a=list;
		*b=slow->next;
		slow->next=NULL;
	}
}

void printList(validWords *list){
	while(list!=NULL){
		printf("%s\t%d\n",list->word,list->occurences);
		list=list->next;
	}
}
