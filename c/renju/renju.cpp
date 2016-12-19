// renju.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include "graphics.h"
#include "conio.h"
#include "time.h"
#include "math.h"
#include "string.h"

#define WEIGHT 550
#define HEIGHT 550

struct ju
{
	int ju_x;
	int ju_y;
	int ju_n;
	char ju_k;
}jua[11][11];

int ju_temp_xy[2];
int ju_temp_n = 0;
bool goon = true;
int win_point[3] = {0,0,0};

extern void initialize();
extern void ju_painting(int ju_painting_x,int ju_painting_y,char ju_painting_m);
extern bool mouse_rule(int mouse_rule_x,int mouse_rule_y,int *p_temp_ju);
extern char win_rule(struct ju win_rule_temp[11][11],int *p_temp_win);
extern void winc(char winner,int *p_win_point);
extern void grid();

void main()
{	
	initialize();

	initgraph(850,600);
	grid();

	MOUSEMSG m;

	while(true)
	{
		m = GetMouseMsg();

		switch(m.uMsg)
		{
			case WM_LBUTTONDOWN:
				if (m.mkCtrl)
					return;						
				else
				{
					if(mouse_rule(m.x,m.y,ju_temp_xy) && goon)
					{
						if(ju_temp_n % 2 !=0)
						{
							ju_painting(jua[ju_temp_xy[0]][ju_temp_xy[1]].ju_x ,jua[ju_temp_xy[0]][ju_temp_xy[1]].ju_y , 'A');
						
						}
						else
						{
							ju_painting(jua[ju_temp_xy[0]][ju_temp_xy[1]].ju_x ,jua[ju_temp_xy[0]][ju_temp_xy[1]].ju_y , 'B');
						}
						if(ju_temp_n == 121)winc('D',win_point);
						winc(win_rule(jua,win_point),win_point);
						
					}
				}
				break;
		}
	}

	closegraph();
}

void ju_painting(int ju_painting_x,int ju_painting_y,char ju_painting_m)
{
	IMAGE ju_painting_s;
	if(ju_painting_m == 'A')
	{
		jua[ju_temp_xy[0]][ju_temp_xy[1]].ju_k = 'A';
		jua[ju_temp_xy[0]][ju_temp_xy[1]].ju_n = ju_temp_n;
		loadimage(&ju_painting_s, "xpic\\A.BMP");
		putimage(ju_painting_x-20, ju_painting_y-20, &ju_painting_s);
	}
	else if(ju_painting_m == 'B')
	{
		jua[ju_temp_xy[0]][ju_temp_xy[1]].ju_k = 'B';
		jua[ju_temp_xy[0]][ju_temp_xy[1]].ju_n = ju_temp_n;
		loadimage(&ju_painting_s, "xpic\\B.BMP");
		putimage(ju_painting_x-20, ju_painting_y-20, &ju_painting_s);
	}
	else if(ju_painting_m == 'W')
	{
		loadimage(&ju_painting_s, "xpic\\W.BMP");
		putimage(ju_painting_x-20, ju_painting_y-20, &ju_painting_s);
	}
}
bool mouse_rule(int mouse_rule_x,int mouse_rule_y,int *p_temp_ju)
{
	for(int jua_temp_j = 0 ; jua_temp_j < 11 ; jua_temp_j ++)
	{
		for(int jua_temp_k = 0 ; jua_temp_k <11 ; jua_temp_k ++)
		{
			/*if(abs(jua[jua_temp_j][jua_temp_k].ju_x - mouse_rule_x) <= 20 && 
				abs(jua[jua_temp_j][jua_temp_k].ju_y - mouse_rule_y) <= 20 &&
				jua[jua_temp_j][jua_temp_k].ju_k == 'N')*/
			if(sqrt(pow(abs(jua[jua_temp_j][jua_temp_k].ju_x - mouse_rule_x),2) + 
					pow(abs(jua[jua_temp_j][jua_temp_k].ju_y - mouse_rule_y),2) ) <= 24 &&
				jua[jua_temp_j][jua_temp_k].ju_k == 'N')
			{
				*p_temp_ju = jua_temp_j;
				*(p_temp_ju+1) = jua_temp_k;
				ju_temp_n ++;
				return true;
			}
		}
	}
	return false;
}
void initialize()
{
	for(int jua_temp_j = 0 ; jua_temp_j < 11 ; jua_temp_j ++)
	{
		for(int jua_temp_k = 0 ; jua_temp_k <11 ; jua_temp_k ++)
		{
			jua[jua_temp_j][jua_temp_k].ju_x = (jua_temp_k+1) * 50;
			jua[jua_temp_j][jua_temp_k].ju_y = (jua_temp_j+1) * 50;
			jua[jua_temp_j][jua_temp_k].ju_k = 'N';
		}
	}
}
char win_rule(struct ju win_rule_temp[11][11],int *p_temp_win)
{
	int win_rule_j = 0;
	int win_rule_k = 0;
	int win_rule_temp_t = 0;
	int win_rule_j_con = 0;
	int win_rule_k_con = 0;
	
	int win_rule_temp_sum = 0;
	char win_rule_temp_char = 'N';
//****************************************************
	for(win_rule_j = 0 ;win_rule_j <11 ;win_rule_j ++)
	{
		win_rule_temp_sum = 0;
		win_rule_temp_char = 'N';

		for(win_rule_k = 0 ;win_rule_k <11 ;win_rule_k ++)
		{
			if(win_rule_temp[win_rule_j][win_rule_k].ju_k == 'N')
			{
				win_rule_temp_sum = 0;
				win_rule_temp_char = 'N';
			}

			if(win_rule_temp[win_rule_j][win_rule_k].ju_k != 'N' && win_rule_temp_char == 'N')
			{
				win_rule_temp_char = win_rule_temp[win_rule_j][win_rule_k].ju_k;
				win_rule_temp_sum ++;
			}
			else if(win_rule_temp[win_rule_j][win_rule_k].ju_k != 'N' && win_rule_temp_char != 'N')
			{
				if(win_rule_temp[win_rule_j][win_rule_k].ju_k == win_rule_temp_char)
				{
					win_rule_temp_sum ++;
					if(win_rule_temp_sum == 5)
					{
						*p_temp_win=win_rule_j;
						*(p_temp_win+1)=win_rule_k;
						*(p_temp_win+2)=1;

						return win_rule_temp_char;
					}
				}
				else
				{
					win_rule_temp_char = win_rule_temp[win_rule_j][win_rule_k].ju_k;
					win_rule_temp_sum = 1;
				}
			}
		}
	}
//****************************************************
	for(win_rule_k = 0 ;win_rule_k <11 ;win_rule_k ++)
	{
		win_rule_temp_sum = 0;
		win_rule_temp_char = 'N';

		for(win_rule_j = 0 ;win_rule_j <11 ;win_rule_j ++)
		{
			if(win_rule_temp[win_rule_j][win_rule_k].ju_k == 'N')
			{
				win_rule_temp_sum = 0;
				win_rule_temp_char = 'N';
			}

			if(win_rule_temp[win_rule_j][win_rule_k].ju_k != 'N' && win_rule_temp_char == 'N')
			{
				win_rule_temp_char = win_rule_temp[win_rule_j][win_rule_k].ju_k;
				win_rule_temp_sum ++;
			}
			else if(win_rule_temp[win_rule_j][win_rule_k].ju_k != 'N' && win_rule_temp_char != 'N')
			{
				if(win_rule_temp[win_rule_j][win_rule_k].ju_k == win_rule_temp_char)
				{
					win_rule_temp_sum ++;
					if(win_rule_temp_sum == 5)
					{
						*p_temp_win=win_rule_j;
						*(p_temp_win+1)=win_rule_k;
						*(p_temp_win+2)=2;

						return win_rule_temp_char;
					}
				}
				else
				{
					win_rule_temp_char = win_rule_temp[win_rule_j][win_rule_k].ju_k;
					win_rule_temp_sum = 1;
				}
			}
		}
	}
//****************************************************
	win_rule_j_con = 6;
	win_rule_k_con = 0;

	for(win_rule_temp_t = 0 ; win_rule_temp_t < 13 ; win_rule_temp_t ++)
	{

		win_rule_temp_sum = 0;
		win_rule_temp_char = 'N';

		for(win_rule_j = win_rule_j_con , win_rule_k = win_rule_k_con ; win_rule_j < 11 && win_rule_k < 11; win_rule_j ++ ,win_rule_k ++)
		{
			if(win_rule_temp[win_rule_j][win_rule_k].ju_k == 'N')
			{
				win_rule_temp_sum = 0;
				win_rule_temp_char = 'N';
			}

			if(win_rule_temp[win_rule_j][win_rule_k].ju_k != 'N' && win_rule_temp_char == 'N')
			{
				win_rule_temp_char = win_rule_temp[win_rule_j][win_rule_k].ju_k;
				win_rule_temp_sum ++;
			}
			else if(win_rule_temp[win_rule_j][win_rule_k].ju_k != 'N' && win_rule_temp_char != 'N')
			{
				if(win_rule_temp[win_rule_j][win_rule_k].ju_k == win_rule_temp_char)
				{
					win_rule_temp_sum ++;
					if(win_rule_temp_sum == 5)
					{
						*p_temp_win=win_rule_j;
						*(p_temp_win+1)=win_rule_k;
						*(p_temp_win+2)=3;

						return win_rule_temp_char;
					}
				}
				else
				{
					win_rule_temp_char = win_rule_temp[win_rule_j][win_rule_k].ju_k;
					win_rule_temp_sum = 1;
				}
			}
		}
		//---------------------
		if(win_rule_j_con == 0)
		{
			win_rule_k_con ++;
		}
		if(win_rule_j_con > 0)
		{
			win_rule_j_con --;
		}

	}
//****************************************************

	win_rule_j_con = 4;
	win_rule_k_con = 0;

	for(win_rule_temp_t = 0 ; win_rule_temp_t < 13 ; win_rule_temp_t ++)
	{

		win_rule_temp_sum = 0;
		win_rule_temp_char = 'N';

		for(win_rule_j = win_rule_j_con , win_rule_k = win_rule_k_con ; win_rule_j >=0 && win_rule_k < 11; win_rule_j -- ,win_rule_k ++)
		{
			if(win_rule_temp[win_rule_j][win_rule_k].ju_k == 'N')
			{
				win_rule_temp_sum = 0;
				win_rule_temp_char = 'N';
			}

			if(win_rule_temp[win_rule_j][win_rule_k].ju_k != 'N' && win_rule_temp_char == 'N')
			{
				win_rule_temp_char = win_rule_temp[win_rule_j][win_rule_k].ju_k;
				win_rule_temp_sum ++;
			}
			else if(win_rule_temp[win_rule_j][win_rule_k].ju_k != 'N' && win_rule_temp_char != 'N')
			{
				if(win_rule_temp[win_rule_j][win_rule_k].ju_k == win_rule_temp_char)
				{
					win_rule_temp_sum ++;
					if(win_rule_temp_sum == 5)
					{
						*p_temp_win=win_rule_j;
						*(p_temp_win+1)=win_rule_k;
						*(p_temp_win+2)=4;

						return win_rule_temp_char;
					}
				}
				else
				{
					win_rule_temp_char = win_rule_temp[win_rule_j][win_rule_k].ju_k;
					win_rule_temp_sum = 1;
				}
			}
		}
		//---------------------
		if(win_rule_j_con == 10)
		{
			win_rule_k_con ++;
		}
		if(win_rule_j_con < 10)
		{
			win_rule_j_con ++;
		}

	}
//****************************************************
	return 'N';

}
void winc(char winner,int *p_win_point)
{
	MOUSEMSG m_winc;


//----------------------------
	if(winner == 'D')
	{
		goon=false;
		
		FlushMouseMsgBuffer();
		
		while(!goon)
		{
			m_winc = GetMouseMsg();

			switch(m_winc.uMsg)
			{
				
			case WM_LBUTTONDOWN:
				if (m_winc.mkCtrl){}					
				else
				{
					for(int winc_j = 0 ; winc_j < 11 ; winc_j ++)
						for(int winc_k = 0 ; winc_k < 11 ; winc_k ++)
						{
							Sleep(10);
							ju_painting(jua[winc_j][winc_k].ju_x ,jua[winc_j][winc_k].ju_y , 'W');
						}
					goon=true;
				}
				break;
			}
		}

		goon=false;
		FlushMouseMsgBuffer();
		
		while(!goon)
		{
			m_winc = GetMouseMsg();

			switch(m_winc.uMsg)
			{
				
			case WM_LBUTTONDOWN:
				if (m_winc.mkCtrl){}				
				else
				{
					initialize();
					cleardevice();
					grid();
					ju_temp_n = 0;
					goon=true;
				}
				break;
			}
		}
	}

	if(winner == 'A' || winner == 'B')
	{
		if(*(p_win_point+2) == 1)
		{
			ju_painting(jua[*p_win_point][*(p_win_point+1)-0].ju_x ,jua[*p_win_point][*(p_win_point+1)-0].ju_y , 'W');
			ju_painting(jua[*p_win_point][*(p_win_point+1)-1].ju_x ,jua[*p_win_point][*(p_win_point+1)-1].ju_y , 'W');
			ju_painting(jua[*p_win_point][*(p_win_point+1)-2].ju_x ,jua[*p_win_point][*(p_win_point+1)-2].ju_y , 'W');
			ju_painting(jua[*p_win_point][*(p_win_point+1)-3].ju_x ,jua[*p_win_point][*(p_win_point+1)-3].ju_y , 'W');
			ju_painting(jua[*p_win_point][*(p_win_point+1)-4].ju_x ,jua[*p_win_point][*(p_win_point+1)-4].ju_y , 'W');
			Sleep(500);
			ju_painting(jua[*p_win_point][*(p_win_point+1)-0].ju_x ,jua[*p_win_point][*(p_win_point+1)-0].ju_y , winner);
			ju_painting(jua[*p_win_point][*(p_win_point+1)-1].ju_x ,jua[*p_win_point][*(p_win_point+1)-1].ju_y , winner);
			ju_painting(jua[*p_win_point][*(p_win_point+1)-2].ju_x ,jua[*p_win_point][*(p_win_point+1)-2].ju_y , winner);
			ju_painting(jua[*p_win_point][*(p_win_point+1)-3].ju_x ,jua[*p_win_point][*(p_win_point+1)-3].ju_y , winner);
			ju_painting(jua[*p_win_point][*(p_win_point+1)-4].ju_x ,jua[*p_win_point][*(p_win_point+1)-4].ju_y , winner);
			Sleep(500);
			ju_painting(jua[*p_win_point][*(p_win_point+1)-0].ju_x ,jua[*p_win_point][*(p_win_point+1)-0].ju_y , 'W');
			ju_painting(jua[*p_win_point][*(p_win_point+1)-1].ju_x ,jua[*p_win_point][*(p_win_point+1)-1].ju_y , 'W');
			ju_painting(jua[*p_win_point][*(p_win_point+1)-2].ju_x ,jua[*p_win_point][*(p_win_point+1)-2].ju_y , 'W');
			ju_painting(jua[*p_win_point][*(p_win_point+1)-3].ju_x ,jua[*p_win_point][*(p_win_point+1)-3].ju_y , 'W');
			ju_painting(jua[*p_win_point][*(p_win_point+1)-4].ju_x ,jua[*p_win_point][*(p_win_point+1)-4].ju_y , 'W');
			Sleep(500);
			ju_painting(jua[*p_win_point][*(p_win_point+1)-0].ju_x ,jua[*p_win_point][*(p_win_point+1)-0].ju_y , winner);
			ju_painting(jua[*p_win_point][*(p_win_point+1)-1].ju_x ,jua[*p_win_point][*(p_win_point+1)-1].ju_y , winner);
			ju_painting(jua[*p_win_point][*(p_win_point+1)-2].ju_x ,jua[*p_win_point][*(p_win_point+1)-2].ju_y , winner);
			ju_painting(jua[*p_win_point][*(p_win_point+1)-3].ju_x ,jua[*p_win_point][*(p_win_point+1)-3].ju_y , winner);
			ju_painting(jua[*p_win_point][*(p_win_point+1)-4].ju_x ,jua[*p_win_point][*(p_win_point+1)-4].ju_y , winner);
		}
		else if(*(p_win_point+2) == 2)
		{
			ju_painting(jua[*p_win_point-0][*(p_win_point+1)].ju_x ,jua[*p_win_point-0][*(p_win_point+1)].ju_y , 'W');
			ju_painting(jua[*p_win_point-1][*(p_win_point+1)].ju_x ,jua[*p_win_point-1][*(p_win_point+1)].ju_y , 'W');
			ju_painting(jua[*p_win_point-2][*(p_win_point+1)].ju_x ,jua[*p_win_point-2][*(p_win_point+1)].ju_y , 'W');
			ju_painting(jua[*p_win_point-3][*(p_win_point+1)].ju_x ,jua[*p_win_point-3][*(p_win_point+1)].ju_y , 'W');
			ju_painting(jua[*p_win_point-4][*(p_win_point+1)].ju_x ,jua[*p_win_point-4][*(p_win_point+1)].ju_y , 'W');
			Sleep(500);
			ju_painting(jua[*p_win_point-0][*(p_win_point+1)].ju_x ,jua[*p_win_point-0][*(p_win_point+1)].ju_y , winner);
			ju_painting(jua[*p_win_point-1][*(p_win_point+1)].ju_x ,jua[*p_win_point-1][*(p_win_point+1)].ju_y , winner);
			ju_painting(jua[*p_win_point-2][*(p_win_point+1)].ju_x ,jua[*p_win_point-2][*(p_win_point+1)].ju_y , winner);
			ju_painting(jua[*p_win_point-3][*(p_win_point+1)].ju_x ,jua[*p_win_point-3][*(p_win_point+1)].ju_y , winner);
			ju_painting(jua[*p_win_point-4][*(p_win_point+1)].ju_x ,jua[*p_win_point-4][*(p_win_point+1)].ju_y , winner);
			Sleep(500);
			ju_painting(jua[*p_win_point-0][*(p_win_point+1)].ju_x ,jua[*p_win_point-0][*(p_win_point+1)].ju_y , 'W');
			ju_painting(jua[*p_win_point-1][*(p_win_point+1)].ju_x ,jua[*p_win_point-1][*(p_win_point+1)].ju_y , 'W');
			ju_painting(jua[*p_win_point-2][*(p_win_point+1)].ju_x ,jua[*p_win_point-2][*(p_win_point+1)].ju_y , 'W');
			ju_painting(jua[*p_win_point-3][*(p_win_point+1)].ju_x ,jua[*p_win_point-3][*(p_win_point+1)].ju_y , 'W');
			ju_painting(jua[*p_win_point-4][*(p_win_point+1)].ju_x ,jua[*p_win_point-4][*(p_win_point+1)].ju_y , 'W');
			Sleep(500);
			ju_painting(jua[*p_win_point-0][*(p_win_point+1)].ju_x ,jua[*p_win_point-0][*(p_win_point+1)].ju_y , winner);
			ju_painting(jua[*p_win_point-1][*(p_win_point+1)].ju_x ,jua[*p_win_point-1][*(p_win_point+1)].ju_y , winner);
			ju_painting(jua[*p_win_point-2][*(p_win_point+1)].ju_x ,jua[*p_win_point-2][*(p_win_point+1)].ju_y , winner);
			ju_painting(jua[*p_win_point-3][*(p_win_point+1)].ju_x ,jua[*p_win_point-3][*(p_win_point+1)].ju_y , winner);
			ju_painting(jua[*p_win_point-4][*(p_win_point+1)].ju_x ,jua[*p_win_point-4][*(p_win_point+1)].ju_y , winner);
		}
		else if(*(p_win_point+2) == 3)
		{
			ju_painting(jua[*p_win_point-0][*(p_win_point+1)-0].ju_x ,jua[*p_win_point-0][*(p_win_point+1)-0].ju_y , 'W');
			ju_painting(jua[*p_win_point-1][*(p_win_point+1)-1].ju_x ,jua[*p_win_point-1][*(p_win_point+1)-1].ju_y , 'W');
			ju_painting(jua[*p_win_point-2][*(p_win_point+1)-2].ju_x ,jua[*p_win_point-2][*(p_win_point+1)-2].ju_y , 'W');
			ju_painting(jua[*p_win_point-3][*(p_win_point+1)-3].ju_x ,jua[*p_win_point-3][*(p_win_point+1)-3].ju_y , 'W');
			ju_painting(jua[*p_win_point-4][*(p_win_point+1)-4].ju_x ,jua[*p_win_point-4][*(p_win_point+1)-4].ju_y , 'W');
			Sleep(500);
			ju_painting(jua[*p_win_point-0][*(p_win_point+1)-0].ju_x ,jua[*p_win_point-0][*(p_win_point+1)-0].ju_y , winner);
			ju_painting(jua[*p_win_point-1][*(p_win_point+1)-1].ju_x ,jua[*p_win_point-1][*(p_win_point+1)-1].ju_y , winner);
			ju_painting(jua[*p_win_point-2][*(p_win_point+1)-2].ju_x ,jua[*p_win_point-2][*(p_win_point+1)-2].ju_y , winner);
			ju_painting(jua[*p_win_point-3][*(p_win_point+1)-3].ju_x ,jua[*p_win_point-3][*(p_win_point+1)-3].ju_y , winner);
			ju_painting(jua[*p_win_point-4][*(p_win_point+1)-4].ju_x ,jua[*p_win_point-4][*(p_win_point+1)-4].ju_y , winner);
			Sleep(500);
			ju_painting(jua[*p_win_point-0][*(p_win_point+1)-0].ju_x ,jua[*p_win_point-0][*(p_win_point+1)-0].ju_y , 'W');
			ju_painting(jua[*p_win_point-1][*(p_win_point+1)-1].ju_x ,jua[*p_win_point-1][*(p_win_point+1)-1].ju_y , 'W');
			ju_painting(jua[*p_win_point-2][*(p_win_point+1)-2].ju_x ,jua[*p_win_point-2][*(p_win_point+1)-2].ju_y , 'W');
			ju_painting(jua[*p_win_point-3][*(p_win_point+1)-3].ju_x ,jua[*p_win_point-3][*(p_win_point+1)-3].ju_y , 'W');
			ju_painting(jua[*p_win_point-4][*(p_win_point+1)-4].ju_x ,jua[*p_win_point-4][*(p_win_point+1)-4].ju_y , 'W');
			Sleep(500);
			ju_painting(jua[*p_win_point-0][*(p_win_point+1)-0].ju_x ,jua[*p_win_point-0][*(p_win_point+1)-0].ju_y , winner);
			ju_painting(jua[*p_win_point-1][*(p_win_point+1)-1].ju_x ,jua[*p_win_point-1][*(p_win_point+1)-1].ju_y , winner);
			ju_painting(jua[*p_win_point-2][*(p_win_point+1)-2].ju_x ,jua[*p_win_point-2][*(p_win_point+1)-2].ju_y , winner);
			ju_painting(jua[*p_win_point-3][*(p_win_point+1)-3].ju_x ,jua[*p_win_point-3][*(p_win_point+1)-3].ju_y , winner);
			ju_painting(jua[*p_win_point-4][*(p_win_point+1)-4].ju_x ,jua[*p_win_point-4][*(p_win_point+1)-4].ju_y , winner);
		}
		else if(*(p_win_point+2) == 4)
		{
			ju_painting(jua[*p_win_point+0][*(p_win_point+1)-0].ju_x ,jua[*p_win_point+0][*(p_win_point+1)-0].ju_y , 'W');
			ju_painting(jua[*p_win_point+1][*(p_win_point+1)-1].ju_x ,jua[*p_win_point+1][*(p_win_point+1)-1].ju_y , 'W');
			ju_painting(jua[*p_win_point+2][*(p_win_point+1)-2].ju_x ,jua[*p_win_point+2][*(p_win_point+1)-2].ju_y , 'W');
			ju_painting(jua[*p_win_point+3][*(p_win_point+1)-3].ju_x ,jua[*p_win_point+3][*(p_win_point+1)-3].ju_y , 'W');
			ju_painting(jua[*p_win_point+4][*(p_win_point+1)-4].ju_x ,jua[*p_win_point+4][*(p_win_point+1)-4].ju_y , 'W');
			Sleep(500);
			ju_painting(jua[*p_win_point+0][*(p_win_point+1)-0].ju_x ,jua[*p_win_point+0][*(p_win_point+1)-0].ju_y , winner);
			ju_painting(jua[*p_win_point+1][*(p_win_point+1)-1].ju_x ,jua[*p_win_point+1][*(p_win_point+1)-1].ju_y , winner);
			ju_painting(jua[*p_win_point+2][*(p_win_point+1)-2].ju_x ,jua[*p_win_point+2][*(p_win_point+1)-2].ju_y , winner);
			ju_painting(jua[*p_win_point+3][*(p_win_point+1)-3].ju_x ,jua[*p_win_point+3][*(p_win_point+1)-3].ju_y , winner);
			ju_painting(jua[*p_win_point+4][*(p_win_point+1)-4].ju_x ,jua[*p_win_point+4][*(p_win_point+1)-4].ju_y , winner);
			Sleep(500);
			ju_painting(jua[*p_win_point+0][*(p_win_point+1)-0].ju_x ,jua[*p_win_point+0][*(p_win_point+1)-0].ju_y , 'W');
			ju_painting(jua[*p_win_point+1][*(p_win_point+1)-1].ju_x ,jua[*p_win_point+1][*(p_win_point+1)-1].ju_y , 'W');
			ju_painting(jua[*p_win_point+2][*(p_win_point+1)-2].ju_x ,jua[*p_win_point+2][*(p_win_point+1)-2].ju_y , 'W');
			ju_painting(jua[*p_win_point+3][*(p_win_point+1)-3].ju_x ,jua[*p_win_point+3][*(p_win_point+1)-3].ju_y , 'W');
			ju_painting(jua[*p_win_point+4][*(p_win_point+1)-4].ju_x ,jua[*p_win_point+4][*(p_win_point+1)-4].ju_y , 'W');
			Sleep(500);
			ju_painting(jua[*p_win_point+0][*(p_win_point+1)-0].ju_x ,jua[*p_win_point+0][*(p_win_point+1)-0].ju_y , winner);
			ju_painting(jua[*p_win_point+1][*(p_win_point+1)-1].ju_x ,jua[*p_win_point+1][*(p_win_point+1)-1].ju_y , winner);
			ju_painting(jua[*p_win_point+2][*(p_win_point+1)-2].ju_x ,jua[*p_win_point+2][*(p_win_point+1)-2].ju_y , winner);
			ju_painting(jua[*p_win_point+3][*(p_win_point+1)-3].ju_x ,jua[*p_win_point+3][*(p_win_point+1)-3].ju_y , winner);
			ju_painting(jua[*p_win_point+4][*(p_win_point+1)-4].ju_x ,jua[*p_win_point+4][*(p_win_point+1)-4].ju_y , winner);
		}

		

		goon=false;
		
		FlushMouseMsgBuffer();
		
		while(!goon)
		{
			m_winc = GetMouseMsg();

			switch(m_winc.uMsg)
			{
				
			case WM_LBUTTONDOWN:
				if (m_winc.mkCtrl){}					
				else
				{
					for(int winc_j = 0 ; winc_j < 11 ; winc_j ++)
						for(int winc_k = 0 ; winc_k < 11 ; winc_k ++)
						{
							Sleep(10);
							jua[winc_j][winc_k].ju_k = winner;
							ju_painting(jua[winc_j][winc_k].ju_x ,jua[winc_j][winc_k].ju_y , winner);
						}
					goon=true;
				}
				break;
			}
		}
		//----------------------------

		goon=false;
		FlushMouseMsgBuffer();
		
		while(!goon)
		{
			m_winc = GetMouseMsg();

			switch(m_winc.uMsg)
			{
				
			case WM_LBUTTONDOWN:
				if (m_winc.mkCtrl){}				
				else
				{
					initialize();
					cleardevice();
					grid();
					ju_temp_n = 0;
					goon=true;
				}
				break;
			}
		}

	}
	
}
void grid()
{
	for(int line_temp_row =50 ; line_temp_row <= WEIGHT ; line_temp_row += 50)
		line(line_temp_row,50,line_temp_row,HEIGHT);

	for(int line_temp_col= 50 ; line_temp_col <= HEIGHT ; line_temp_col += 50)
		line(50,line_temp_col,WEIGHT,line_temp_col);
}