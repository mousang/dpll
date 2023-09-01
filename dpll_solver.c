#include "head.h"

status Dpll_Solver(ClauseNode* s,int* truth_table,int literal_num,Order_Table* ot,int* stack,Order_Table* ct,int* Hash){
    int operate_times=0;
    ClauseNode* s_temp=s;
    ClauseNode* unit_clause=HasUnitClause(s_temp);
    while(unit_clause){
        operate_times++;
        int unit_data=unit_clause->right->data;
        //printf("%d ",unit_data);
        truth_table[abs(unit_data)]=unit_data;
        stack[0]++;
        stack[stack[0]]=unit_data;
        Remove_Unit(s,unit_data,&ot[abs(unit_data)],&ct[abs(unit_data)]);
        if(s->num==0||s->down==NULL){
            Back_Track(operate_times,s,stack,ot);
            return FOUND;
        }
        ClauseNode* s_hash=HasEmptyClause(s);
        if(s_hash){
            LiteralNode* l_hash=s_hash->left;
            while(l_hash){
                Hash[abs(l_hash->data)]=1;
                l_hash=l_hash->next;
            }
            Back_Track(operate_times,s,stack,ot);
            return NOTFOUND;
        }
        s_temp=s;
        unit_clause=HasUnitClause(s_temp);
    }
    int var=PickVar(s,literal_num);
    int i;
    for(i=stack[0];i>stack[0]-operate_times;i--){
        if(Hash[stack[i]]) break;
    }
    if(Dpll_Solver(Add_Unit_Clause(s,var),truth_table,literal_num,ot,stack,ct,Hash)){
        Back_Track(operate_times,s,stack,ot);
        return FOUND;
    }
    else if(i==stack[stack[0]]-operate_times){
        Back_Track(operate_times,s,stack,ot);
        return NOTFOUND;
    }
    else if(Dpll_Solver(Add_Unit_Clause(s,-var),truth_table,literal_num,ot,stack,ct,Hash)){
        for(i=stack[0];i>stack[0]-operate_times;i--){
            if(Hash[abs(stack[i])]) Hash[abs(stack[i])]=0;
        }
        Back_Track(operate_times,s,stack,ot);
        return FOUND;
    }
    else{
        Back_Track(operate_times,s,stack,ot);
        return NOTFOUND;
    }
}

ClauseNode* HasUnitClause(ClauseNode* s){
    ClauseNode* s_temp=s->down;
    while(s_temp){
        if(s_temp->num==1) return s_temp;
        s_temp=s_temp->down;
    }
    return NULL;
}

void Remove_Unit(ClauseNode* s,int unit_data,Order_Table* ot,Order_Table* ct){
    To_Clause* c_temp=ct->right;
    while(c_temp){
        if(c_temp->target->down==c_temp->target){
            c_temp=c_temp->next;
            continue;
        }
        if((c_temp->sign==1&&unit_data>0)||(c_temp->sign==-1&&unit_data<0)) c_temp->target->num=-c_temp->target->num;
        else DeleteLiteral(c_temp->target,unit_data,ot);
        c_temp=c_temp->next;
    }
    ClauseNode* s_1=s;
    ClauseNode* s_2=s->down;
    while(s_2){
        if(s_2->num<0){
            s_2->num=-s_2->num;
            s_2=DeleteClause(s_1->down,ot);
            s_1->down=s_2;
            s->num--;
            continue;
        }
        if(s_2==NULL) break;
        s_1=s_2;
        s_2=s_2->down;
    }
    if(s->down&&s->down->right&&s->down->right->data==unit_data){
        s->num--;
        ClauseNode* s_temp=s->down;
        s->down=s->down->down;
        free(s_temp->right);
        s_temp->down=NULL;
        free(s_temp);
    }
}

void DeleteLiteral(ClauseNode* s,int unit_data,Order_Table* ot){
    LiteralNode *l=s->right,*l_temp=NULL;
    if(l&&l->data==-unit_data){
        l_temp=s->right->next;
        To_Clause* c_temp=(To_Clause*)malloc(sizeof(To_Clause));
        if(!c_temp) printf("No available space");
        c_temp->sign=-1;
        c_temp->target=s;
        c_temp->next=ot->right;
        ot->right=c_temp;
        free(l);
        s->right=l_temp;
        s->num--;
        return;
    }
    while(l){
        if(l->next&&l->next->data==-unit_data){
            l_temp=l->next;
            l->next=l->next->next;
            To_Clause* c_temp=(To_Clause*)malloc(sizeof(To_Clause));
            if(!c_temp) printf("No available space");
            c_temp->sign=-1;
            c_temp->target=s;
            c_temp->next=ot->right;
            ot->right=c_temp;
            free(l_temp);
            s->num--;
            return;
        }
        l=l->next;
    }
    return;
}

ClauseNode* DeleteClause(ClauseNode* s,Order_Table* ot){
    To_Clause* c_temp=(To_Clause*)malloc(sizeof(To_Clause));
    if(!c_temp) printf("No available space");
    c_temp->sign=1;
    c_temp->target=s;
    c_temp->next=ot->right;
    ot->right=c_temp;
    ClauseNode* s_temp=s;
    s=s->down;
    s_temp->down=s_temp;
    return s;
}

ClauseNode* HasEmptyClause(ClauseNode* s){
    ClauseNode* s_temp=s->down;
    while(s_temp){
        if(!s_temp->num) return s_temp;
        s_temp=s_temp->down;
    }
    return NULL;
}

/*int PickVar(ClauseNode* s,int literal_num){
    return s->down->right->data;
}*/

int PickVar(ClauseNode* s,int literal_num){
    int min_len=100;
    ClauseNode* s_temp=s->down;
    while(s_temp){
        if(min_len>s_temp->num) min_len=s_temp->num;
        s_temp=s_temp->down;
    }
    int* x=(int*)malloc((literal_num+1)*sizeof(int));
    if(!x) printf("No available space");
    int* y=(int*)malloc((literal_num+1)*sizeof(int));
    if(!x) printf("No available space");
    int* f=(int*)malloc((literal_num+1)*sizeof(int));
    if(!x) printf("No available space");
    for(int i=0;i<=literal_num;i++){
        x[i]=y[i]=f[i]=0;
    }
    s_temp=s->down;
    while(s_temp){
        if(s_temp->num!=min_len){
            s_temp=s_temp->down;
            continue;
        }
        LiteralNode* l_temp=s_temp->right;
        while(l_temp){
            if(l_temp->data>0) x[l_temp->data]++;
            else y[-l_temp->data]++;
            l_temp=l_temp->next;
        }
        s_temp=s_temp->down;
    }
    int max_f=0;
    int target=0;
    for(int i=1;i<=literal_num;i++){
        f[i]=(x[i]+1)*(y[i]+1);
        if(f[i]==1) continue;
        if(max_f<f[i]){
            max_f=f[i];
            target=i;
        }
    }
    if(x[target]>y[target]){
        free(x);
        free(y);
        free(f);
        return target;
    }
    free(x);
    free(y);
    free(f);
    return -target;
}

/*int PickVar(ClauseNode* s,int literal_num){
    int min_len=100;
    ClauseNode* s_temp=s->down;
    while(s_temp){
        if(min_len>s_temp->num) min_len=s_temp->num;
        s_temp=s_temp->down;
    }
    int* x=(int*)malloc((literal_num+1)*sizeof(int));
    if(!x) printf("No available space");
    int* y=(int*)malloc((literal_num+1)*sizeof(int));
    if(!x) printf("No available space");
    double* f=(double*)malloc((literal_num+1)*sizeof(double));
    if(!x) printf("No available space");
    for(int i=0;i<=literal_num;i++){
        x[i]=y[i]=0;
        f[i]=0.0;
    }
    s_temp=s->down;
    while(s_temp){
        if(s_temp->num!=min_len){
            s_temp=s_temp->down;
            continue;
        }
        LiteralNode* l_temp=s_temp->right;
        while(l_temp){
            if(l_temp->data>0) x[l_temp->data]++;
            else y[-l_temp->data]++;
            l_temp=l_temp->next;
        }
        s_temp=s_temp->down;
    }
    double max_f=0;
    int target=0;
    for(int i=1;i<=literal_num;i++){
        f[i]=log2(x[i]+1.1)*log2(y[i]+1.1);
        if(max_f<f[i]){
            max_f=f[i];
            target=i;
        }
    }
    if(x[target]>=y[target]){
        free(x);
        free(y);
        free(f);
        return target;
    }
    free(x);
    free(y);
    free(f);
    return -target;
}*/

/*int PickVar(ClauseNode* s,int literal_num){
    int min_len=100;
    ClauseNode* s_temp=s->down;
    ClauseNode* ans=NULL;
    while(s_temp){
        if(min_len>s_temp->num){
            ans=s_temp;
            min_len=s_temp->num;
            if(min_len<3) break;
        }
        s_temp=s_temp->down;
    }
    return -ans->right->data;
}*/

/*int PickVar(ClauseNode* s,int literal_num){
    double* pos=(double*)malloc((literal_num+1)*sizeof(double));
    if(!pos) printf("No available space");
    double* neg=(double*)malloc((literal_num+1)*sizeof(double));
    if(!neg) printf("No available space");
    for(int i=0;i<=literal_num;i++){
        pos[i]=neg[i]=0.0;
    }
    ClauseNode* s_temp=s->down;
    int l_data=0;
    while(s_temp){
        LiteralNode* l_temp=s_temp->right;
        while(l_temp){
            l_data=l_temp->data;
            if(l_data>0) pos[l_data]+=pow(0.5,(double)(s_temp->num-1));
            else neg[-l_data]+=pow(0.5,(double)(s_temp->num-1));
            l_temp=l_temp->next;
        }
        s_temp=s_temp->down;
    }
    double max_count=0.0;
    int ans=0;
    for(int i=1;i<=literal_num;i++){
        if(max_count<pos[i]+neg[i]){
            ans=i;
            max_count=pos[i]+neg[i];
        }
    }
    if(pos[ans]>neg[ans]){
        free(pos);
        free(neg);
        return ans;
    }
    free(pos);
    free(neg);
    return -ans;
}*/

ClauseNode* Add_Unit_Clause(ClauseNode* s,int var){
    ClauseNode* adding=(ClauseNode*)malloc(sizeof(ClauseNode));
    if(!adding) printf("No available space");
    adding->num=1;
    adding->right=(LiteralNode*)malloc(sizeof(LiteralNode));
    if(!adding->right) printf("No available space");
    adding->right->data=var;
    adding->right->next=NULL;
    adding->down=s->down;
    s->down=adding;
    s->num++;
    return s;
}

void Back_Track(int operate_times,ClauseNode* s,int* stack,Order_Table* ot){
    int re_num;
    for(int i=0;i<operate_times;i++){
        re_num=stack[stack[0]];
        stack[0]--;
        Unit_Back_Track(s,&ot[abs(re_num)],re_num);
    }
}

void Unit_Back_Track(ClauseNode* s,Order_Table* ot,int re_num){
    To_Clause* c_temp=ot->right;
    while(c_temp){
        if(c_temp->sign==1){
            ot->right=c_temp->next;
            c_temp->target->down=s->down;
            s->down=c_temp->target;
            c_temp->target=NULL;
            free(c_temp);
            c_temp=ot->right;
            s->num++;
        }
        else{
            ot->right=c_temp->next;
            LiteralNode* l_temp=(LiteralNode*)malloc(sizeof(LiteralNode));
            if(!l_temp) printf("No available space");
            c_temp->target->num++;
            l_temp->data=-re_num;
            l_temp->next=c_temp->target->right;
            c_temp->target->right=l_temp;
            c_temp->target=NULL;
            free(c_temp);
            c_temp=ot->right;
        }
    }
    ot->right=NULL;
}

void Print(ClauseNode* s){
    ClauseNode* s_temp=s;
    printf("%d\n",s_temp->num);
    s_temp=s_temp->down;
    while(s_temp!=NULL){
        printf("%d ",s_temp->num);
        LiteralNode* l_temp=s_temp->right;
        while(l_temp!=NULL){
            printf("%d ",l_temp->data);
            l_temp=l_temp->next;
        }
        printf("\n");
        s_temp=s_temp->down;
    }
}

