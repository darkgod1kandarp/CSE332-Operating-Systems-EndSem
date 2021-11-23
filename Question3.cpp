//AU1940112 kandarp sharda

// deffining library 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <string.h>
#include <pthread.h>



pthread_mutex_t mux;
sem_t semEmpty;
sem_t semFull;



int buffer[5];  // declaing buffer
int counter = 0; //increasing counter value

//producer it wil generate random numer and that generated number will be stored in buffer 
void* producer(void* args) {
    while (1) {
        
        
        // generating random number 
        int number = rand() % 1000;

        //using sleep to produce the number
        sleep(1);

        //If the buffer is full it will wait until buffer gets space 
        sem_wait(&semEmpty);

        //taking process in critical section using mutext lock  
        pthread_mutex_lock(&mux);

        // storing the value in buffer 
        buffer[counter] = number;

        //increasing counter for adding number 
        counter++;
        

        //taking process out of critical section so that another process can come in critical section
        pthread_mutex_unlock(&mux);

        //This is saying that buffer has added some value 
        sem_post(&semFull);
    }
}


//consumer used for consuming the number that has been produced by producer 
void* consumer(void* args) {

    //infinite while loop
    while (1) {
        int number;

        // Waiting till the buffer get added by some value .
        sem_wait(&semFull);

         //taking process in critical section using mutext lock 
        pthread_mutex_lock(&mux);
        number = buffer[counter - 1];

        // decreasing counter value 
        counter--;
        

        //taking process out of critical section so that another process can come in critical section
        pthread_mutex_unlock(&mux);
        sem_post(&semEmpty);

        // Consuming  = printing the value that has been taken from buffer
        printf("number %d\n", number);

        //giving time to thread to consume data
        sleep(1);
    }
}

//main function
int main(int argc, char* argv[]) {
    

    //declaring variable for thread
    pthread_t consump,produc;

    //declaring variale for mutext 
    pthread_mutex_init(&mux, NULL);

    //declaring semaphores
    sem_init(&semEmpty, 0, 10);
    sem_init(&semFull, 0, 0);
   

   //creating thread 
    if (pthread_create(&produc, NULL, &producer, NULL) != 0) {
                perror("Failed to create thread");
            }
    if (pthread_create(&consump, NULL, &consumer, NULL) != 0) {
                perror("Failed to create thread");
            }
  
  //joining it to main thread
    if (pthread_join(produc, NULL) != 0) {
            perror("Failed to join thread");
        }
    if (pthread_join(consump, NULL) != 0) {
            perror("Failed to join thread");
        }

    //destroying the semaphores
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    pthread_mutex_destroy(&mux);
    
    return EXIT_SUCCESS;
}


















