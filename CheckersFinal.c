#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

char piece;
int black,red;
int row=8,col=8;
int x,dx,dy;
char pla1[100],pla2[100];

char giveMePiece(int n)
{
    switch(n)
    {
        case 0:
            return ' ';
        case 1:
            return ' ';
        case 2:
            return 'r';
        case 3:
            return 'b';
        case 4:
            return 'R';
        case 5:
            return 'B';
    }
}
void swapPiece(int a[8][8], int i, int j, int k, int l,int player)
{
    int temp;

   if(player == 2)
    {
        printf("RED move from %d,%c to %d,%c\n", i+1, j+'a', k+1, l+'a');
    }
    else if(player == 3)
    {
        printf("BLACK move from %d,%c to %d,%c\n", i+1, j+'a', k+1, l+'a');
    }
    printf("SWAP: \tFrom row= %d, column= %d \n\tto row= %d,column= %d\n", i+1, j+1, k+1, l+1);

    if(i - k == -2 || i - k == 2)
    {
        if(j - l == -2 || j - l == 2)
        {
            if(player==2)
            {
                red++;
                printf("Black piece captured\n");
            }
            else
            {
                black++;
                printf("Red piece captured\n");
            }
        }
    }
    if(player==2)  //RED king piece
    {
        if(k==7)
        {
            a[i][j]=4;
        }
    }
    else if(player==3)  // BLACK king piece
    {
        if(k==0)
        {
            a[i][j]=5;
        }
    }
    temp = a[i][j];

    a[i][j] = a[k][l];

    a[k][l] = temp;

}
void leaderboard(int player,char pla1[100],char pla2[100],int red,int black)
{
    FILE *fp;
    fp = fopen("leaderboard.txt","a");
    if(player == 2)
        fprintf(fp,"%s(%d)\t\t%s(%d) \n",pla1,red,pla2,black);
    else if(player == 3)
        fprintf(fp,"%s(%d)\t\t%s(%d) \n",pla2,black,pla1,red);
}
void scan_board(int a[8][8])
{
   FILE *fp;
    fp=fopen("leaderboard.txt","r");
    system("cls");
    printf("[[ Press escape button to go back ]]\n\n");
    printf("Winner\t\t\tLoser\n");
    while(1)
    {
        char ch;
        if(ch==EOF) break;
        ch=fgetc(fp);
        printf("%c",ch);
    }
    while(1)
    {
        if(kbhit())
        {
            char key=getche();
            if(key==27)
            {
                return;
            }
        }
    }
}

void rule()
{
    system("mode 350,300");
    FILE *fp2;
    fp2=fopen("rule.txt","r");
    system("cls");
    while(1)
    {
        char ch;
        if(ch==EOF) break;
        ch=fgetc(fp2);
        printf("%c",ch);
    }
    while(1)
    {
        if(kbhit())
        {
            char key=getche();
            if(key==27)
            {
                system("mode 100,40");
                return;
            }
        }
    }
}
int double_jump(int a[8][8],int player,int k,int l)
{
    if(player==2)
    {
        if((k==6 || l==6) && a[k][l]!=4) return -1;
        if(a[k+1][l+1]==3 && a[k+2][l+2]==1) return 1;
        else if(a[k+1][l-1]==3 && a[k+2][l-2]==1) return 1;
        else if(a[k-1][l+1]==3 && a[k-2][l+2]==1 &&a[k][l]==4) return 1;
        else if(a[k-1][l-1]==3 && a[k-2][l-2]==1 && a[k][l]==4) return 1;
        else return -1;
    }
    else
    {
        if((k==1 || l==1)&& a[k][l]!=5) return -1;
        if(a[k+1][l+1]==2 && a[k+2][l+2]==1 && a[k][l]==5) return 1;
        else if(a[k+1][l-1]==2 && a[k+2][l-2]==1 && a[k][l]==5) return 1;
        else if(a[k-1][l+1]==2 && a[k-2][l+2]==1) return 1;
        else if(a[k-1][l-1]==2 && a[k-2][l-2]==1) return 1;
        else return -1;
    }
}

void random_move(int a[8][8],int player)
{
    int i,j,k,l,b=0,n,m;
    for(i = 0;i < 8;i++)
    {
        for(j = 0; j < 8;j++)
        {
            if(a[i][j] == player)
            {
                if(player == 2)
                {
                    if(a[i+1][j+1] == 1)
                    {
                        swapPiece(a,i,j,i+1,j+1,player);
                        b = 1;
                    }
                    else if(a[i+1][j-1] == 1)
                    {
                        swapPiece(a,i,j,i+1,j-1,player);
                        b = 1;
                    }
                }
                else if(player == 3)
                {
                    if(a[i-1][j+1] == 1)
                    {
                        swapPiece(a,i,j,i-1,j+1,player);
                        b = 1;
                    }
                    else if(a[i-1][j-1] == 1)
                    {
                        swapPiece(a,i,j,i-1,j-1,player);
                        b = 1;
                    }
                }
            }
        if(b == 1) break;
        }
    if(b == 1) break;
    }
}

void delay(double sec)
{
    clock_t start,current;
    start = clock();
    current = clock();
    while((double)(current-start)/CLOCKS_PER_SEC < sec)
        current = clock();
}
void showWelcomeScreen()
{
    printf("Press any key to continue");
    char str1[200]={"\n\n\n\t\t\tWELCOME TO CHECKERS GAME...\n\n\n\t\tDeveloped by :-\n\n\t\tAdham Arik Rahman(180041219)\n\n\t\tIshrak Hossain(180041218)\n\n\t\tSamiul Islam(180041221) "};
    printf("\t\t");
    int j=strlen(str1);
    for(int run=0;run<j;run++)
    {
        printf("%c",str1[run]);
        delay(0.1);
        if(kbhit())
        {
            getch();
            system("cls");
            puts(str1);
            break;
        }
    }
    delay(1);
}
int getChoice(int choice)
{
    char ch=10;
    while(ch!=13){
        system("cls");
        if(choice==1){
            printf("\n\n\n\n\t\t\t ---> E N T E R  T H E  G A M E \n");
        }
        else printf("\n\n\n\n\t\t\t ---> Enter the game \n");
        if(choice == 2)
            printf("\n\n\t\t\t ---> R U L E  O F  T H I S  G A M E \n");
        else printf("\n\n\t\t\t ---> Rule of this game \n");
        if(choice == 3)
            printf("\n\n\t\t\t ---> L O A D  G A M E \n");
        else printf("\n\n\t\t\t ---> Load game \n");
        if(choice == 4)
            printf("\n\n\t\t\t ---> L E A D E R B O A R D \n");
        else printf("\n\n\t\t\t ---> Leaderboard \n");
        if(choice==5)
            printf("\n\n\t\t\t ---> Q U I T \n");
        else printf("\n\n\t\t\t ---> Quit \n");
        printf("\n\n[ Use UP and DOWN arrow to select an option ]");
        ch = getch();
        if(ch == 72)
            choice--;
        else if(ch == 80)
            choice++;
        if(choice<1)
            choice = 5;
        else if(choice>5)
            choice = 1;
    }
    return choice;
}

int inMenu(int choice)
{
    char ch=10;
    while(ch!=13){
        system("cls");
        if(choice==1){
            printf("\n\n\n\n\t\t\t ---> R E S U M E  G A M E \n");
        }
        else printf("\n\n\n\n\t\t\t ---> Resume game \n");
        if(choice == 2)
            printf("\n\n\t\t\t ---> S A V E  G A M E \n");
        else printf("\n\n\t\t\t ---> Save game \n");
        if(choice == 3)
            printf("\n\n\t\t\t ---> L E A D E R B O A R D \n");
        else printf("\n\n\t\t\t ---> Leaderboard \n");
        if(choice==4)
            printf("\n\n\t\t\t ---> Q U I T \n");
        else printf("\n\n\t\t\t ---> Quit \n");
        printf("\n\n[ Use UP and DOWN arrow to select an option ]");
        ch = getch();
        if(ch == 72)
            choice--;
        else if(ch == 80)
            choice++;
        if(choice<1)
            choice = 4;
        else if(choice>4)
            choice = 1;
    }
    return choice;
}

int inMenu2(int choice,char pla1[100],char pla2[100],int player)
{
    char ch=10;
    while(ch!=13){
        system("cls");

        if(player==2) printf("Congratulations! %s won!\n",pla1);
        else if(player==3) printf("Congratulations! %s won!\n",pla2);
        printf("Do you want to play again? ");
        if(choice==1){
            printf("\n\n\n\n\t\t\t ---> Y E S \n");
        }
        else printf("\n\n\n\n\t\t\t ---> Yes \n");
        if(choice == 2)
            printf("\n\n\t\t\t ---> N O \n");
        else printf("\n\n\t\t\t ---> No \n");
        printf("\n\n[ Use UP and DOWN arrow to select an option ]");
        ch = getch();
        if(ch == 72)
            choice--;
        else if(ch == 80)
            choice++;
        if(choice<1)
            choice = 2;
        else if(choice>2)
            choice = 1;
    }
    return choice;
}

void file(int a[8][8],char pla1[100],char pla2[100],int player)
{
    FILE *fp1;
    fp1=fopen("array.txt","w+");
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            fprintf(fp1,"%d ",a[i][j]);
        }
        fprintf(fp1,"\n");
    }
    fprintf(fp1,"%s %s\n",pla1,pla2);
    fprintf(fp1,"%d %d %d ",player,red,black);
}

void printDisplay(int a[8][8])
{
    int r, c, x=0;
    printf("\n\n\t\t\t");
    printf("    a   b   c   d   e   f   g   h\t\t%s  %s\n",pla1,pla2);
    printf("\t\t\t");
    printf("  +...+...+...+...+...+...+...+...+\t\t%d\t%d\n",red,black);

    for (r=0; r<row; r++)
    {
        printf("\t\t\t");
        printf("%d |", r+1);
        for (c=0;c<col;c++)
        {
            printf(" %c |", giveMePiece(a[r][c]) );
        }
        printf(" %d\n",r+1);
        printf("\t\t\t");
        printf("  +...+...+...+...+...+...+...+...+\n");
    }
    printf("\t\t\t");
    printf("    a   b   c   d   e   f   g   h\n\n");
    printf("\t\t[ Use row-column coordinates to make your move ]\n\n");
    printf("\t\t[ Use escape button to access menu ]\n\n");

}

int playerMovement(int a[8][8], int player,int i,int j,int k,int l)
{
    int jmp_r;
    int jmp_c;
    int row=8,col=8;
    //de<<1;
    if(i < 0 || row <= i)
    {
        printf("Out of bounds\n");         //keeping in bounds
        return -1;
    }
    if(j < 0 || col <= j)
    {
        printf("Out of bounds\n");
        return -1;
    }

    if(k < 0 || row <= k)
    {
        printf("Out of bounds\n");
        return -1;

    }
    if(l < 0 || col<= l)
    {
        printf("Out of bounds\n");
        return -1;
    }
    //de<<2;
    // check player if its moving his own piece.
    if(player == 2)
    {
       // de<<3;
        if(a[i][j] != 2 && a[i][j]!=4)
        {
            printf("Move your own piece!\n");
            return -1;
        }
        //de<<4;
    }
    else
    {
        if(a[i][j] != 3 && a[i][j]!=5)
        {
            printf("Move your own piece!\n");
            return -1;
        }
    }
    //make sure they are jumping to a empty location
    if(a[k][l]==0) return -1;
    if(a[k][l] != 1)
    {
        printf("You must move to an empty location");
        return -1;
    }
    // make sure the vertical direction of the move is not illegal
    if(player == 2)
    {
        //make sure he moves down
        if(i >= k && a[i][j]!=4)
        {
            printf("RED player must move down\n");
            return -1;
        }
    }
    else
    {
        // make sure player moves up
        if(i <= k && a[i][j]!=5)
        {
            printf("BLACK player must move up\n");
            return -1;
        }
    }
    //de<<5;

    // checking if it's a regular move
    if(i - k == -1 || i - k == 1)
    {
        if(j - l == 1 || j - l == -1)
        {
            swapPiece(a,i,j,k,l,player);
            return 0;
        }
    }

    //checking if it's a jump move
    if(i - k == -2 || i - k == 2)
    {
        if(j - l == -2 || j - l == 2)
        {
            // checking if the jump position is enemy
            if(i < k)
            { // move down
                jmp_r = i + 1;
            }
            else
            { // move up
                jmp_r = i - 1;
            }
            if(j < l)
            { // move down
                jmp_c = j + 1;
            }
            else
            { // move up
                jmp_c = j - 1;
            }

            if(player==2 && a[jmp_r][jmp_c]!=3)
            {
                printf("Enemy is not at %d %d\n",jmp_r, jmp_c);
                printf("You can only jump over an enemy player\n");
                return -1;
            }
            if(player==3 && a[jmp_r][jmp_c] != 2)
            {
                printf("Enemy is not at %d %d\n",jmp_r, jmp_c);
                printf("You can only jump over an enemy player\n");
                return -1;
            }

            // the move is valid:
            a[jmp_r][jmp_c] = 1;
            swapPiece(a,i,j,k,l,player);
            return 0;
        }
    }

    printf("You can only move one step diagonally\n");
    return -1;

}

int main()
{
    system("mode 100,40");
    system("COLOR 3F");
    char j,l;
    int i,k,n,y,z,time, a[8][8]={0,2,0,2,0,2,0,2,2,0,2,0,2,0,2,0,0,2,0,2,0,2,0,2,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,1,3,0,3,0,3,0,3,0,0,3,0,3,0,3,0,3,3,0,3,0,3,0,3,0};
    top:
    system("cls");
    showWelcomeScreen();
    x=getChoice(1);
    start:
    if(x==1)
    {
        system("cls");
        printf("Enter First Player's Name: ");
        gets(pla1);
        printf("Enter Second Player's Name: ");
        gets(pla2);
        game_red:
        while(1)
        {
            system("cls");
            printDisplay(a);
            file(a,pla1,pla2,2);
            if(black==12 || red==12)
            {
                goto khela_shesh;
            }
            while(1)
            {
                // RED
                here:
                time=0;
                while(1)
                {
                    if(time > 30)
                    {
                        random_move(a,2);
                        goto shomoy_shesh;
                    }
                    printf("\nTime: %d\n",time%60);
                    printf("%s's turn:\n",pla1);
                    printf("from: ");
                    if(kbhit())
                    {
                        char key=getche();
                        if(key==27)
                        {
                            x=inMenu(1);
                            if(x==4) return 0;
                            else if(x==2)
                            {
                                file(a,pla1,pla2,2);
                                system("cls");
                                printf("Game Saved!\n\n");
                                printDisplay(a);
                            }
                            else if(x==3) scan_board(a);
                        }
                        else
                        {
                            i=key-48;
                            scanf("%c",&j);
                            fflush(stdin);
                            printf("\nto: ");
                            scanf("%d %c",&k,&l);
                            fflush(stdin);
                            break;
                        }
                    }
                    delay(1);
                    time++;
                    system("cls");
                    printDisplay(a);
                }

                system("cls");
                if(playerMovement(a,2,i-1,j-97,k-1,l-97) == 0)
                {
                    if((i-1) - (k-1) == -2 || (i-1) - (k-1) == 2)
                    {
                        if((j-97) - (l-97) == 2 || (j-97) - (l-97) == -2)
                        {
                            if(double_jump(a,2,k-1,l-97)==1)
                            {
                                printDisplay(a);
                                goto here;
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                    else
                    {
                        //printDisplay(a);
                        break;
                    }
                }
                else
                {
                    printf("\nIllegal move, try again\n");
                    printDisplay(a);
                }
            }
            printDisplay(a);
            delay(1);
            //printf("\n");
            shomoy_shesh:
            game_black:
            system("cls");
            printDisplay(a);
            file(a,pla1,pla2,3);
            if(black==12 || red==12)
            {
                goto khela_shesh;
            }

            while(1)
            {
                // BLACK
                here_again:
                time=0;
                int abcd=0;
                while(1)
                {
                    if(time > 30)
                    {
                        random_move(a,3);
                        abcd=1;
                        break;
                    }
                    printf("\nTime: %d\n",time%60);
                    printf("%s's turn:\n",pla2);
                    printf("from: ");
                    if(kbhit())
                    {
                        char key=getche();
                        if(key==27)
                        {
                            x=inMenu(1);
                            if(x==4) return 0;
                            else if(x==2)
                            {
                                file(a,pla1,pla2,3);
                                system("cls");
                                printf("Game Saved!\n\n");
                                printDisplay(a);
                            }
                            else if(x==3) scan_board(a);
                        }
                        else
                        {
                            i=key-48;
                            scanf("%c",&j);
                            fflush(stdin);
                            printf("\nto: ");
                            scanf("%d %c",&k,&l);
                            fflush(stdin);
                            break;
                        }
                    }
                    delay(1);
                    time++;
                    system("cls");
                    printDisplay(a);
                }
                system("cls");
                if(abcd==1) break;
                if(playerMovement(a,3,i-1,j-97,k-1,l-97) == 0)
                {
                    if(i - k == -2 || i - k == 2)
                    {
                        if((j-97) - (l-97) == 2 || (j-97) - (l-97) == -2)
                        {
                            if(double_jump(a,3,k-1,l-97)==1)
                            {
                                printDisplay(a);
                                goto here_again;
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                    else
                    {
                        //printDisplay(a);
                        break;
                    }
                }
                else
                {
                    printf("\nIllegal move, try again\n");
                    printDisplay(a);
                }
            }
            printDisplay(a);
            delay(1);
        }
    }

        outside:
        if(x==2)
        {
            rule();
            x=getChoice(1);
            if(x!=1)
            {
                goto outside;
            }
            else goto start;
        }
        if(x==3)
        {
            FILE *fp1;
            int colour;
            fp1=fopen("array.txt","r");
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    fscanf(fp1,"%d",&a[i][j]);
                }
            }
            fscanf(fp1,"%s %s",pla1,pla2);
            fflush(stdin);
            fscanf(fp1,"%d %d %d",&colour,&red,&black);
            if(colour==2) goto game_red;
            else if(colour==3) goto game_black;
        }
        if(x==4)
        {
            scan_board(a);
            x=getChoice(1);
            if(x!=1)
            {
                goto outside;
            }
            else goto start;
        }
        if(x==5)
        {
            return 0;
        }
        khela_shesh:
        if(black==12)
        {
            leaderboard(3,pla1,pla2,red,black);
            black=0;
            red=0;
            printf("Congratulations! %s won!\n",pla2);
            x=inMenu2(1,pla1,pla2,3);
            if(x==1) goto top;
            else return 0;

        }
        else if(red==12)
        {
            leaderboard(2,pla1,pla2,red,black);
            black=0;
            red=0;
            printf("Congratulations! %s won!\n",pla1);
            x=inMenu2(1,pla1,pla2,2);
            if(x==1) goto top;
            else return 0;
        }

}

