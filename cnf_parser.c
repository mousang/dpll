#include "head.h"
#define cnf_size 256

ClauseNode* Cnf_Parser(int* literal_num, char* filename, int init){
    int clause_num;
    char cnf_cut[cnf_size];
    ClauseNode* s;
    FILE* fp=fopen(filename,"r");
    if(!fp){
        printf("Â·¾¶´íÎó\n");
        return ERROR;
    }
    GetInfo(cnf_cut,literal_num,&clause_num,fp);
    if(init) return NULL;
    s=ReadClauses(cnf_cut,fp,literal_num,clause_num);
    fclose(fp);
    return s;
}

status GetInfo(char* cnf_cut,int* literal_num,int* clause_num,FILE* fp){
    while(fgets(cnf_cut,cnf_size,fp)){
        if(cnf_cut[0]=='p') break;
    }
    char* token=strtok(cnf_cut," ");
    token=strtok(NULL," ");
    token=strtok(NULL," ");
    *literal_num=atoi(token);
    token=strtok(NULL," ");
    *clause_num=atoi(token);
    return OK;
}

ClauseNode* ReadClauses(char* cnf_cut,FILE* fp,int* literal_num,int clause_num){
    ClauseNode* root=(ClauseNode*)malloc(sizeof(ClauseNode));
    root->right=NULL;
    root->left=NULL;
    root->num=clause_num;
    ClauseNode* temp=root;
    for(int i=0;i<clause_num;i++){
        temp->down=CreatClauseUnit(cnf_cut,fp);
        temp=temp->down;
    }
    return root;
}

ClauseNode* CreatClauseUnit(char* cnf_cut,FILE* fp){
    ClauseNode* ClauseUnit=(ClauseNode*)malloc(sizeof(ClauseNode));
    ClauseUnit->right=NULL;
    ClauseUnit->down=NULL;
    fscanf(fp,"%s",cnf_cut);
    ClauseUnit->right=CreatLiteralUnit(cnf_cut);
    ClauseUnit->left=CreatLiteralUnit(cnf_cut);
    LiteralNode* LiteralUnit_r=ClauseUnit->right;
    LiteralNode* LiteralUnit_l=ClauseUnit->left;
    LiteralNode* temp_r=NULL;
    LiteralNode* temp_l=NULL;
    fscanf(fp,"%s",cnf_cut);
    int unit_num=1;
    while(strcmp(cnf_cut,"0")){
        temp_r=CreatLiteralUnit(cnf_cut);
        LiteralUnit_r->next=temp_r;
        LiteralUnit_r=LiteralUnit_r->next;
        temp_l=CreatLiteralUnit(cnf_cut);
        LiteralUnit_l->next=temp_l;
        LiteralUnit_l=LiteralUnit_l->next;
        unit_num++;
        fscanf(fp,"%s",cnf_cut);
    }
    ClauseUnit->num=unit_num;
    return ClauseUnit;
}

LiteralNode* CreatLiteralUnit(char* cnf_cut){
    LiteralNode* temp=(LiteralNode*)malloc(sizeof(LiteralNode));
    temp->data=atoi(cnf_cut);
    temp->next=NULL;
    return temp;
}
