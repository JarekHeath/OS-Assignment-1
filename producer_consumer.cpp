#include <iostream>
#include <stdio.h>		
#include <stdlib.h>		
#include <sys/mman.h>	
#include <sys/shm.h>	
#include <sys/stat.h>	
#include <sys/types.h>
#include <sys/ipc.h>	
#include <fcntl.h>	
#include <unistd.h>
#include <semaphore.h>	
#include <errno.h>	
#include <string.h>	
#include <time.h>


using namespace std;

const int LoopAmount = 10;
#define SHMSIZE 4096
const int CAPACITY = 2;

pthread_mutex_t Mutex;

	
sem_t *EmptyTable = sem_open("empty", O_CREAT, 0666, 2);
sem_t *FullTable = sem_open("full", O_CREAT, 0666, 0);

void *producer(void *) {
	int tableID = shm_open("table", O_CREAT|O_RDWR, 0666);
	ftruncate(tableID, SHMSIZE);
	int *table = (int*)mmap(0, SHMSIZE, PROT_READ|PROT_WRITE, MAP_SHARED, tableID, 0);

	int temp = 0;
	int in = 0;
	int i = 0;
	int a = 0;
	int b = 0;
	while (in < LoopAmount) {
		temp = ((rand() % 100) +1);
		
		sem_wait(EmptyTable);
		
		sleep(rand() % 2 + 1);
		
		pthread_mutex_lock(&Mutex);
		
		table[i] = temp;
		
		std::cout << "\nProduced Number: " << temp << "\nTable is now  " << table[0] << " " << table[1];
		
		
		pthread_mutex_unlock(&Mutex);
		sem_post(FullTable);
		
		++i;
		i = i % 2;
		in++;
		}
	munmap(table, SHMSIZE);
	close(tableID);
	shm_unlink("table");
	return NULL;
}


void *consumer(void *) {
	int tableID = shm_open("table", O_CREAT|O_RDWR, 0666);
	ftruncate(tableID, SHMSIZE);
	int *table = (int*)mmap(0, SHMSIZE, PROT_READ|PROT_WRITE, MAP_SHARED, tableID, 0);

	int out = 0;
	int temp = 0;
	int i = 0;
	int a = 0;
	int b = 0;
	while (out < LoopAmount) {
		sem_wait(FullTable);

		sleep(rand() % 2 + 1);

		pthread_mutex_lock(&Mutex);
		
		temp = table[i];
		table[i] = 0;
		
		std::cout << "\nConsumed Number: " << temp << "\nTable is now  " << table[0] << " " << table[1];
		
		pthread_mutex_unlock(&Mutex);
		sem_post(EmptyTable);
		
		i++;
		i = i % 2;
		out++;
		}
	munmap(table, SHMSIZE);
	close(tableID);
	shm_unlink("table");
	return NULL;
}

int main() {

	pthread_t pro, con;
	pthread_attr_t attr;

	pthread_mutex_init(&Mutex,0);
	pthread_attr_init(&attr);
	
	pthread_create(&pro, &attr, &producer, (void *)NULL);
	pthread_create(&con, &attr, &consumer, (void *)NULL);
	
	pthread_join(pro, NULL);
	pthread_join(con, NULL);
	
	sem_close(EmptyTable);
	sem_close(FullTable);
	
	sem_unlink("empty");
	sem_unlink("full");
	
	std::cout << "\nProducer and Consumer have finished.";
	return 0;
}









