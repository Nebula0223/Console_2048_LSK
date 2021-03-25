#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<math.h>
#include<conio.h>
int board[4][4],new_board[4][4];
int score=0,best_score,move=0;
void menu();
void initial_board();
void print();
int game_operate(char direction,int board[4][4]);
int judge();//判断是否成为死局 
int victory();
int effictive_move(char direction);
int main()
{
	system("mode con cols=25 lines=20");
	FILE* fp;
	if((fp=fopen("D:\\个人\\C语言\\C语言自编程序\\2048 2.0\\best score.txt","r"))==NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN+FOREGROUND_RED);
		printf("注意！当前无法查看最高分！\n");
		SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE);
		Sleep(2000);
		system("cls");
	}
	else 
	fscanf(fp,"%d",&best_score);
	fclose(fp);
	srand(time(0));
	int i,j,rand_y,rand_x,rand_num,time=1;
	char input;
	menu();
	initial_board();
    while(time<=2)
	{
		rand_y=rand()%4;
    	rand_x=rand()%4;
    	rand_num=pow(2,rand()%2+1);
    	if(board[rand_y][rand_x]==0)
    	{
    		board[rand_y][rand_x]=rand_num;
    		time++;
		}
	}
	print();
	while(1)
	{
		again:
		system("cls");
		menu();
		print();
		int judgement=0;
		for(i=0;i<=3;i++)
		{
			for(j=0;j<=3;j++)
			{
				if(board[i][j]==0)
				{
					judgement=1;
					break;
				}
			}
		}
		if(!judgement)
		{
			if(judge())
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN+FOREGROUND_RED);
				printf("你输了!\n你的分数是:%d",score);
				SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE);
			    break;
			}
		}
		input=getch();
		if(((input!='w')&&(input!='s')&&(input!='a')&&(input!='d'))||(effictive_move(input)==0))
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN+FOREGROUND_RED);
			printf("无效移动！"); 
			SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE);
			Sleep(1500);
			goto again;
		}
		move++;
		score+=game_operate(input,board);
		best_score=(best_score>score?best_score:score);
		if(victory())
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN+FOREGROUND_RED);
			printf("你赢了!\n你的分数是:%d",score);
			SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE);
			break;
		}
		time=0;
		while(time<1)
		{
			rand_y=rand()%4;
    		rand_x=rand()%4;
    		rand_num=pow(2,rand()%2+1);
    		if(board[rand_y][rand_x]==0)
    		{
    			board[rand_y][rand_x]=rand_num;
    			time++;
			}
		}		
	}
	if((fp=fopen("D:\\个人\\C语言\\C语言自编程序\\2048 2.0\\best score.txt","w"))==NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN+FOREGROUND_RED);
		printf("注意！当前无法保存最高分！\n");
		SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE);
		return 0;
	}
	fprintf(fp,"%d",best_score);
	fclose(fp);
	return 0;
}
void menu()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN+FOREGROUND_RED);
	printf("  Welcome To 2048 Game\n");
	printf("      Best Score:%d\n",best_score);
	printf("        Score:%d\n",score);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED+FOREGROUND_INTENSITY);
	printf("*************************\n");
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE);
}
void initial_board()
{
	int i,j;
	for(i=0;i<=3;i++)
	{
		for(j=0;j<=3;j++)
		{
			board[i][j]=0;
		}
	}
}
void print()
{
	int i,j,line;
	for(i=0;i<=3;i++)
	{
		printf("  ");
		for(line=1;line<=4;line++)
		printf(" ----");
		printf("\n");
		for(j=0;j<=3;j++)
		{		
			if(j==0) printf("  |");
			switch(board[i][j])
			{
				case 0://白色 
					printf("    |");
					break;
				case 2://深绿色 
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN);
					printf("%4d",board[i][j]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE);
					printf("|");
					break; 
				case 4://绿色
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN+FOREGROUND_INTENSITY);
					printf("%4d",board[i][j]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE);
					printf("|");
					break;
				case 8://深蓝色
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE);
					printf("%4d",board[i][j]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE);
					printf("|");
					break; 
				case 16://蓝色
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE+FOREGROUND_INTENSITY);
					printf("%4d",board[i][j]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE);
					printf("|");
					break;  
				case 32://青色
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE+FOREGROUND_GREEN);
					printf("%4d",board[i][j]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE);
					printf("|");
					break; 
				case 64://深紫色 
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE+FOREGROUND_RED);
					printf("%4d",board[i][j]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE);
					printf("|");
					break;
				case 128://紫色
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE+FOREGROUND_RED+FOREGROUND_INTENSITY);
					printf("%4d",board[i][j]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE);
					printf("|"); 
					break;
				case 256://深黄色 
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN+FOREGROUND_RED);
					printf("%4d",board[i][j]);
					SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE);	
					printf("|");
					break;			
				case 512://黄色 
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN+FOREGROUND_RED+FOREGROUND_INTENSITY);
					printf("%4d",board[i][j]);
					SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE);
					printf("|");
					break;
				case 1024://深红色
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);
					printf("%4d",board[i][j]);
					SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE); 
					printf("|");
					break;
				case 2048://红色
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED+FOREGROUND_INTENSITY);
					printf("%4d",board[i][j]);
					SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE);  
					printf("|");
					break;
			}
		}
		printf("\n");
	}
	printf("  ");
	for(line=1;line<=4;line++)
	printf(" ----");
	printf("\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN+FOREGROUND_RED);
	printf("请使用w，a，s，d进行操作\n");
	printf("Move:%d\n",move);
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_BLUE);  
}
int game_operate(char direction,int board[4][4])
{
	int i,j,score_add=0;
	switch(direction)
	{
		case 'w':
			for(j=0;j<=3;j++)
			{
				for(i=0;i<3;i++)
				{
					if(board[i][j]==0)
					{
						int I=i;
						do
						{
							I++;
						}
						while(board[I][j]==0&&I<3);
						board[i][j]=board[I][j];
						board[I][j]=0;
					}
				}
			} 
			for(j=0;j<=3;j++)
			{
				if(board[0][j]==board[1][j])
				{
					if(board[2][j]==board[3][j])
					{
						board[0][j]*=2;
						board[1][j]=board[2][j]*2;
						board[2][j]=0;
						board[3][j]=0;
						score_add+=board[0][j]+board[1][j];
					}
					else
					{
						board[0][j]*=2;
						board[1][j]=board[2][j];
						board[2][j]=board[3][j];
						board[3][j]=0;
						score_add+=board[0][j];
					}
				}
				else
				{
					if(board[1][j]==board[2][j])
					{
						board[1][j]*=2;
						board[2][j]=board[3][j];
						board[3][j]=0;
						score_add+=board[1][j];
					}
					else
					{
						if(board[2][j]==board[3][j])
						{
							board[2][j]*=2;
							board[3][j]=0;
							score_add+=board[2][j];
						}
					}
				}
			}
			break;
		case 's':
			for(j=0;j<=3;j++)
			{
				for(i=3;i>0;i--)
				{
					if(board[i][j]==0)
					{
						int I=i;
						do
						{
							I--;
						}
						while(board[I][j]==0&&I>0);
						board[i][j]=board[I][j];
						board[I][j]=0;
					}
				}
			} 
			for(j=0;j<=3;j++)
			{
				if(board[3][j]==board[2][j])
				{
					if(board[1][j]==board[0][j])
					{
						board[3][j]*=2;
						board[2][j]=board[1][j]*2;
						board[1][j]=0;
						board[0][j]=0;
						score_add+=board[3][j]+board[2][j];
					}
					else
					{
						board[3][j]*=2;
						board[2][j]=board[1][j];
						board[1][j]=board[0][j];
						board[0][j]=0;
						score_add+=board[3][j];
					}
				}
				else
				{
					if(board[2][j]==board[1][j])
					{
						board[2][j]*=2;
						board[1][j]=board[0][j];
						board[0][j]=0;
						score_add+=board[2][j];
					}
					else
					{
						if(board[1][j]==board[0][j])
						{
							board[1][j]*=2;
							board[0][j]=0;
							score_add+=board[1][j];
						}
					}
				}
			}
			break;
		case 'a':
			for(i=0;i<=3;i++)
			{
				for(j=0;j<3;j++)
				{
					if(board[i][j]==0)
					{
						int J=j;
						do
						{
							J++;
						}
						while(board[i][J]==0&&J<3);
						board[i][j]=board[i][J];
						board[i][J]=0;
					}
				}
			} 
			for(i=0;i<=3;i++)
			{
				if(board[i][0]==board[i][1])
				{
					if(board[i][2]==board[i][3])
					{
						board[i][0]*=2;
						board[i][1]=board[i][2]*2;
						board[i][2]=0;
						board[i][3]=0;
						score_add+=board[i][0]+board[i][1];
					}
					else
					{
						board[i][0]*=2;
						board[i][1]=board[i][2];
						board[i][2]=board[i][3];
						board[i][3]=0;
						score_add+=board[i][0];
					}
				}
				else
				{
					if(board[i][1]==board[i][2])
					{
						board[i][1]*=2;
						board[i][2]=board[i][3];
						board[i][3]=0;
						score_add+=board[i][1];
					}
					else
					{
						if(board[i][2]==board[i][3])
						{
							board[i][2]*=2;
							board[i][3]=0;
							score_add+=board[i][2];
						}
					}
				}
			}
			break;
		case 'd':
			for(i=0;i<=3;i++)
			{
				for(j=3;j>0;j--)
				{
					if(board[i][j]==0)
					{
						int J=j;
						do
						{
							J--;
						}
						while(board[i][J]==0&&J>0);
						board[i][j]=board[i][J];
						board[i][J]=0;
					}
				}
			} 
			for(i=0;i<=3;i++)
			{
				if(board[i][3]==board[i][2])
				{
					if(board[i][1]==board[i][0])
					{
						board[i][3]*=2;
						board[i][2]=board[i][1]*2;
						board[i][1]=0;
						board[i][0]=0;
						score_add+=board[i][3]+board[i][2];
					}
					else
					{
						board[i][3]*=2;
						board[i][2]=board[i][1];
						board[i][1]=board[i][0];
						board[i][0]=0;
						score_add+=board[i][3];
					}
				}
				else
				{
					if(board[i][2]==board[i][1])
					{
						board[i][2]*=2;
						board[i][1]=board[i][0];
						board[i][0]=0;
						score_add+=board[i][2];
					}
					else
					{
						if(board[i][1]==board[i][0])
						{
							board[i][1]*=2;
							board[i][0]=0;
							score_add+=board[i][1];
						}
					}
				}
			}
			break;
	}
	return score_add;
}
int judge()
{
	int i,j;
	for(i=0;i<=3;i++)
	{
		for(j=0;j<=2;j++)
		{
			if(board[i][j]==board[i][j+1])
			return 0;
		}
	}
	for(j=0;j<=3;j++)
	{
		for(i=0;i<=2;i++)
		{
			if(board[i][j]==board[i+1][j])
			return 0;
		}
	}
	return 1;
}
int victory()
{
	int i,j;
	for(i=0;i<=3;i++)
	{
		for(j=0;j<=3;j++)
		{
			if(board[i][j]==2048)
			return 1;
		}
	}
	return 0;
}
int effictive_move(char direction)
{
	int i,j;
	for(i=0;i<=3;i++)
	{
		for(j=0;j<=3;j++)
		{
			new_board[i][j]=board[i][j];
		}
	}
	game_operate(direction,new_board);
	for(i=0;i<=3;i++)
	{
		for(j=0;j<=3;j++)
		{
			if(new_board[i][j]!=board[i][j])
			return 1;
		}
	}
	return 0;
}
