#include <stdio.h>
#include <stdlib.h>

void lru(){
    int pages;
    int frames;
    int page[50], frame[50], time[50];

    printf("Enter number of pages: ");
    scanf("%d", &pages);

    for(int i = 0; i < pages; i++){
        scanf("%d",&page);
    }

    printf("Enter number of frames: ");
    
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
                time[i] = timer;
                found = 1;
                break;
            }
        }

        if(!found){
            int pos = 0;

            for(int j = 0; j < frames; j++){
                if(time[j] < time[pos]){
                    pos = j;
                }
            }

            frame[pos] = page[i];
            timer++;
            time[pos] = timer;
            pagefault++;
        }


        printf("After : %d",&page[i]);
        for(int j = 0; j < frames; j++){
            if(frame[j] == -1){
                printf("%d");
            }
        }
    }

    printf("PAGE Fault: %d",pagefault);
}

void mru(){
    int pages;
    int frames;
    int page[50], frame[50], time[50];

    printf("Enter number of pages: ");
    scanf("%d",&pages);

    for(int i = 0; i < pages; i++){
        scanf("%d",&page[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d",&frames);

    for(int i = 0; i < frames; i++){
        frame[i] = -1;
        time[i] = 0;
    }

    int fault = 0;
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
                if(time[j] > time[pos]){
                    pos = j;
                }
            }

            frame[pos] = page[i];
            timer++;
            time[pos] = timer;
            fault++;
        }

        printf("Page after : %d",page[i]);
        for(int j = 0; j < frames; j++){
            if(frame[j] == -1){
                printf("- ");
            }
            else{
                printf("%d ",frame[j]);
            }
        }
    }
}

void lfu(){
    int pages;
    int frames;
    int page[50], frame[50], count[50], time[50];

    printf("Enter number of pages: ");
    scanf("%d",&pages);

    for(int i = 0; i < pages; i++){
        scanf("%d",&page[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    for(int i = 0; i < frames; i++){
        frame[i] = -1;
        count[i] = 0;
        time[i] = 0;
    }

    int timer = 0;
    int fault = 0;

    for(int i = 0; i < pages; i++){
        int found = 0;

        for(int j = 0; j < frames; j++){
            if(frame[j] == page[i]){
                timer++;
                found = 1;
                break;
            }
        }

        if(!found){
            int pos = 0;

            for(int j = 1; j < frames; j++){
                if(count[j] < count[pos]){
                    pos = j;
                }
                else if(count[j] == count[pos]){
                    if(time[j] < time[pos]){
                        pos = j;
                    }
                }
            }

            frame[pos] = page[i];
            count[pos] = 1;
            time[pos] = timer++;
            fault++;
        }

        printf("After page: %d",page[i]);
        for(int j = 0; j < frames; j++){
            if(frame[j] == -1){
                printf("- ");
            }
            else{
                printf("%d", frame[j]);
            }
        }
    }
    printf("Page fault: %d", fault);
}

void mfu(){
        int pages;
    int frames;
    int page[50], frame[50], count[50], time[50];

    printf("Enter number of pages: ");
    scanf("%d",&pages);

    for(int i = 0; i < pages; i++){
        scanf("%d",&page[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    for(int i = 0; i < frames; i++){
        frame[i] = -1;
        count[i] = 0;
        time[i] = 0;
    }

    int timer = 0;
    int fault = 0;

    for(int i = 0; i < pages; i++){
        int found = 0;

        for(int j = 0; j < frames; j++){
            if(frame[j] == page[i]){
                timer++;
                found = 1;
                break;
            }
        }

        if(!found){
            int pos = 0;

            for(int j = 1; j < frames; j++){
                if(count[j] > count[pos]){
                    pos = j;
                }
                else if(count[j] == count[pos]){
                    if(time[j] < time[pos]){
                        pos = j;
                    }
                }
            }

            frame[pos] = page[i];
            count[pos] = 1;
            time[pos] = timer++;
            fault++;
        }

        printf("After page: %d",page[i]);
        for(int j = 0; j < frames; j++){
            if(frame[j] == -1){
                printf("- ");
            }
            else{
                printf("%d", frame[j]);
            }
        }
    }
    printf("Page fault: %d", fault);
}

void optimal(){
    int pages;
    int frames;
    int page[50], frame[50];

    printf("enter number of pages: ");
    scanf("%d", &pages);

    for(int i = 0; i < pages; i++){
        scanf("%d", &page[i]);
    }

    printf("enter number of frames: ");
    scanf("%d", &frames);

    for(int i = 0; i < frames; i++){
        frame[i] = -1;
    }

    int fault = 0;

    for(int i = 0; i < pages; i++){
        int found = 0;

        for(int j = 0; j < frames; j++){
            if(frame[j] == page[i]){
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
                int farthest = -1;

                for(int j = 0; j < frames; j++){
                    int k;

                    for(int k = i+1; k < pages; k++){
                        if(frame[j] == frame[k]){
                            break;
                        }
                    }

                    if(k == pages){
                        pos = j;
                        break;
                    }

                    if(k > farthest){
                        farthest = k;
                        pos = j;
                    }
                }
            }

            frame[pos] = page[i];
            fault++;
        }
    }
}

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

void look(int num[], int n, int head){
    int seek = 0;
    sort(num, n);
    int i;

    for(i = 0; i < n; i++){
        if(num[i] > head){
            break;
        }
    }

    for(int j = i; j < n; j++){
        seek += abs(head - num[j]);
        head = num[j];
        printf("%d -> ",head);
    }

    for(int j = i-1; j >= 0; j--){
        seek += abs(head - num[j]);
        head = num[j];
        printf("%d -> ",head);
    }

    printf("\n Seek: %d",seek);
}

void clook(int num[], int n, int head){
    sort(num, n);
    int i;
    int seek = 0;

    for(i = 0; i < n; i++){
        if(num[i] > head){
            break;
        }
    }

    for(int j = i; j < n; j++){
        seek += abs(head - num[j]);
        head = num[j];
        printf("%d -> ",head);
    }

    seek += abs(head - num[0]);
    head = num[0];

    for(int j = 0; j < i; j++){
        seek += abs(head - num[j]);
        head = num[j];
        printf("%d -> ",head);
    }

    printf("seek : %d", seek);
}

void scan(int num[], int n, int head, int disk_size){
    int i;
    sort(num, n);
    int seek = 0;

    for(i = 0; i < n; i++){
        if(num[i] > head)break;
    }

    for(int j = i; j < n; j++){
        seek += abs(head - num[j]);
        head = num[j];
        printf("%d -> ", head);
    }

    seek += abs(head - disk_size - 1);
    printf("%d -> ", disk_size-1);
    head = disk_size - 1;

    for(int j = i - 1; j >= 0; j--){
        seek += abs(head - num[j]);
        head = num[j];
        printf("%d -> ", head);
    }

    printf("Seek time : %d",seek);
}

void cscan(int num[], int n, int head, int disk_size){
    int i;
    int seek = 0;
    sort(num, n);

    for(i = 0; i < n; i++){
        if(num[i] > head){
            break;
        }
    }

    for(int j = i; j < n; j++){
        seek += abs(head - num[j]);
        head = num[j];
        printf("%d ->", head);
    }

    seek += abs(head - disk_size - 1);
    printf("%d ->", disk_size-1);
    seek += disk_size - 1;
    head = 0;
    printf("%d ->", head);
    
    for(int j = 0; j < i; j++){
        seek += abs(head - num[j]);
        head = num[j];
        printf("%d ->", head);
    }
}


int main(){
    lfu();
    return 0;
}
