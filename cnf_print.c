#include "head.h"

#define EPOCH 1

void Cnf_print(ClauseNode* s,status ans,int* truth_table,char* filename,int literal_num,Order_Table* ot,int* stack,Order_Table* ct,int* Hash){
    clock_t t_start=0,t_end=0;
    for(int i=0;i<EPOCH;i++){
        s=Cnf_Parser(&literal_num,filename,0);
        Make_Constant_Table(s,ct,literal_num);
        t_start=clock();
        Dpll_Solver(s,truth_table,literal_num,ot,stack,ct,Hash);
        t_end+=clock()-t_start;
    }
    int i=0;
    while(filename[i]){
        if(filename[i]=='.'&&filename[i+4]=='\0'){
            filename[i+1]='r';
            filename[i+2]='e';
            filename[i+3]='s';
            break;
        }
        i++;
    }
    FILE* fp=fopen(filename,"w");
    if(!fp){
        printf("Â·¾¶´íÎó\n");
        return ;
    }
    if(ans){
        fprintf(fp,"%c %d\n",'s',1);
        fprintf(fp,"%c ",'v');
        for(int i=1;i<=literal_num;i++) fprintf(fp,"%d ",truth_table[i]);
        fprintf(fp,"\n");
    }
    else{
        fprintf(fp,"%c %d\n",'s',0);
        fprintf(fp,"%c\n",'v');
    }
    fprintf(fp,"%c %ld",'t',t_end/EPOCH);
}
