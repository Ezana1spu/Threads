struct tData{
        double time;
        float avg;
        const char *fName;
};

void * AddNum(void * args) 
{  
    //Time
    struct timespec sTime, eTime; 
    clock_gettime(CLOCK_MONOTONIC, &sTime);

    struct tData* tdata = (struct tData *) args;

    //strcat(s1, s2)
    const char leta[] = "A";
    char mName[18] = "Data_Thread_";
    strcat(mName, tdata->fName);
    strcat(mName, ".txt");
    //printf("Thread %s",mName);    

    FILE *fp = fopen(tdata->fName, "w");
    FILE *fpp = fopen("Data.txt", "r");

    float numVale, numCount;
    int holdNum;

    while (fscanf(fpp, "%d", &holdNum) == 1){
        fprintf(fp, "%d ", holdNum);
        numVale = numVale + holdNum;
        numCount += 1;
    }

    fclose(fp); 
    fclose(fpp);
    
    tdata->avg = numVale/numCount;
    
    clock_gettime(CLOCK_MONOTONIC, &eTime);
    tdata->time = ((eTime.tv_sec - sTime.tv_sec)* 1000.0) + ((eTime.tv_nsec - sTime.tv_nsec)/1000000.0);
    printf("Thread %s - Run Time: %f ms | Average: %.2f\n",tdata->fName, tdata->time,tdata->avg);
    return 0;  
} 

int main() {
    struct timespec sTime, eTime; 
    clock_gettime(CLOCK_MONOTONIC, &sTime);

    //srand(time(NULL));
    //Make file
    FILE *fp = fopen("Data.txt", "w");
    for (int i=0; i<1000000; i++){
        int randNum = rand() % 100 + 1;
        fprintf(fp, "%d ", randNum); 
    }
    fclose(fp); 

    //Pthread variables
    pthread_t thread1,thread2,thread3;

    struct tData *threadA = malloc(sizeof(struct tData));
    threadA->fName = "Data_Thread_A.txt";
    struct tData *threadB = malloc(sizeof(struct tData));
    threadB->fName = "Data_Thread_B.txt";
    struct tData *threadC = malloc(sizeof(struct tData));
    threadC->fName = "Data_Thread_C.txt";


    pthread_create(&thread1, NULL, AddNum, threadA);
    pthread_create(&thread2, NULL, AddNum, threadB);
    pthread_create(&thread3, NULL, AddNum, threadC);


    //RunTime
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    
    //printf("Thread A - Run Time: %f ms | Average: %.2f\n", threadA->time,threadA->avg);
    printf("Thread B - Run Time: %f ms | Average: %.2f\n", threadB->time,threadB->avg);
    printf("Thread C - Run Time: %f ms | Average: %.2f\n", threadC->time,threadC->avg);
    free(threadA);
    free(threadB);
    free(threadC);
    clock_gettime(CLOCK_MONOTONIC, &eTime);
    double totalTime = ((eTime.tv_sec - sTime.tv_sec)* 1000.0) + ((eTime.tv_nsec - sTime.tv_nsec)/1000000.0);
    printf("Wall CLock: %f ms",  totalTime);
    return 0;
}