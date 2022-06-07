#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define ROWS 6
#define COLS 6
#define BUF_SIZE 50
#define LETTER_A 65
#define YEL "\e[0;33m"
#define GRN "\e[0;32m"
#define WHT "\e[0;37m"
#define BLU "\e[0;34m"
#define RED "\e[0;31m"
#define reset "\e[0m"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

//Hra WORDLE
//V cmd bude asi problem s ANSI farbami .. najlepsie spustat wsl/linux/poewrshell/vscode
//som tiez nemal problem,clion neviem 

//Globalne premmenne
char used_let[27] = {0};
char mention_let[27] = {0};
char other_let[27]  = {0};

//Databaza slov
char db[50][6] =    {{"AGENT"},{"ADULT"},{"BEACH"},{"CHIEF"},{"GLASS"},
                    {"CRIME"},{"QUEST"},{"DANCE"},{"DRINK"},{"ENEMY"},
                    {"SIGMA"},{"ALPHA"},{"KNIFE"},{"MONTH"},{"MOTOR"},
                    {"IMAGE"},{"BUNNY"},{"MONEY"},{"HONEY"},{"PAPER"},
                    {"NIGHT"},{"MUSIC"},{"PLANE"},{"POWER"},{"PARTY"},
                    {"QUEEN"},{"RATIO"},{"RANGE"},{"RIVER"},{"SCOPE"},
                    {"SHEEP"},{"SPEED"},{"STAFF"},{"SUGAR"},{"STONE"},
                    {"TABLE"},{"STEEL"},{"SKILL"},{"SMOKE"},{"TRAIN"},
                    {"TOWER"},{"TESLA"},{"VALUE"},{"VIDEO"},{"UNCLE"},
                    {"WOMAN"},{"WHITE"},{"WATER"},{"YOUNG"},{"ZEBRA"}};

void instructions(){  //Print funkcia s infom o hre
    char gamestart[BUF_SIZE];
    printf("+-------------------------------------------------+\n");
    printf("|              WELCOME IN WORDLE GAME             |\n");
    printf("|              -----INSTRUCTIONS-----             |\n");
    printf("|            Guess the word in 6 tries.           |\n");
    printf("|     After each guess the color of letter,       |\n");
    printf("|    change to show how close your guess was.     |\n");
    printf("|                  ----COLORS----                 |\n");
    printf(WHT"|       WHITE - Letter is not in the word         |\n");
    printf("|"YEL"YELLOW - Letter is in the word but in wrong spot"reset" |\n");
    printf(GRN"|GREEN - Letter is in the word and in correct spot"reset"|\n");
    printf("|"RED"   RED - Used letter, which is not in the word"reset"   |\n");
    printf("|            Type START for a new game            |\n");
    printf("+-------------------------------------------------+\n");
    while(1){
        scanf("%s",gamestart);
        if(strcmp(gamestart,"START") == 0){
            system(CLEAR);
            break;
        }   
        else{
            printf("You didnt type START\n");
            continue;
        }    
    }
}
//Random number generator
int randomgenerator(){
    srand(time(NULL));
    int number = rand() % 50;
    return number;
}
//Funkcia na pouzite/nepouzite pismena
void letter_used(char letter,char array[]){
    int counter = 0;
    if(strlen(array) == 0){ //ak je prazdny array
        array[0] = letter;
    }
    else{
        for(int i = 0;i<strlen(array);i++){ //kontrola ci uz sa tam pismeno nenachadza
            if(letter!=array[i])
                counter++;
            else 
                break;
        }
        if(counter == strlen(array))    //pridanie pismena
            array[strlen(array)] = letter;
    }
}

void letter_check(char letter,char word[],char tip[],int position){
    char *ptr;  
    ptr = strchr(word,letter); //lokalizacia pismena v slove
    if(ptr!= NULL){ // pismmeno je v slove
        if(position == ptr-word){ //pozicie pismen sa rovnaju
            printf(GRN" %c "reset,letter);
            letter_used(letter,used_let);
            word[position] = '-';
        }
        else if (tip[ptr-word] == letter){ //ak sa rovnaju pismena v slove (to co si zadal na vstup)
            while(1){
                ptr = strchr(ptr+1,letter); //lokalizacia dalsieho pismena
                if(ptr == NULL){    //nie je v slove dalsie print nabielo
                    printf(" %c ",letter);
                    letter_used(letter,other_let);
                    break;}
                else{   //je v slove a nerovnaju sa pismena v slove print nazlto
                    if(tip[ptr-word] != letter){ 
                        printf(YEL" %c "reset,letter); 
                        letter_used(letter,mention_let); 
                        word[ptr-word] = '-';
                        break;
                    }
                }
            }    
        }   
        else{   //pozicie pismen sa nerovnaju
            printf(YEL" %c "reset,letter);
            letter_used(letter,mention_let);
            word[ptr-word] = '-';
        }
    }
    else{ // pismeno nie je v slove
        printf(" %c ",letter);
        letter_used(letter,other_let);
    }
}
//print prveho riadku
void fst_row(){
	for(int i =0;i<5;i++){
		printf("+---+ ");
	}
	printf("\n");
}
//print druehho riadku
void scnd_row(char array[ROWS][COLS],int row,char unknown[]){
	char letter;
    char test[6];
    strcpy(test,unknown);
    for(int i =0;i<5;i++){
        letter = array[row][i];
		printf("|");
        letter_check(letter,test,array[row],i);
        printf("| ");
	}
	printf("\n");
}
//print treti riadok
void thrd_row(){
	for(int i =0;i<5;i++){
		printf("+---+ ");
	}
	printf("\n");
}
//Init 2D pola s '_'
void table_init(char array[ROWS][COLS]){
    int i = 0,k= 0;
    for(i = 0;i<6;i++){
        for(k = 0;k<5;k++){
            array[i][k] = '_';
        }
    array[i][5] = '\0';
    }
}
//kontrola konca hry
int game_end(int count,char word[],char unknown[]){
    if(strcmp(word,unknown)==0)
        return 1;
    if(count == 6)
        return 2;
    else
        return 0;
}
//print hracej plochy
void table_print(char array[ROWS][COLS],char unknown[]){
    for(int i = 0;i<6;i++){
        fst_row();
		scnd_row(array,i,unknown);
		thrd_row();
    }
}
//print klavesnice pouzitych pismen
void keyboard(char used_let[],char mention_let[],char other_let[]){
    char c;
    int k,count;
    for(int i = 0;i<26;i++){
        c = LETTER_A+i;
        count = 0;
        if (i%10 == 0)
            printf("\n     ");
        if (i == 20)
            printf("    ");

        for(k = 0;k<strlen(used_let);k++){ //pouzite pismena spravna pozicia
            if(c == used_let[k] && count == 0){
                printf(GRN"%c "reset,c);
                count++;
            }
        }
        for(k = 0;k<strlen(mention_let);k++){   //pouzite pismena na zlej pozicii
            if(c == mention_let[k] && count == 0){
                printf(YEL"%c "reset,c);
                count++;
            }
        }
        for(k = 0;k<strlen(other_let);k++){ //pouzite pismena ktore nie su v slove
            if(c == other_let[k] && count == 0){
                printf(RED"%c "reset,c);
                count++;
            }
        }
        if(count == 0)  // zatial nepouzite pismena
            printf(WHT"%c "WHT,c);
    }
    printf("\n\n");
}
//pridanie slova do 2D array
void table_add(char array[ROWS][COLS],char word[],int *count){
    int i = 0;
    for(i = 0;i<5;i++){
        array[*count][i] = word[i];
    }
    *count +=1;
}
//scan ci nie je slovo kratsie/dlhsie
int scan_check(char word[]){ 
    if (strlen(word)>COLS-1)
        return 1;
    if (strlen(word)<COLS-1)
        return 2;
    return 0;
}
//konvert na velke pismena 
void to_upper(char word[]){
    for(int i = 0;i<COLS-1;i++){
        word[i] = toupper(word[i]);
    }
}

int main(){
    char array[ROWS][COLS];
    int round = 0,result = 0,a;
    char *word;
    char unknown[6];
    
    instructions();
    strcpy(unknown,db[randomgenerator()]);
    table_init(array);
    table_print(array,unknown);
    keyboard(used_let,mention_let,other_let);

    while(round<6){
 
        word = (char*) malloc(sizeof(char)*BUF_SIZE);
        printf("Enter word with 5 letters: ");   
        scanf("%s",word);
        system(CLEAR);
        if((a = scan_check(word)) != 0){
            table_print(array,unknown);
            keyboard(used_let,mention_let,other_let);
            printf(RED"You entered word with %s letters, try again!\n"reset,a == 1 ? "more":"less");
            free(word);
            continue;
        }

        to_upper(word);

        table_add(array,word,&round);

        table_print(array,unknown);  
        free(word);
        keyboard(used_let,mention_let,other_let);

        result = game_end(round,word,unknown);
        
        if(result == 1){
            printf(GRN"You guessed the word in %d %s!"reset,round,round == 1 ? "turn":"turns");
            break;
        }
        else if(result == 2){
            printf(RED"You lost, better luck next time!\n"reset);
            printf("Unknown word was %s",unknown);
            }
        else
            continue;
    }
    return 0;
}