#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<dos.h>

struct COORDS
{   int row;
    int col;
};


char square[8][8]={     'r','n','b','q','k','b','n','r',
                        'p','p','p','p','p','p','p','p',
                        '\0','\0','\0','\0','\0','\0','\0','\0',
                        '\0','\0','\0','\0','\0','\0','\0','\0',
                        '\0','\0','\0','\0','\0','\0','\0','\0',
                        '\0','\0','\0','\0','\0','\0','\0','\0',
                        'P','P','P','P','P','P','P','P',
                        'R','N','B','Q','K','B','N','R'      };


void display();
int valid_move2(struct COORDS Curr,struct COORDS New);
int valid_move(struct COORDS,struct COORDS);
int bk_underattack2(struct COORDS);
int wk_underattack2(struct COORDS);
int bk_underattack();
int wk_underattack();
int b_total_valid_moves();
int w_total_valid_moves();
void b_checkmate();
void w_checkmate();
void b_check();
void w_check();
void b_stalemate();
void w_stalemate();
void w_promote();
void b_promote();

void display()
{   struct COORDS pos;
    printf("\n");
    printf("   0  1  2  3  4  5  6  7\n");
    for(pos.row=0;pos.row<8;++pos.row)
    {   printf("%d |",pos.row);
        for(pos.col=0;pos.col<8;++pos.col)
            printf("%-2c|",square[pos.row][pos.col]);
        printf("\n");
    }

}

void main()
{   int turn=0;
    struct COORDS Curr,New;
    display();
    while(1)
    {   if(turn%2==0)
        {
            printf("\nEnter White's Move: ");
            scanf("%d.%d to %d.%d",&Curr.row,&Curr.col,&New.row,&New.col);
            if(isupper(square[Curr.row][Curr.col])>0)
            {   if(valid_move(Curr,New))
                {   square[New.row][New.col]=square[Curr.row][Curr.col];
                    square[Curr.row][Curr.col]='\0';
                    w_promote();
                    b_checkmate();
                    b_stalemate();
                    b_check();
                }
                else
                {   printf("\nInvalid Move!!Try Again\n");
                    delay(2000);
                    ++turn;
                }
            }
            else
            {   printf("\nTry Again!!It's White turn\n");
                delay(2000);
                ++turn;
            }
            system("cls");
            display();
            ++turn;

        }
        else
        {
            printf("\nEnter Black's Move: ");
            scanf("%d.%d to %d.%d",&Curr.row,&Curr.col,&New.row,&New.col);
            if(islower(square[Curr.row][Curr.col])>0)
            {   if(valid_move(Curr,New))
                {   square[New.row][New.col]=square[Curr.row][Curr.col];
                    square[Curr.row][Curr.col]='\0';
                    b_promote();
                    w_checkmate();
                    w_stalemate();
                    w_check();
                }
                else
                {   printf("\nInvalid Move!!Try Again\n");
                    delay(2000);
                    ++turn;
                }
            }
            else
            {   ++turn;
                printf("\nTry Again!!It's Black turn\n");
                delay(2000);
            }
            system("cls");
            display();
            ++turn;

        }

    }

}




int valid_move2(struct COORDS Curr,struct COORDS New)
{
    char unit,newunit;
    int color,row,col,i,j;

    unit=square[Curr.row][Curr.col];
    newunit=square[New.row][New.col];

    if(isalpha(newunit))
            color=islower(newunit);
    else
            color=-1;
//////////////////////////////////////////////////////////////////////////////////
    if(unit=='K')
    {   if(New.row==Curr.row-1&&New.col==Curr.col&&color!=0)
            return 1;
        else if(New.row==Curr.row-1&&New.col==Curr.col-1&&color!=0)
            return 1;
        else if(New.row==Curr.row&&New.col==Curr.col-1&&color!=0)
            return 1;
        else if(New.row==Curr.row+1&&New.col==Curr.col-1&&color!=0)
            return 1;
        else if(New.row==Curr.row+1&&New.col==Curr.col&&color!=0)
            return 1;
        else if(New.row==Curr.row+1&&New.col==Curr.col+1&&color!=0)
            return 1;
        else if(New.row==Curr.row&&New.col==Curr.col+1&&color!=0)
            return 1;
        else if(New.row==Curr.row-1&&New.col==Curr.col+1&&color!=0)
            return 1;
        else
            return 0;
    }
//////////////////////////////////////////////////////////////////////////////////
    else if(unit=='k')
    {   if(New.row==Curr.row-1&&New.col==Curr.col&&color<=0)
            return 1;
        else if(New.row==Curr.row-1&&New.col==Curr.col-1&&color<=0)
            return 1;
        else if(New.row==Curr.row&&New.col==Curr.col-1&&color<=0)
            return 1;
        else if(New.row==Curr.row+1&&New.col==Curr.col-1&&color<=0)
            return 1;
        else if(New.row==Curr.row+1&&New.col==Curr.col&&color<=0)
            return 1;
        else if(New.row==Curr.row+1&&New.col==Curr.col+1&&color<=0)
            return 1;
        else if(New.row==Curr.row&&New.col==Curr.col+1&&color<=0)
            return 1;
        else if(New.row==Curr.row-1&&New.col==Curr.col+1&&color<=0)
            return 1;
        else
            return 0;
    }
//////////////////////////////////////////////////////////////////////////////////
    else if(unit=='Q')
    {  square[Curr.row][Curr.col]='R';
       i=valid_move2(Curr,New);

       square[Curr.row][Curr.col]='B';
       j=valid_move2(Curr,New);

       square[Curr.row][Curr.col]='Q';

       return i+j;
    }
////////////////////////////////////////////////////////////////////////////////////
    else if(unit=='q')
    {  square[Curr.row][Curr.col]='r';
       i=valid_move2(Curr,New);

       square[Curr.row][Curr.col]='b';
       j=valid_move2(Curr,New);

       square[Curr.row][Curr.col]='q';

       return i+j;
    }
////////////////////////////////////////////////////////////////////////////////////
    else if(unit=='P')
    {

            if(New.row==Curr.row-1&&New.col==Curr.col+1)
                    if(color>0)
                            return 1;
                    else
                            return 0;
            else if(New.row==Curr.row-1&&New.col==Curr.col-1)
                    if(color>0)
                            return 1;
                    else
                            return 0;
            else if(New.row==Curr.row-1&&New.col==Curr.col)
                    if(color<0)
                        return 1;
                    else
                        return 0;
            else if(New.row==Curr.row-2&&New.col==Curr.col&&Curr.row==6)
                    if(color<0&&square[New.row+1][New.col]=='\0')
                        return 1;
                    else
                        return 0;
            else
                        return 0;

    }

/////////////////////////////////////////////////////////////////////////////

    else if(unit=='p')
    {

            if(New.row==Curr.row+1&&New.col==Curr.col+1)
                    if(color==0)
                            return 1;
                    else
                            return 0;
            else if(New.row==Curr.row+1&&New.col==Curr.col-1)
                    if(color==0)
                            return 1;
                    else
                            return 0;
            else if(New.row==Curr.row+1&&New.col==Curr.col)
                    if(color<0)
                        return 1;
                    else
                        return 0;
            else if(New.row==Curr.row+2&&New.col==Curr.col&&Curr.row==1)
                    if(color<0&&square[New.row-1][New.col]=='\0')
                        return 1;
                    else
                        return 0;
            else
                        return 0;

    }


////////////////////////////////////////////////////////////////////////////

    else if(unit=='R')
    {
            if(New.col==Curr.col)
            {   if(New.row<Curr.row)
                {   for(row=Curr.row-1;row>New.row;--row)
                        if(square[row][Curr.col]!='\0')
                                return 0;
                    if(color>0||color<0)
                        return 1;
                    else
                        return 0;
                }
                else if(New.row>Curr.row)
                {   for(row=Curr.row+1;row<New.row;++row)
                        if(square[row][Curr.col]!='\0')
                                return 0;
                    if(color>0||color<0)
                        return 1;
                    else
                        return 0;
                }
                else
                    return 0;
            }
            else if(New.row==Curr.row)
            {   if(New.col<Curr.col)
                {   for(col=Curr.col-1;col>New.col;--col)
                        if(square[Curr.row][col]!='\0')
                                return 0;
                    if(color>0||color<0)
                        return 1;
                    else
                        return 0;
                }
                else if(New.col>Curr.col)
                {   for(col=Curr.col+1;col<New.col;++col)
                        if(square[Curr.row][col]!='\0')
                                return 0;
                    if(color>0||color<0)
                        return 1;
                    else
                        return 0;
                }
                else
                    return 0;
            }
            else
                return 0;

    }


//////////////////////////////////////////////////

    else if(unit=='r')
    {
            if(New.col==Curr.col)
            {   if(New.row<Curr.row)
                {   for(row=Curr.row-1;row>New.row;--row)
                        if(square[row][Curr.col]!='\0')
                                return 0;
                    if(color==0||color<0)
                        return 1;
                    else
                        return 0;
                }
                else if(New.row>Curr.row)
                {   for(row=Curr.row+1;row<New.row;++row)
                        if(square[row][Curr.col]!='\0')
                                return 0;
                    if(color==0||color<0)
                        return 1;
                    else
                        return 0;
                }
                else
                    return 0;
            }
            else if(New.row==Curr.row)
            {   if(New.col<Curr.col)
                {   for(col=Curr.col-1;col>New.col;--col)
                        if(square[Curr.row][col]!='\0')
                                return 0;
                    if(color==0||color<0)
                        return 1;
                    else
                        return 0;
                }
                else if(New.col>Curr.col)
                {   for(col=Curr.col+1;col<New.col;++col)
                        if(square[Curr.row][col]!='\0')
                                return 0;
                    if(color==0||color<0)
                        return 1;
                    else
                        return 0;
                }
                else
                    return 0;
            }
            else
                return 0;

    }



///////////////////////////////////////////////////////////////////

    else if(unit=='N')
    {
        if((New.row==Curr.row-2)&&(New.col==Curr.col+1)&&color!=0)
                return 1;
        else if((New.row==Curr.row-2)&&(New.col==Curr.col-1)&&color!=0)
                return 1;
        else if((New.row==Curr.row-1)&&(New.col==Curr.col-2)&&color!=0)
                return 1;
        else if((New.row==Curr.row+1)&&(New.col==Curr.col-2)&&color!=0)
                return 1;
        else if((New.row==Curr.row+2)&&(New.col==Curr.col-1)&&color!=0)
                return 1;
        else if((New.row==Curr.row+2)&&(New.col==Curr.col+1)&&color!=0)
                return 1;
        else if((New.row==Curr.row+1)&&(New.col==Curr.col+2)&&color!=0)
                return 1;
        else if((New.row==Curr.row-1)&&(New.col==Curr.col+2)&&color!=0)
                return 1;
        else
                return 0;

    }

///////////////////////////////////////////////////////////////////

    else if(unit=='n')
    {
        if((New.row==Curr.row-2)&&(New.col==Curr.col+1)&&color<=0)
                return 1;
        else if((New.row==Curr.row-2)&&(New.col==Curr.col-1)&&color<=0)
                return 1;
        else if((New.row==Curr.row-1)&&(New.col==Curr.col-2)&&color<=0)
                return 1;
        else if((New.row==Curr.row+1)&&(New.col==Curr.col-2)&&color<=0)
                return 1;
        else if((New.row==Curr.row+2)&&(New.col==Curr.col-1)&&color<=0)
                return 1;
        else if((New.row==Curr.row+2)&&(New.col==Curr.col+1)&&color<=0)
                return 1;
        else if((New.row==Curr.row+1)&&(New.col==Curr.col+2)&&color<=0)
                return 1;
        else if((New.row==Curr.row-1)&&(New.col==Curr.col+2)&&color<=0)
                return 1;
        else
                return 0;

    }

//////////////////////////////////////////////////////////////////////////////

   else if(unit=='B')
   {

        if(Curr.row-New.row==New.col-Curr.col)
        {
            if(New.col>Curr.col)
            {   for(row=Curr.row-1,col=Curr.col+1;row>New.row;--row,++col)
                        if(square[row][col]=='\0')
                                continue;
                        else
                                return 0;
                if(color!=0)
                        return 1;
                else
                        return 0;

            }
            else if(New.col<Curr.col)
            {   for(row=Curr.row+1,col=Curr.col-1;row<New.row;++row,--col)
                        if(square[row][col]=='\0')
                                continue;
                        else
                                return 0;
                if(color!=0)
                        return 1;
                else
                        return 0;

            }
            else
                return 0;
        }
        else if(Curr.row-New.row==Curr.col-New.col)
        {
            if(New.col>Curr.col)
            {   for(row=Curr.row+1,col=Curr.col+1;row<New.row;++row,++col)
                        if(square[row][col]=='\0')
                                continue;
                        else
                                return 0;
                if(color!=0)
                        return 1;
                else
                        return 0;

            }
            else if(New.col<Curr.col)
            {   for(row=Curr.row-1,col=Curr.col-1;row>New.row;--row,--col)
                        if(square[row][col]=='\0')
                                continue;
                        else
                                return 0;
                if(color!=0)
                        return 1;
                else
                        return 0;

            }
            else
                return 0;
        }
        else
            return 0;
   }
///////////////////////////////////////////////////////////////////////////////


   else if(unit=='b')
   {

        if(Curr.row-New.row==New.col-Curr.col)
        {
            if(New.col>Curr.col)
            {   for(row=Curr.row-1,col=Curr.col+1;row>New.row;--row,++col)
                        if(square[row][col]=='\0')
                                continue;
                        else
                                return 0;
                if(color<=0)
                        return 1;
                else
                        return 0;

            }
            else if(New.col<Curr.col)
            {   for(row=Curr.row+1,col=Curr.col-1;row<New.row;++row,--col)
                        if(square[row][col]=='\0')
                                continue;
                        else
                                return 0;
                if(color<=0)
                        return 1;
                else
                        return 0;

            }
            else
                return 0;
        }
        else if(Curr.row-New.row==Curr.col-New.col)
        {
            if(New.col>Curr.col)
            {   for(row=Curr.row+1,col=Curr.col+1;row<New.row;++row,++col)
                        if(square[row][col]=='\0')
                                continue;
                        else
                                return 0;
                if(color<=0)
                        return 1;
                else
                        return 0;

            }
            else if(New.col<Curr.col)
            {   for(row=Curr.row-1,col=Curr.col-1;row>New.row;--row,--col)
                        if(square[row][col]=='\0')
                                continue;
                        else
                                return 0;
                if(color<=0)
                        return 1;
                else
                        return 0;

            }
            else
                return 0;
        }
        else
            return 0;
   }
   /////////////////////////////////////////////////////////////////////////
   else
        return 0;


///////////////////////////////////////////////////////////////////////////////
}





//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



int valid_move(struct COORDS Curr,struct COORDS New)
{//*********************************************************************
    int s;
    char unit,newunit;
    struct COORDS pos;

    unit=square[Curr.row][Curr.col];
    newunit=square[New.row][New.col];

    s=valid_move2(Curr,New);

    if(s==0)
        return 0;
    else if(s==1)
    {   /////////////////////////////////////////////
        if(islower(unit)==0)
        {   square[New.row][New.col]=unit;
            square[Curr.row][Curr.col]='\0';
            for(pos.row=0;pos.row<8;++pos.row)
                for(pos.col=0;pos.col<8;++pos.col)
                    if(wk_underattack2(pos))
                    {   square[New.row][New.col]=newunit;
                        square[Curr.row][Curr.col]=unit;
                        return 0;
                    }
             square[New.row][New.col]=newunit;
             square[Curr.row][Curr.col]=unit;
             return 1;
        }
        else if(islower(unit)>0)
        {   square[New.row][New.col]=unit;
            square[Curr.row][Curr.col]='\0';
            for(pos.row=0;pos.row<8;++pos.row)
                for(pos.col=0;pos.col<8;++pos.col)
                    if(bk_underattack2(pos))
                    {   square[New.row][New.col]=newunit;
                        square[Curr.row][Curr.col]=unit;
                        return 0;
                    }
             square[New.row][New.col]=newunit;
             square[Curr.row][Curr.col]=unit;
             return 1;
        }
        /////////////////////////////////////////////////

    }

//*********************************************************
}





int w_total_valid_moves()
{
    int no_of_validmoves=0;
    struct COORDS Curr,New;

    for(Curr.row=0;Curr.row<8;++Curr.row)
        for(Curr.col=0;Curr.col<8;++Curr.col)

            if(isupper(square[Curr.row][Curr.col])>0)

                for(New.row=0;New.row<8;++New.row)
                    for(New.col=0;New.col<8;++New.col)

                        if(valid_move(Curr,New))
                            ++no_of_validmoves;



    return no_of_validmoves;
}



int b_total_valid_moves()
{
    int no_of_validmoves=0;
    struct COORDS Curr,New;

    for(Curr.row=0;Curr.row<8;++Curr.row)
        for(Curr.col=0;Curr.col<8;++Curr.col)

            if(islower(square[Curr.row][Curr.col])>0)

                for(New.row=0;New.row<8;++New.row)
                    for(New.col=0;New.col<8;++New.col)

                        if(valid_move(Curr,New))
                            ++no_of_validmoves;



    return no_of_validmoves;
}



void w_checkmate()
{
    if(wk_underattack()==1&&w_total_valid_moves()==0)
    {       printf("\nIt's Checkmate!!Black Wins\n");
            exit(0);
    }

}

void b_checkmate()
{
    if((bk_underattack()==1)&&(b_total_valid_moves()==0))
    {       printf("\nIt's Checkmate!!White Wins\n");
            exit(0);
    }

}

void w_check()
{
    if(wk_underattack()==1&&w_total_valid_moves()>0)
            printf("\nIt's Check\n");

}

void b_check()
{
    if(bk_underattack()==1&&b_total_valid_moves()>0)
            printf("\nIt's Check\n");

}

void w_stalemate()
{
    if(wk_underattack()==0&&w_total_valid_moves()==0)
    {   printf("\nIts Draw!!Stalemate\n");
        exit(0);
    }

}


void b_stalemate()
{
    if(bk_underattack()==0&&b_total_valid_moves()==0)
    {   printf("\nIts Draw!!Stalemate\n");
        exit(0);
    }

}




int bk_underattack2(struct COORDS Curr)
{
//******************************************************************************************
    int i,j,row,col;
    char unit;
    struct COORDS bkpos;

    for(i=0;i<8;++i)
        for(j=0;j<8;++j)
            if(square[i][j]=='k')
                    goto out;
    out:
    bkpos.row=i;
    bkpos.col=j;

    unit=square[Curr.row][Curr.col];
    //////////////////////////////////////////////////////////
    if(unit=='K')
    {   if(bkpos.row==Curr.row-1&&bkpos.col==Curr.col)
            return 1;
        else if(bkpos.row==Curr.row-1&&bkpos.col==Curr.col-1)
            return 1;
        else if(bkpos.row==Curr.row&&bkpos.col==Curr.col-1)
            return 1;
        else if(bkpos.row==Curr.row+1&&bkpos.col==Curr.col-1)
            return 1;
        else if(bkpos.row==Curr.row+1&&bkpos.col==Curr.col)
            return 1;
        else if(bkpos.row==Curr.row+1&&bkpos.col==Curr.col+1)
            return 1;
        else if(bkpos.row==Curr.row&&bkpos.col==Curr.col+1)
            return 1;
        else if(bkpos.row==Curr.row-1&&bkpos.col==Curr.col+1)
            return 1;
        else
            return 0;
    }
    //////////////////////////////////////////////////////////
    else if(unit=='Q')
    {   square[Curr.row][Curr.col]='R';
        i=bk_underattack2(Curr);

        square[Curr.row][Curr.col]='B';
        j=bk_underattack2(Curr);

        square[Curr.row][Curr.col]='Q';

        return i+j;
    }
    //////////////////////////////////////////////////////////
    else if(unit=='P')
    {
        if(bkpos.row==Curr.row-1&&bkpos.col==Curr.col+1)
                return 1;
        else if(bkpos.row==Curr.row-1&&bkpos.col==Curr.col-1)
                return 1;
        else
                return 0;
    }
    //////////////////////////////////////////////////////////
    else if(unit=='R')
    {
            if(bkpos.col==Curr.col)
            {   if(bkpos.row<Curr.row)
                {   for(row=Curr.row-1;row>bkpos.row;--row)
                        if(square[row][Curr.col]=='\0')
                                continue;
                        else
                                return 0;
                    return 1;
                }
                else if(bkpos.row>Curr.row)
                {   for(row=Curr.row+1;row<bkpos.row;++row)
                        if(square[row][Curr.col]=='\0')
                                continue;
                        else
                                return 0;
                    return 1;
                }

            }
            else if(bkpos.row==Curr.row)
            {   if(bkpos.col<Curr.col)
                {   for(col=Curr.col-1;col>bkpos.col;--col)
                        if(square[Curr.row][col]=='\0')
                                continue;
                        else
                                return 0;
                    return 1;
                }
                else if(bkpos.col>Curr.col)
                {   for(col=Curr.col+1;col<bkpos.col;++col)
                        if(square[Curr.row][col]=='\0')
                                continue;
                        else
                                return 0;
                    return 1;
                }

            }
            else
                return 0;

    }
    //////////////////////////////////////////////////////////////
    else if(unit=='N')
    {
        if((bkpos.row==Curr.row-2)&&(bkpos.col==Curr.col+1))
                return 1;
        else if((bkpos.row==Curr.row-2)&&(bkpos.col==Curr.col-1))
                return 1;
        else if((bkpos.row==Curr.row-1)&&(bkpos.col==Curr.col-2))
                return 1;
        else if((bkpos.row==Curr.row+1)&&(bkpos.col==Curr.col-2))
                return 1;
        else if((bkpos.row==Curr.row+2)&&(bkpos.col==Curr.col-1))
                return 1;
        else if((bkpos.row==Curr.row+2)&&(bkpos.col==Curr.col+1))
                return 1;
        else if((bkpos.row==Curr.row+1)&&(bkpos.col==Curr.col+2))
                return 1;
        else if((bkpos.row==Curr.row-1)&&(bkpos.col==Curr.col+2))
                return 1;
        else
                return 0;

    }
    ////////////////////////////////////////////////////////////////

    else if(unit=='B')
    {

        if(Curr.row-bkpos.row==bkpos.col-Curr.col)
        {
            if(bkpos.col>Curr.col)
            {   for(row=Curr.row-1,col=Curr.col+1;row>bkpos.row;--row,++col)
                        if(square[row][col]=='\0')
                                continue;
                        else
                                return 0;
                return 1;

            }
            else if(bkpos.col<Curr.col)
            {   for(row=Curr.row+1,col=Curr.col-1;row<bkpos.row;++row,--col)
                        if(square[row][col]=='\0')
                                continue;
                        else
                                return 0;
                return 1;

            }

        }
        else if(Curr.row-bkpos.row==Curr.col-bkpos.col)
        {
            if(bkpos.col>Curr.col)
            {   for(row=Curr.row+1,col=Curr.col+1;row<bkpos.row;++row,++col)
                        if(square[row][col]=='\0')
                                continue;
                        else
                                return 0;
                return 1;

            }
            else if(bkpos.col<Curr.col)
            {   for(row=Curr.row-1,col=Curr.col-1;row>bkpos.row;--row,--col)
                        if(square[row][col]=='\0')
                                continue;
                        else
                                return 0;
                return 1;

            }

        }
        else
            return 0;
    }
   ////////////////////////////////////////////////////////
    else
        return 0;

//******************************************************************************************
}


//########################################################################################################################
//########################################################################################################################
//########################################################################################################################





int wk_underattack2(struct COORDS Curr)
{
//******************************************************************************************
    int i,j,row,col;
    char unit;
    struct COORDS wkpos;

    for(i=0;i<8;++i)
        for(j=0;j<8;++j)
            if(square[i][j]=='K')
                    goto out2;
    out2:
    wkpos.row=i;
    wkpos.col=j;

    unit=square[Curr.row][Curr.col];
    //////////////////////////////////////////////////////////
    if(unit=='k')
    {   if(wkpos.row==Curr.row-1&&wkpos.col==Curr.col)
            return 1;
        else if(wkpos.row==Curr.row-1&&wkpos.col==Curr.col-1)
            return 1;
        else if(wkpos.row==Curr.row&&wkpos.col==Curr.col-1)
            return 1;
        else if(wkpos.row==Curr.row+1&&wkpos.col==Curr.col-1)
            return 1;
        else if(wkpos.row==Curr.row+1&&wkpos.col==Curr.col)
            return 1;
        else if(wkpos.row==Curr.row+1&&wkpos.col==Curr.col+1)
            return 1;
        else if(wkpos.row==Curr.row&&wkpos.col==Curr.col+1)
            return 1;
        else if(wkpos.row==Curr.row-1&&wkpos.col==Curr.col+1)
            return 1;
        else
            return 0;
    }
    //////////////////////////////////////////////////////////
    else if(unit=='q')
    {   square[Curr.row][Curr.col]='r';
        i=wk_underattack2(Curr);

        square[Curr.row][Curr.col]='b';
        j=wk_underattack2(Curr);

        square[Curr.row][Curr.col]='q';

        return i+j;
    }
    //////////////////////////////////////////////////////////
    else if(unit=='p')
    {
        if(wkpos.row==Curr.row+1&&wkpos.col==Curr.col+1)
                return 1;
        else if(wkpos.row==Curr.row+1&&wkpos.col==Curr.col-1)
                return 1;
        else
                return 0;
    }
    //////////////////////////////////////////////////////////
    else if(unit=='r')
    {
            if(wkpos.col==Curr.col)
            {   if(wkpos.row<Curr.row)
                {   for(row=Curr.row-1;row>wkpos.row;--row)
                        if(square[row][Curr.col]=='\0')
                                continue;
                        else
                                return 0;
                    return 1;
                }
                else if(wkpos.row>Curr.row)
                {   for(row=Curr.row+1;row<wkpos.row;++row)
                        if(square[row][Curr.col]=='\0')
                                continue;
                        else
                                return 0;
                    return 1;
                }

            }
            else if(wkpos.row==Curr.row)
            {   if(wkpos.col<Curr.col)
                {   for(col=Curr.col-1;col>wkpos.col;--col)
                        if(square[Curr.row][col]=='\0')
                                continue;
                        else
                                return 0;
                    return 1;
                }
                else if(wkpos.col>Curr.col)
                {   for(col=Curr.col+1;col<wkpos.col;++col)
                        if(square[Curr.row][col]=='\0')
                                continue;
                        else
                                return 0;
                    return 1;
                }

            }
            else
                return 0;

    }
    //////////////////////////////////////////////////////////////
    else if(unit=='n')
    {
        if((wkpos.row==Curr.row-2)&&(wkpos.col==Curr.col+1))
                return 1;
        else if((wkpos.row==Curr.row-2)&&(wkpos.col==Curr.col-1))
                return 1;
        else if((wkpos.row==Curr.row-1)&&(wkpos.col==Curr.col-2))
                return 1;
        else if((wkpos.row==Curr.row+1)&&(wkpos.col==Curr.col-2))
                return 1;
        else if((wkpos.row==Curr.row+2)&&(wkpos.col==Curr.col-1))
                return 1;
        else if((wkpos.row==Curr.row+2)&&(wkpos.col==Curr.col+1))
                return 1;
        else if((wkpos.row==Curr.row+1)&&(wkpos.col==Curr.col+2))
                return 1;
        else if((wkpos.row==Curr.row-1)&&(wkpos.col==Curr.col+2))
                return 1;
        else
                return 0;

    }
    ////////////////////////////////////////////////////////////////

    else if(unit=='b')
    {

        if(Curr.row-wkpos.row==wkpos.col-Curr.col)
        {
            if(wkpos.col>Curr.col)
            {   for(row=Curr.row-1,col=Curr.col+1;row>wkpos.row;--row,++col)
                        if(square[row][col]=='\0')
                                continue;
                        else
                                return 0;
                return 1;

            }
            else if(wkpos.col<Curr.col)
            {   for(row=Curr.row+1,col=Curr.col-1;row<wkpos.row;++row,--col)
                        if(square[row][col]=='\0')
                                continue;
                        else
                                return 0;
                return 1;

            }

        }
        else if(Curr.row-wkpos.row==Curr.col-wkpos.col)
        {
            if(wkpos.col>Curr.col)
            {   for(row=Curr.row+1,col=Curr.col+1;row<wkpos.row;++row,++col)
                        if(square[row][col]=='\0')
                                continue;
                        else
                                return 0;
                return 1;

            }
            else if(wkpos.col<Curr.col)
            {   for(row=Curr.row-1,col=Curr.col-1;row>wkpos.row;--row,--col)
                        if(square[row][col]=='\0')
                                continue;
                        else
                                return 0;
                return 1;

            }

        }
        else
            return 0;
    }
   ////////////////////////////////////////////////////////
    else
        return 0;

//******************************************************************************************
}



int wk_underattack()
{   struct COORDS pos;

    for(pos.row=0;pos.row<8;++pos.row)
                for(pos.col=0;pos.col<8;++pos.col)
                    if(wk_underattack2(pos))
                        return 1;
    return 0;
}



int bk_underattack()
{   struct COORDS pos;

    for(pos.row=0;pos.row<8;++pos.row)
                for(pos.col=0;pos.col<8;++pos.col)
                    if(bk_underattack2(pos))
                        return 1;
    return 0;
}





void w_promote()
{   int i=0,j;
    char unit;
    for(j=0;j<8;++j)
        if(square[i][j]=='P')
           while(1)
            {    printf("\nPromote your pawn to any one of these:(Q R B N) ");fflush(stdin);
                 scanf("%c",&unit);
                 switch(unit)
                 {   case 'Q': square[i][j]='Q';
                               return;
                     case 'R': square[i][j]='R';
                               return;
                     case 'B': square[i][j]='B';
                               return;
                     case 'N': square[i][j]='N';
                               return;
                     default : printf("Invalid choice Try Again!!");
                 }

            }


}




void b_promote()
{   int i=7,j;
    char unit;
    for(j=0;j<8;++j)
        if(square[i][j]=='p')
           while(1)
            {    printf("\nPromote your pawn to any one of these:(q r b n) ");fflush(stdin);
                 scanf("%c",&unit);
                 switch(unit)
                 {   case 'q': square[i][j]='q';
                               return;
                     case 'r': square[i][j]='r';
                               return;
                     case 'b': square[i][j]='b';
                               return;
                     case 'n': square[i][j]='n';
                               return;
                     default : printf("Invalid choice Try Again!!");
                 }

            }


}



