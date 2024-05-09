#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int n,*v;
/*static inline void swap_el_asm (int *a,int *b){
    asm(
        "":
        "=r"(*a),"=r"(*b):
        "0"(*b),"1"(*a):
    );
    return;
}*/

void heapify(int arr[], int N, int i)
{
    int largest = i;
    int l = 2 * i + 1;
   int r = 2 * i + 2;
    if (l < N && arr[l] > arr[largest])
        largest = l;
    if (r < N && arr[r] > arr[largest])
        largest = r;
    if (largest != i) {
        /*int aux=arr[i];
        arr[i]=arr[largest];
        arr[largest]=aux;*/
        asm(
            "":
            "=r"(*(arr+i)),"=r"(*(arr+largest)):
            "0"(*(arr+largest)),"1"(*(arr+i)):
        );
        //swap_el_asm(arr+i,arr+largest);
        heapify(arr, N, largest);
    }
}

void heapsort(int m, int N,int *arr)
{
    for (int i = N / 2 - 1; i >= m; i--)
        heapify(arr, N, i);
    for (int i = N - 1; i > m; i--) {
        /*int aux=arr[0];
        arr[0]=arr[i];
        arr[i]=aux;*/
        asm(
            "":
            "=r"(*(arr+i)),"=r"(*(arr+0)):
            "0"(*(arr+0)),"1"(*(arr+i)):
        );
        //swap_el_asm(arr+0,arr+i);
        heapify(arr, i, 0);
    }
}
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
        /*int temp=*(l+i);
        *(l+i)=*(l+poz_el);
        *(l+poz_el)=temp;*/
        asm(
            "":
            "=r"(*(l+i)),"=r"(*(l+poz_el)):
            "0"(*(l+poz_el)),"1"(*(l+i)):
        );
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
                /*int temp=*(l+i);
                *(l+i)=*(l+i+1);
                *(l+i+1)=temp;*/
               asm(
                "":
                "=r"(*(l+i)),"=r"(*(l+i+1)):
                "0"(*(l+i+1)),"1"(*(l+i)):
                );
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
            /*int temp=*(l+i);
            *(l+i)=*(l+j);
            *(l+j)=temp;*/
            asm(
            "":
            "=r"(*(l+i)),"=r"(*(l+j)):
            "0"(*(l+j)),"1"(*(l+i)):
        );
        }
    }
    /*int temp=*(l+i+1);
    *(l+i+1)=*(l+high-1);
    *(l+high-1)=temp;*/
   asm(
            "":
            "=r"(*(l+i+1)),"=r"(*(l+high-1)):
            "0"(*(l+high-1)),"1"(*(l+1+i)):
        );
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
    //int dsadsa[(1<<19)];
    //printf("%d",SIZE_MAX);
    char*file_name_output=(char*)malloc(sizeof(char)*100),*input_file_name=(char*)malloc(sizeof(char)*100),*bubble=(char*)malloc(sizeof(char)*100),*merge,*selection,*heap,*insertion,*quick;
    strcpy(file_name_output,__FILE__);
    file_name_output[strlen(file_name_output)-6]='\0';
    merge=(char*)malloc(sizeof(char)*100);
    selection=(char*)malloc(sizeof(char)*100);
    heap=(char*)malloc(sizeof(char)*100);
    insertion=(char*)malloc(sizeof(char)*100);
    quick=(char*)malloc(sizeof(char)*100);
    strcpy(bubble,file_name_output);
    strcpy(merge,file_name_output);
    strcpy(selection,file_name_output);
    strcpy(heap,file_name_output);
    strcpy(insertion,file_name_output);
    strcpy(quick,file_name_output);
    strcat(bubble,"bubble2.csv");
    strcat(merge,"merge2.csv");
    strcat(selection,"selection2.csv");
    strcat(heap,"heap2.csv");
    strcat(insertion,"insertion2.csv");
    strcat(quick,"quick2.csv");
    strcpy(input_file_name,file_name_output);
    strcat(input_file_name,"input_test.in");
    //strcat(file_name_output,"merge.csv");
    //printf("%s\n",file_name_output);
    int reset_input=0;
    scanf("%d",&reset_input);
    if (reset_input==1){
        time_t t1;
        srand((unsigned)time(&t1));
        FILE *input=fopen(input_file_name,"w");
        for (int i=1; i<=500000; i++){
            fprintf(input,"%d ",rand());
        }
        fclose(input);
    }
    //printf("%d %d\n",rand(),rand());
    int input_size[]={100,500,1000,5000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000,300000,400000,500000};
    FILE *input_file;
    FILE *output_file;
    void (*sort_alg)(int,int,int*);
    int choice;
    scanf("%d",&choice);
    switch(choice){
    case 0:
        sort_alg=bubble_sort;
        output_file=fopen(bubble,"w");
        break;
    case 1:
        sort_alg=selection_sort;
        output_file=fopen(selection,"w");
        break;
    case 2:
        sort_alg=insertion_sort;
        output_file=fopen(insertion,"w");
        break;
    case 3:
        sort_alg=merge_sort;
        output_file=fopen(merge,"w");
        break;
    case 4:
        sort_alg=quick_sort;
        output_file=fopen(quick,"w");
        break;
    case 5:
        sort_alg=heapsort;
        output_file=fopen(heap,"w");
    default:
        break;
    }
    char *file_name;
    file_name=malloc(sizeof(char)*101);
    strcpy(file_name,input_file_name);
    //strcpy(file_name,"");
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
        fprintf(output_file,"test,size,time\n");
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
            fprintf(output_file,"%d,%d,%f\n",i,input_size[i],time_taken);
            printf("%d\n",i);
            /*for (int j=0; j<input_size[i]; j++){
                printf("%d\n",l[j]);
            }*/
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
