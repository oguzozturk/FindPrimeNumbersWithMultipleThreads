# FindPrimeNumbersWithMultipleThreads

In this program, I implement a program that takes a number  “n”  as input  and
calculates all the prime numbers less than n. I write all the prime numbers and the thread that finds this prime number 
to both the screen and an output file.  

In the implementation, I use stack that holds the prime numbers, and each thread will take a number and 
try to decide whether the number is prime or not.  
Main thread creates some number of worker threads. 
Each worker thread locks a mutex and "takes" the next untaken number to work on to see if prime. 
When done, the worker thread marks the number as prime and takes a new number to test it for primality. 
If all numbers have been taken then the thread exits. Two threads don't test the same number for primality. 
The main thread has to wait for all worker threads to complete. 
After all worker threads have completed, the main thread prints the results of the primality testing.  
To make program more efficient, when a thread test primality of a number x, 
it also mark off the multiples of x (2x, 3x, 5x, 7x, 11x, etc.)  as  not prime. 
The multiples of a prime number generated with using Sieve of Eratoshthenes method.  
The invocation of program as follows:   
(1)  ./FindPrimeNumbersWithMultipleThreads.out          
(2)  ./FindPrimeNumbersWithMultipleThreads.out  -n 100  -o outputfile 
(3)  ./FindPrimeNumbersWithMultipleThreads.out  -n 100  -t 4  -o outputfile  

If there is no option spesified, then print an error message and quit. 
The –n option specifies the largest number that the program will test for primality. 
The program will test all numbers from 2 up to the entered number. 
The –t option specifies the number of threads that should be created. 
If it is not spesified, then create 2 threads as default.
The name of the output file  is specified using the –o option.   

Sample Run: 
./FindPrimeNumbersWithMultipleThreads.out  -n 50 -t 4  -o outputfile    
Thread 1 Prime 2
Thread 2 Prime 3 
Thread 3 Prime 5 
…… 
Thread 4 Prime 43 
Thread 2 Prime 47
