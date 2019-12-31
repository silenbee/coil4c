#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<vector>
#include<string>
#include<string.h>
#include<unistd.h>
#include <sys/shm.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/time.h>
#include"fftw3.h"
#include"readData.h"

struct shareMemory{
    int is_write = 0;
    int index = 0;
    int data[2000];
};

using namespace std;
int main()
{
    int buffer[80000];
    int mutex1[80000],mutex2[80000];
    int data_avail[80000];
    int write_iter = 0;
    int com_pointer_1;
    int com_pointer_2;
    int running = 1;
    // shm
    key_t  key_n ;
    int shm_id;
    void *shm = NULL;
    struct shareMemory *shared;

    if((key_n = ftok("/",'s')<0))  //生成共享内存的key值
    {
        perror("Fail to ftok");
        exit(EXIT_SUCCESS);
    }
    printf("key num:%d\n",key_n);
 
    if((shm_id = shmget(key_n,1024,0666|IPC_CREAT))==-1)  //创建共享内存
    {
        perror("Fail to shmget");
        exit(EXIT_SUCCESS);
    }
    printf("share memory id:%d\n",shm_id);


    //read 40000 points
    printf("40000 read finished\n");

    //process
    pid_t pid = fork();
    if(pid < 0){
        perror("error fork pid1 \n");
        exit(EXIT_SUCCESS);
    }
    else if(pid == 0){
        shm = shmat(shm_id,0,0);                     //将共享内存连接到当前进程的地址空间
        if(shm==(void *)-1)
        {
            perror("Fail to shmat");
            exit(EXIT_SUCCESS);
        }
        //printf("pid1 Memory attached at %x\n",(int)shm);

        shared = (struct shareMemory *)shm;        //设置共享内存
        // shared->is_write = 1;

        // above are testing shm
        while(running){
           
            if(shared->is_write!=1)
            {
                shared->is_write = 1;
                printf("You worte:%d integers\n",shared->index);
                for(int i=0;i<shared->index;i++){
                    printf("%d ",shared->data[i]);
                }
                printf("\n");
                shared->is_write = 0;
 
                // if(strncmp(shared->data,"end",3)==0)  //输入end退出循环
                // {
                //     running = 0;
                // }
                // else      //有其他进程在写数据，不能读
                //     sleep(1);
            }
        
        //     if(data_avail[com_pointer_1]&&data_avail[(com_pointer_1+40000-1)%80000]){
        //         //set mutex
        //         for(int i=com_pointer_1;i<(com_pointer_1+40000-1)%80000;i++)
        //             mutex1[i]=1;

        //         //compute
        //         printf("com1: read data: from %d to %d\n",com_pointer_1,(com_pointer_1+40000-1)%80000);

        //         //clear flag
        //         for(int i=com_pointer_1;i<(com_pointer_1+40000-1)%80000;i++){
        //             mutex1[i]=0;
        //             if(!mutex2[i])
        //                 data_avail[i]=0;
        //         }

        //         //iter
        //         com_pointer_1 = (com_pointer_1+40000)%80000;
        //     }
        
        printf("pid 1 is running\n");
        sleep(2);
        }
    }
    else{
        pid_t pid2 = fork();
        if(pid2<0){
            perror("error pid2\n");
            exit(EXIT_SUCCESS);
        }
        else if(pid2 == 0){
            // usleep(20000);

            shm = shmat(shm_id,0,0);                     //将共享内存连接到当前进程的地址空间
            if(shm==(void *)-1)
            {
                perror("Fail to shmat");
                exit(EXIT_SUCCESS);
            }
            // printf("pid2 Memory attached at %x\n",(int)shm);
    
            shared = (struct shareMemory *)shm;        //设置共享内存
            // shared->is_write = 1;
 
            sleep(2);
            while(running){

                if(shared->is_write == 0){
                    //向共享内存中写入数据
                    shared->is_write = 1;
                    printf("write in pid2:\n");
                    shared->data[shared->index] = shared->index+5;
                    shared->index++;
                    shared->is_write = 0;        //写完数据后，置1使可读
                }

    
            
                // if(data_avail[com_pointer_2]&&data_avail[(com_pointer_2+40000-1)%80000]){
                //     //set mutex
                //     for(int i=com_pointer_2;i<(com_pointer_2+40000-1)%80000;i++)
                //         mutex2[i]=1;

                //     //compute
                //     printf("com2: read data: from %d to %d\n",com_pointer_2,(com_pointer_2+40000-1)%80000);

                //     //clear flag
                //     for(int i=com_pointer_2;i<(com_pointer_2+40000-1)%80000;i++){
                //         mutex2[i]=0;
                //         if(!mutex1[i])
                //             data_avail[i]=0;
                //     }
                //     //iter
                //     com_pointer_2 = (com_pointer_2+40000)%80000;
                // }
                printf("pid 2 is running\n");
                sleep(3);
            }
        }
        else{
            //main process
            //read data
            while(running){
                // if(mutex1[write_iter]||mutex2[write_iter])
                //     continue;
                // // read new data
                // printf("write data: %d\n",write_iter);
                // data_avail[write_iter++] = 1;
                printf("main process running\n");
                sleep(5);
              
            }
        }
    }

}