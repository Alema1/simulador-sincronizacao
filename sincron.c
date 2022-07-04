/*
Trabalho de Sistemas Operacionais - T3
sincron.
Vinicius Hardt Schreiner 
*/

#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"
#include "semaphore.h"
#define LIMBUFFER 5
#define TRUE 1
#define FALSE 0
#define DIRETORIA 0
#define RH 1
#define FUNCIONARIOS 2

int buffer[LIMBUFFER];

sem_t full;  // declaração dos semáforos
sem_t empty; 
sem_t mutex;
               
void entra_no_buffer(int tipo_arquivo){ //função que insere no buffer 
	sem_wait(&empty);
	sem_wait(&mutex);
	if(tipo_arquivo == DIRETORIA){
	printf("Um arquivo da Diretoria entrou no Buffer\n");
	}
	if(tipo_arquivo == RH){
	printf("Um arquivo do RH entrou no Buffer\n");
	}
	if(tipo_arquivo == FUNCIONARIOS){
	printf("Um arquivo dos Funcionarios entrou no Buffer\n");
	}
	sem_post(&mutex);
	sem_post(&full);
}

void sai_do_buffer(int tipo_arquivo){ // função que retira do buffer
	sem_wait(&full);
	sem_wait(&mutex);
	if(tipo_arquivo == DIRETORIA){
	printf("Um arquivo da Diretoria saiu do Buffer\n");
	}
	if(tipo_arquivo == RH){
	printf("Um arquivo do RH saiu do Buffer\n");
	}
	if(tipo_arquivo == FUNCIONARIOS){
	printf("Um arquivo dos Funcionarios saiu do Buffer\n");
	}
	sem_post(&mutex);
	sem_post(&empty);
	
}

void * thread_arquivo(){
int tipo_arquivo = rand()%3;		//geração randomica dos arquivos da DIR/RD/FUNC
	while(TRUE){
	entra_no_buffer(tipo_arquivo);	//insere o arquivo no buffer
	printf("Arquivo impresso!\n",tipo_arquivo);	// impressão
	sleep(1);
	sai_do_buffer(tipo_arquivo);	//retira arquivo do buffer apos impressão
	}

}

int main(){

int i;

sem_init(&full, FALSE, 1);		//inicialização dos semáforos
sem_init(&empty, FALSE, LIMBUFFER);
sem_init(&mutex, TRUE, 1);

pthread_t buffer[LIMBUFFER];

for(i = 0; i < LIMBUFFER; i++) {
	pthread_create(&buffer[i], NULL,thread_arquivo, (void *) &i);	//criação das threads
	}for(i = 0; i < LIMBUFFER; i++){
	pthread_exit(NULL);
	}


return 0;
}


