#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LIMIT 30 
//below consts are searlization strings used to write and read data from a json format.
const char* Teams_Format_out = "{\"team name\": \"%s\",\"games played\": \"%d\",\"games won\": \"%d\",\"games lost\": \"%d\",\"games drawn\": \"%d\",\"points\": \"%d\"}\n";
const char* Teams_Format_in = "{\"team name\": \"%[^\"]\",\"games played\": \"%d\",\"games won\": \"%d\",\"games lost\": \"%d\",\"games drawn\": \"%d\",\"points\": \"%d\"}\n";

//custom structucture for football league system
typedef struct Teams {
    char team_name[30];
    int games_played;
    int games_won;
    int games_lost;
    int games_drawn;
    int points;
} Teams;

//to count no of lines in the file.
int count_lines(){
    FILE* file;
    int linesCount=0;
    char ch;
    file = fopen("main_teams.txt","r");

    while((ch=fgetc(file))!=EOF) {
      if(ch=='\n')
         linesCount++;
   }

    fclose(file);

    return linesCount;
}

//funtion to enter a result
int enter_result(char name[MAX_LIMIT], int played, int won, int lost){
    Teams t1;
    
    
    strcpy(t1.team_name, name);
    t1.games_played = played;
    t1.games_won = won;
    t1.games_lost = lost;
    t1.games_drawn = t1.games_played-t1.games_won-t1.games_lost;
    t1.points =  t1.games_won*3+t1.games_drawn*1;

    FILE* file;
    file = fopen("main_teams.txt","a");



    fprintf(file, Teams_Format_out, t1.team_name, t1.games_played, t1.games_won, t1.games_lost, t1.games_drawn, t1.points);
    printf("\ndata inserted\n");
    fclose(file);

    printf("\n\n");
    return 0;

}

//Function to results stored in file
void display_results(){
    FILE* file;
    int lines = count_lines();
    Teams t2[lines];
    int i;
    
    file = fopen("main_teams.txt","r");
    fseek(file, 0, SEEK_SET);
    for(i = 0; i < lines; i ++){
    fscanf(file, Teams_Format_in, t2[i].team_name, &t2[i].games_played, &t2[i].games_won, &t2[i].games_lost, &t2[i].games_drawn, &t2[i].points);
    }

    for(i = 0; i < lines; i ++){
    printf("team name : %s ,", t2[i].team_name);
    printf("games played : %d ,", t2[i].games_played);
    printf("games drawn : %d ,", t2[i].games_drawn);
    printf("games won : %d ,", t2[i].games_won);
    printf("points : %d \n", t2[i].points);
    }

    fclose(file);

    printf("\n\n");
     
}

//function to display the league table
void display_league_table(){
    FILE* file;
    int lines = count_lines();
    Teams t2[lines];
    Teams element;
    int i,j;
    
    file = fopen("main_teams.txt","r");
    fseek(file, 0, SEEK_SET);
    for(i = 0; i < lines; i ++){
    fscanf(file, Teams_Format_in, t2[i].team_name, &t2[i].games_played, &t2[i].games_won, &t2[i].games_lost, &t2[i].games_drawn, &t2[i].points);
    }

    for(i = 0; i < lines - 1; i++){
        for(j = 0; j < lines - i - 1; j++){
            if(t2[j].points < t2[j + 1].points) 
                {
                element = t2[j];
                t2[j] = t2[j + 1];
                t2[j + 1] = element;
                }
        }
    }
    printf("--------------LEAGUE TABLE---------------\n\n");
    printf("Team name\tGames\tWon\tLost\tDraw\tPoints\n\n");
    for(i = 0; i < lines; i ++){
        printf("%s", t2[i].team_name);
        if(i < 2 || i == 4){
            printf("\t");
        }
        printf("\t%d", t2[i].games_played);
        printf("\t%d", t2[i].games_won);
        printf("\t%d", t2[i].games_lost);
        printf("\t%d", t2[i].games_drawn);
        printf("\t%d", t2[i].points);
        printf("\n");
    }

    fclose(file);

    printf("\n\n");
     
}


//main function
int main(){
    system("clear");
    bool i = true;
    char name[MAX_LIMIT];
            int played, won, lost;
    while(i){
        int choice;
        printf("options\n");
        printf("\t1. Enter a record\n");
        printf("\t2. Display all results\n");
        printf("\t3. Display legue table\n");
        printf("\t4. exit\n");
        printf(">>");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("clear");
            fflush(stdin);
            printf("****Please enter the following values****\n");
            printf("\tTeam Name >> ");
            scanf ("%[^\n]s", name);
            printf("\tGames Played >> ");
            scanf("%d",&played);
            printf("\tGames Won >> ");
            scanf("%d",&won);
            printf("\tGames Lost >> ");
            scanf("%d",&lost);
            enter_result(name, played, won, lost);
            break;
        
        case 2:
            system("clear");
            display_results();
            break;

        case 3:
            system("clear");
            display_league_table();
            break;

        case 4:
            printf("exiting...");
            i = false;
            break;
        
        default:
            printf("Incorrect option selected, choose again..");
            break;
        }
    }

    return 0;
}