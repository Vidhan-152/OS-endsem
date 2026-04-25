#include <stdio.h>
#include <stdlib.h>

int seq[50];
int k = 0;

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
            idx = (idx + 1)%frames;
            pagefault++;
        }

        printf("Page after %d : ", page[i]);
        for(int j = 0; j < frames; j++){
            if(frame[j] == -1){
                printf("- ");
            }
            else{
                printf("%d ",frame[j]);
            }
        }
        printf("\n");
    }

    int hits = pages - pagefault;

    printf("\nPage faults = %d", pagefault);
    printf("\nHits = %d", hits);
    printf("\nHit ratio = %.2f", (float)hits / pages);
    printf("\nMiss ratio = %.2f\n", (float)pagefault / pages);
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

                for(int j = 0; j<frames; j++){
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

        printf("Page after %d : ", page[i]);
        for(int j = 0; j < frames; j++){
            if(frame[j] == -1){
                printf("- ");
            }
            else{
                printf("%d ",frame[j]);
            }
        }
        printf("\n");
    }

    int hits = pages - pagefault;

    printf("\nPage faults = %d", pagefault);
    printf("\nHits = %d", hits);
    printf("\nHit ratio = %.2f", (float)hits / pages);
    printf("\nMiss ratio = %.2f\n", (float)pagefault / pages);
}

void sstf(int num[] , int n, int head){
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
        seq[k++] = head;
        printf("%d -> ",head);
    }

    printf("\nSeek time = %d ",seek);
}

int main(){
    int pages;
    int page[50];
    int frames;
    int head;

    printf("Enter number of pages : ");
    scanf("%d",&pages);

    for(int i = 0; i < pages; i++){
        scanf("%d",&page[i]);
    }

    printf("Enter number of frames : ");
    scanf("%d", &frames);

    printf("Enter head position : ");
    scanf("%d", &head);

    printf("\n\n");

    // getting seq from sstf
    sstf(page, pages, head);

    printf("\n\n");

    // putting that seq in fifo
    //fifo(k, frames, seq);
    lru(k, frames, seq);

}

