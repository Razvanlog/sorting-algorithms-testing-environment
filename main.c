#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int n,*v;
FILE *input_file,*bubble_file,*selection_file,*insertion_file,*merge_file,*quick_file;
FILE *output_files[5];
void bubble_sort(int st,int dr,int *l){
    int not_sorted=0;
    do{
        not_sorted=0;
        //printf("succes");
        for (int i=st; i<dr-1; i++){
            if (!(*(l+i)<*(l+i+1))){
                int temp=*(l+i);
                *(l+i)=*(l+i+1);
                *(l+i+1)=temp;
                not_sorted=1;
            }
        }
    }while(not_sorted);
}
void selection_sort(int st,int dr,int *l){
    for (int i=st; i<dr; i++){
        int min_el=*(l+i),poz_el=i;
        for (int j=i+1; j<dr; j++){
            if (min_el>*(l+j)){
                min_el=*(l+j);
                poz_el=j;
            }
        }
        int temp=*(l+i);
        *(l+i)=*(l+poz_el);
        *(l+poz_el)=temp;
        printf("%d\n",poz_el);
    }
}
void insertion_sort(int st,int dr,int *l){
    for (int i=st+1; i<dr; i++){
        int el=*(l+i),it=i-1;
        while (el<*(l+it) && it>=0){
            *(l+it+1)=*(l+it);
            it--;
        }
        *(l+it+1)=el;
    }
}
void merge_sort(int st,int dr,int *l){
    if (st<dr-1)
    {
        int m=(st+dr)/2;
        merge_sort(st,m,l);
        merge_sort(m,dr,l);
        int it1=st,it2=m,it=0,*tmp;
        tmp=malloc(sizeof(int)*(dr-st+1));
        //printf("succes");
        while (it1<m && it2<dr){
            if (*(l+it1)<*(l+it2)){
                *(tmp+it)=*(l+it1);
                it1++;
            }
            else *(tmp+it)=*(l+it2),it2++;
            //printf("%d\n",*(tmp+it));
            it++;
        }
        while (it1<m){
            *(tmp+it)=*(l+it1);
            it1++;
            it++;
        }
        while (it2<dr){
            *(tmp+it)=*(l+it2);
            it2++;
            it++;
        }
        it=0;
        for (int i=st; i<dr; i++,it++){
            *(l+i)=*(tmp+it);
        }
        free(tmp);
    }
}
int partition(int low,int high,int *l){
    int pivot=*(l+high-1);
    int i=(low-1);
    for (int j=low; j<high; j++){
        if (*(l+j)<pivot){
            i++;
            int temp=*(l+i);
            *(l+i)=*(l+j);
            *(l+j)=temp;
        }
    }
    int temp=*(l+i+1);
    *(l+i+1)=*(l+high-1);
    *(l+high-1)=temp;
    return i+1;
}
void quick_sort(int low,int high,int *l){
    if (low<high-1){
        int pi=partition(low,high,l);
        quick_sort(low,pi,l);
        quick_sort(pi,high,l);
    }
}
int main(){
    *(output_files)=fopen("bubble_file.txt","w");
    *(output_files+1)=fopen("selection_file.txt","w");
    *(output_files+2)=fopen("insertion_file.txt","w");
    *(output_files+3)=fopen("merge_file.txt","w");
    *(output_files+4)=fopen("quick_file.txt","w");
    void (*sort_alg[5])(int,int,int*);
    *sort_alg=bubble_sort;
    *(sort_alg+1)=selection_sort;
    *(sort_alg+2)=insertion_sort;
    *(sort_alg+3)=merge_sort;
    *(sort_alg+4)=quick_sort;
    for (int i=1; i<=20; i++){
        char *file_name;
        file_name=malloc(sizeof(char)*50);
        strcpy(file_name,"grader_test");
        char *add;
        if (i<10){
            //char*add;
            add=malloc(sizeof(char)*2);
            *add=i+'0';
            *(add+1)='\0';
        }
        else {
            add=malloc(sizeof(char)*3);
            *(add+1)=i%10+'0';
            *(add)=i/10+'0';
            *(add+2)='\0';
        }
        strcpy(file_name+strlen(file_name),add);
        strcpy(file_name+strlen(file_name),".in");
        //printf("%s\n",file_name);
        input_file=fopen(file_name,"r");
        if (input_file!=NULL){
        fscanf(input_file,"%d",&n);
        v=malloc(sizeof(int)*n);
        for (int i=0; i<n; i++){
            fscanf(input_file,"%d",(v+i));
        }
        for (int it=0; it<5; it++){
            clock_t t;
            t=clock();
            sort_alg[it](0,n,v);
            t=clock()-t;
            double time_taken=((double)t)/CLOCKS_PER_SEC;
            fprintf(output_files[it],"%f\n",time_taken);
        }
        //printf("succesfully read file %s\n",file_name);
        }
        else {
            printf("there is no file %s\n",file_name);
        }
        free(add);
        free(file_name);
    }
    return 0;
}