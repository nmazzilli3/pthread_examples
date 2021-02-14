#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

typedef struct 
{
    uint32_t limit; 
    uint64_t answer;
}sum_runner_t; 


void* sum_runner(void* arg)
{
    uint32_t idx =0; 
    uint64_t overflow = 0;
    sum_runner_t *limit_struct_t = (sum_runner_t*)arg; 
    uint64_t sum = 0;

    for(idx=0;idx<=limit_struct_t->limit;idx++)
    {
        overflow = UINT64_MAX-sum;
        if(overflow > 0)
        {
            if(idx > overflow)
            {
                sum = UINT64_MAX;
            }
            else
            {
                /* code */
                sum += idx;
            }
            
        }
    }

    limit_struct_t->answer = sum;
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
    sum_runner_t arg_t[num_arguments];

    //Thread ID 
    pthread_t tids[num_arguments]; 
    uint16_t idx = 0; 
    for(idx =0;idx<num_arguments;idx++)
    {
        arg_t[idx].limit = atoll(argv[idx+1]);
        pthread_attr_t attr; 
        pthread_attr_init(&attr);
        pthread_create(&tids[idx],&attr,sum_runner,&arg_t[idx]);
    }
    
    for(idx =0;idx<num_arguments;idx++)
    {
        pthread_join(tids[idx],NULL);
        printf("Thread %d had limit of %u which returned sum of %lu\n",idx,arg_t[idx].limit,arg_t[idx].answer);
    }

}