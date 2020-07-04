#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define MAX_SIZE_Q 3

/*INITIALISATION (global)*/
//buffer CR1 
struct t_elem{
	int number;
	struct t_elem* next;
};
struct t_elem* beg_q = NULL;
struct t_elem* end_q = NULL;
int size_q = 0;
//atom CR2
typedef struct atom{
	int first_i;
	int second_i;
	unsigned first_u;
	unsigned second_u;
	long first_l;
	long second_l;
	long unsigned first_lu;
	long unsigned second_lu;
}atomVar;
struct atom CR2;
//other
pthread_cond_t SIG21 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t MCR1 = PTHREAD_MUTEX_INITIALIZER;
sem_t SCR1;
pthread_barrier_t BCR2;
int f2 = 0, f3 = 0 ,f4 = 0 ,f6 = 0;

FILE* fileLog = NULL;
/*IMPLAMANTATION*/
// struct t_elem (queue)
// -add new element to the queue
void add_elem() {
	struct t_elem*  p = (struct t_elem*)malloc(sizeof(struct t_elem));
	p->next = NULL;
	if (beg_q == NULL) {
	    p->number = 0;
	    beg_q = p;
	}
	else {
	    p->number = end_q->number +1;
	    end_q->next = p;
	}
	end_q = p;
	end_q->next = beg_q;
    size_q++;
}
// - get element from queue
struct t_elem* get_elem() {
	return beg_q;
}
// - delete element from queue
void del_node_q(){
	if (beg_q != NULL) {
		size_q--;
		end_q->next = beg_q->next;
		free(beg_q);
		if (size_q == 0) beg_q = NULL;
		else beg_q = end_q->next;
	}
}
// - del_queue queue
void del_queue() {
	if (beg_q != NULL){
		for (int i = 0; i < size_q; i++) {
			del_node_q();
		}
	}
}
//threads
void* thread_P1(void* unused){
	fprintf(fileLog,"THREAD - P%d BEGIN\n", *(int*)unused);
	int sem_value = 0, end_threads = 0;
	while(1){
		if (pthread_mutex_trylock(&MCR1) == 0){
			sem_getvalue(&SCR1,&sem_value);
			if (sem_value < MAX_SIZE_Q) {
				add_elem();
				fprintf(fileLog,"P%d ADD ELEMENT (SCR1 + MCR1)\n", *(int*)unused);
				sem_post(&SCR1);
			}
			pthread_mutex_unlock(&MCR1);
		} 
		else {
			end_threads++;
		}
		while (size_q != 0);
		if(end_threads >= 2) break;
	}
	fprintf(fileLog, "THREAD - P%d END\n", *(int*)unused);
}

void* thread_P2(void* unused){
	struct t_elem *var;
	fprintf(fileLog,"THREAD - P%d BEGIN\n", *(int*)unused);

	while(1){
		pthread_mutex_lock(&MCR1);
		fprintf(fileLog, "P%d WAIT FOR SIGNAL (SIG21)\n", *(int*)unused);
		while (f2 == 0) pthread_cond_wait(&SIG21,&MCR1);
		f2=0;
		pthread_mutex_unlock(&MCR1);
		fprintf(fileLog, "P%d GET SIGNAL (SCR21)\n", *(int*)unused);
		fprintf(fileLog, "P%d USE ATOM (CR2)\n", *(int*)unused);
		__sync_fetch_and_sub(&CR2.first_i, 3);
		__sync_add_and_fetch(&CR2.second_i, 3);
		__sync_fetch_and_or(&CR2.second_u, 3);
		__sync_fetch_and_and(&CR2.first_u, 3);
		__sync_xor_and_fetch(&CR2.first_l, 3);
		__sync_nand_and_fetch(&CR2.first_u, 1);
		__sync_bool_compare_and_swap(&CR2.first_lu, 2, 1);
		__sync_val_compare_and_swap(&CR2.first_lu, 2, 5);
		fprintf(fileLog, "P%d MODIFICATES ATOM (CR2)\n", *(int*)unused);
		CR2.first_i = 70;
    	CR2.first_l--;	
		if (pthread_mutex_trylock (&MCR1) == 0){
			if (sem_trywait(&SCR1) == 0){
				var = get_elem();
				fprintf(fileLog, "P%d GET NODE : %d\n", *(int*)unused, var->number);
				del_node_q();			
			}
			pthread_mutex_unlock (&MCR1);
		}
	}
}

void* thread_P3(void* unused){
	fprintf(fileLog,"THREAD - P%d BEGIN\n", *(int*)unused);

	while(1){
		pthread_mutex_lock (&MCR1);
		fprintf(fileLog, "P%d WAIT FOR SIGNAL (SIG21)\n", *(int*)unused);
		while (f3 == 0) pthread_cond_wait(&SIG21,&MCR1);
		f3=0;
		fprintf(fileLog, "P%d GET SIGNAL (SCR21)\n", *(int*)unused);
		pthread_mutex_unlock (&MCR1);
		fprintf(fileLog, "P%d USE ATOM-1 (CR2)\n", *(int*)unused);
		__sync_fetch_and_sub(&CR2.first_i, 3);
		__sync_add_and_fetch(&CR2.second_i, 3);
		__sync_fetch_and_or(&CR2.second_u, 3);
		__sync_fetch_and_and(&CR2.first_u, 3);

		fprintf(fileLog, "P%d WAITING FOR P6\n", *(int*)unused);
		pthread_barrier_wait(&BCR2);
		fprintf(fileLog, "P%d SYNCHRONIZED WITH P6\n", *(int*)unused);
		
		fprintf(fileLog, "P%d USE ATOM-2 (CR2)\n", *(int*)unused);
		__sync_xor_and_fetch(&CR2.first_l, 3);
		__sync_nand_and_fetch(&CR2.first_u, 1);
		__sync_bool_compare_and_swap(&CR2.first_lu, 2, 1);
		__sync_val_compare_and_swap(&CR2.first_lu, 2, 5);
	}
}

void* thread_P4(void* unused){
	struct t_elem *var;
	fprintf(fileLog,"THREAD - P%d BEGIN\n", *(int*)unused);

	while(1){
		pthread_mutex_lock (&MCR1);
		fprintf(fileLog, "P%d WAIT FOR SIGNAL (SIG21)\n", *(int*)unused);
		while (f4 == 0) pthread_cond_wait(&SIG21,&MCR1);
		f4=0;
		fprintf(fileLog, "P%d GET SIGNAL (SCR21)\n", *(int*)unused);
		pthread_mutex_unlock(&MCR1);

		if (pthread_mutex_trylock(&MCR1) == 0 ){
			if (sem_trywait(&SCR1) == 0){
				var = get_elem();
				fprintf(fileLog, "P%d GET NODE : %i\n", *(int*)unused, var->number);
				del_node_q();
			}
			pthread_mutex_unlock (&MCR1);
		}
	}
}

void* thread_P5(void* unused){
	struct t_elem *var;
	fprintf(fileLog,"THREAD - P%d BEGIN\n", *(int*)unused);

	while(1){
		fprintf(fileLog, "P%d MODIFICATES ATOM (CR2)\n", *(int*)unused);
		CR2.first_i = 156;
		CR2.second_i = 100;
		CR2.first_u = 10000;
		CR2.second_u = 17000;
		CR2.first_l += 15;
		CR2.second_l /= 2;
		CR2.first_lu += 5;
		CR2.second_lu -= 10;

		pthread_mutex_lock (&MCR1);
		f2 = f3 = f4 = f6 = 1;
		fprintf(fileLog, "P%d SEND SIGNAL (SIG21)\n", *(int*)unused);
		pthread_cond_broadcast(&SIG21);
		pthread_mutex_unlock(&MCR1);
		

		if (pthread_mutex_trylock (&MCR1) == 0 ){
			if (sem_trywait (&SCR1) == 0){
				var = get_elem();
				fprintf(fileLog, "P%d GET NODE : %i\n", *(int*)unused, var->number);
				del_node_q();
			}
			pthread_mutex_unlock (&MCR1);
		}
	}
}

void* thread_P6(void* unused){
	fprintf(fileLog,"THREAD - P%d BEGIN\n", *(int*)unused);

	while(1){
		pthread_mutex_lock (&MCR1);
		fprintf(fileLog, "P%d WAIT SIGNAL (SIG21)\n", *(int*)unused);
		while (f6 == 0) pthread_cond_wait(&SIG21,&MCR1);
		f6 = 0;
		fprintf(fileLog, "P%d GET NODE SIGNAL (SCR21)\n", *(int*)unused);
		pthread_mutex_unlock (&MCR1);

		fprintf(fileLog, "P%d USE (CR2)\n", *(int*)unused);
		__sync_fetch_and_sub(&CR2.first_i, 3);
		__sync_add_and_fetch(&CR2.second_i, 3);
		__sync_fetch_and_or(&CR2.second_u, 3);
		__sync_fetch_and_and(&CR2.first_u, 3);
		
		fprintf(fileLog, "P%d WAITING FOR P3\n", *(int*)unused);
		pthread_barrier_wait(&BCR2);
		fprintf(fileLog, "P%d SYNCHRONIZED WITH P3\n", *(int*)unused);

		CR2.first_i = 7;
		CR2.second_i = 10;
		fprintf(fileLog, "P%d MODIFICATES ATOM (CR2)\n", *(int*)unused);
	}
}

//
int main(){
	//threads
	pthread_t P1;
	pthread_t P2;
	pthread_t P3;
	pthread_t P4;
	pthread_t P5;
	pthread_t P6;
	//initialisation atom
	CR2.first_i = 60;
	CR2.second_i = -15;
	CR2.first_u = 79;
	CR2.second_u = 17;
	CR2.first_l = -111111;
	CR2.second_l = 555555;
	CR2.first_lu = 1111111;
	CR2.second_lu = 8888888;
	//
	fileLog = fopen("lab4.log", "w");
	sem_init(&SCR1, 0, 0);
	pthread_barrier_init(&BCR2,NULL,2);
	// thread id
	int id1 = 1, id2 = 2, id3 = 3, id4 = 4, id5 = 5, id6 = 6;
	// creare threads
	pthread_create(&P1, NULL, &thread_P1, (void*)&id1);
	pthread_create(&P2, NULL, &thread_P2, (void*)&id2);
	pthread_create(&P3, NULL, &thread_P3, (void*)&id3);
	pthread_create(&P4, NULL, &thread_P4, (void*)&id4);
	pthread_create(&P5, NULL, &thread_P5, (void*)&id5);
	pthread_create(&P6, NULL, &thread_P6, (void*)&id6);

	pthread_join(P1, NULL);
	pthread_cancel(P2);
	pthread_cancel(P3);
	pthread_cancel(P4);
	pthread_cancel(P5);
	pthread_cancel(P6);
	pthread_barrier_destroy(&BCR2);

	del_queue();
	fprintf(fileLog, "\nEND");

	fclose(fileLog);
	
	return 0;
}
