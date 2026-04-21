#include <stdio.h>
#include <stdlib.h>

//! ----------------SORT-------------
void sort(int num[], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(num[j] > num[j + 1]){
                int temp = num[j];
                num[j] = num[j + 1];
                num[j + 1] = temp;
            }
        }
    }
}

//! -----------FCFS---------------

void fcfs(int num[] , int n, int head){
    int seek = 0;
    for(int i = 0; i < n; i++){
        seek += abs(num[i] - head);
        head = num[i];
    }

    printf("Seek time : ",seek);
}

//! ----------SSTF-------------

void sstf(int num[], int n, int head){
    int seek = 0;
    int visited[10] = {0};

    for(int i = 0; i < n; i++){
        int min = 1e9;
        int idx = -1;

        for(int j = 0; j < n; j++){
            if(!visited[j] && abs(num[j] - head) < min){
                min = abs(num[j] - head);
                idx = j;
            }
        }

        visited[idx] = 1;
        seek += min;
        head = num[idx];
    }

    printf("SSTF Seek time: ",seek);
}

//! ----------SCAN-------------

void scan(int num[], int n, int head, int disk_size){
    int seek = 0;
    sort(num, n);

    int i;
    for(i = 0; i < n; i++){
        if(num[i] > head)break;
    }

    //* move right
    for(int j = i; j < n; j++){
        seek += abs(num[j] - head);
        head = num[j];
    }

    //* go to end
    seek += abs((disk_size-1) - head);
    head = disk_size - 1;

    //* move left
    for(int j = i; j >= 0; j--){
        seek += abs(num[j] - head);
        head = num[j];
    }

    printf("Seek time : ",seek);
}

//! -----------LOOK--------------

void look(int num[], int n, int head, int disk_size){
    int seek = 0;
    sort(num, n);

    int i;
    for(i = 0; i < n; i++){
        if(num[i] > head)break;
    }

    //* move right
    for(int j = i; j < n; j++){
        seek += abs(num[j] - head);
        head = num[j];
    }


    //* move left
    for(int j = i-1; j >= 0; j--){
        seek += abs(num[j] - head);
        head = num[j];
    }

    printf("Seek time : ",seek);
}

//! -----------C-SCAN--------------

void cscan(int num[], int n, int head, int disk_size){
    int seek = 0;
    sort(num, n);

    int i;
    for(i = 0; i < n; i++){
        if(num[i] > head)break;
    }

    //* move right
    for(int j = i; j < n; j++){
        seek += abs(num[j] - head);
        head = num[j];
    }

    seek += abs((disk_size-1) - head);
    seek += (disk_size - 1);
    head = 0;

    //* move left
    for(int j = 0; j < i; j++){
        seek += abs(num[j] - head);
        head = num[j];
    }

    printf("Seek time : ",seek);
}

//! -----------C-LOOK-----------
void clook(int num[], int n, int head){
    int seek = 0;
    sort(num, n);

    int i;
    for(i = 0; i < n; i++){
        if(num[i] > head)break;
    }

    //* move right
    for(int j = i; j < n; j++){
        seek += abs(num[j] - head);
        head = num[j];
    }

    seek += abs(head - num[0]);
    head = num[0];

    //* move left
    for(int j = 1; j < i; j++){
        seek += abs(num[j] - head);
        head = num[j];
    }

    printf("Seek time : ",seek);
}
int main(){
    return 0;
}