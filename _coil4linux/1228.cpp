#include<iostream>

using namespace std;
int main()
{
    int buffer[80000];
    int mutex1[80000],mutex2[80000];
    int data_avail[80000];
    int write_iter = 0;
    int com_pointer_1;
    int com_pointer_2;

    //read 40000 points
    printf("40000 read finished\n");

    //process
    int pid;
    if(pid < 0){}
    else if(pid == 0){
        while(1){
            if(data_avail[com_pointer_1]&&data_avail[(com_pointer_1+40000-1)%80000]){
                //set mutex
                for(int i=com_pointer_1;i<(com_pointer_1+40000-1)%80000;i++)
                    mutex1[i]=1;

                //compute
                printf("com1: read data: from %d to %d\n",com_pointer_1,(com_pointer_1+40000-1)%80000);

                //clear flag
                for(int i=com_pointer_1;i<(com_pointer_1+40000-1)%80000;i++){
                    mutex1[i]=0;
                    if(!mutex2[i])
                        data_avail[i]=0;
                }

                //iter
                com_pointer_1 = (com_pointer_1+40000)%80000;
            }
        }
    }
    else{
        int pid2;
        if(pid2<0){
            printf("error pid2\n");
        }
        else if(pid2 == 0){
            usleep(20000);
            while(1){
                if(data_avail[com_pointer_2]&&data_avail[(com_pointer_2+40000-1)%80000]){
                    //set mutex
                    for(int i=com_pointer_2;i<(com_pointer_2+40000-1)%80000;i++)
                        mutex2[i]=1;

                    //compute
                    printf("com2: read data: from %d to %d\n",com_pointer_2,(com_pointer_2+40000-1)%80000);

                    //clear flag
                    for(int i=com_pointer_2;i<(com_pointer_2+40000-1)%80000;i++){
                        mutex2[i]=0;
                        if(!mutex1[i])
                            data_avail[i]=0;
                    }
                    //iter
                    com_pointer_2 = (com_pointer_2+40000)%80000;
                }
        }
        else{
            //main process
            //read data
            while(1){
                if(mutex1[write_iter]||mutex2[write_iter])
                    continue;
                // read new data
                printf("write data: %d\n",write_iter);
                data_avail[write_iter++] = 1;
                
            }
        }
    }
}