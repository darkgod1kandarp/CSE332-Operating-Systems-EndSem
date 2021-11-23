//AU1940112 kandarp sharda
//calling library 
#include <iostream>
#include <thread>
#include<mutex>
#include<semaphore.h>
#include <unistd.h>
//defining number of thread
#define THREAD_NUM 3
using namespace std;

//declaring variable
sem_t smallLetter;
sem_t capitalLetter;
sem_t numerical;


//capital Letter generator 
void capitalLetterGenerator(){

//declaring variable 
char c;
    
    //for loop that generate A to Z letter
    for (c = 'A'; c <= 'Z'; ++c){

     //it will wait until that until the siganl value get 1 means until the running procces get complete 
     sem_wait(&capitalLetter);

     //printing output 
        std::cout<<c<<"";

    //it will increase the count of numerical variable, in laymans term it is saying that one process in quess is freed 
    sem_post(&numerical);
    }
    
}


//numeric value generator 
void NumericValueGenerator(){

    
    //for loop for generating number from 1 to 27
    for(int i = 1;i<27;i++){

        //it will wait until that until the numerical variable get value 1 ,means until the running procces get complete 
      sem_wait(&numerical);   
        std::cout<<" "<<i<<" ";

    //it will increase the count of smallLetter variable, in laymans term it is saying that one process in quess is freed 
    sem_post(&smallLetter);
        
    }


}

//small letter generator 
void SmallLetterGenerator(){

    char c;

   //for loop for generating number from a to z
    for (c = 'a'; c <= 'z'; ++c){

     //it will wait until that until the smallLetter variable get value 1 ,means until the running procces get complete 
    sem_wait(&smallLetter);
        std::cout<<c<<" ";
    
    //it will increase the count of smallLetter variable, in laymans term it is saying that one process in quess is freed 
    sem_post(&capitalLetter);
    }

}

int main(){


//giving semaphores value
sem_init(&smallLetter, 0, 0);
sem_init(&capitalLetter, 0, 1);
sem_init(&numerical, 0, 0);

// declaring the variable of thread
  std::thread small,capital,numeric;


//Passing the function that will get executed by thread
  small =  std::thread(SmallLetterGenerator);
  capital = std::thread(capitalLetterGenerator);
  numeric = std::thread(NumericValueGenerator);
  

//joining it to main function  
capital.join();
numeric.join();
small.join();


//destroying semaphores 
sem_destroy(&smallLetter);
sem_destroy(&capitalLetter);
sem_destroy(&numerical);
  

  return EXIT_SUCCESS;

}