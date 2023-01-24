#include <stdio.h>
#include "mylib/mylib.h"
#include <termios.h>
#include <unistd.h>

int main(void) {
    int onoff, current1, current2, choice1, choice2;
    int nextstate[2];
    char input;
    struct termios old_tio, new_tio;

    printf("car blinker\n");
    printf("space before symbol = means to enter\n");
    //input
    printf("what is the current state ?\n");
    printf("0 0 = off\n");
    printf("1 0 = left light blinking\n");
    printf("0 1 = right light blinking\n");
    printf("1 1 = both lights blinking\n");
    printf("first number :\n");
    scanf("%d", &current1);
    printf("second number :\n");
    scanf("%d", &current2);
    if (current1 == 1 && current2 == 0){
        printf("Currently the left light is blinking\n");
    }
    else if (current1 == 0 && current2 == 1){
        printf("Currently the left light is blinking\n");
    }
    else if (current1 == 1 && current2 == 1){
        printf("Currently the left light is blinking\n");
    }
    else if (current1 == 0 && current2 == 0){
        printf("Currently it is off\n");
    }
    printf("what would you like to do ?\n");
    printf("0 0 = off\n");
    printf("1 0 = left light blinking\n");
    printf("0 1 = right light blinking\n");
    printf("1 1 = both lights blinking\n");
    printf("first number :\n");
    scanf("%d", &choice1);
    printf("second number :\n");
    scanf("%d", &choice2);
    if (choice1 == 0 && choice2 == 0){
        printf("you would like to turn off lights\n");
    } 
    else if (choice1 == 1 && choice2 == 0){
        printf("you would like to turn on the left blinker\n");
    }
    else if (choice1 == 0 && choice2 == 1){
        printf("you would like to turn on the right blinker\n");
    }
    else if (choice1 == 1 && choice2 == 1){
        printf("you would like to turn on both blinkers\n");
    }
    tcgetattr(STDIN_FILENO,&old_tio);
    new_tio=old_tio;
    new_tio.c_lflag &=(~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);
    while (1) {
        //light off
        if (current1 == 0 && current2 == 0) {
        printf("current state : \n");
        printf(" xxxxx\033[0m                          xxxxx\033[0m\n");
        printf("xxxxxxx\033[0m                        xxxxxxx\033[0m\n");
        printf(" xxxxx\033[0m                          xxxxx\033[0m\n");
        }
        //left light on
        if (current1 == 1 && current2 == 0) {
        printf("current state : \n");
        printf("\033[31m xxxxx\033[0m                          xxxxx\033[0m\n");
        printf("\033[31mxxxxxxx\033[0m                        xxxxxxx\033[0m\n");
        printf("\033[31m xxxxx\033[0m                          xxxxx\033[0m\n");
        }
        //right light on
        if (current1 == 0 && current2 == 1) {
        printf("current state : \n");
        printf(" xxxxx\033[0m                         \033[31m xxxxx\033[0m\n");
        printf("xxxxxxx\033[0m                       \033[31m xxxxxxx\033[0m\n");
        printf(" xxxxx\033[0m                         \033[31m xxxxx\033[0m\n");
        }
        //both light on
        if (current1 == 1 && current2 == 1) {
        printf("current state : \n");
        printf("\033[31m  xxxxx\033[0m                         \033[31m xxxxx\033[0m\n");
        printf("\033[31m xxxxxxx\033[0m                       \033[31m xxxxxxx\033[0m\n");
        printf("\033[31m  xxxxx\033[0m                         \033[31m xxxxx\033[0m\n");
        }
        printf("\n\n\n");
        //next state
        calcnextstate(current1, current2, choice1, choice2, nextstate);
        if (current1 == 1 && current2 == 1 && choice1 == 1 && choice2 == 1) {
            printf("Next State is 0 0\n\n\n\n");
        }else {printf("Next state is %d %d\n\n\n\n", nextstate[0], nextstate[1]);}

        if (current1 == 0 && current2 == 0 && choice1 == 0 && choice2 == 0 || 
            current1 == 1 && current2 == 0 && (choice1 == 0 || 1) && choice2 == 0 || 
            current1 == 0 && current2 == 1 && choice1 == 0 && (choice2 == 0 || 1) || 
            current1 == 1 && current2 == 1 && (choice1 == 0 || 1) && (choice2 == 0 || 1) ) {
            //all off
            printf("blinker becomes : \n");
            printf(" xxxxx\033[0m                          xxxxx\033[0m\n");
            printf("xxxxxxx\033[0m                        xxxxxxx\033[0m\n");
            printf(" xxxxx\033[0m                          xxxxx\033[0m\n");
            }
        if (current1 == 0 && current2 == 0 && choice1 == 1 && choice2 == 0 ||
            current1 == 0 && current2 == 1 && choice1 == 1 && choice2 == 0 ) {
            //left on 
            printf("blinker becomes : \n");
            printf("\033[31m xxxxx\033[0m                          xxxxx\033[0m\n");
            printf("\033[31mxxxxxxx\033[0m                        xxxxxxx\033[0m\n");
            printf("\033[31m xxxxx\033[0m                          xxxxx\033[0m\n");
            }
        if (current1 == 0 && current2 == 0 && choice1 == 0 && choice2 == 1 ||
            current1 == 1 && current2 == 0 && choice1 == 0 && choice2 == 1 ) {
            //right on
            printf("blinker becomes : \n");
            printf(" xxxxx\033[0m                         \033[31m xxxxx\033[0m\n");
            printf("xxxxxxx\033[0m                       \033[31m xxxxxxx\033[0m\n");
            printf(" xxxxx\033[0m                         \033[31m xxxxx\033[0m\n");
            }
                
        if (current1 == 0 && current2 == 0 && choice1 == 1 && choice2 == 1 ||
            current1 == 1 && current2 == 0 && choice1 == 1 && choice2 == 1 ||
            current1 == 0 && current2 == 1 && choice1 == 1 && choice2 == 1 ) {
            //both on
            printf("blinker becomes : \n");
            printf("\033[31m xxxxx\033[0m                         \033[31m xxxxx\033[0m\n");
            printf("\033[31mxxxxxxx\033[0m                       \033[31m xxxxxxx\033[0m\n");
            printf("\033[31m xxxxx\033[0m                         \033[31m xxxxx\033[0m\n");
            }
           
    fflush(stdout);
    printf("\nPress q to stop the loop: ");
    if (kbhit()) {
        input = getchar();
        if (input == 'q') {
            break;
        }
    }
    sleep(1);
    printf("\033c");
        
        printf("current state : \n");
        printf(" xxxxx\033[0m                          xxxxx\033[0m\n");
        printf("xxxxxxx\033[0m                        xxxxxxx\033[0m\n");
        printf(" xxxxx\033[0m                          xxxxx\033[0m\n");
        
        printf("\n\n\n");
        //next state
        calcnextstate(current1, current2, choice1, choice2, nextstate);
        if (current1 == 1 && current2 == 1 && choice1 == 1 && choice2 == 1) {
            printf("Next State is 0 0\n\n\n\n");
        }else {printf("Next state is %d %d\n\n\n\n", nextstate[0], nextstate[1]);}

        if (current1 == 0 && current2 == 0 && choice1 == 0 && choice2 == 0 || 
            current1 == 1 && current2 == 0 && (choice1 == 0 || 1) && choice2 == 0 || 
            current1 == 0 && current2 == 1 && choice1 == 0 && (choice2 == 0 || 1) || 
            current1 == 1 && current2 == 1 && (choice1 == 0 || 1) && (choice2 == 0 || 1) ) {
            //all off
                printf("blinker becomes : \n");
                printf(" xxxxx\033[0m                          xxxxx\033[0m\n");
                printf("xxxxxxx\033[0m                        xxxxxxx\033[0m\n");
                printf(" xxxxx\033[0m                          xxxxx\033[0m\n");
        }
        if (current1 == 0 && current2 == 0 && choice1 == 1 && choice2 == 0 ||
            current1 == 0 && current2 == 1 && choice1 == 1 && choice2 == 0 ) {
            //left on 
                printf("blinker becomes : \n");
                printf(" xxxxx\033[0m                          xxxxx\033[0m\n");
                printf("xxxxxxx\033[0m                        xxxxxxx\033[0m\n");
                printf(" xxxxx\033[0m                          xxxxx\033[0m\n");
            }
        if (current1 == 0 && current2 == 0 && choice1 == 0 && choice2 == 1 ||
            current1 == 1 && current2 == 0 && choice1 == 0 && choice2 == 1 ) {
            //right on
                printf("blinker becomes : \n");
                printf(" xxxxx\033[0m                          xxxxx\033[0m\n");
                printf("xxxxxxx\033[0m                        xxxxxxx\033[0m\n");
                printf(" xxxxx\033[0m                          xxxxx\033[0m\n");
            }        
        if (current1 == 0 && current2 == 0 && choice1 == 1 && choice2 == 1 ||
            current1 == 1 && current2 == 0 && choice1 == 1 && choice2 == 1 ||
            current1 == 0 && current2 == 1 && choice1 == 1 && choice2 == 1 ) {
            //both on
                printf("blinker becomes : \n");
                printf(" xxxxx\033[0m                          xxxxx\033[0m\n");
                printf("xxxxxxx\033[0m                        xxxxxxx\033[0m\n");
                printf(" xxxxx\033[0m                          xxxxx\033[0m\n");
            }        
    fflush(stdout);
    printf("\nPress q to stop the loop: ");
    if (kbhit()) {
        input = getchar();
        if (input == 'q') {
            break;
        }
    }
    sleep(1);
    printf("\033c");
    }  
    tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
    return 0;
}