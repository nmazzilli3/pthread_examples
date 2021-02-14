#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>


typedef struct 
{
    uint32_t limit; 
    uint64_t answer;
}sum_runner_t; 

/*Best Practice to place mutex in struct to remind everyone of shared data */
typedef struct
{
    pthread_mutex_t mutex;
    uint64_t sum;
}sum_mutex_t; 

sum_mutex_t mutex_t = {.mutex = PTHREAD_MUTEX_INITIALIZER,.sum = 0}; 


void* sum_runner(void* arg)
{
    uint32_t idx =0; 
    uint64_t overflow = 0;
    uint32_t *limit_ptr = (uint32_t*)arg; 
    uint32_t limit = *limit_ptr;

    for(idx=0;idx<=limit;idx++)
    {
        pthread_mutex_lock(&mutex_t.mutex);
        overflow = UINT64_MAX-mutex_t.sum;
        if(overflow > 0)
        {
            if(idx > overflow)
            {
                mutex_t.sum = UINT64_MAX;
            }
            else
            {
                /* code */
                mutex_t.sum += idx;
            }
            
        }
        pthread_mutex_unlock(&mutex_t.mutex);
    }

    pthread_exit(0);
}

int main(int argc,char **argv)
{
    if(argc<2)
    {
        printf("Usage: %s <num>\n",argv[0]);
        exit(-1);
    }

    uint16_t num_arguments = argc-1;
    uint32_t limits[num_arguments];

    //Thread ID 
    pthread_t tids[num_arguments]; 
    uint16_t idx = 0; 
    for(idx =0;idx<num_arguments;idx++)
    {
        limits[idx] = atoll(argv[idx+1]);
        pthread_attr_t attr; 
        pthread_attr_init(&attr);
        pthread_create(&tids[idx],&attr,sum_runner,&limits[idx]);
    }
    
    for(idx =0;idx<num_arguments;idx++)
    {
        pthread_join(tids[idx],NULL);
        printf("Thread %d had limit of %u which returned sum of %lu\n",idx,limits[idx],mutex_t.sum);
    }

}

