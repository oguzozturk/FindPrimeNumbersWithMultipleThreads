#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct node {
  long tid;
  int primenumber;
  struct node *next;
}*head,*var;

//Initialize variables
int number=0;
char filename[20];
int isLooked[100000000];
FILE *file;

//Insert to list thread id and prime numbers
void createList(long td,int n){

      struct node *temp; 
      temp=head;
      var=(struct node *)malloc(sizeof (struct node));
      var->tid=td;
      var->primenumber=n;

      if(head==NULL){
          head=var;
          head->next=NULL;
      }
      else{
          while(temp->next!=NULL){     
               temp=temp->next;
          }
          var->next=NULL;
          temp->next=var;
      }
}

//Display thread id and prime numbers
void display(){

     var=head;
     file = fopen(filename,"w"); //Open file
     if(var==NULL){
          printf("List is Empty\n");
     }
     else{         
          while(var!=NULL){
               printf("Thread %ld\tPrime number:%d",var->tid,var->primenumber);                
               fprintf(file,"Thread %ld\tPrime number:%d\n",var->tid,var->primenumber); // write to file                   
               var=var->next;
               printf("\n");
          } 
                       
      printf("\n");
     }
     fclose(file); // close file   
}

//Initialize mutex
pthread_mutex_t lockx;

//Marks prime numbers
void *primeNumbers(void *t){

    int i,j;  
    //Critical session
    pthread_mutex_lock(&lockx); 

    for(i=2;i<number;i++){
        //enter this condition if number is prime
        if(isLooked[i]==0){
          
          //**************************PRINTS PROMES HIGH VALUES HERE*************************
          //printf("Thread %ld\tPrimeNumber: %d\n",(long)t,i );
          //**************************PRINTS PRIMES PARTICULAR RANGE*************************
          //insert variables to list
          createList((long)t,i);
          //marks prime number of floor as 1 according to sieve method 
          for(j=i;i*j<number;j++){
            if(isLooked[i*j]==0){
              isLooked[i*j]=1;
            }
          }
          isLooked[i]=1;
          usleep(1);
          
        }

    pthread_mutex_unlock(&lockx);      
  }
   
    pthread_exit(NULL);

}
 

int main( int argc, char *argv[]){

   //This condition runs 2 thread as default
   if( argc == 5 && strstr(argv[1],"-n") && strstr(argv[3],"-o") ){
      strcpy(filename,argv[4]);
      number=atoi(argv[2]);
      //Initialize default threads
      int numbthread=2;
      pthread_t threads2[numbthread];
      int rc;
      long t;
      void *status;
      //assign all array variables to 0
      int x;
      for(x=0;x<number;x++){
        isLooked[x]=0;
      }
      //Create threads
      for(t=0;t<numbthread;t++){
        if ((rc = pthread_create(&threads2[t], NULL, primeNumbers, (void *)t))) {
            fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
            return EXIT_FAILURE;
          }
      }

      int i;
      // block until all threads complete 
      for (i = 0; i < numbthread; ++i){
        pthread_join(threads2[i], &status);
      }

      pthread_mutex_destroy(&lockx);


   }

   //This condition creates threads according to enter number
   else if( argc == 7 && strstr(argv[1],"-n") && strstr(argv[3],"-t") && strstr(argv[5],"-o")) {

      number=atoi(argv[2]);
      int numbOfThreads=atoi(argv[4]);
      strcpy(filename,argv[6]);
      //Initialize threads
      pthread_t threads[numbOfThreads];
      int rc;
      long t;
      void *status;
      //assign all array variables to 0
      int x;
      for(x=0;x<number;x++){
        isLooked[x]=0;
      }
      //create threads
      for(t=0;t<numbOfThreads;t++){
        if ((rc = pthread_create(&threads[t], NULL, primeNumbers, (void *)t))) {
            fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
            return EXIT_FAILURE;
          }
      }

      int i;
      // block until all threads complete 
      for (i = 0; i < numbOfThreads; ++i){
        pthread_join(threads[i], &status);
      }
      pthread_mutex_destroy(&lockx);
   }
   //Error checking
   else {
      printf("Invalid arguments.\n");
   }
   //main thread displays output
    display();
    return EXIT_SUCCESS;
  
}