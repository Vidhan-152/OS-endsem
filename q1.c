#include <stdio.h>
#include <stdlib.h>

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

int seq[50];
int k = 0;

void clook(int num[], int n, int head){
    int seek = 0;
    int i;
    sort(num, n);

    for(i = 0; i < n; i++){
        if(num[i] > head)break;
    }

    for(int j = i; j < n; j++){
        seek +=abs(head - num[j]);
        head = num[j];
        seq[k++] = head;
    }

    seek += abs(head - num[0]);
    head = num[0];
    seq[k++] = head;

    for(int j = 1; j < i; j++){
        seek += abs(head - num[j]);
        head = num[j];
        seq[k++] = head;
    }

    printf("Seek time : %d",seek);
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
            int pos = 0;

            for(int j = 1; j < frames; j++){
                if(time[j] < time[pos]){
                    pos = j;
                }
            }

            frame[pos] = page[i];
            timer++;
            time[pos] = timer;
            pagefault++;
        }

        printf("After page %d : ",page[i]);
        for(int j = 0; j < frames; j++){
            if(frame[j] == -1){
                printf("- ");
            }
            else{
                printf("%d ", frame[j]);
            }
        }
        printf("\n");

    }

    printf("page fault : %d", pagefault);
}

int main(){

    int pages_test[] = {82, 170, 43, 140, 24, 16, 190};
    int page_test = 7;
    int head_test = 50;

    clook(pages_test, page_test, head_test);
    lru(page_test, 3, seq);
}