#include <stdio.h>
#include <stdlib.h>

int seq1[50];
int k1 = 0;
int seq2[50];
int k2 = 0;
int seq3[50];
int k3 = 0;
int seq4[50];
int k4 = 0;

void sort(int num[], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(num[j] > num[j+1]){
                int temp = num[j];
                num[j] = num[j+1];
                num[j+1] = temp;
            }
        }
    }
}

void fifo(int pages, int frames, int page[]){
    int frame[50];

    for(int i = 0; i < frames; i++){
        frame[i] = -1;
    }

    int pagefault = 0;
    int idx = 0;

    for(int i = 0; i < pages; i++){
        int found = 0;

        for(int j = 0; j < frames; j++){
            if(frame[j] == page[i]){
                found = 1;
                break;
            }
        }

        if(!found){
            frame[idx] = page[i];
            idx = (idx + 1) % frames;
            pagefault++;
        }
        

        printf("After page %d : ",page[i]);

        for(int j = 0; j < frames; j++){
            if(frame[j] == -1){
                printf("- ");
            }
            else{
                printf("%d ",frame[j]);
            }
        }
    }

    printf("Page faults : %d",pagefault);
}

void lru(int pages, int frames, int page[]){
    int frame[50];
    int time[50];

    for(int i = 0; i < frames; i++){
        frame[i] = -1;
        time[i] = 0;
    }

    int pagefault = 0;
    int timer = 0;

    for(int i = 0; i < pages; i++){
        int found = 0;

        for(int j = 0; j < frames; j++){
            if(frame[j] == page[i]){
                timer++;
                time[j] = timer;
                found = 1;
                break;
            }
        }

        if(!found){
            int pos = -1;

            for(int j = 0; j < frames; j++){
                if(frame[j] == -1){
                    pos = j;
                    break;
                }
            }

            if(pos == -1){
                pos = 0;
                for(int j = 1; j < frames; j++){
                    if(time[j] < time[pos]){
                        pos = j;
                    }
                }
            }

            frame[pos] = page[i];
            timer++;
            time[pos] = timer;
            pagefault++;
        }

        printf("after page %d :",page[i]);
        for(int j = 0; j < frames; j++){
            if(frame[j] == -1){
                printf("- ");
            }
            else{
                printf("%d ",frame[j]);
            }
        }
    }

    printf("Page fault %d ",pagefault);
}

void fcfs(int num[], int n, int head){
    int seek = 0;

    for(int i = 0; i < n; i++){
        seek += abs(head - num[i]);
        head = num[i];
        seq1[k1++] = head;
    }

    printf("Seek time : %d",seek);
}

void sstf(int num[], int n, int head){
    int seek = 0;
    int visited[50] = {0};

    for(int i = 0; i < n; i++){
        int min = 1e9;
        int idx = -1;

        for(int j = 0; j < n; j++){

            if(!visited[j] && abs(head - num[j]) < min){
                min = abs(head - num[j]);
                idx = j;
            }
        }

        visited[idx] = 1;
        seek += min;
        head = num[idx];
        seq2[k2++] = head;
    }

    printf("Seek time : %d",seek);
}

void cscan(int num[], int n, int head, int disk_size){
    int seek = 0;
    int i;
    sort(num, n);

    for(i = 0; i < n; i++){
        if(num[i] > head){
            break;
        }
    }

    for(int j = i; j < n; j++){
        seek += abs(head - num[j]);
        head = num[j];
        seq3[k3++] = head;
    }

    seek += abs(head - (disk_size - 1));
    head = disk_size-1;
    seq3[k3++] = head;
    seek += disk_size-1;
    head = 0;
    seq3[k3++] = head;

    for(int j = 0; j < i; j++){
        seek += abs(head - num[j]);
        head = num[j];
        seq3[k3++] = head;
    }

    printf("Seek time: %d",seek);
}

void look(int num[], int n, int head){
    int seek = 0;
    int i;
    sort(num, n);

    for(i = 0; i < n; i++){
        if(num[i] > head){
            break;
        }
    }

    for(int j = i; j < n; j++){
        seek += abs(head - num[j]);
        head = num[j];
        seq4[k4++] = head;
    }

    for(int j = i-1; j >= 0; j--){
        seek += abs(head - num[j]);
        head = num[j];
        seq4[k4++] = head;
    }

    printf("Seek time %d",seek);
}

int main(){
    int disk_requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = 8;
    int head = 53;
    int disk_size = 200;

    int frames = 3;

    printf("\n--- FCFS ---\n");
    k1 = 0;
    fcfs(disk_requests, n, head);

    printf("\n\n--- SSTF ---\n");
    k2 = 0;
    sstf(disk_requests, n, head);

    printf("\n\n--- CSCAN ---\n");
    k3 = 0;
    cscan(disk_requests, n, head, disk_size);

    printf("\n\n--- LOOK ---\n");
    k4 = 0;
    look(disk_requests, n, head);

    // Now using disk sequences as page reference strings

    printf("\n\n=== FIFO using FCFS sequence ===\n");
    fifo(k1, frames, seq1);

    printf("\n\n=== LRU using SSTF sequence ===\n");
    lru(k2, frames, seq2);

    printf("\n\n=== FIFO using CSCAN sequence ===\n");
    fifo(k3, frames, seq3);

    printf("\n\n=== LRU using LOOK sequence ===\n");
    lru(k4, frames, seq4);

    return 0;
}