#include <stdio.h>
#include <stdlib.h>

//! fifo
void fifo(){
    int frames, pages;
    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter number of pages: ");
    scanf("%d", &pages);

    int ref[100], frame[50];

    printf("Enter page reference string:\n");
    for(int i = 0; i < pages; i++)
        scanf("%d", &ref[i]);

    for(int i = 0; i < frames; i++)
        frame[i] = -1;

    int faults = 0;
    int index = 0;

    for(int i = 0; i < pages; i++){
        int found = 0;

        // checking if the number is already there or not 
        for(int j = 0; j < frames; j++){
            if(frame[j] == ref[i]){
                found = 1;
                break;
            }
        }

        if(!found){
            frame[index] = ref[i];
            index = (index + 1)%frames;
            faults++;
        }
    }

    printf("Total page fault = %d", faults);
}

//! optimal 
void optimal() {
    int pages, frames;
    int page[50], frame[50];

    printf("Enter number of pages: ");
    scanf("%d", &pages);

    printf("Enter page reference string:\n");
    for (int i = 0; i < pages; i++) {
        scanf("%d", &page[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    // initialize all frames as empty
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
    }

    int pageFaults = 0;

    // traverse all pages
    for (int i = 0; i < pages; i++) {

        int found = 0;

        // check if page already exists in frame
        for (int j = 0; j < frames; j++) {
            if (frame[j] == page[i]) {
                found = 1;
                break;
            }
        }

        // if page fault
        if (!found) {

            int pos = -1;

            // first check for empty frame
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // if no empty frame → apply optimal logic
            if (pos == -1) {

                int farthest = -1;

                for (int j = 0; j < frames; j++) {
                    int k;

                    // find next use of current frame page
                    for (k = i + 1; k < pages; k++) {
                        if (frame[j] == page[k]) {
                            break;
                        }
                    }

                    // if page is never used again
                    if (k == pages) {
                        pos = j;
                        break;
                    }

                    // choose farthest future use
                    if (k > farthest) {
                        farthest = k;
                        pos = j;
                    }
                }
            }

            // replace page
            frame[pos] = page[i];
            pageFaults++;
        }

        // print frame status
        printf("After page %d: ", page[i]);
        for (int j = 0; j < frames; j++) {
            if (frame[j] == -1)
                printf("- ");
            else
                printf("%d ", frame[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults = %d\n", pageFaults);
}

//! lru
void lru() {
    int pages;
    int frames;

    int page[50];
    int frame[50];
    int time[50];

    printf("Enter number of pages : ");
    scanf("%d",&pages);

    for(int i = 0; i < pages; ++i){
        scanf("%d",&page[i]);
    }

    printf("Enter number of frames : ");
    scanf("%d",&frames);

    for(int i = 0; i < frames; i++){
        time[i] = 0;
        frame[i] = -1;
    }

    int counter = 0;
    int pagefault = 0;

    for(int i = 0; i < pages; i++){
        int found = 0;

        for(int j = 0; j < frames; j++){
            if(frame[j] == page[i]){
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        if(!found){
            int pos = 0;

            // finding smallest
            for(int k = 1; k < frames; k++){
                if(time[k] < time[pos]){
                    pos = k;
                }
            }

            // replcaing
            frame[pos] = page[i];
            counter++;
            time[pos] = counter;
            pagefault++;
        }

        printf("After page %d:",page[i]);
        for(int l = 0; l < frames; l++){
            if(frame[l] == -1){
                printf("- ");
            }
            else{
                printf("%d",frame[l]);
            }
        }
        printf("\n");
    }

    printf("PAGE FAULT %d", pagefault);
}

//! lfu
void lfu(){
    int pages;
    int frames;
    int page[50];
    int frame[50];
    int count[50];
    int timer[50];

    printf("Enter number of pages: ");
    scanf("%d",&pages);

    for(int i = 0; i < pages; i++){
        scanf("%d",&page[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d",&frames);

    for(int i = 0; i < frames; i++){
        frame[i] = -1;
        count[i] = 0;
        timer[i] = 0;
    }

    int pagefault = 0;
    int time = 0;

    for(int i = 0; i < pages; i++){
        int found = 0;

        for(int j = 0; j < frames; j++){
            if(frame[j] == page[i]){
                count[j]++;
                found = 1;
                break;
            }
        }

        if(!found){
            int pos = 0;
            for(int k = 1; k < frames; k++){
                if(count[k] < count[pos]){
                    pos = k;
                }
                else if(count[k] == count[pos]){
                    if(timer[k] < timer[pos]){
                        pos = k;
                    }
                }
            }

            frame[pos] = page[i];
            count[pos] = 1;
            timer[pos] = time++;
            pagefault++;
        }

        printf("After page %d:",page[i]);
        for(int l = 0; l < frames; l++){
            if(frame[l] == -1){
                printf("- ");
            }
            else{
                printf("%d",frame[l]);
            }
        }
        printf("\n");
    }
    printf("PAGE FAULT %d", pagefault);
}

//! mfu
void mfu(){
    int pages;
    int frames;
    int page[50];
    int frame[50];
    int count[50];
    int timer[50];

    printf("Enter number of pages: ");
    scanf("%d",&pages);

    for(int i = 0; i < pages; i++){
        scanf("%d",&page[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d",&frames);

    for(int i = 0; i < frames; i++){
        frame[i] = -1;
        count[i] = 0;
        timer[i] = 0;
    }

    int pagefault = 0;
    int time = 0;

    for(int i = 0; i < pages; i++){
        int found = 0;

        for(int j = 0; j < frames; j++){
            if(frame[j] == page[i]){
                count[j]++;
                found = 1;
                break;
            }
        }

        if(!found){
            int pos = 0;
            for(int k = 1; k < frames; k++){
                if(count[k] > count[pos]){
                    pos = k;
                }
                else if(count[k] == count[pos]){
                    if(timer[k] < timer[pos]){
                        pos = k;
                    }
                }
            }

            frame[pos] = page[i];
            count[pos] = 1;
            timer[pos] = time++;
            pagefault++;
        }

        printf("After page %d:",page[i]);
        for(int l = 0; l < frames; l++){
            if(frame[l] == -1){
                printf("- ");
            }
            else{
                printf("%d",frame[l]);
            }
        }
        printf("\n");
    }
    printf("PAGE FAULT %d", pagefault);
}

//! mru
void mru() {
    int pages;
    int frames;

    int page[50];
    int frame[50];
    int time[50];

    printf("Enter number of pages : ");
    scanf("%d",&pages);

    for(int i = 0; i < pages; ++i){
        scanf("%d",&page[i]);
    }

    printf("Enter number of frames : ");
    scanf("%d",&frames);

    for(int i = 0; i < frames; i++){
        time[i] = 0;
        frame[i] = -1;
    }

    int counter = 0;
    int pagefault = 0;

    for(int i = 0; i < pages; i++){
        int found = 0;

        for(int j = 0; j < frames; j++){
            if(frame[j] == page[i]){
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        if(!found){
            int pos = 0;

            // finding smallest
            for(int k = 1; k < frames; k++){
                if(time[k] > time[pos]){
                    pos = k;
                }
            }

            // replcaing
            frame[pos] = page[i];
            counter++;
            time[pos] = counter;
            pagefault++;
        }

        printf("After page %d:",page[i]);
        for(int l = 0; l < frames; l++){
            if(frame[l] == -1){
                printf("- ");
            }
            else{
                printf("%d",frame[l]);
            }
        }
        printf("\n");
    }

    printf("PAGE FAULT %d", pagefault);
}

int main(){

    return 0;
}

