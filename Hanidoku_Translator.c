#include "head.h"
#define PATH_SIZE 1024

void Hanidoku_Transform(int n,int (*h_table)[11]){
    char filename[PATH_SIZE]="C:\\Users\\mjh\\Desktop\\dpll_final\\example\\Hanidoku.cnf";
    //scanf("%s",filename);
    FILE* fp=fopen(filename,"w");
    fprintf(fp,"%c %s %d %d\n",'p',"cnf",1000,n+9855);
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            if(h_table[i][j]!=0) fprintf(fp,"%d %d\n",100*i+10*j+h_table[i][j],0);
        }
    }
    int left[10],right[10];
    for(int i=1;i<=9;i++){
        left[i]=i-4>1?i-4:1;
        right[i]=i+4<9?i+4:9;
    }
    for(int i=1;i<=9;i++){
        for(int j=left[i];j<=right[i];j++){
            for(int num1=1;num1<=9;num1++){
                for(int num2=num1+1;num2<=9;num2++){
                    fprintf(fp,"%d %d %d\n",-(100*i+10*j+num1),-(100*i+10*j+num2),0);
                }
            }
        }
    }
    for(int i=1;i<=9;i++){//排或列
        for(int j=left[i];j<right[i];j++){
            for(int k=j+1;k<=right[i];k++){
                for(int num=1;num<=9;num++){//数字
                    fprintf(fp,"%d %d %d\n",-(100*i+10*j+num),-(100*i+10*k+num),0);
                    fprintf(fp,"%d %d %d\n",-(100*j+10*i+num),-(100*k+10*i+num),0);
                }
            }
        }
    }
    for(int i=1;i<=9;i++){//斜线
        int j,k,num;
        if(i<=5){
            j=1;
            k=6-i;
            num=4+i;
        }
        else{
            j=i-4;
            k=1;
            num=14-i;
        }
        for(int l=1;l<num;l++){
            for(int m=1;m<=num-l;m++){
                for(int num=1;num<=9;num++){
                    fprintf(fp,"%d %d %d\n",-(100*j+10*k+num),-(100*(j+m)+10*(k+m)+num),0);
                }
            }
            j++;
            k++;
        }
    }
    for(int i=1;i<=9;i++){//排
        if(i<=5){
            for(int k=6-i;k<=4+i;k++){
                for(int j=left[i];j<=right[i];j++){
                    fprintf(fp,"%d ",100*i+10*j+k);
                }
                fprintf(fp,"%d\n",0);
            }
        }
        else{
            for(int k=i-4;k<=14-i;k++){
                for(int j=left[i];j<=right[i];j++){
                    fprintf(fp,"%d ",100*i+10*j+k);
                }
                fprintf(fp,"%d\n",0);
            }
        }
    }
    for(int i=1;i<=9;i++){//列
        if(i<=5){
            for(int k=6-i;k<=4+i;k++){
                for(int j=left[i];j<=right[i];j++){
                    fprintf(fp,"%d ",100*j+10*i+k);
                }
                fprintf(fp,"%d\n",0);
            }
        }
        else{
            for(int k=i-4;k<=14-i;k++){
                for(int j=left[i];j<=right[i];j++){
                    fprintf(fp,"%d ",100*j+10*i+k);
                }
                fprintf(fp,"%d\n",0);
            }
        }
    }
    for(int i=1;i<=9;i++){//斜线
        int j,k;
        if(i<=5){
            j=1;
            k=6-i;
            for(int num=6-i;num<=4+i;num++){
                for(int l=1;l<=4+i;l++){
                    fprintf(fp,"%d ",100*j+10*k+num);
                    j++;
                    k++;
                }
                fprintf(fp,"%d\n",0);
                j-=(4+i);
                k-=(4+i);
            }
        }
        else{
            j=i-4;
            k=1;
            for(int num=i-4;num<=14-i;num++){
                for(int l=1;l<=14-i;l++){
                    fprintf(fp,"%d ",100*j+10*k+num);
                    j++;
                    k++;
                }
                fprintf(fp,"%d\n",0);
                j-=(14-i);
                k-=(14-i);
            }
        }
    }
    for(int i=1;i<=9;i++){
        if(i==1||i==9){
            int arr[9]={0,1,2,3,4,6,7,8,9};
            for(int a=1;a<=4;a++){
                for(int b=(a>2?a:2);b<=5;b++){
                    for(int c=(b>3?b:3);c<=6;c++){
                        for(int d=(c>4?c:4);d<=7;d++){
                            for(int e=(d>5?d:5);e<=8;e++){
                                for(int j=left[i];j<=right[i];j++){
                                    fprintf(fp,"%d ",100*i+10*j+arr[a]);
                                    if(b>a) fprintf(fp,"%d ",100*i+10*j+arr[b]);
                                    if(c>b) fprintf(fp,"%d ",100*i+10*j+arr[c]);
                                    if(d>c) fprintf(fp,"%d ",100*i+10*j+arr[d]);
                                    if(e>d) fprintf(fp,"%d ",100*i+10*j+arr[e]);
                                }
                                fprintf(fp,"%d\n",0);
                                for(int j=left[i];j<=right[i];j++){
                                    fprintf(fp,"%d ",100*j+10*i+arr[a]);
                                    if(b>a) fprintf(fp,"%d ",100*j+10*i+arr[b]);
                                    if(c>b) fprintf(fp,"%d ",100*j+10*i+arr[c]);
                                    if(d>c) fprintf(fp,"%d ",100*j+10*i+arr[d]);
                                    if(e>d) fprintf(fp,"%d ",100*j+10*i+arr[e]);
                                }
                                fprintf(fp,"%d\n",0);
                            }
                        }
                    }
                }
            }
        }
        else if(i==2||i==8){
            int arr[7]={0,1,2,3,7,8,9};
            for(int a=1;a<=3;a++){
                for(int b=(a>2?a:2);b<=4;b++){
                    for(int c=(b>3?b:3);c<=5;c++){
                        for(int d=(c>4?c:4);d<=6;d++){
                            for(int j=left[i];j<=right[i];j++){
                                fprintf(fp,"%d ",100*i+10*j+arr[a]);
                                if(b>a) fprintf(fp,"%d ",100*i+10*j+arr[b]);
                                if(c>b) fprintf(fp,"%d ",100*i+10*j+arr[c]);
                                if(d>c) fprintf(fp,"%d ",100*i+10*j+arr[d]);
                            }
                            fprintf(fp,"%d\n",0);
                            for(int j=left[i];j<=right[i];j++){
                                fprintf(fp,"%d ",100*j+10*i+arr[a]);
                                if(b>a) fprintf(fp,"%d ",100*j+10*i+arr[b]);
                                if(c>b) fprintf(fp,"%d ",100*j+10*i+arr[c]);
                                if(d>c) fprintf(fp,"%d ",100*j+10*i+arr[d]);
                            }
                            fprintf(fp,"%d\n",0);
                        }
                    }
                }
            }
        }
        else if(i==3||i==7){
            int arr[5]={0,1,2,8,9};
            for(int a=1;a<=2;a++){
                for(int b=(a>2?a:2);b<=3;b++){
                    for(int c=(b>3?b:3);c<=4;c++){
                        for(int j=left[i];j<=right[i];j++){
                            fprintf(fp,"%d ",100*i+10*j+arr[a]);
                            if(b>a) fprintf(fp,"%d ",100*i+10*j+arr[b]);
                            if(c>b) fprintf(fp,"%d ",100*i+10*j+arr[c]);
                        }
                        fprintf(fp,"%d\n",0);
                        for(int j=left[i];j<=right[i];j++){
                            fprintf(fp,"%d ",100*j+10*i+arr[a]);
                            if(b>a) fprintf(fp,"%d ",100*j+10*i+arr[b]);
                            if(c>b) fprintf(fp,"%d ",100*j+10*i+arr[c]);
                        }
                        fprintf(fp,"%d\n",0);
                    }
                }
            }
        }
        else if(i==4||i==6){
            int arr[3]={0,1,9};
            for(int a=1;a<=2;a++){
                for(int j=left[i];j<=right[i];j++){
                    fprintf(fp,"%d ",100*i+10*j+arr[a]);
                }
            }
            fprintf(fp,"%d\n",0);
            for(int a=1;a<=2;a++){
                for(int j=left[i];j<=right[i];j++){
                    fprintf(fp,"%d ",100*j+10*i+arr[a]);
                }
            }
            fprintf(fp,"%d\n",0);
        }
    }
    for(int i=1;i<=9;i++){
        int j,k;
        if(i<=5){
            j=1;
            k=6-i;
        }
        else{
            j=i-4;
            k=1;
        }
        if(i==1||i==9){
            int arr[9]={0,1,2,3,4,6,7,8,9};
            for(int a=1;a<=4;a++){
                for(int b=(a>2?a:2);b<=5;b++){
                    for(int c=(b>3?b:3);c<=6;c++){
                        for(int d=(c>4?c:4);d<=7;d++){
                            for(int e=(d>5?d:5);e<=8;e++){
                                for(int num=1;num<=5;num++){
                                    fprintf(fp,"%d ",100*j+10*k+arr[a]);
                                    if(b>a) fprintf(fp,"%d ",100*j+10*k+arr[b]);
                                    if(c>b) fprintf(fp,"%d ",100*j+10*k+arr[c]);
                                    if(d>c) fprintf(fp,"%d ",100*j+10*k+arr[d]);
                                    if(e>d) fprintf(fp,"%d ",100*j+10*k+arr[e]);
                                    j++;
                                    k++;
                                }
                                fprintf(fp,"%d\n",0);
                                j-=5;
                                k-=5;
                            }
                        }
                    }
                }
            }
        }
        else if(i==2||i==8){
            int arr[7]={0,1,2,3,7,8,9};
            for(int a=1;a<=3;a++){
                for(int b=(a>2?a:2);b<=4;b++){
                    for(int c=(b>3?b:3);c<=5;c++){
                        for(int d=(c>4?c:4);d<=6;d++){
                            for(int num=1;num<=6;num++){
                                fprintf(fp,"%d ",100*j+10*k+arr[a]);
                                if(b>a) fprintf(fp,"%d ",100*j+10*k+arr[b]);
                                if(c>b) fprintf(fp,"%d ",100*j+10*k+arr[c]);
                                if(d>c) fprintf(fp,"%d ",100*j+10*k+arr[d]);
                                j++;
                                k++;
                            }
                            fprintf(fp,"%d\n",0);
                            j-=6;
                            k-=6;
                        }
                    }
                }
            }
        }
        else if(i==3||i==7){
            int arr[5]={0,1,2,8,9};
            for(int a=1;a<=2;a++){
                for(int b=(a>2?a:2);b<=3;b++){
                    for(int c=(b>3?b:3);c<=4;c++){
                        for(int num=1;num<=7;num++){
                            fprintf(fp,"%d ",100*j+10*k+arr[a]);
                            if(b>a) fprintf(fp,"%d ",100*j+10*k+arr[b]);
                            if(c>b) fprintf(fp,"%d ",100*j+10*k+arr[c]);
                            j++;
                            k++;
                        }
                        fprintf(fp,"%d\n",0);
                        j-=7;
                        k-=7;
                    }
                }
            }
        }
        else if(i==4||i==6){
            int arr[3]={0,1,9};
            for(int a=1;a<=2;a++){
                for(int num=1;num<=8;num++){
                    fprintf(fp,"%d ",100*j+10*k+arr[a]);
                    j++;
                    k++;
                }
                j-=8;
                k-=8;
            }
            fprintf(fp,"%d\n",0);
        }
    }
    fclose(fp);
}

/*void Hanidoku_Transform(int n,int (*h_table)[11]){
    char filename[PATH_SIZE]="C:\\Users\\mjh\\Desktop\\dpll_final\\example\\Hanidoku.cnf";
    //scanf("%s",filename);
    FILE* fp=fopen(filename,"w");
    fprintf(fp,"%c %s %d %d\n",'p',"cnf",1000,n+9855);
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            if(h_table[i][j]!=0) fprintf(fp,"%d %d\n",100*i+10*j+h_table[i][j],0);
        }
    }
    int left[10],right[10];
    for(int i=1;i<=9;i++){
        left[i]=i-4>1?i-4:1;
        right[i]=i+4<9?i+4:9;
    }
    for(int i=1;i<=9;i++){
        for(int j=left[i];j<=right[i];j++){
            for(int k=1;k<=9;k++){
                fprintf(fp,"%d ",100*i+10*j+k);
            }
            fprintf(fp,"%d \n",0);
        }
    }
    for(int i=1;i<=9;i++){
        for(int j=left[i];j<=right[i];j++){
            for(int num1=1;num1<=9;num1++){
                for(int num2=num1+1;num2<=9;num2++){
                    fprintf(fp,"%d %d %d\n",-(100*i+10*j+num1),-(100*i+10*j+num2),0);
                }
            }
        }
    }
    for(int i=1;i<=9;i++){//排或列
        for(int j=left[i];j<right[i];j++){
            for(int k=j+1;k<=right[i];k++){
                for(int num=1;num<=9;num++){//数字
                    fprintf(fp,"%d %d %d\n",-(100*i+10*j+num),-(100*i+10*k+num),0);
                    fprintf(fp,"%d %d %d\n",-(100*j+10*i+num),-(100*k+10*i+num),0);
                }
            }
        }
    }
    for(int i=1;i<=9;i++){//斜线
        int j,k,num;
        if(i<=5){
            j=1;
            k=6-i;
            num=4+i;
        }
        else{
            j=i-4;
            k=1;
            num=14-i;
        }
        for(int l=1;l<num;l++){
            for(int m=1;m<=num-l;m++){
                for(int num=1;num<=9;num++){
                    fprintf(fp,"%d %d %d\n",-(100*j+10*k+num),-(100*(j+m)+10*(k+m)+num),0);
                }
            }
            j++;
            k++;
        }
    }
    for(int i=1;i<=9;i++){
        for(int j=left[i];j<=right[i];j++){
            for(int k=j+1;k<=right[i];k++){
                int st,en;
                if(i<5){
                    st=1;
                    en=9-right[i];
                }
                else{
                    st=1;
                    en=left[i]-1;
                }
                for(int m=st;m<=en;m++){
                    for(int l=m+9-en;l<=9;l++){
                        fprintf(fp,"%d %d %d\n",-(i*100+j*10+m),-(i*100+k*10+l),0);
                        fprintf(fp,"%d %d %d\n",-(i*100+k*10+m),-(i*100+j*10+l),0);
                        fprintf(fp,"%d %d %d\n",-(j*100+i*10+m),-(k*100+i*10+l),0);
                        fprintf(fp,"%d %d %d\n",-(k*100+i*10+m),-(j*100+i*10+l),0);
                    }
                }
            }
        }
    }
    for(int i=1;i<=9;i++){//斜线
        int j,k,num,q=1;
        if(i<=5){
            j=1;
            k=6-i;
            num=4+i;
        }
        else{
            j=i-4;
            k=1;
            num=14-i;
        }
        for(int l=1;l<=9-num;l++){
            for(int p=1;p<=num-q;p++){
                for(int m=1;m<=9-num;m++){
                    for(int o=m+num;o<=9;o++){
                        fprintf(fp,"%d %d %d\n",-(100*j+10*k+m),-(100*(j+p)+10*(k+p)+o),0);
                        fprintf(fp,"%d %d %d\n",-(100*j+10*k+o),-(100*(j+p)+10*(k+p)+m),0);
                    }
                }
            }
            j++;
            k++;
            q++;
        }
    }
    fclose(fp);
}*/

//C:\\Users\\mjh\\Desktop\\dpll_final\\example\\Hanidoku.cnf
