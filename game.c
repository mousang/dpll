#include "head.h"
#define PATH_SIZE 1024

//void init_all(ClauseNode* s,Order_Table* ot,Order_Table* ct,int literal_num,int (*h_table)[11]);

void Hanidoku_Game(int n){
    int h_table[11][11];
    int left[10],right[10];
    for(int i=1;i<=9;i++){
        left[i]=i-4>1?i-4:1;
        right[i]=i+4<9?i+4:9;
    }
    char txt_content[70];
    FILE* fp=NULL;
    if(n==0) fp=fopen("C:\\Users\\mjh\\Desktop\\dpll_final\\easy_hanidoku.txt","r");
    else fp=fopen("C:\\Users\\mjh\\Desktop\\dpll_final\\hard_hanidoku.txt","r");
    srand((unsigned)time(NULL));
    int rand_num;
    if(n==0) rand_num=1+rand()%5190;
    else rand_num=1+rand()%1050;
    for(int i=1;i<rand_num;i++) fscanf(fp,"%*[^\n]%*c");
    fscanf(fp,"%s",txt_content);
    for(int i=0;i<=10;i++){
        for(int j=0;j<=10;j++){
            h_table[i][j]=0;
        }
    }
    int num=0;
    for(int i=5;i<=65;i++) if(txt_content[i]!='0') num++;
    int order=5;
    for(int i=1;i<=9;i++){
        for(int j=left[i];j<=right[i];j++){
            if(txt_content[order]!='0') h_table[i][j]=(int)(txt_content[order]-'0');
            order++;
        }
    }
    for(int i=1;i<=9;i++){
        if(i>5) for(int j=1;j<left[i]-1;j++) printf("  ");
        else for(int j=9;j>right[i];j--) printf("  ");
        printf(" ");
        if(i<=5) for(int j=1;j<=right[i];j++) printf("/ \\ ");
        else for(int j=1;j<=11-left[i];j++) printf("\\ / ");
        printf("\n");
        if(i>5) for(int j=1;j<left[i];j++) printf("  ");
        else for(int j=9;j>right[i];j--) printf("  ");
        printf("\| ");
        for(int j=left[i];j<=right[i];j++){
            if(h_table[i][j]==0) printf(". \| ");
            else printf("%d \| ",h_table[i][j]);
        }
        printf("\n");
    }
    for(int i=1;i<=4;i++) printf("  ");
    printf(" ");
    for(int i=1;i<=5;i++) printf("\\ / ");
    printf("\n");
    Hanidoku_Transform(num,h_table);
    int literal_num;
    ClauseNode* use;
    char filename[PATH_SIZE]="C:\\Users\\mjh\\Desktop\\dpll_final\\example\\Hanidoku.cnf";
    Cnf_Parser(&literal_num,filename,1);
    int* Hash=(int*)malloc((literal_num+1)*sizeof(int));
    int* truth_table=(int*)malloc((literal_num+1)*sizeof(int));
    int* stack=(int*)malloc((literal_num+1)*sizeof(int));
    Order_Table ot[literal_num+1];
    Order_Table ct[literal_num+1];
    use=Cnf_Parser(&literal_num,filename,0);
    init(literal_num,Hash,truth_table,ot,ct,stack);
    Make_Constant_Table(use,ct,literal_num);
    Dpll_Solver(use,truth_table,literal_num,ot,stack,ct,Hash);
    int s_table[62];
    int s_order=0;
    for(int i=1;i<=literal_num;i++){
        if(truth_table[i]>0) s_table[++s_order]=truth_table[i];
    }
    s_order=0;
    //init_all(use,ot,ct,literal_num,h_table);
    int option;
    printf("Please choose to participate in solving (1) or see the answer (0): ");
    scanf("%d",&option);
    if(option==0){
        system("cls");
        printf("Hanidoku was solved as follows\n");
        for(int i=1;i<=9;i++){
            if(i>5) for(int j=1;j<left[i]-1;j++) printf("  ");
            else for(int j=9;j>right[i];j--) printf("  ");
            printf(" ");
            if(i<=5) for(int j=1;j<=right[i];j++) printf("/ \\ ");
            else for(int j=1;j<=11-left[i];j++) printf("\\ / ");
            printf("\n");
            if(i>5) for(int j=1;j<left[i];j++) printf("  ");
            else for(int j=9;j>right[i];j--) printf("  ");
            printf("| ");
            for(int j=left[i];j<=right[i];j++) printf("%d \| ",s_table[++s_order]%10);
            printf("\n");
        }
        for(int i=1;i<=4;i++) printf("  ");
        printf(" ");
        for(int i=1;i<=5;i++) printf("\\ / ");
        printf("\n");
    }
    else{
        printf("Please enter the value according to the regulations\nsuch as 111,which means filling in 1 at (1,1).If you want to see the answer, enter 0.\n");
        printf("your choice: ");
        int p_num;
        scanf("%d",&p_num);
        while(p_num!=0){
            int x,y,value;
            value=p_num%10;
            p_num/=10;
            y=p_num%10;
            p_num/=10;
            x=p_num;
            int xu=0;
            for(int i=1;i<=x;i++){
                for(int j=left[i];j<=right[i];j++){
                    xu++;
                    if(i==x&&j-left[i]+1==y) break;
                }
            }
            if(s_table[xu]%10==value){
                system("cls");
                printf("You are right!\n");
                h_table[x][y+left[x]-1]=value;
                for(int i=1;i<=9;i++){
                    if(i>5) for(int j=1;j<left[i]-1;j++) printf("  ");
                    else for(int j=9;j>right[i];j--) printf("  ");
                    printf(" ");
                    if(i<=5) for(int j=1;j<=right[i];j++) printf("/ \\ ");
                    else for(int j=1;j<=11-left[i];j++) printf("\\ / ");
                    printf("\n");
                    if(i>5) for(int j=1;j<left[i];j++) printf("  ");
                    else for(int j=9;j>right[i];j--) printf("  ");
                    printf("\| ");
                    for(int j=left[i];j<=right[i];j++){
                        if(h_table[i][j]==0) printf(". \| ");
                        else printf("%d \| ",h_table[i][j]);
                    }
                    printf("\n");
                }
                for(int i=1;i<=4;i++) printf("  ");
                printf(" ");
                for(int i=1;i<=5;i++) printf("\\ / ");
                printf("\n");
            }
            else{
                system("cls");
                printf("You are wrong,please try again!\n");
                for(int i=1;i<=9;i++){
                    if(i>5) for(int j=1;j<left[i]-1;j++) printf("  ");
                    else for(int j=9;j>right[i];j--) printf("  ");
                    printf(" ");
                    if(i<=5) for(int j=1;j<=right[i];j++) printf("/ \\ ");
                    else for(int j=1;j<=11-left[i];j++) printf("\\ / ");
                    printf("\n");
                    if(i>5) for(int j=1;j<left[i];j++) printf("  ");
                    else for(int j=9;j>right[i];j--) printf("  ");
                    printf("\| ");
                    for(int j=left[i];j<=right[i];j++){
                        if(h_table[i][j]==0) printf(". \| ");
                        else printf("%d \| ",h_table[i][j]);
                    }
                    printf("\n");
                }
                for(int i=1;i<=4;i++) printf("  ");
                printf(" ");
                for(int i=1;i<=5;i++) printf("\\ / ");
                printf("\n");
            }
            printf("your choice: ");
            scanf("%d",&p_num);
        }
        system("cls");
        printf("Hanidoku was solved as follows\n");
        for(int i=1;i<=9;i++){
            if(i>5) for(int j=1;j<left[i]-1;j++) printf("  ");
            else for(int j=9;j>right[i];j--) printf("  ");
            printf(" ");
            if(i<=5) for(int j=1;j<=right[i];j++) printf("/ \\ ");
            else for(int j=1;j<=11-left[i];j++) printf("\\ / ");
            printf("\n");
            if(i>5) for(int j=1;j<left[i];j++) printf("  ");
            else for(int j=9;j>right[i];j--) printf("  ");
            printf("| ");
            for(int j=left[i];j<=right[i];j++) printf("%d \| ",s_table[++s_order]%10);
            printf("\n");
        }
        for(int i=1;i<=4;i++) printf("  ");
        printf(" ");
        for(int i=1;i<=5;i++) printf("\\ / ");
        printf("\n");
    }
    return;
}

/*void Hanidoku_Game(int n){
    int h_table[11][11];
    srand((unsigned)time(NULL));
    int left[10],right[10];
    for(int i=1;i<=9;i++){
        left[i]=i-4>1?i-4:1;
        right[i]=i+4<9?i+4:9;
    }
    int ans;
    do{
        for(int i=0;i<=10;i++){
            for(int j=0;j<=10;j++){
                h_table[i][j]=0;
            }
        }
        //int x,y,num=1;
        while(num<=9){
            x=1+rand()%9;
            y=left[x]+rand()%(right[x]-left[x]+1);
            if(h_table[x][y]==0){
                h_table[x][y]=num;
                num++;
            }
            else continue;
        //}
        int num[10];
        for(int i=0;i<=9;i++) num[i]=i;
        for(int i=9;i>1;i--){
            int randnum=rand()%i+1;
			if (i!=randnum){
				int temp=num[i];
                num[i]=num[randnum];
				num[randnum]=temp;
			}
        }
        for(int i=1;i<=9;i++) h_table[5][i]=num[i];
        Hanidoku_Transform(9,h_table);
        int literal_num;
        ClauseNode* use;
        char filename[PATH_SIZE]="C:\\Users\\mjh\\Desktop\\dpll_final\\example\\Hanidoku.cnf";
        Cnf_Parser(&literal_num,filename,1);
        int* truth_table=(int*)malloc((literal_num+1)*sizeof(int));
        int* stack=(int*)malloc((literal_num+1)*sizeof(int));
        Order_Table ot[literal_num+1];
        Order_Table ct[literal_num+1];
        use=Cnf_Parser(&literal_num,filename,0);
        init(literal_num,truth_table,ot,stack);
        Make_Constant_Table(use,ct,literal_num);
        ans=Dpll_Solver(use,truth_table,literal_num,ot,stack,ct);

        //init_all(use,ot,ct,literal_num,h_table);
        printf("%d",ans);
    }while(ans==0);
    return;
}*/

/*void init_all(ClauseNode* s,Order_Table* ot,Order_Table* ct,int literal_num,int (*h_table)[11]){
    s->num=0;
    ClauseNode* s_temp=s->down;
    while(s_temp){
        LiteralNode* l_temp=s_temp->right;
        while(l_temp){
            s_temp->right=l_temp->next;
            free(l_temp);
            l_temp=s_temp->right;
        }
        s->down=s->down->down;
        free(s_temp);
        s_temp=s->down;
    }
    for(int i=1;i<=literal_num;i++){
        To_Clause* c_temp=ot[i].right;
        if(c_temp){
            ot[i].right=c_temp->next;
            ClauseNode* sc_temp=c_temp->target;
            if(sc_temp){
                LiteralNode* lc_temp=sc_temp->right;
                while(lc_temp){
                    sc_temp->right=lc_temp->next;
                    free(lc_temp);
                    lc_temp=sc_temp->right;
                }
                c_temp->target=NULL;
                free(sc_temp);
            }
            c_temp->target=NULL;
            free(c_temp);
            c_temp=ot[i].right;
        }
        c_temp=ct[i].right;
        if(c_temp){
            ct[i].right=c_temp->next;
            c_temp->target=NULL;
            free(c_temp);
            c_temp=ct[i].right;
        }
    }
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            h_table[i][j]=0;
        }
    }
    return;
}*/
