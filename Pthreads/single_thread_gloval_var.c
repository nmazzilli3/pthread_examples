#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

uint64_t sum = 0;

void* sum_runner(void* arg)
{
    uint32_t idx =0; 
    uint64_t overflow = 0;
    uint32_t *limit_ptr = (uint32_t*)arg; 
    uint32_t limit = *limit_ptr;

    for(idx=0;idx<=limit;idx++)
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

    pthread_exit(0);
}

int main(int argc,char **argv)
{
    if(argc<2)
    {
        printf("Usage: %s <num>\n",argv[0]);
        exit(-1);
    }

    uint32_t limit = atoll(argv[1]);

    //Thread ID 
    pthread_t tid; 

    //Attributes
    pthread_attr_t attr; 
    pthread_attr_init(&attr); 

    pthread_create(&tid,&attr,sum_runner,&limit);

    //Wait until thread is done 
    pthread_join(tid,NULL);
    printf("Sum is %lu \n",sum);
}