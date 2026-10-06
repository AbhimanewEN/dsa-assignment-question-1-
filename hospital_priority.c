#include <stdio.h>
#define N 7
long cmp, swp;

void show(const char *t, int a[], int n){
    printf("%s[", t);
    for(int i=0;i<n;i++) printf("%d%s", a[i], i<n-1?", ":"");
    printf("]\n");
}
void swap(int *a,int *b){int t=*a;*a=*b;*b=t;swp++;}

/* ---------- (a) Max Heap insertion ---------- */
int height(int n){int h=0;while(n>1){n/=2;h++;}return h;}
void insert(int h[], int *n, int v){
    int i=(*n)++; h[i]=v;
    while(i>0){
        cmp++;
        int p=(i-1)/2;
        if(h[p]<h[i]){swap(&h[p],&h[i]); i=p;} else break;
    }
}

/* ---------- (b) Heap Sort ---------- */
void heapify(int a[],int n,int i){
    for(;;){
        int l=2*i+1,r=2*i+2,m=i;
        if(l<n){cmp++; if(a[l]>a[m]) m=l;}
        if(r<n){cmp++; if(a[r]>a[m]) m=r;}
        if(m==i) break;
        swap(&a[i],&a[m]); i=m;
    }
}
void heapsort(int a[],int n){
    for(int i=n/2-1;i>=0;i--) heapify(a,n,i);
    show("  After build-heap : ",a,n);
    for(int i=n-1;i>0;i--){
        swap(&a[0],&a[i]); heapify(a,i,0);
        printf("  Extract %2d -> ", a[i]); show("",a,n);
    }
}

/* ---------- (b) Quick Sort (Lomuto, last element pivot) ---------- */
int partition(int a[],int lo,int hi){
    int p=a[hi],i=lo-1;
    for(int j=lo;j<hi;j++){cmp++; if(a[j]<=p){i++; if(i!=j) swap(&a[i],&a[j]);}}
    if(i+1!=hi) swap(&a[i+1],&a[hi]);
    printf("  pivot=%2d (range %d..%d) -> ",p,lo,hi); show("",a,N);
    return i+1;
}
void quicksort(int a[],int lo,int hi){
    if(lo<hi){int p=partition(a,lo,hi); quicksort(a,lo,p-1); quicksort(a,p+1,hi);}
}

int main(void){
    int in[N]={45,72,30,90,65,50,85}, h[N], n=0;
    printf("=== (a) Max Heap insertion ===\n");
    for(int i=0;i<N;i++){insert(h,&n,in[i]); printf("Insert %2d : ",in[i]); show("",h,n);}
    printf("Heap height = %d, comparisons = %ld, swaps = %ld\n\n",height(n),cmp,swp);

    printf("=== (b) Heap Sort ===\n");
    int a[N]; for(int i=0;i<N;i++) a[i]=in[i];
    cmp=swp=0; show("  Input : ",a,N); heapsort(a,N);
    show("  Sorted: ",a,N);
    printf("Heap Sort: comparisons = %ld, swaps = %ld\n\n",cmp,swp);

    printf("=== (b) Quick Sort ===\n");
    for(int i=0;i<N;i++) a[i]=in[i];
    cmp=swp=0; show("  Input : ",a,N); quicksort(a,0,N-1);
    show("  Sorted: ",a,N);
    printf("Quick Sort: comparisons = %ld, swaps = %ld\n",cmp,swp);
    return 0;
}
