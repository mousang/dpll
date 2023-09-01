#include "head.h"
#define PATH_SIZE 1024

int main()
{
    int option,h_op;
    int literal_num;
    ClauseNode* use;
    char filename[PATH_SIZE];
    system("cls"); printf("\n");
    printf("             Menu for SAT \n");
    printf("----------------------------------------\n");
    printf("       1. SAT       2. Hanidoku\n");
    printf("       0. Exit\n");
    printf("----------------------------------------\n");
    printf("       请选择你的操作:");
    scanf("%d",&option);
    system("cls");
    while(option){
        if(option==1){
            printf("请输入cnf文件名：");
            strcpy(filename, ChooseExample());
            Cnf_Parser(&literal_num,filename,1);
            int* Hash=(int*)malloc((literal_num+1)*sizeof(int));//哈希表，用于回溯的判定
            int* truth_table=(int*)malloc((literal_num+1)*sizeof(int));//真值表
            int* stack=(int*)malloc((literal_num+1)*sizeof(int));//存储每次选出变元的栈
            use=Cnf_Parser(&literal_num,filename,0);
            Order_Table ot[literal_num+1];//是用于存储每次选出变元后删除子句和删除文字头节点的表
            Order_Table ct[literal_num+1];//类似于十字链表的存储文字在邻接表中位置的表
            init(literal_num,Hash,truth_table,ot,ct,stack);
            Make_Constant_Table(use,ct,literal_num);
            int ans=Dpll_Solver(use,truth_table,literal_num,ot,stack,ct,Hash);
            Cnf_print(use,ans,truth_table,filename,literal_num,ot,stack,ct,Hash);//转出.res文件
            printf("FINISHED\n");
            //重新读取文件并判断真值表是否正确
            int i=0;
            while(filename[i]){
                if(filename[i]=='.'&&filename[i+4]=='\0'){
                    filename[i+1]='c';
                    filename[i+2]='n';
                    filename[i+3]='f';
                    break;
                }
                i++;
            }
            Cnf_Parser(&literal_num,filename,1);
            use=Cnf_Parser(&literal_num,filename,0);
            check(use,truth_table);
        }
        else if(option==2){
            printf("请选择难度 困难（1）简单（0）:");//困难基本算不出来
            scanf("%d",&h_op);
            system("cls");
            Hanidoku_Game(h_op);
        }
        getchar();
        getchar();
        system("cls"); printf("\n");
        printf("             Menu for SAT \n");
        printf("----------------------------------------\n");
        printf("       1. SAT       2. Hanidoku\n");
        printf("       0. Exit\n");
        printf("----------------------------------------\n");
        printf("       请选择你的操作:");
        scanf("%d",&option);
        system("cls");
    }
    printf("Thank you for participating!\n");
    return 0;
}


char* ChooseExample(void){
    static char filename[PATH_SIZE];
    scanf("%s",filename);
    return filename;
}

void init(int literal_num,int* Hash,int* truth_table,Order_Table* ot,Order_Table* ct,int* stack){
    for(int i=0;i<=literal_num;i++){
        ot[i].right=NULL;
        ct[i].right=NULL;
        truth_table[i]=0;
        Hash[i]=0;
        stack[i]=0;
    }
}

void Make_Constant_Table(ClauseNode* s,Order_Table* ct,int literal_num){
    ClauseNode* s_temp=s->down;
    while(s_temp){
        LiteralNode* l_temp=s_temp->right;
        while(l_temp){
            To_Clause* c_temp=(To_Clause*)malloc(sizeof(To_Clause));
            c_temp->sign=(l_temp->data)/abs(l_temp->data);
            c_temp->target=s_temp;
            c_temp->next=ct[abs(l_temp->data)].right;
            ct[abs(l_temp->data)].right=c_temp;
            l_temp=l_temp->next;
        }
        s_temp=s_temp->down;
    }
}

void check(ClauseNode* s,int *truth_table){
    ClauseNode* s_temp=s->down;
    while(s_temp){
        LiteralNode* l_temp=s_temp->right;
        int flag=0;
        while(l_temp){
            if(l_temp->data==truth_table[abs(l_temp->data)]) flag=1;
            l_temp=l_temp->next;
        }
        if(!flag) break;
        s_temp=s_temp->down;
    }
    if(s_temp) printf("wrong");
    else printf("right");
}
//C:\\Users\\mjh\\Desktop\\dpll_advanced\\dpll_example\\sat-20.cnf
//C:\\Users\\mjh\\Desktop\\dpll_advanced\\dpll_example\self.cnf
//C:\\Users\\mjh\\Desktop\\dpll_advanced\\dpll_example\\ais10.cnf
//C:\\Users\\mjh\\Desktop\\dpll_advanced\\dpll_example\\problem1-20.cnf
//C:\\Users\\mjh\\Desktop\\dpll_advanced\\dpll_example\\m-mod2c-rand3bip-sat-240-2.shuffled-as.sat05-2519-338.cnf
//C:\\Users\\mjh\\Desktop\\dpll_final\\example\\Hanidoku.cnf
/*
1 4 3
2 1 4
2 2 3
3 5 1
4 3 9
5 1 3
5 2 8
5 3 7
5 6 1
5 9 6
6 4 9
7 9 2
8 8 4
*/
//C:\\Users\\mjh\\Desktop\\假期作业\\程序设计综合课程设计任务及指导学生包(1)\\程序设计综合课程设计任务及指导学生包\\SAT测试备选算例\\满足算例\\M\\ec-mod2c-rand3bip-sat-250-2.shuffled-as.sat05-2534.cnf
