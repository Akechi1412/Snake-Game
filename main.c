#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "console.h" 
#include <math.h>

#define MIN_Y_BOX 3 // y min coordinate of box
#define MIN_X_BOX 3 // x min coordinate of box
#define MAX_Y_BOX 17 //  y max coordinate of box
#define MAX_X_BOX 50 //  x max coordinate of box
#define MENU_LIST 5 // number of options in the menu
#define MIN_Y_MENU 2 // y min coordinate of menu
#define MIN_X_MENU 15 // x min coordinate of menu
#define MAX_Y_MENU 22 // y max coordinate of menu
#define MAX_X_MENU 55 // x max coordinate of menus
#define NUM_MODE 2 // number of game mode
#define NUM_LEVEL 4 // mumber of game level
#define MIN_X_CONSOLE 0
#define MIN_Y_CONSOLE 0
#define MAX_X_CONSOLE 0
#define MAX_Y_CONSOLE 0

const short X_RIGHT = MAX_X_BOX + 10;
const short Y_TOP = MIN_Y_BOX - 2;
const short Y_BOTTOM = MAX_Y_BOX + 2;
const short Y_RIGHT_TOP = MIN_Y_BOX;
const short X_BOTTOM_LEFT = MIN_X_BOX + 2; 

typedef struct {
    int x;
    int y;
} Dot;

typedef struct {
    char score[30];
    char name[30];
} SaveScore;

void gameLoadingScreen();
void menu();
int ateFood(); // handle when snake has eaten food
void classicMode(); 
void runGame(); 
void setupConsole(); 
void initGame(); // initialize the game
int checkDot(); // check if "Dot food" is the same as "Dot snake[]"
void moveSnake();
void drawFood();
void drawGame(); // draw additional skins for the game
void modernMode(); 
void drawSnake();
void drawGameBox(); // draw game frame
void firstSnake(); // create first snake
void snakeUndo(); // give the snake a step back
void selfBite(); // handle the snake biting itself
void inGame(); // handle in-game events 
void quitGame();
void aboutGame();
void gameMode();
void drawMenuBox();
void scoreUpdate(); // score and print to the screen
void pauseGame();
void controlSnake();
void gameOver(); // handle when game over
void enterPlayerName();
void exitInGame(); 
int checkReward(); // check if the snake has eaten the reward
void drawReward();
void getReward(); // handle when snake has eaten food
int checkDots(); // check if "reward" dots is the same as "Dot snake[]" 
void countdown(); // diem nguoc thoi gian bien mat cua reward
void stopCountdown();
void highScore(); 
void saveHighScore(); //save highs score to file
void getHighScoreClassic(); // get the high score of the classic mode and save it to the corresponding struct
void getHighScoreModern(); // get the high score of the modern mode and save it to the corresponding struct
void showHighScoreClassic(); 
void showHighScoreModern();
void updateHighScore();

char playerName[100]; 
int chose_mode = 0; // check if the player has chose the game mode
unsigned char key; // save the keys that the user presses in the game to handle
int score = 0; // init score = 0
int delay;
int end_game; // check end game
int snake_length;
Dot snake[500]; 
Dot food; 
Dot reward;
SaveScore high_score_classic[20];
SaveScore high_score_modern[20]; 
int count_score = 0; // count the number of score update
int count_time = 0; // time since reward appeared

// Direction for snake
enum direction {
    up,
    down,
    left,
    right
} derection;

enum mode {
    classic,
    modern
} mode;

enum level {
    noob = 1,
    normal = 2,
    difficult = 3,  
    professional = 4
} level;

int main(int argc, char* argv[]) {
    setupConsole();
    // gameLoadingScreen();
    menu();
    return 0;
}

void gameLoadingScreen() {
    setBothColor(0, 5);                                                    
    gotoxy(15, 5);
    printf(".d88888b                    dP");
    gotoxy(15, 6);
    printf("88.    \"'                   88");
    gotoxy(15, 7);
    printf("`Y88888b. 88d888b. .d8888b. 88  .dP  .d8888b.");
    gotoxy(15,8);
    printf("      `8b 88'  `88 88'  `88 88888\"   88ooood8");
    gotoxy(15, 9);
    printf("d8'   .8P 88    88 88.  .88 88  `8b. 88.  ...");
    gotoxy(15, 10);
    printf(" Y88888P  dP    dP `88888P8 dP   `YP `88888P'");
    setBothColor(0, 6);
    gotoxy(15, 11);
    printf("oooooooooooooooooooooooooooooooooooooooooooooo");
    setBothColor(0, 5);
    gotoxy(62, 12);
    printf(" .88888. ");
    gotoxy(62, 13);
    printf("d8'   `88");
    gotoxy(62, 14);
    printf("88        .d8888b. 88d8b.d8b. .d8888b.");
    gotoxy(62, 15);
    printf("88   YP88 88'  `88 88'`88'`88 88ooood8");
    gotoxy(62, 16);
    printf("Y8.   .88 88.  .88 88  88  88 88.  ...");
    gotoxy(62, 17);
    printf(" `88888'  `88888P8 dP  dP  dP `88888P'");
    setBothColor(0, 6);
    gotoxy(61, 18);
    printf("ooooooooooooooooooooooooooooooooooooooo");
    gotoxy(61, 11);
    printf("o");
    gotoxy(61, 12);
    printf("o");
    gotoxy(61, 13);
    printf("o");
    gotoxy(61, 14);
    printf("o");
    gotoxy(61, 15);
    printf("o");
    gotoxy(61, 16);
    printf("o");
    gotoxy(61, 17);
    printf("o");
    setBothColor(0, 1);
    gotoxy(100, 18);
    printf("#");

    Sleep(200);
    setBothColor(15, 15);
    for (int i = 20; i <= 100; ++i) {
        gotoxy(i, 24);
        printf("^");
    }
    setBothColor(0, 14);
    gotoxy(91, 23);
    printf("Loading...");
    for (int i = 20; i <= 52; ++i) {
        Sleep(50);
        setBothColor(0, 14);
        gotoxy(102, 24);
        printf("%3d%%", (i - 20) * 5 / 4);
        setBothColor(10, 10);
        gotoxy(i, 24);
        printf("^");
    }
    for (int i = 52; i <= 96; i += 4) {
        Sleep(200);
        setBothColor(0, 14);
        gotoxy(102, 24);
        printf("%3d%%", (i - 20) * 5 / 4);
        setBothColor(10, 10);
        gotoxy(i, 24);
        printf("^^^^");
    }
    Sleep(400);
    for (int i = 96; i <= 100; ++i) {
        Sleep(200);
        setBothColor(0, 14);
        gotoxy(102, 24);
        printf("%3d%%", (i - 20) * 5 / 4);
        setBothColor(10, 10);
        gotoxy(i, 24);
        printf("^");
    }
    Sleep(200);
}

void drawMenuBox() {
    clrscr();
    setBothColor(8, 8);
    // draw top menu box
    for (int i = MIN_X_MENU + 1; i < MAX_X_MENU; ++i) {
        gotoxy(i, MIN_Y_MENU);
        printf("*");
    }
    // draw bottom menu box
    for (int i = MIN_X_MENU + 1; i < MAX_X_MENU; ++i) {
        gotoxy(i, MAX_Y_MENU);
        printf("*");
    }
    // draw left menu box
    for (int i = MIN_Y_MENU; i <= MAX_Y_MENU; ++i) {
        gotoxy(MIN_X_MENU, i);
        printf("=");
    }
    // draw right menu box
    for (int i = MIN_Y_MENU; i <= MAX_Y_MENU; ++i) {
        gotoxy(MAX_X_MENU, i);
        printf("=");
    }
}

void menu() {
    system("color F1");
    drawMenuBox();
    const char* p_menu[] = {
        "NEW GAME ",
        "GAME MODE",
        "HIGH SCORE",
        "QUIT",
        "ABOUT"
    };
    int pointer = 0;
    while (1) {
        // show select list
        setBothColor(5, 15);
        gotoxy(MIN_X_MENU + 16, MIN_Y_MENU);
        printf("SNAKE GAME");
        for (int i = 0; i < MENU_LIST; ++i) {
            int k = i + 4;
            if (pointer == i) {
                setBothColor(0, 9);
                gotoxy((MAX_X_MENU + MIN_X_MENU) / 2 - strlen(p_menu[i]) / 2 - 3, MIN_Y_MENU + i + k);
                printf("  %c %s %c", 175, p_menu[i], 174);
            }
            else {
                setBothColor(0, 14);
                gotoxy((MAX_X_MENU + MIN_X_MENU) / 2 - strlen(p_menu[i]) / 2 - 3, MIN_Y_MENU + i + k);
                printf("[+] %s  ", p_menu[i]);
            }
        }
        // keyboard handling
        while (1) {
            char choose;
            if (_kbhit()) {
                choose = _getch();
                if (choose == 'w' || choose == 'W') {
                    if (pointer > 0) {
                        pointer--;
                    }
                    else {
                        pointer = MENU_LIST - 1;
                    }
                    break;
                }
                if (choose == 's' || choose == 'S') {
                    if (pointer < MENU_LIST - 1) {
                        pointer++;
                    }
                    else {
                        pointer = 0;
                    }
                    break;
                }
                if (choose == 13) {
                    switch (pointer) {
                        case 0:
                            Sleep(50);
                            inGame();
                        break;
                        case 1:
                            Sleep(50);
                            gameMode();
                        break;
                        case 2:
                            Sleep(50);
                            highScore();
                        break;
                        case 3:
                            Sleep(50);
                            quitGame();
                        break;
                        case 4:
                            Sleep(50);
                            aboutGame();
                        break;
                    }
                    break;
                }
            }
            Sleep(100);
        }
    }
}

int checkDot() {
    for (int i = 0; i < snake_length; ++i) {
        if (food.x == snake[i].x && food.y == snake[i].y) {
            return 0;
        }
    }
    return 1;
}

void drawGameBox() {
    setBothColor(8, 8);
    // draw top game box
    for (int i = MIN_X_BOX + 1; i < MAX_X_BOX; ++i) {
        gotoxy(i, MIN_Y_BOX);
        printf("*");
    }
    // draw bottom game box
    for (int i = MIN_X_BOX + 1; i < MAX_X_BOX; ++i) {
        gotoxy(i, MAX_Y_BOX);
        printf("*");
    }
    // draw left game box
    for (int i = MIN_Y_BOX; i <= MAX_Y_BOX; ++i) {
        gotoxy(MIN_X_BOX - 1, i);
        printf("==");
    }
    //draw right game box
    for (int i = MIN_Y_BOX; i <= MAX_Y_BOX; ++i) {
        gotoxy(MAX_X_BOX, i);
        printf("==");
    }
}

void drawFood() {
    time_t t;
    srand((unsigned)time(&t));
    food.x = rand() % (MAX_X_BOX - MIN_X_BOX - 1) + MIN_X_BOX+ 1;
    food.y = rand() % (MAX_Y_BOX - MIN_Y_BOX - 1) + MIN_Y_BOX + 1;
    gotoxy(food.x, food.y);
    setBothColor(4, 4);
    printf("=");
}

void firstSnake() {
    snake_length = 3;
    snake[0].x = (MAX_X_BOX + MIN_X_BOX) / 2 + 2 ; 
    snake[0].y = (MAX_Y_BOX + MIN_Y_BOX) / 2;
    snake[1].x = (MAX_X_BOX + MIN_X_BOX) / 2  + 1; 
    snake[1].y = (MAX_Y_BOX + MIN_Y_BOX) / 2;
    snake[2].x = (MAX_X_BOX + MIN_X_BOX) / 2  + 0;
    snake[2].y = (MAX_Y_BOX + MIN_Y_BOX) / 2;
}

void drawSnake() {
    setBothColor(11, 1);
    for (int i = 0; i < snake_length; i++) {
        gotoxy(snake[i].x, snake[i].y);
        if (i == 0) {
            setColor(1);
            printf("#");
        }
        else {
            setColor(6);
            printf("O");
        }
    }
}

void initGame() {
    clrscr();
    system("color B1");
    score = 0;
    end_game = 0;
    derection = right;
    firstSnake();
    drawSnake();
    do {
        drawFood();
    } while (checkDot == 0);
    drawGameBox();
}

void setupConsole() {
    SetConsoleTitle("Snake Game");
    setWindowConsole(100, 100, 680, 530);
    disableCtrButton(0, 0, 1);
    disableResizeWindow();
    showCur(0);
    hideScrollbar();
}

void moveSnake() {
    for (int i = snake_length; i > 0; --i) {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }
    if (derection == 0) {
        snake[0].y -= 1;
    }
    else if (derection == 1) {
        snake[0].y += 1;
    }
    else if (derection == 2) {
        snake[0].x -= 1;
    }
    else if (derection == 3) {
        snake[0].x += 1;
    }
    drawSnake();
}

void pauseGame() {
    setBothColor(5, 7);
    gotoxy(MIN_X_BOX + (MAX_X_BOX - MIN_X_BOX) / 2 - 5, MIN_Y_BOX+ (MAX_Y_BOX - MIN_Y_BOX) / 2);
    printf("PAUSE GAME");
    key = _getch();
    while (key != 32) {
        key = _getch();
        Sleep(0);
    }
    setBothColor(11, 11);
    gotoxy(MIN_X_BOX + (MAX_X_BOX - MIN_X_BOX) / 2 - 5, MIN_Y_BOX + (MAX_Y_BOX - MIN_Y_BOX) / 2);
    printf("          ");
    Sleep(1000);
}

void controlSnake() {
    if (_kbhit()) {
        key = _getch();
        if ((key == 'w' || key == 'W') && derection != 1) {
            derection = up;
        }
        else if ((key == 's' || key == 'S') && derection != 0) {
            derection = down;
        }
        else if ((key == 'a' || key == 'A') && derection != 3) {
            derection = left;
        }
        else if ((key == 'd' || key == 'D') && derection != 2) {
            derection = right;
        }
        else if (key == 32){
            pauseGame();
        }
        else if (key == 27) {
            exitInGame();
        }
    }
}

void runGame() {
    Sleep(1000);
    delay = 5 * (int)pow(level, 2) - 45 * level + 120;
    while (1) {
        moveSnake();
        controlSnake();
        selfBite();
        // choose default mode is classic
        if (chose_mode == 0) {
            classicMode();
        }
        else if (mode == 1){
            modernMode();
        }
        else if (mode == 0) {
            classicMode();
        }
        // handling snakes eat prey
        static int checkDrawReward = 0;
        if (ateFood() && count_score < 5) {
            score += 10;
            count_score++;
            scoreUpdate();
            setBothColor(11, 6);
            gotoxy(snake[snake_length].x, snake[snake_length].y);
            printf("O");
            snake_length++;
            if (count_score < 5) {
                do {
                    drawFood();
                } 
                while (checkDot() == 0);
            }
        }
        else if (ateFood() == 0) {
            setBothColor(11, 11);
            gotoxy(snake[snake_length].x, snake[snake_length].y);
            printf(" ");
        }
        if (count_score == 5) {
            if (checkDrawReward == 0) {
                count_time = 0;
                do {
                    drawReward();
                    if (checkDots == 0) {
                        gotoxy(reward.x, reward.y);
                        printf("  ");
                    }
                }           
                while (checkDots == 0);
                checkDrawReward = 1;
            }
            countdown();
            if (checkReward()) {
                count_score = 0;
                getReward();
                stopCountdown();
                checkDrawReward = 0;
                do {
                    drawFood();
                }               
                while (checkDot() == 0);
            }
            else if (count_time >= 5200) {
                count_score = 0;
                checkDrawReward = 0;
                do {
                    drawFood();
                }               
                while (checkDot() == 0);
            }
        }
        // handling end game
        gameOver();
        // handling delay (speed)
        if (derection == 0 || derection == 1) {
            count_time += (int)(2.5 * delay);
            Sleep((int)(2.5*delay));
        }
        else {
            count_time += delay;
            Sleep(delay);
        }
    }
}

void gameOver() {
    setBothColor(5, 7);
    if (end_game == 1) {
        if (mode == 0) {
            strcpy(high_score_classic[5].name, playerName);
            _itoa(score, high_score_classic[5].score, 10);
        }
        else if (mode == 1) {
            strcpy(high_score_modern[5].name, playerName);
            _itoa(score, high_score_modern[5].score, 10);
        }
        updateHighScore();

        gotoxy((MAX_X_BOX + MIN_X_BOX) / 2 - 5, (MAX_Y_BOX + MIN_Y_BOX) / 2 - 2);
        printf("Game Over!");
        Sleep(200);
        gotoxy((MAX_X_BOX + MIN_X_BOX) / 2 - 7, (MAX_Y_BOX + MIN_Y_BOX) / 2);
        printf("Your Score: %d", score);
        Sleep(200);
        // gotoxy(MIN_X_BOX + (MAX_X_BOX - MIN_X_BOX) / 2 - 15, MIN_Y_BOX + (MAX_Y_BOX - MIN_Y_BOX) / 2 + 2);
        // printf("Do you want to play again? (Y/N)");
        // unsigned char ch = _getch();
        // while (1) {
        //     if (ch == 'y' || ch == 'Y') {
        //         Sleep(200);
        //         initGame();
        //         drawGame();
        //         runGame();
        //     }
        //     else if (ch == 'n' || ch == 'N') {
        //         Sleep(50);
        //         menu();
        //     }
        //     else {
        //         ch = _getch();
        //     }
        // }
        const char* p_select[] = {
        "PLAY AGAIN",
        "MENU"
        };
        int pointer = 0;
        while (1) {
            // show selector list
            for (int i = 0; i < 2; ++i) {
                if (pointer == i) {
                    setBothColor(14, 2);
                    if (i == 0) {
                        gotoxy((MIN_X_BOX + MAX_X_BOX) / 2 - 13, (MAX_Y_BOX + MIN_Y_BOX) / 2 + 2);
                        printf(" %c%s%c ", 175, p_select[i], 174);
                    }
                    else if (i == 1) {
                        gotoxy((MIN_X_BOX + MAX_X_BOX) / 2 + 6, (MAX_Y_BOX + MIN_Y_BOX) / 2 + 2);
                        printf("%c%s%c", 175, p_select[i], 174);
                    }
                }
                else {
                    setBothColor(14, 0);
                    if (i == 0) {
                        gotoxy((MIN_X_BOX + MAX_X_BOX) / 2 - 13, (MAX_Y_BOX + MIN_Y_BOX) / 2 + 2);
                        printf("  %s  ", p_select[i]);
                    }
                    else if (i == 1) {
                        gotoxy((MIN_X_BOX + MAX_X_BOX) / 2 + 6, (MAX_Y_BOX + MIN_Y_BOX) / 2 + 2);
                        printf(" %s ",  p_select[i]);
                    }
                }
            }
            // keyboard handling
            while (1) {
                unsigned char choose;
                if (_kbhit()) {
                    choose = _getch();
                    if (choose == 'a' || choose == 'A') {
                        if (pointer == 1) {
                            pointer = 0;
                        }
                        else {
                            pointer = 1;
                        }
                        break;
                    }
                    if (choose == 'd' || choose == 'D') {
                        if (pointer == 0) {
                            pointer = 1;
                        }
                        else {
                            pointer = 0;
                        }
                        break;
                    }
                    if (choose == 13) {
                        switch (pointer) {
                            case 0:
                                Sleep(200);
                                initGame();
                                drawGame();
                                runGame();
                            break;
                            case 1:
                                menu();
                            break;
                        }
                    }
                    Sleep(100);
                }
            }
        }
    }
}

void classicMode() {
    setBothColor(8, 8);
    if (snake[0].x == MAX_X_BOX) {
        gotoxy(snake[0].x, snake[0].y);
        printf("=");
        snake[0].x = MIN_X_BOX + 1;
    }
    else if (snake[0].x == MIN_X_BOX) {
        gotoxy(snake[0].x, snake[0].y);
        printf("=");
        snake[0].x = MAX_X_BOX - 1;
    }
    else if (snake[0].y == MAX_Y_BOX) {
        gotoxy(snake[0].x, snake[0].y);
        printf("*");
        snake[0].y = MIN_Y_BOX + 1;
    }
    else if (snake[0].y == MIN_Y_BOX) {
        gotoxy(snake[0].x, snake[0].y);
        printf("*");
        snake[0].y = MAX_Y_BOX - 1;
    }
}

void snakeUndo() {
    for (int i = 0; i <= snake_length; ++i) {
        snake[i].x = snake[i + 1].x;
        snake[i].y = snake[i + 1].y;
    }
}

void modernMode() {
    setBothColor(8, 8);
    if (snake[0].x == MAX_X_BOX) {
        gotoxy(snake[0].x, snake[0].y);
        printf("=");
        snakeUndo();
        drawSnake();
        end_game = 1;
    }
    else if (snake[0].x == MIN_X_BOX) {
        gotoxy(snake[0].x, snake[0].y);
        printf("=");
        snakeUndo();
        drawSnake();
        end_game = 1;
    }
    else if (snake[0].y == MAX_Y_BOX) {
        gotoxy(snake[0].x, snake[0].y);
        printf("*");
        snakeUndo();
        drawSnake();
        end_game = 1;
    }
    else if (snake[0].y == MIN_Y_BOX) {
        gotoxy(snake[0].x, snake[0].y);
        printf("*");
        snakeUndo();
        drawSnake();
        end_game = 1;
    }
}

void selfBite() {
    for (int i = 1; i < snake_length; ++i) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            snakeUndo();
            drawSnake();
            end_game = 1;
            break;
        }
    }
}

int ateFood() {
    return (snake[0].x == food.x && snake[0].y == food.y);
}

void inGame() {
    clrscr();
    system("color F1");
    drawMenuBox();
    const char* p_level[] = {
        "NOOB",
        "NORMAl",
        "DIFFICULT",
        "PROFESSIONAL"
    };
    int pointer = 0;
    while (1) {
        // show selector list
        setBothColor(5, 15);
        gotoxy(MIN_X_MENU + 17, MIN_Y_MENU);
        printf("NEW GAME");
        for (int i = 0; i < NUM_LEVEL; ++i) {
            int k = i + 6;
            if (pointer == i) {
                setBothColor(0, 9);
                gotoxy((MAX_X_MENU + MIN_X_MENU) / 2 - strlen(p_level[i]) / 2 - 3, MIN_Y_MENU + i + k);
                printf("  %c %s %c", 175, p_level[i], 174);
            }
            else {
                setBothColor(0, 14);
                gotoxy((MAX_X_MENU + MIN_X_MENU) / 2 - strlen(p_level[i]) / 2 - 3, MIN_Y_MENU + i + k);
                printf("[+] %s  ", p_level[i]);
            }
        }
        // keyboard handling
        while (1) {
            unsigned char choose;
            if (_kbhit()) {
                choose = _getch();
                if (choose == 'w' || choose == 'W') {
                    if (pointer > 0) {
                        pointer--;
                    }
                    else {
                        pointer = NUM_LEVEL - 1;
                    }
                    break;
                }
                if (choose == 's' || choose == 'S') {
                    if (pointer < NUM_LEVEL - 1) {
                        pointer++;
                    }
                    else {
                        pointer = 0;
                    }
                    break;
                }
                if (choose == 13) {
                    switch (pointer) {
                        case 0:
                            level = noob;
                        break;
                        case 1:
                            level = normal;
                        break;
                        case 2:
                            level = difficult;
                        break;
                        case 3:
                            level = professional;
                        break;
                    }
                    enterPlayerName();
                    initGame();
                    drawGame();
                    runGame();
                    break;
                }
            }
            Sleep(100);
        }
    }
}

void quitGame() {
    clrscr();
    system("Color F1");
    drawMenuBox();
    setBothColor(5, 15);
    gotoxy(MIN_X_MENU + 18, MIN_Y_MENU);
    printf("QUIT");
    setBothColor(15, 6);
    gotoxy((MAX_X_MENU + MIN_X_MENU) / 2 - 17, (MAX_Y_MENU + MIN_Y_MENU) / 2 - 3);
    printf("Are you sure want to quit the game?");
    // gotoxy((MAX_X_MENU + MIN_X_MENU) / 2 - 13, (MAX_Y_MENU + MIN_Y_MENU) / 2 - 1);
    // printf("You have to choose Y or N!");
    // unsigned char ch = _getch();
    // while (1) {
    //     if (ch == 'y' || ch == 'Y') {
    //         Sleep(50);
    //         clrscr();
    //         system("color F0");
    //         exit(0);
    //     }
    //     else if (ch == 'n' || ch == 'N') {
    //         Sleep(50);
    //         menu();
    //     }
    //     else {
    //         ch = _getch();
    //     }
    // }
    const char* p_select[] = {
        "QUIT",
        "MENU"
    };
    int pointer = 0;
    while (1) {
        // show selector list
        for (int i = 0; i < 2; ++i) {
            if (pointer == i) {
                setBothColor(14, 2);
                if (i == 0) {
                    gotoxy(MIN_X_MENU + 5, MAX_Y_MENU - 8);
                    printf(" %c%s%c ", 175, p_select[i], 174);
                }
                else if (i == 1) {
                    gotoxy(MAX_X_MENU - 12, MAX_Y_MENU - 8);
                    printf("%c%s%c", 175, p_select[i], 174);
                }
            }
            else {
                setBothColor(14, 0);
                if (i == 0) {
                    gotoxy(MIN_X_MENU + 5, MAX_Y_MENU - 8);
                    printf("  %s  ", p_select[i]);
                }
                else if (i == 1) {
                    gotoxy(MAX_X_MENU - 12, MAX_Y_MENU - 8);
                    printf(" %s ",  p_select[i]);
                }
            }
        }
        // keyboard handling
        while (1) {
            unsigned char choose;
            if (_kbhit()) {
                choose = _getch();
                if (choose == 'a' || choose == 'A') {
                    if (pointer == 1) {
                        pointer = 0;
                    }
                    else {
                        pointer = 1;
                    }
                    break;
                }
                if (choose == 'd' || choose == 'D') {
                    if (pointer == 0) {
                        pointer = 1;
                    }
                    else {
                        pointer = 0;
                    }
                    break;
                }
                if (choose == 13) {
                        switch (pointer) {
                        case 0:
                            exit(0);
                        break;
                        case 1:
                            menu();
                        break;
                    }
                }
                Sleep(100);
            }
        }
    }
}

void gameMode() {
    clrscr();
    system("color F1");
    drawMenuBox();
    const char* p_mode[] = { 
        "CLASSIC",
        "MODERN" 
    };
    int pointer = 0;
    while (1) {
        // show selector list
        setBothColor(5, 15);
        gotoxy(MIN_X_MENU + 16, MIN_Y_MENU);
        printf("GAME MODE");
        for (int i = 0; i < NUM_MODE; ++i) {
            int k = i + 8;
            if (pointer == i) {
                setBothColor(0, 9);
                gotoxy((MAX_X_MENU + MIN_X_MENU) / 2 - strlen(p_mode[i]) / 2 - 3, MIN_Y_MENU + i + k);
                printf("  %c %s %c", 175, p_mode[i], 174);
            }
            else {
                setBothColor(0, 14);
                gotoxy((MAX_X_MENU + MIN_X_MENU) / 2 - strlen(p_mode[i]) / 2 - 3, MIN_Y_MENU + i + k);
                printf("[+] %s  ", p_mode[i]);
            }
        }
        // keyboard handling
        while (1) {
            unsigned char choose;
            if (_kbhit()) {
                choose = _getch();
                if (choose == 'w' || choose == 'W') {
                    if (pointer > 0) {
                        pointer--;
                    }
                    else {
                        pointer = NUM_MODE - 1;
                    }
                    break;
                }
                if (choose == 's' || choose == 'S') {
                    if (pointer < NUM_MODE - 1) {
                        pointer++;
                    }
                    else {
                        pointer = 0;
                    }
                    break;
                }
                if (choose == 13) {
                    chose_mode = 1;
                    switch (pointer) {
                        case 0:
                            mode = classic;
                        break;
                        case 1:
                            mode = modern;
                        break;
                    }
                    Sleep(50);
                    menu();
                }
                Sleep(100);
            }
        }
    }
}

void scoreUpdate() {
    int tmp = score, count = 0;
    while (tmp > 0) {
        count++;
        tmp /= 10;
    }
    setBothColor(2, 7);
    gotoxy(X_RIGHT - count / 2, Y_RIGHT_TOP + 6);
    printf("%d", score);
}

void aboutGame() {
    clrscr();
    system("Color F1");
    drawMenuBox();
    setBothColor(5, 15);
    gotoxy(MIN_X_MENU + 18, MIN_Y_MENU);
    printf("ABOUT");
    setBothColor(15, 6);
    gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 8, MIN_Y_MENU + 3);
    printf("Akechi Snake Game");
    gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 9, MIN_Y_MENU + 6);
    printf("Development Platform ");
    gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 4, MIN_Y_MENU + 9);
    printf("Developer");
    gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 5, MIN_Y_MENU + 12);
    printf("Contact Info");

    setBothColor(15, 1);
    gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 6, MIN_Y_MENU + 4);
    printf("Version 2.0.2");
    gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 15, MIN_Y_MENU + 7);
    printf("C language in Windows console");
    gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 3, MIN_Y_MENU + 10);
    printf("Akechi");
     gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 17, MIN_Y_MENU + 13);
    printf("https://www.facebook.com/akechi1412");

    setBothColor(15, 8);
    gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 1, MIN_Y_MENU + 5);
    printf("***");
    gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 1, MIN_Y_MENU + 8);
    printf("***");
    gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 1, MIN_Y_MENU + 11);
    printf("***");

    // setBothColor(15, 1);
    // gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 15, MIN_Y_MENU + 16);
    // printf("Press any key to continue....");
    // while (1) {
    //     if (_kbhit()) {
    //         menu();
    //     }
    // }

    const char* p_select[] = {
        "MENU",
        "RETURN"
    };
    int pointer = 0;
    while (1) {
        // show selector list
        for (int i = 0; i < 2; ++i) {
            if (pointer == i) {
                setBothColor(14, 2);
                if (i == 0) {
                    gotoxy(MIN_X_MENU + 5, MIN_Y_MENU + 16);
                    printf(" %c%s%c ", 175, p_select[i], 174);
                }
                else if (i == 1) {
                    gotoxy(MAX_X_MENU - 12, MIN_Y_MENU + 16);
                    printf("%c%s%c", 175, p_select[i], 174);
                }
            }
            else {
                setBothColor(14, 0);
                if (i == 0) {
                    gotoxy(MIN_X_MENU + 5, MIN_Y_MENU + 16);
                    printf("  %s  ", p_select[i]);
                }
                else if (i == 1) {
                    gotoxy(MAX_X_MENU - 12, MIN_Y_MENU + 16);
                    printf(" %s ",  p_select[i]);
                }
            }
        }
        // keyboard handling
        while (1) {
            unsigned char choose;
            if (_kbhit()) {
                choose = _getch();
                if (choose == 'a' || choose == 'A') {
                    if (pointer == 1) {
                        pointer = 0;
                    }
                    else {
                        pointer = 1;
                    }
                    break;
                }
                if (choose == 'd' || choose == 'D') {
                    if (pointer == 0) {
                        pointer = 1;
                    }
                    else {
                        pointer = 0;
                    }
                    break;
                }
                if (choose == 13) {
                    switch (pointer) {
                        case 0:
                            menu();
                        break;
                        case 1:
                            menu();
                        break;
                    }
                }
                Sleep(100);
            }
        }
    }
}

void drawGame() {
    setBothColor(1, 7);
    gotoxy(X_RIGHT - 5, Y_RIGHT_TOP);
    printf("%-7s", "PLAYER NAME");
    gotoxy(X_RIGHT - 2, Y_RIGHT_TOP + 4);
    printf("%-5s", "SCORE");
    gotoxy(X_RIGHT - 2, Y_RIGHT_TOP + 8);
    printf("%-5s", "MODE");
    gotoxy(X_RIGHT - 2, Y_RIGHT_TOP + 12);
    printf("%-5s", "LEVEL");

    setBothColor(11, 8);
    gotoxy(X_RIGHT - 1, Y_RIGHT_TOP + 3);
    printf("***");
    gotoxy(X_RIGHT - 1, Y_RIGHT_TOP + 7);
    printf("***");
    gotoxy(X_RIGHT - 1, Y_RIGHT_TOP + 11);
    printf("***");

    setBothColor(2, 7);
    gotoxy(X_RIGHT - (strlen(playerName) - 1) / 2, Y_RIGHT_TOP + 2);
    printf("%s", playerName);
    gotoxy(X_RIGHT, Y_RIGHT_TOP + 6);
    printf("%d", score);

    if (mode == 0) {
        gotoxy(X_RIGHT - 3, Y_RIGHT_TOP + 10);
        printf("%-7s", "Classic");
    }
    else if (mode == 1) {
        gotoxy(X_RIGHT - 3, Y_RIGHT_TOP + 10);
        printf("%-7s", "Modern");
    }
    if (level == 1) {
        gotoxy(X_RIGHT - 2, Y_RIGHT_TOP + 14);
        printf("%-5s", "Noob");
    }
    else if (level == 2) {
        gotoxy(X_RIGHT - 3, Y_RIGHT_TOP + 14);
        printf("%-7s", "Normal");
    }
    else if (level == 3) {
        gotoxy(X_RIGHT - 4, Y_RIGHT_TOP + 14);
        printf("%-9s", "Difficult");
    }
    else if (level == 4) {
        gotoxy(X_RIGHT - 6, Y_RIGHT_TOP + 14);
        printf("%-13s", "Professional");
    }

    setBothColor(1, 7);
    gotoxy(X_BOTTOM_LEFT, Y_BOTTOM);
    printf("W, S, A, D:");
    setBothColor(2, 7);
    gotoxy(X_BOTTOM_LEFT + 12, Y_BOTTOM);
    printf("Up, Dow, Left, Right");
    setBothColor(1, 7);
    gotoxy(X_BOTTOM_LEFT, Y_BOTTOM + 2);
    printf("Space:");
    setBothColor(2, 7);
    gotoxy(X_BOTTOM_LEFT + 7, Y_BOTTOM + 2);
    printf("Pause/Continue");
    setBothColor(1, 7);
    gotoxy(X_BOTTOM_LEFT + 23, Y_BOTTOM + 2);
    printf("Esc:");
    setBothColor(2, 7);
    gotoxy(X_BOTTOM_LEFT + 28, Y_BOTTOM + 2);
    printf("Exit");
    setBothColor(11, 0);
    gotoxy(X_BOTTOM_LEFT + 40, Y_BOTTOM);
    printf("Akechi Snake Game");
    gotoxy(X_BOTTOM_LEFT + 40, Y_BOTTOM + 2);
    printf("  Version 2.0.2  ");

    setBothColor(11, 8);
    gotoxy(X_BOTTOM_LEFT + 15, Y_BOTTOM + 1);
    printf("***");
     gotoxy(X_BOTTOM_LEFT + 47, Y_BOTTOM + 1);
    printf("***");
}

void enterPlayerName() {
    clrscr();
    system("color F1");
    drawMenuBox();
    setBothColor(5, 15);
    gotoxy(MIN_X_MENU + 17, MIN_Y_MENU);
    printf("NEW GAME");
    setBothColor(15, 6);
    gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 8, (MIN_Y_MENU + MAX_Y_MENU) / 2 - 4);
    printf("ENTER YOUR NAME!");

    int begin_input = (MIN_X_MENU + MAX_X_MENU) / 2 - 10;
    int end_input = (MIN_X_MENU + MAX_X_MENU) / 2 + 10;
    setBothColor(2, 2);
    for (int i = begin_input; i < end_input; ++i) {
        gotoxy(i, (MIN_Y_MENU + MAX_Y_MENU) / 2 - 2);
        printf("^");
    }
    setBothColor(15, 6);
    gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 16, (MIN_Y_MENU + MAX_Y_MENU) / 2);
    printf("If you don't want to enter a name,");
    gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 16, (MIN_Y_MENU + MAX_Y_MENU) / 2 + 1);
    printf("press enter to continue");
    setBothColor(2, 7);
    gotoxy(begin_input, (MIN_Y_MENU + MAX_Y_MENU) / 2 - 2);
    showCur(1);
    fgets(playerName, sizeof playerName, stdin);
    showCur(0);

    int a = playerName[0] < 'a' || playerName[0] > 'z';
    int b = playerName[0] < 'A' || playerName[0] > 'Z';
    int c = playerName[0] < '0' || playerName[0] > '9';

    while ((strlen(playerName) - 1 > 20) || (a && b && c)) {
        if (playerName[0] == '\n') {
            break;
        }
        setBothColor(2, 2);
        for (int i = begin_input; i < end_input; ++i) {
            gotoxy(i, (MIN_Y_MENU + MAX_Y_MENU) / 2 - 2);
            printf("^");
        }
        if (strlen(playerName) - 1 > 20) {
            for (int i = end_input; i < (begin_input + strlen(playerName)); ++i) {
                gotoxy(i, (MIN_Y_MENU + MAX_Y_MENU) / 2 - 2);
                if (i == MAX_X_MENU) {
                    setBothColor(8, 8);
                    printf("=");
                }
                setBothColor(15, 15);
                printf(" ");
            }
            setBothColor(15, 4);
            gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 18, (MIN_Y_MENU + MAX_Y_MENU) / 2 + 3);
            printf("Error: Please enter name less than 20");
            gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 18, (MIN_Y_MENU + MAX_Y_MENU) / 2 + 4);
            printf("characters!");
        }
        else if (a && b && c) {
            setBothColor(15, 4);
            gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 18, (MIN_Y_MENU + MAX_Y_MENU) / 2 + 3);
            printf("Error: Player name must begin with a");
            gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 11, (MIN_Y_MENU + MAX_Y_MENU) / 2 + 4);
            printf("letter or a number!");
        }

        setBothColor(2, 7);
        gotoxy(begin_input, (MIN_Y_MENU + MAX_Y_MENU) / 2 - 2);
        showCur(1);
        fgets(playerName, sizeof playerName, stdin);
        showCur(0);
        a = playerName[0] < 'a' || playerName[0] > 'z';
        b = playerName[0] < 'A' || playerName[0] > 'Z';
        c = playerName[0] < '0' || playerName[0] > '9';
        Sleep(200);
    }

    if (strlen(playerName) - 1 == 0) {
        strcpy_s(playerName, sizeof playerName, "#No_name");
    }
    else {
        playerName[strlen(playerName) - 1] = '\0';
        int k = strlen(playerName) - 1;
        while (playerName[k] == ' ') {
            k--;
        }
        playerName[k + 1] = '\0';
    }
}

void exitInGame() {
    setBothColor(5, 7);
    // gotoxy((MAX_X_BOX + MIN_X_BOX) / 2 - 15, (MAX_Y_BOX + MIN_Y_BOX) / 2 - 1);
    // printf("Do you want to give up? (Y/N)");
    gotoxy((MAX_X_BOX + MIN_X_BOX) / 2 - 14, (MAX_Y_BOX + MIN_Y_BOX) / 2 + 1);
    printf("Your score will not be save!!");

    // unsigned char ch = _getch();
    // while (1) {
    //     if (ch == 'y' || ch == 'Y') {
    //         Sleep(200);
    //         menu();
    //     }
    //     else if (ch == 'n' || ch == 'N') {
    //         setBothColor(11, 11);
    //         gotoxy(MIN_X_BOX + (MAX_X_BOX - MIN_X_BOX) / 2 - 15, MIN_Y_BOX + (MAX_Y_BOX - MIN_Y_BOX) / 2 - 1);
    //         printf("                              ");
    //         gotoxy(MIN_X_BOX + (MAX_X_BOX - MIN_X_BOX) / 2 - 15, MIN_Y_BOX + (MAX_Y_BOX - MIN_Y_BOX) / 2 + 1);
    //         printf("                              ");
    //         Sleep(1000);
    //         break;
    //     }
    //     else {
    //         ch = _getch();
    //     }
    // }

    const char* p_select[] = {
        "EXIT",
        "CONTINUE"
    };
    int pointer = 0;
    while (1) {
        // show selector list
        for (int i = 0; i < 2; ++i) {
            if (pointer == i) {
                setBothColor(14, 2);
                if (i == 0) {
                    gotoxy((MIN_X_BOX + MAX_X_BOX) / 2 - 10, (MAX_Y_BOX + MIN_Y_BOX) / 2 - 1);
                    printf(" %c%s%c ", 175, p_select[i], 174);
                }
                else if (i == 1) {
                    gotoxy((MIN_X_BOX + MAX_X_BOX) / 2 + 4, (MAX_Y_BOX + MIN_Y_BOX) / 2 - 1);
                    printf("%c%s%c", 175, p_select[i], 174);
                }
            }
            else {
                setBothColor(14, 0);
                if (i == 0) {
                    gotoxy((MIN_X_BOX + MAX_X_BOX) / 2 - 10, (MAX_Y_BOX + MIN_Y_BOX) / 2 - 1);
                    printf("  %s  ", p_select[i]);
                }
                else if (i == 1) {
                    gotoxy((MIN_X_BOX + MAX_X_BOX) / 2 + 4, (MAX_Y_BOX + MIN_Y_BOX) / 2 - 1);
                    printf(" %s ",  p_select[i]);
                }
            }
        }
        // keyboard handling
        unsigned char choose;
        while (1) {
            if (_kbhit()) {
                choose = _getch();
                if (choose == 'a' || choose == 'A') {
                    if (pointer == 1) {
                        pointer = 0;
                    }
                    else {
                        pointer = 1;
                    }
                    break;
                }
                if (choose == 'd' || choose == 'D') {
                    if (pointer == 0) {
                        pointer = 1;
                    }
                    else {
                        pointer = 0;
                    }
                    break;
                }
                if (choose == 13) {
                    switch (pointer) {
                        case 0:
                            menu();
                        break;
                        case 1:
                            setBothColor(11, 11);
                            gotoxy((MAX_X_BOX + MIN_X_BOX) / 2 - 15, (MAX_Y_BOX + MIN_Y_BOX) / 2 - 1);
                            printf("                              ");
                            gotoxy((MAX_X_BOX + MIN_X_BOX) / 2 - 15, (MAX_Y_BOX + MIN_Y_BOX) / 2 + 1);
                            printf("                              ");
                            Sleep(1000);
                        break;
                    }
                    break;
                }
            }
        }
        if (choose == 13) {
            break;
        }
    }
}

int checkDots() {
    for (int i = 0; i < snake_length; ++i) {
        if (reward.x == snake[i].x && reward.y == snake[i].y) {
            return 0;
        }
        if ((reward.x + 1) == snake[i].x && reward.y == snake[i].y) {
            return 0;
        }
    }
    return 1;
}

void getReward() {
    snakeUndo();
    gotoxy(reward.x, reward.y);
    setBothColor(11, 11);
    printf("  ");
    score += (5200 - count_time) / 20 * (snake_length / 20 + 1);
    scoreUpdate();
}

void drawReward() {
    time_t s;
    srand((unsigned)time(&s));
    reward.x = rand() % (MAX_X_BOX - MIN_X_BOX - 2) + MIN_X_BOX + 1;
    reward.y = rand() % (MAX_Y_BOX - MIN_Y_BOX - 1) + MIN_Y_BOX + 1;
    gotoxy(reward.x, reward.y);
    setBothColor(5, 5);
    printf("==");
}

int checkReward() {
    if (reward.x == snake[0].x && reward.y == snake[0].y) {
        return 1;
    }
    return ((reward.x + 1) == snake[0].x && reward.y == snake[0].y);
}

void countdown() {
    setBothColor(5, 7);
    gotoxy((MIN_X_BOX + MAX_X_BOX) / 2 - 6, Y_TOP);
    printf("COUNTDOWN");
    gotoxy((MIN_X_BOX + MAX_X_BOX) / 2 + 5, Y_TOP);
    printf(" 5 ");
    if (count_time >= 1000 && count_time < 2000) {
        gotoxy((MIN_X_BOX + MAX_X_BOX) / 2 + 5, Y_TOP);
        printf(" 4 ");
    }
    else if (count_time >= 2000 && count_time < 3000) {
        gotoxy((MIN_X_BOX + MAX_X_BOX) / 2 + 5, Y_TOP);
        printf(" 3 ");
    }
    else if (count_time >= 3000 && count_time < 4000) {
        gotoxy((MIN_X_BOX + MAX_X_BOX) / 2 + 5, Y_TOP);
        printf(" 2 ");
    }
    else if (count_time >= 4000 && count_time < 5000) {
        gotoxy((MIN_X_BOX + MAX_X_BOX) / 2 + 5, Y_TOP);
        printf(" 1 ");
    }
    else if (count_time >= 5000 && count_time < 5200) {
        gotoxy((MIN_X_BOX + MAX_X_BOX) / 2 + 5, Y_TOP);
        printf(" 0 ");
        setBothColor(11, 11);
        gotoxy(reward.x, reward.y);
        printf("  ");
        reward.x = 0;
        reward.y = 0;
    }
    else if (count_time >= 5200) {
        stopCountdown();
    }
}

void stopCountdown() {
    setBothColor(11, 11);
    gotoxy((MIN_X_BOX + MAX_X_BOX) / 2 - 6, Y_TOP);
    printf("              ");
}

void highScore() {
    clrscr();
    system("color F1");
    drawMenuBox();
    setBothColor(5, 15);
    gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 5, MIN_Y_MENU);
    printf("HIGH SCORE");
    const char* p_mode[] = {
        "CLASSIC",
        "MODERN"
    };
    int pointer = 0;
    while (1) {
        // show selector list
        for (int i = 0; i < NUM_MODE; ++i) {
            int k = i + 8;
            if (pointer == i) {
                setBothColor(0, 9);
                gotoxy((MAX_X_MENU + MIN_X_MENU) / 2 - strlen(p_mode[i]) / 2 - 3, MIN_Y_MENU + i + k);
                printf("  %c %s %c", 175, p_mode[i], 174);
            }
            else {
                setBothColor(0, 14);
                gotoxy((MAX_X_MENU + MIN_X_MENU) / 2 - strlen(p_mode[i]) / 2 - 3, MIN_Y_MENU + i + k);
                printf("[+] %s  ", p_mode[i]);
            }
        }
        // keyboard handling
        while (1) {
            unsigned char choose;
            if (_kbhit()) {
                choose = _getch();
                if (choose == 'w' || choose == 'W') {
                    if (pointer > 0) {
                        pointer--;
                    }
                    else {
                        pointer = NUM_MODE - 1;
                    }
                    break;
                }
                if (choose == 's' || choose == 'S') {
                    if (pointer < NUM_MODE - 1) {
                        pointer++;
                    }
                    else {
                        pointer = 0;
                    }
                    break;
                }
                if (choose == 13) {
                    switch (pointer) {
                        case 0:
                            showHighScoreClassic();
                        break;
                        case 1:
                            showHighScoreModern();
                        break;
                        }
                    Sleep(50);
                    menu();
                }
                Sleep(100);
            }
        }
    }
}

void saveHighScore() {
    FILE* fp;
    if (mode == 0) {
        fp = fopen("high_score_classic.txt", "w");
        for (int i = 0; i < 5; ++i) {
            fputs(high_score_classic[i].name, fp);
            fputs("\n", fp);
            fprintf(fp, "%s", high_score_classic[i].score);
            fputs("\n", fp);
        }
        fclose(fp);
    }

    else if (mode == 1) {
        fp = fopen("high_score_modern.txt", "w");
        for (int i = 0; i < 5; ++i) {
            fputs(high_score_modern[i].name, fp);
            fputs("\n", fp);
            fprintf(fp, "%s", high_score_modern[i].score);
            fputs("\n", fp);
        }
        fclose(fp);
    }
}

void getHighScoreClassic() {
    int count = 0, i = 0;
    char line[30];
    FILE* fp;
    fp = fopen("high_score_classic.txt", "r");
    while (count < 10) {
        if (fgets(line, sizeof line, fp)) {
            if (count % 2 == 0) {
                strcpy(high_score_classic[i].name, line);
                count++;
            }
            else {
                strcpy(high_score_classic[i].score, line);
                count++;
                i++;
            }
        }
    }
    for (int i = 0; i < 5; ++i) {
        high_score_classic[i].name[strlen(high_score_classic[i].name) - 1] = '\0';
        high_score_classic[i].score[strlen(high_score_classic[i].score) - 1] = '\0';
    }
    fclose(fp);
}

void getHighScoreModern() {
    int count = 0, i = 0;
    char line[30];
    FILE* fp;
    fp = fopen("high_score_modern.txt", "r");
    while (count < 10) {
        if (fgets(line, sizeof line, fp)) {
            if (count % 2 == 0) {
                strcpy(high_score_modern[i].name, line);
                count++;
            }
            else {
                strcpy(high_score_modern[i].score, line);
                count++;
                i++;
            }
        }
    }
    for (int i = 0; i < 5; ++i) {
        high_score_modern[i].name[strlen(high_score_modern[i].name) - 1] = '\0';
        high_score_modern[i].score[strlen(high_score_modern[i].score) - 1] = '\0';
    }
    fclose(fp);
}

void showHighScoreClassic() {
    mode = 0;
    updateHighScore();
    clrscr();
    system("color F1");
    drawMenuBox();
    setBothColor(5, 15);
    gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 3, MIN_Y_MENU);
    printf("CLASSIC");

    int k = 3;
    for (int i = 0; i < 5; ++i) {
        setBothColor(15, 6);
        gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - strlen(high_score_classic[i].name) / 2, MIN_Y_MENU + k + i);
        printf("%s", high_score_classic[i].name);
        setBothColor(15, 1);
        gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - strlen(high_score_classic[i].score) / 2, MIN_Y_MENU + k + i + 1);
        printf("%s", high_score_classic[i].score);
        k+= 2;
    }

    const char* p_select[] = {
        "MENU",
        "RETURN"
    };
    int pointer = 0;
    while (1) {
        // show selector list
        for (int i = 0; i < 2; ++i) {
            if (pointer == i) {
                setBothColor(14, 2);
                if (i == 0) {
                    gotoxy(MIN_X_MENU + 5, MAX_Y_MENU - 2);
                    printf(" %c%s%c ", 175, p_select[i], 174);
                }
                else if (i == 1) {
                    gotoxy(MAX_X_MENU - 12, MAX_Y_MENU - 2);
                    printf("%c%s%c", 175, p_select[i], 174);
                }
            }
            else {
                setBothColor(14, 0);
                if (i == 0) {
                    gotoxy(MIN_X_MENU + 5, MAX_Y_MENU - 2);
                    printf("  %s  ", p_select[i]);
                }
                else if (i == 1) {
                    gotoxy(MAX_X_MENU - 12, MAX_Y_MENU - 2);
                    printf(" %s ",  p_select[i]);
                }
            }
        }
        // keyboard handling
        while (1) {
            unsigned char choose;
            if (_kbhit()) {
                choose = _getch();
                if (choose == 'a' || choose == 'A') {
                    if (pointer == 1) {
                        pointer = 0;
                    }
                    else {
                        pointer = 1;
                    }
                    break;
                }
                if (choose == 'd' || choose == 'D') {
                    if (pointer == 0) {
                        pointer = 1;
                    }
                    else {
                        pointer = 0;
                    }
                    break;
                }
                if (choose == 13) {
                    switch (pointer) {
                        case 0:
                            menu();
                        break;
                        case 1:
                            highScore();
                        break;
                    }
                }
                Sleep(100);
            }
        }
    }
}

void showHighScoreModern() {
    mode = 1;
    updateHighScore();
    clrscr();
    system("color F1");
    drawMenuBox();
    setBothColor(5, 15);
    gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - 2, MIN_Y_MENU);
    printf("MODERN");

    int k = 3;
    for (int i = 0; i < 5; ++i) {
        setBothColor(15, 6);
        gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - strlen(high_score_modern[i].name) / 2, MIN_Y_MENU + k + i);
        printf("%s", high_score_modern[i].name);
        setBothColor(15, 1);
        gotoxy((MIN_X_MENU + MAX_X_MENU) / 2 - strlen(high_score_modern[i].score) / 2, MIN_Y_MENU + k + i + 1);
        printf("%s", high_score_modern[i].score);
        k += 2;
    }

    const char* p_select[] = {
        "MENU",
        "RETURN"
    };
    int pointer = 0;
    while (1) {
        // show selector list
        for (int i = 0; i < 2; ++i) {
            if (pointer == i) {
                setBothColor(14, 2);
                if (i == 0) {
                    gotoxy(MIN_X_MENU + 5, MAX_Y_MENU - 2);
                    printf(" %c%s%c ", 175, p_select[i], 174);
                }
                else if (i == 1) {
                    gotoxy(MAX_X_MENU - 12, MAX_Y_MENU - 2);
                    printf("%c%s%c", 175, p_select[i], 174);
                }
            }
            else {
                setBothColor(14, 0);
                if (i == 0) {
                    gotoxy(MIN_X_MENU + 5, MAX_Y_MENU - 2);
                    printf("  %s  ", p_select[i]);
                }
                else if (i == 1) {
                    gotoxy(MAX_X_MENU - 12, MAX_Y_MENU - 2);
                    printf(" %s ", p_select[i]);
                }
            }
        }
        // keyboard handling
        while (1) {
            unsigned char choose;
            if (_kbhit()) {
                choose = _getch();
                if (choose == 'a' || choose == 'A') {
                    if (pointer == 1) {
                        pointer = 0;
                    }
                    else {
                        pointer = 1;
                    }
                    break;
                }
                if (choose == 'd' || choose == 'D') {
                    if (pointer == 0) {
                        pointer = 1;
                    }
                    else {
                        pointer = 0;
                    }
                    break;
                }
                if (choose == 13) {
                    switch (pointer) {
                        case 0:
                            menu();
                        break;
                        case 1:
                            highScore();
                        break;
                    }
                }
                Sleep(100);
            }
        }
    }
}

void updateHighScore() {
    if (mode == 0) {
        getHighScoreClassic();
        for (int i = 0; i < 6 - 1; ++i) {
            for (int j = i; j < 6; ++j) {
                if (atoi(high_score_classic[j].score) > atoi(high_score_classic[i].score)) {
                    SaveScore tmp;
                    tmp = high_score_classic[i];
                    high_score_classic[i] = high_score_classic[j];
                    high_score_classic[j] = tmp;
                }
            }
        }
    }
    else if (mode == 1) {
        getHighScoreModern();
        for (int i = 0; i < 6 - 1; ++i) {
            for (int j = i; j < 6; ++j) {
                if (atoi(high_score_modern[j].score) > atoi(high_score_modern[i].score)) {
                    SaveScore tmp;
                    tmp = high_score_modern[i];
                    high_score_modern[i] = high_score_modern[j];
                    high_score_modern[j] = tmp;
                }
            }
        }
    }
    saveHighScore();
}



