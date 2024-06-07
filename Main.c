/**   
* Ezana Girmay
* CSC3350 - Operating Systems Programming 
* Threads Assignment
* Professor Cameron Andy
* 6/4/2024
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

//Thread: Calculate the average of the numbers while coping them over to a new file.
//Input: (const char *) passed in as a void pointer, contains a single letter
//Print out runtime and average of numbers. 
void * AddNum(void * args){  
    //Start run time timer  
    struct timespec sTime, eTime; 
    clock_gettime(CLOCK_MONOTONIC, &sTime);

    //Make file Name
    char *fName = args;
    char mName[18] = "Data_Thread_";
    strcat(mName, fName);
    strcat(mName, ".txt");  

    FILE *fp = fopen(mName, "w");
    FILE *fpp = fopen("Data.txt", "r");
    float numVale, numCount, total;
    int holdNum;
    double runTime;

    //Calculate average and copy numbers to new file
    while (fscanf(fpp, "%d", &holdNum) == 1){
        fprintf(fp, "%d ", holdNum);
        numVale = numVale + holdNum;
        numCount += 1;
    }

    fclose(fp); 
    fclose(fpp);
    total = numVale/numCount;
    
    //Find run time 
    clock_gettime(CLOCK_MONOTONIC, &eTime);
    runTime = ((eTime.tv_sec - sTime.tv_sec)* 1000.0) + ((eTime.tv_nsec - sTime.tv_nsec)/1000000.0);

    printf("Thread %s - Run Time: %f ms | Average: %.2f\n",fName, runTime,total);
    return 0;  
} 


//Make file with random numbers and creat three threads calling Addnum().
//Print out run time
int main() {
    //Start run time timer
    struct timespec sTime, eTime; 
    clock_gettime(CLOCK_MONOTONIC, &sTime);

    //srand(sTime.tv_nsec); //To make the numbers generated in Data.txt randome every time

    //Make file with 1,000,000 numbers
    FILE *fp = fopen("Data.txt", "w");
    for (int i=0; i<1000000; i++){
        int randNum = rand() % 100 + 0;
        fprintf(fp, "%d ", randNum); 
    }
    fclose(fp); 

    //Creat Pthreads and arguments variables
    pthread_t thread1,thread2,thread3;
    const char *aName = "A";
    const char *bName = "B";
    const char *cName = "C";
    pthread_create(&thread1, NULL, AddNum, (void *) aName);
    pthread_create(&thread2, NULL, AddNum, (void *) bName);
    pthread_create(&thread3, NULL, AddNum, (void *) cName);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    //Calculate run time 
    clock_gettime(CLOCK_MONOTONIC, &eTime);
    double totalTime = ((eTime.tv_sec - sTime.tv_sec)* 1000.0) + ((eTime.tv_nsec - sTime.tv_nsec)/1000000.0);

    printf("Wall Clock: %f ms",  totalTime);
    return 0;
}