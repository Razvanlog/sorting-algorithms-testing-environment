#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int n,*v;
void selection_sort(int st,int dr,int *l)
{
    for (int i=st; i<dr; i++)
    {
        int min_el=*(l+i),poz_el=i;
        for (int j=i+1; j<dr; j++)
        {
            if (min_el>*(l+j))
            {
                min_el=*(l+j);
                poz_el=j;
            }
        }
        int temp=*(l+i);
        *(l+i)=*(l+poz_el);
        *(l+poz_el)=temp;
    }
}
void insertion_sort(int st,int dr,int *l)
{
    for (int i=st+1; i<dr; i++)
    {
        int el=*(l+i),it=i-1;
        while (el<*(l+it) && it>=0)
        {
            *(l+it+1)=*(l+it);
            it--;
        }
        *(l+it+1)=el;
    }
}
void merge_sort(int st,int dr,int *l)
{
    if (st<dr-1)
    {
        int m=(st+dr)/2;
        merge_sort(st,m,l);
        merge_sort(m,dr,l);
        int it1=st,it2=m,it=0,*tmp;
        tmp=malloc(sizeof(int)*(dr-st+1));
        while (it1<m && it2<dr)
        {
            if (*(l+it1)<*(l+it2))
            {
                *(tmp+it)=*(l+it1);
                it1++;
            }
            else *(tmp+it)=*(l+it2),it2++;
            it++;
        }
        while (it1<m)
        {
            *(tmp+it)=*(l+it1);
            it1++;
            it++;
        }
        while (it2<dr)
        {
            *(tmp+it)=*(l+it2);
            it2++;
            it++;
        }
        it=0;
        for (int i=st; i<dr; i++,it++)
        {
            *(l+i)=*(tmp+it);
        }
        free(tmp);
    }
}
void bubble_sort(int st,int dr,int *l)
{
    int not_sorted=0;
    do
    {
        not_sorted=0;
        for (int i=st; i<dr-1; i++)
        {
            if (*(l+i)>*(l+i+1))
            {
                int temp=*(l+i);
                *(l+i)=*(l+i+1);
                *(l+i+1)=temp;
                not_sorted=1;
            }
        }
    }
    while(not_sorted);
}
int partition(int low,int high,int *l){
    int pivot=*(l+high-1);
    int i=(low-1);
    for (int j=low; j<high-1; j++){
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
        quick_sort(pi+1,high,l);
    }
}
int main()
{
    int input_size[]={100,500,1000,5000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000,300000,400000,500000};
    FILE *input_file;
    FILE *output_file;
    void (*sort_alg)(int,int,int*);
    int choice;
    scanf("%d",&choice);
    switch(choice){
    case 0:
        sort_alg=bubble_sort;
        output_file=fopen("bubble2.out","w");
        break;
    case 1:
        sort_alg=selection_sort;
        output_file=fopen("selection2.out","w");
        break;
    case 2:
        sort_alg=insertion_sort;
        output_file=fopen("insertion2.out","w");
        break;
    case 3:
        sort_alg=merge_sort;
        output_file=fopen("merge2.out","w");
        break;
    case 4:
        sort_alg=quick_sort;
        output_file=fopen("quick2.out","w");
        break;
    default:
        break;
    }
    char *file_name;
    file_name=malloc(sizeof(char)*50);
    strcpy(file_name,"input_test.in");
    input_file=fopen(file_name,"r");
    if (input_file!=NULL)
    {
        fscanf(input_file,"%d",&n);
        v=malloc(sizeof(int)*n);
        for (int j=0; j<n; j++)
        {
            fscanf(input_file,"%d",(v+j));
        }
        fclose(input_file);
        for (int i=0; i<18; i++)
        {
            int *l=malloc(sizeof(int)*input_size[i]);
            for (int j=0; j<input_size[i]; j++)
                l[j]=v[j];
            clock_t t;
            t=clock();
            sort_alg(0,input_size[i],l);
            t=clock()-t;
            double time_taken=((double)t)/CLOCKS_PER_SEC;
            fprintf(output_file,"%d %d %f\n",i,input_size[i],time_taken);
            printf("%d\n",i);
            free(l);
        }
    }
    else
    {
        printf("there is no file %s\n",file_name);
    }
    free(file_name);
    fclose(output_file);
    free(v);
    return 0;
}
