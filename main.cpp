/*=============================================================
                      _ooOoo_
                     o8888888o
                     88" . "88
                    (| - _ - |)
                    O \  =  / O
                 ____/ `---'\____
                .'  \\|     |//  `.
               /  \\|||  :  |||//  \
              /  -||||| -:- |||||-  \
             |    | \\\  -  /// |    |
            |  \_ | ''\-- - / '' |    |
            \  . - \__  `-`  ___ / -. /
            ___`. .'  /--.--\  `. .`___
         ."" '<  `.___\_<|>_/___.' > '"".
       | | :  `- \`.; `\ _ / `;.`/ - ` : | |
       \  \ `-.   \_ __\ / __ _ / . - ` /  /
======`-.____`-.___\___ _ ____/. - `____. - '======
					 `=----= '
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    ���汣��       ����BUG
    ���ޱ�ʦ����Ĳ��� ����ҩʦ������������ 
	���ް����ӷ� ���޹����������� �������������� �������������� 
	���޴�Ը�ز��������� �������������� ����ʮ���������������

==================================================================*/

#include<graphics.h>
#include<mmsystem.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#pragma comment(lib,"winmm.lib")
#define MAXSTAR 1000	//���Ǹ���

//���ڿ��
const int WIDTH = 750;
const int HEIGHT = 600;


struct STAR
{
	double x;
	int y;
	double step;
	int color;
};
STAR star[MAXSTAR];

//��ȷ�ʺʹ�����
int right = 0;
int error = 0;

//��׹�ַ����Ľṹ��
struct TARGET
{
	int x;
	int y;  //����
	char* str;  //�����ַ���
};

//�����û�������ַ����Ľṹ��
struct USERKEY
{
	int x;
	int y;  //����
	char str[20];  //�����ַ���

}userkey = { 320,HEIGHT - 30,"" };

//��׹��ĸ�Ľṹ��
typedef struct  node
{
	int x;
	int y;
	int s;
}letter;


void outtextxy_int(int x, int y, char* format, int num);
void outtextxy_double(int x, int y, char* format, double num);
void divWindow();
void drawScore();

void MYmusic();//����
void welcome();// ��ӭ����
void bkpicture();//����ͼ 
void bkpicture2();
void bkpicture3();
void goodbye();// �˳�����
void ifget();// ʵ����˸�ġ��������������  ���� ������ͣ

void divWindow2();//game2 ����
void InitGame2Target(letter FangAn[], int n);//game2 ��ʼ���ַ�
void illustrate();
void mygame1();
void mygame2();
void mygame3();


void InitStar(int i)// �ƶ�����
{
	star[i].x = 0;
	star[i].y = rand() % 810;
	star[i].step = (rand() % 5000) / 1000.0 + 1;
	star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	// �ٶ�Խ�죬��ɫԽ��
	star[i].color = RGB(star[i].color, star[i].color, star[i].color);
}
void MoveStar(int i)
{
	putpixel((int)star[i].x, star[i].y, 0);	// ����ԭ��������
	star[i].x += star[i].step;	// ������λ��
	if (star[i].x > 810)
		InitStar(i);
	putpixel((int)star[i].x, star[i].y, star[i].color);	// ��������
}
// �˳�����
void goodbye()
{
	/*closegraph();
	initgraph(WIDTH + 50, HEIGHT);*/
	cleardevice();
	setbkcolor(BLACK);
	cleardevice();
	int c = 0;
	int d = 8;//������ɫ
	for (int i = 0; i < MAXSTAR; i++)	// ��ʼ����������
	{
		InitStar(i);
		star[i].x = rand() % 640;
	}
	while (!_kbhit())//û�а���0�����·�0 //ʵ����˸
	{
		for (int i = 0; i < MAXSTAR; i++)	// �����ǿգ���������˳�
			MoveStar(i);
		settextcolor(YELLOW);
		settextstyle(48, 0, _T("����"));
		outtextxy(104, 180, _T("   �˾Ͷ�����"));
		settextcolor(RGB(100, c, c));
		outtextxy(280, 400, _T("�ټ�"));
		c += d;
		if (c < 8 || c>245)
			d = -d; //ʵ����˸
		Sleep(60);//��ʱ20ms
	}


	_getch();
}

// ��ӭ����
void welcome()
{
	// �����Ļ��ʾ

	cleardevice();
	bkpicture();
	setbkcolor(WHITE);
	setbkmode(TRANSPARENT);

	settextcolor(BLACK);
	settextstyle(64, 0, _T("����"));
	outtextxy(280, 50, _T("������ϰ"));

	settextcolor(RED);
	settextstyle(50, 0, _T("����"));
	outtextxy(300, 200, _T("һ���Ѷ�"));
	outtextxy(300, 300, _T("�����Ѷ�"));
	outtextxy(300, 400, _T("�����Ѷ�"));
	settextcolor(LIGHTGRAY);
	outtextxy(700, 550, "�˳�");

	MOUSEMSG m;

	while (1)
	{

		setlinestyle(0, 3, 0, 0);

		m = GetMouseMsg();
		if (m.x > 300 && m.x < 500 && m.y>200 && m.y < 250)
		{

			setlinecolor(WHITE);
			rectangle(298, 198, 502, 252);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				mygame1();
			}
		}
		else if (m.x > 300 && m.x < 500 && m.y>300 && m.y < 350)
		{

			setlinecolor(WHITE);
			rectangle(298, 298, 502, 352);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				mygame2();
			}
		}
		else if (m.x > 300 && m.x < 500 && m.y>400 && m.y < 450)
		{

			setlinecolor(WHITE);
			rectangle(298, 398, 502, 452);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				mygame3();
			}
		}
		else if (m.x > 700 && m.x < 800 && m.y>550 && m.y < 600)
		{

			setlinecolor(WHITE);
			rectangle(700, 548, 800, 600);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				goodbye();
			}
		}
		else
		{

			setlinecolor(BLACK);
			rectangle(298, 198, 502, 252);
			rectangle(298, 298, 502, 352);
			rectangle(298, 398, 502, 452);
			rectangle(700, 548, 800, 600);

		}

	}

}



//����˵��
void illustrate()
{
	cleardevice();
	bkpicture();
	settextcolor(GREEN);
	settextstyle(30, 0, _T("����"));
	outtextxy(300, 50, _T("�����Ӧ��ĸ����"));
	outtextxy(300, 100, _T("������ȷ����"));
	outtextxy(300, 150, _T("����������"));
	outtextxy(300, 150, _T("����������"));
	outtextxy(300, 200, _T("���ո���ͣ�����������"));
	outtextxy(300, 250, _T("��Ϸ������������0��ѡ�Ѷ�"));
	ifget();
}

// ʵ����˸�ġ��������������
void ifget()
{

	int c = 255;
	settextstyle(30, 0, _T("����"));
	while (!_kbhit())
	{
		settextcolor(RGB(c, 0, 0));
		outtextxy(330, 500, _T("�����������"));
		c -= 8;
		if (c < 50) c = 255;
		Sleep(3);
	}
	_getch();
}

//����
void MYmusic()
{
	mciSendString("open D.mp3 alias music", NULL, 0, NULL);
	mciSendString("play music repeat", NULL, 0, NULL);
}

//����ͼ 
void bkpicture()
{
	IMAGE imagebk;
	setbkmode(TRANSPARENT);
	loadimage(&imagebk, "��ʼ����.jpg", 800, 600);
	putimage(0, 0, &imagebk);
}

//����ͼ 
void bkpicture2()
{
	IMAGE imagebk;
	setbkmode(TRANSPARENT);
	loadimage(&imagebk, "bk2.jpg", 800, 600);
	putimage(0, 0, &imagebk);
}
void bkpicture3()
{
	IMAGE imagebk;
	setbkmode(TRANSPARENT);
	loadimage(&imagebk, "bk3.jpg", 800, 600);
	putimage(0, 0, &imagebk);
}
//������game1******************
/*******************   */

//game2��ʼ����ĸ
void InitGame2Target(letter FangAn[], int n)
{
	srand((unsigned)time(NULL));
	FangAn[n].s = 65 + rand() % 26;
	while (FangAn[n].s == FangAn[(n + 1) % 3].s || FangAn[n].s == FangAn[(n + 2) % 3].s)
	{
		FangAn[n].s = 65 + rand() % 26;
	}


	//X���λ��
	FangAn[n].x = rand() % (WIDTH - 200);
	while (FangAn[n].x == FangAn[(n + 1) % 3].x || FangAn[n].x == FangAn[(n + 2) % 3].x)
	{
		FangAn[n].x = rand() % (WIDTH - 200);
	}

	//y ��λ��
	FangAn[n].y = -60;

}
//game2 �ķ�����
void divWindow2()
{
	line(WIDTH - 100, 0, WIDTH - 100, HEIGHT);
	settextcolor(GREEN);
	settextstyle(25, 0, "�ֻ�24��-�������");
	outtextxy(WIDTH - 90, 25, "������ϰ");
	outtextxy(WIDTH - 90, 50, "�����Ѷ�");
	settextcolor(RED);
	outtextxy(WIDTH - 90, 80, "û����ͣ");
	settextcolor(LIGHTBLUE);
	outtextxy(WIDTH - 90, 120, "����1����");
	outtextxy(WIDTH - 90, 145, "����2����");
	outtextxy(WIDTH - 90, 170, "����3��ԭ");
	outtextxy(WIDTH - 90, HEIGHT - 100, "��0��ѡ�Ѷ�");
}


/******************
***************************
****************   game3        */
//��ָ��λ���������
void outtextxy_int(int x, int y, char* format, int num)
{
	char str[20] = "";
	sprintf(str, format, num);
	outtextxy(x, y, str);
}


//��ָ��λ�����������
void outtextxy_double(int x, int y, char* format, double num)
{
	char str[20] = "";
	sprintf(str, format, num);
	outtextxy(x, y, str);
}

//������
void divWindow()
{
	line(WIDTH - 100, 0, WIDTH - 100, HEIGHT - 40);
	line(0, HEIGHT - 40, WIDTH + 50, HEIGHT - 40);
	line(WIDTH - 100, 130, WIDTH + 50, 130);
	settextcolor(GREEN);
	settextstyle(25, 0, "�ֻ�24��-�������");
	outtextxy(WIDTH - 90, 25, "������ϰ");
	outtextxy(WIDTH - 90, 50, "�����Ѷ�");
	outtextxy(WIDTH - 90, 75, "�ո���ͣ");
	outtextxy(WIDTH - 90, HEIGHT - 175, "����1����");
	outtextxy(WIDTH - 90, HEIGHT - 150, "����2����");
	outtextxy(WIDTH - 90, HEIGHT - 125, "����3��ԭ");
	outtextxy(WIDTH - 90, HEIGHT - 100, "��0��ѡ�Ѷ�");


}
//����
void drawScore()
{
	outtextxy(WIDTH - 90, 225, "��ȷ��");
	outtextxy_int(WIDTH - 90, 250, "%d", right);
	settextcolor(RED);
	outtextxy(WIDTH - 90, 285, "������");
	outtextxy_int(WIDTH - 90, 315, "%d", error);
	settextcolor(LIGHTBLUE);
	outtextxy(WIDTH - 90, 285 + 60, "��ȷ��");
	if (right + error == 0)
		outtextxy_double(WIDTH - 90, 285 + 85, "%.2lf%%", 0);
	else
	{
		double sum = right + error;
		outtextxy_double(WIDTH - 90, 285 + 85, "%.2lf%%", right / sum * 100);

	}
}

//��������ַ���
void initTarget(struct TARGET words[], int n)
{
	srand((unsigned)time(NULL));
	static char str[18][10] = { "main","include","void","while","for",
							"if","true","int","sizeof","continue",
							"static","struct","else","void","case",
							"switch","float","short" };  //0-18

	//��������ַ���
	words[n].str = str[rand() % 18];
	while (words[n].str == words[(n + 1) % 3].str || words[n].str == words[(n + 2) % 3].str)
	{
		words[n].str = str[rand() % 18];
	}


	//X���λ��
	words[n].x = rand() % (WIDTH - 200);
	if (abs(words[n].x - words[(n + 1) % 3].x < 50) || abs(words[n].x - words[(n + 2) % 3].x < 50))
	{
		words[n].x = rand() % (WIDTH - 200);
	}

	//y ��λ��
	words[n].y = -20;
}

//��Ϸ����  �Ѷ�1
void mygame1()
{
	illustrate();
	cleardevice();
	bkpicture();
	IMAGE imagebk;
	loadimage(&imagebk, "��ʼ����.jpg", 800, 600);
	IMAGE LB1, LB2;
	srand((unsigned int)time(NULL));

	int x, y;
	int score = 0;//����
	char s[1000];
	_itoa(score, s, 10);
	int speed = 5;//�ٶ�
	char fang;//�����ַ�
	int key; //��������
	while (1)
	{
		fang = 65 + rand() % 26;  //��������ַ�
		x = 10 + rand() % 770; //��10-780

		for (y = 0; y < 600; y++)  //���ϵ��µ���
		{
			BeginBatchDraw();//Ԥ����  ��ֹ��ҫ 

			putimage(0, 0, &imagebk);//���� 
			putimage(x, y, &LB2, SRCPAINT);//���������ܷŷ�
			putimage(x, y, &LB1, SRCAND);//��Ԫ��դ
			setbkmode(TRANSPARENT);

			settextstyle(20, 0, "����");//�ָ�ͼһ�������
			settextcolor(BLACK);
			outtextxy(x + 15, y + 40, fang);

			settextcolor(WHITE);
			outtextxy(700, 580, "score:");

			outtextxy(770, 580, s);

			if (_kbhit())
			{
				key = _getch();
				if (key == fang || key == fang + 32)
				{
					score++; //������
					_itoa(score, s, 10); //ת������
					speed--; //�ٶȼ�
					if (speed < 1)
						speed = 1;
					break;
				}
				else if (key == ' ')
				{
					_getch();
				}
				else if (key == 27)
				{
					EndBatchDraw();/// 
					goodbye();

					exit(0);
				}
				else if (key == '0')
				{
					EndBatchDraw();/// 
					welcome();
				}
				else
				{
					if (speed > 20)
						speed = 20;
					speed += 3;
				}
			}
			Sleep(speed);//����0.0X������������ĸ
			EndBatchDraw();
		}
	}
}
//��Ϸ����  �Ѷ�2
void mygame2()
{

	IMAGE imagebk;
	loadimage(&imagebk, "bk3.jpg", 800, 600);
	IMAGE LB1, LB2;


	letter FangAn[3];  //�����ַ�
	//��ʼ���ַ�
	for (int n = 0; n < 3; n++)
	{
		InitGame2Target(FangAn, n);
		FangAn[n].y = -15 - n * 30; //���ȸ�����
	}
	int speed = 10;//sudu 
	while (1)
	{
		BeginBatchDraw();//Ԥ����  ��ֹ��ҫ 
		cleardevice();
		bkpicture3(); //���»�����
		divWindow2();  //���»�����
		drawScore();

		for (int n = 0; n < 3; n++)
		{
			putimage(FangAn[n].x, FangAn[n].y, &LB2, SRCPAINT);//���������ܷŷ�
			putimage(FangAn[n].x, FangAn[n].y, &LB1, SRCAND);//��Ԫ��դ
			setbkmode(TRANSPARENT);
			settextcolor(YELLOW);
			outtextxy(FangAn[n].x + 15, FangAn[n].y + 40, FangAn[n].s);
			FangAn[n].y += 4;

			//�ײ�����
			if (FangAn[n].y > (HEIGHT))
			{
				InitGame2Target(FangAn, n);
			}
			if (_kbhit())
			{
				char target = _getch(); //���ܼ�������
				int flagERROR = 0;
				for (int i = 0; i < 3; i++)
				{

					if (target == FangAn[i].s || target == FangAn[i].s + 32)
					{
						InitGame2Target(FangAn, i);
						right++;
						flagERROR = 1;
					}
					else if (target == '1')
					{
						speed += 2;
						flagERROR = 1;
						if (speed > 100)
							speed = 100;
					}
					else if (target == '2')
					{
						speed -= 2;
						flagERROR = 1;
						if (speed < 0)
							speed = 0;
					}
					else if (target == '3')
					{
						speed = 10;
						flagERROR = 1;

					}
					else if (target == 27)
					{
						EndBatchDraw();/// 
						goodbye();

						exit(0);
					}
					else if (target == '0')
					{
						EndBatchDraw();/// 
						welcome();
					}

				}
				if (flagERROR == 0)
				{
					error++;
				}

			}
		}
		EndBatchDraw();
		Sleep(speed);
	}

}

//�Ѷ�3���ַ� �������
void mygame3()
{

	struct TARGET words[3];
	IMAGE imagebk;
	loadimage(&imagebk, "bk2.jpg", 800, 600);
	IMAGE LB1, LB2;


	//�����ַ���
	for (int n = 0; n < 3; n++)
	{
		initTarget(words, n);
		words[n].y = -15 - n * 30; //���ȸ�����
	}


	int i = 0;//����
	int speed = 10;
	while (1)
	{
		BeginBatchDraw();//Ԥ����  ��ֹ��ҫ 
		cleardevice();
		bkpicture2(); //���»�����
		divWindow();  //���»�����
		drawScore();
		//��ӡ����
		for (int n = 0; n < 3; n++)
		{
			putimage(words[n].x, words[n].y, &LB2, SRCPAINT);//���������ܷŷ�
			putimage(words[n].x, words[n].y, &LB1, SRCAND);//��Ԫ��դ
			setbkmode(TRANSPARENT);
			settextcolor(YELLOW);
			outtextxy(words[n].x, words[n].y + 40, words[n].str);
			words[n].y += 2;

			//�ײ�����
			if (words[n].y > (HEIGHT - 40 - textheight(words[n].str)))
			{
				initTarget(words, n);
				error++;
			}
		}
		if (_kbhit())
		{

			char target; //���ܼ�������
			target = _getch();

			//����
			if (target == 8)  //���������
			{

				if (i > 0)    //��ǰ��һ��
					i--;
				userkey.str[i] = '\0';  //��ǰ��ĸΪ\0     /
			}
			//�˳�
			else if (target == 27)
			{
				EndBatchDraw();/// 
				goodbye();

				exit(0);
			}
			//��ͣ   ���� ���� ��ԭ
			else if (target == ' ')
			{
				_getch();
			}
			else if (target == '1')
			{
				speed += 2;
				if (speed > 100)
					speed = 100;
			}
			else if (target == '2')
			{
				speed -= 2;
				if (speed < 0)
					speed = 0;
			}
			else if (target == '3')
			{
				speed = 10;

			}
			else if (target == '0')
			{
				EndBatchDraw();/// 
				welcome();
			}

			else if (target != '\r')
			{
				userkey.str[i++] = target;

			}
			else
			{
				int flagERROR = 0;
				for (i = 0; i < 3; i++)
				{
					if (strcmp(userkey.str, words[i].str) == 0)
					{
						initTarget(words, i);
						right++;
						flagERROR = 1;
					}
				}
				if (flagERROR == 0)
				{
					error++;
				}
				userkey.x = 320;
				i = 0;
				memset(userkey.str, 0, 20);

			}

		}
		outtextxy(userkey.x, userkey.y, userkey.str);
		EndBatchDraw();
		Sleep(10);
	}
}


void main()
{
	initgraph(WIDTH + 50, HEIGHT);
	HWND hwnd = GetHWnd();  // ��ȡ��ͼ���ھ��(HWND)
	SetWindowText(hwnd, "������ϰ");  //ʹ�� Windows API �޸Ĵ�������
	MYmusic();
	welcome();// ��ʼ����
	closegraph();

}