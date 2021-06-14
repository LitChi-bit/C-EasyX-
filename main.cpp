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
    佛祖保佑       永无BUG
    南无本师释迦牟尼佛！ 南无药师琉璃光如来！ 
	南无阿弥陀佛！ 南无观世音菩萨！ 南无文殊菩萨！ 南无普贤菩萨！ 
	南无大愿地藏王菩萨！ 南无弥勒菩萨！ 南无十方三世诸佛菩萨！

==================================================================*/

#include<graphics.h>
#include<mmsystem.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#pragma comment(lib,"winmm.lib")
#define MAXSTAR 1000	//星星个数

//窗口宽高
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

//正确率和错误率
int right = 0;
int error = 0;

//下坠字符串的结构体
struct TARGET
{
	int x;
	int y;  //坐标
	char* str;  //保存字符串
};

//保存用户输入的字符串的结构体
struct USERKEY
{
	int x;
	int y;  //坐标
	char str[20];  //保存字符串

}userkey = { 320,HEIGHT - 30,"" };

//下坠字母的结构体
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

void MYmusic();//音乐
void welcome();// 欢迎界面
void bkpicture();//背景图 
void bkpicture2();
void bkpicture3();
void goodbye();// 退出界面
void ifget();// 实现闪烁的“按任意键继续”  可以 用作暂停

void divWindow2();//game2 窗口
void InitGame2Target(letter FangAn[], int n);//game2 初始化字符
void illustrate();
void mygame1();
void mygame2();
void mygame3();


void InitStar(int i)// 移动星星
{
	star[i].x = 0;
	star[i].y = rand() % 810;
	star[i].step = (rand() % 5000) / 1000.0 + 1;
	star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	// 速度越快，颜色越亮
	star[i].color = RGB(star[i].color, star[i].color, star[i].color);
}
void MoveStar(int i)
{
	putpixel((int)star[i].x, star[i].y, 0);	// 擦掉原来的星星
	star[i].x += star[i].step;	// 计算新位置
	if (star[i].x > 810)
		InitStar(i);
	putpixel((int)star[i].x, star[i].y, star[i].color);	// 画新星星
}
// 退出界面
void goodbye()
{
	/*closegraph();
	initgraph(WIDTH + 50, HEIGHT);*/
	cleardevice();
	setbkcolor(BLACK);
	cleardevice();
	int c = 0;
	int d = 8;//用来变色
	for (int i = 0; i < MAXSTAR; i++)	// 初始化所有星星
	{
		InitStar(i);
		star[i].x = rand() % 640;
	}
	while (!_kbhit())//没有按下0，按下非0 //实现闪烁
	{
		for (int i = 0; i < MAXSTAR; i++)	// 绘制星空，按任意键退出
			MoveStar(i);
		settextcolor(YELLOW);
		settextstyle(48, 0, _T("黑体"));
		outtextxy(104, 180, _T("   菜就多练练"));
		settextcolor(RGB(100, c, c));
		outtextxy(280, 400, _T("再见"));
		c += d;
		if (c < 8 || c>245)
			d = -d; //实现闪烁
		Sleep(60);//延时20ms
	}


	_getch();
}

// 欢迎界面
void welcome()
{
	// 输出屏幕提示

	cleardevice();
	bkpicture();
	setbkcolor(WHITE);
	setbkmode(TRANSPARENT);

	settextcolor(BLACK);
	settextstyle(64, 0, _T("黑体"));
	outtextxy(280, 50, _T("打字练习"));

	settextcolor(RED);
	settextstyle(50, 0, _T("黑体"));
	outtextxy(300, 200, _T("一级难度"));
	outtextxy(300, 300, _T("二级难度"));
	outtextxy(300, 400, _T("三级难度"));
	settextcolor(LIGHTGRAY);
	outtextxy(700, 550, "退出");

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



//操作说明
void illustrate()
{
	cleardevice();
	bkpicture();
	settextcolor(GREEN);
	settextstyle(30, 0, _T("黑体"));
	outtextxy(300, 50, _T("输入对应字母消除"));
	outtextxy(300, 100, _T("输入正确加速"));
	outtextxy(300, 150, _T("输入错误减速"));
	outtextxy(300, 150, _T("输入错误减速"));
	outtextxy(300, 200, _T("按空格暂停，任意键继续"));
	outtextxy(300, 250, _T("游戏界面输入数字0重选难度"));
	ifget();
}

// 实现闪烁的“按任意键继续”
void ifget()
{

	int c = 255;
	settextstyle(30, 0, _T("黑体"));
	while (!_kbhit())
	{
		settextcolor(RGB(c, 0, 0));
		outtextxy(330, 500, _T("按任意键继续"));
		c -= 8;
		if (c < 50) c = 255;
		Sleep(3);
	}
	_getch();
}

//音乐
void MYmusic()
{
	mciSendString("open D.mp3 alias music", NULL, 0, NULL);
	mciSendString("play music repeat", NULL, 0, NULL);
}

//背景图 
void bkpicture()
{
	IMAGE imagebk;
	setbkmode(TRANSPARENT);
	loadimage(&imagebk, "开始界面.jpg", 800, 600);
	putimage(0, 0, &imagebk);
}

//背景图 
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
//上面是game1******************
/*******************   */

//game2初始化字母
void InitGame2Target(letter FangAn[], int n)
{
	srand((unsigned)time(NULL));
	FangAn[n].s = 65 + rand() % 26;
	while (FangAn[n].s == FangAn[(n + 1) % 3].s || FangAn[n].s == FangAn[(n + 2) % 3].s)
	{
		FangAn[n].s = 65 + rand() % 26;
	}


	//X随机位置
	FangAn[n].x = rand() % (WIDTH - 200);
	while (FangAn[n].x == FangAn[(n + 1) % 3].x || FangAn[n].x == FangAn[(n + 2) % 3].x)
	{
		FangAn[n].x = rand() % (WIDTH - 200);
	}

	//y 的位置
	FangAn[n].y = -60;

}
//game2 的分数框
void divWindow2()
{
	line(WIDTH - 100, 0, WIDTH - 100, HEIGHT);
	settextcolor(GREEN);
	settextstyle(25, 0, "字魂24号-镇魂手书");
	outtextxy(WIDTH - 90, 25, "打字练习");
	outtextxy(WIDTH - 90, 50, "二级难度");
	settextcolor(RED);
	outtextxy(WIDTH - 90, 80, "没有暂停");
	settextcolor(LIGHTBLUE);
	outtextxy(WIDTH - 90, 120, "数字1减速");
	outtextxy(WIDTH - 90, 145, "数字2加速");
	outtextxy(WIDTH - 90, 170, "数字3复原");
	outtextxy(WIDTH - 90, HEIGHT - 100, "按0重选难度");
}


/******************
***************************
****************   game3        */
//在指定位置输出整数
void outtextxy_int(int x, int y, char* format, int num)
{
	char str[20] = "";
	sprintf(str, format, num);
	outtextxy(x, y, str);
}


//在指定位置输出浮点数
void outtextxy_double(int x, int y, char* format, double num)
{
	char str[20] = "";
	sprintf(str, format, num);
	outtextxy(x, y, str);
}

//画窗口
void divWindow()
{
	line(WIDTH - 100, 0, WIDTH - 100, HEIGHT - 40);
	line(0, HEIGHT - 40, WIDTH + 50, HEIGHT - 40);
	line(WIDTH - 100, 130, WIDTH + 50, 130);
	settextcolor(GREEN);
	settextstyle(25, 0, "字魂24号-镇魂手书");
	outtextxy(WIDTH - 90, 25, "打字练习");
	outtextxy(WIDTH - 90, 50, "三级难度");
	outtextxy(WIDTH - 90, 75, "空格暂停");
	outtextxy(WIDTH - 90, HEIGHT - 175, "数字1减速");
	outtextxy(WIDTH - 90, HEIGHT - 150, "数字2加速");
	outtextxy(WIDTH - 90, HEIGHT - 125, "数字3复原");
	outtextxy(WIDTH - 90, HEIGHT - 100, "按0重选难度");


}
//分数
void drawScore()
{
	outtextxy(WIDTH - 90, 225, "正确数");
	outtextxy_int(WIDTH - 90, 250, "%d", right);
	settextcolor(RED);
	outtextxy(WIDTH - 90, 285, "错误数");
	outtextxy_int(WIDTH - 90, 315, "%d", error);
	settextcolor(LIGHTBLUE);
	outtextxy(WIDTH - 90, 285 + 60, "正确率");
	if (right + error == 0)
		outtextxy_double(WIDTH - 90, 285 + 85, "%.2lf%%", 0);
	else
	{
		double sum = right + error;
		outtextxy_double(WIDTH - 90, 285 + 85, "%.2lf%%", right / sum * 100);

	}
}

//随机产生字符串
void initTarget(struct TARGET words[], int n)
{
	srand((unsigned)time(NULL));
	static char str[18][10] = { "main","include","void","while","for",
							"if","true","int","sizeof","continue",
							"static","struct","else","void","case",
							"switch","float","short" };  //0-18

	//随机产生字符串
	words[n].str = str[rand() % 18];
	while (words[n].str == words[(n + 1) % 3].str || words[n].str == words[(n + 2) % 3].str)
	{
		words[n].str = str[rand() % 18];
	}


	//X随机位置
	words[n].x = rand() % (WIDTH - 200);
	if (abs(words[n].x - words[(n + 1) % 3].x < 50) || abs(words[n].x - words[(n + 2) % 3].x < 50))
	{
		words[n].x = rand() % (WIDTH - 200);
	}

	//y 的位置
	words[n].y = -20;
}

//游戏界面  难度1
void mygame1()
{
	illustrate();
	cleardevice();
	bkpicture();
	IMAGE imagebk;
	loadimage(&imagebk, "开始界面.jpg", 800, 600);
	IMAGE LB1, LB2;
	srand((unsigned int)time(NULL));

	int x, y;
	int score = 0;//分数
	char s[1000];
	_itoa(score, s, 10);
	int speed = 5;//速度
	char fang;//掉落字符
	int key; //键盘输入
	while (1)
	{
		fang = 65 + rand() % 26;  //随机产生字符
		x = 10 + rand() % 770; //从10-780

		for (y = 0; y < 600; y++)  //从上到下掉落
		{
			BeginBatchDraw();//预加载  防止闪耀 

			putimage(0, 0, &imagebk);//背景 
			putimage(x, y, &LB2, SRCPAINT);//这两个不能放反
			putimage(x, y, &LB1, SRCAND);//三元光栅
			setbkmode(TRANSPARENT);

			settextstyle(20, 0, "黑体");//字跟图一起掉下来
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
					score++; //分数加
					_itoa(score, s, 10); //转换分数
					speed--; //速度加
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
			Sleep(speed);//休眠0.0X毫秒再落下字母
			EndBatchDraw();
		}
	}
}
//游戏界面  难度2
void mygame2()
{

	IMAGE imagebk;
	loadimage(&imagebk, "bk3.jpg", 800, 600);
	IMAGE LB1, LB2;


	letter FangAn[3];  //三个字符
	//初始化字符
	for (int n = 0; n < 3; n++)
	{
		InitGame2Target(FangAn, n);
		FangAn[n].y = -15 - n * 30; //不等高落下
	}
	int speed = 10;//sudu 
	while (1)
	{
		BeginBatchDraw();//预加载  防止闪耀 
		cleardevice();
		bkpicture3(); //重新画背景
		divWindow2();  //重新画窗口
		drawScore();

		for (int n = 0; n < 3; n++)
		{
			putimage(FangAn[n].x, FangAn[n].y, &LB2, SRCPAINT);//这两个不能放反
			putimage(FangAn[n].x, FangAn[n].y, &LB1, SRCAND);//三元光栅
			setbkmode(TRANSPARENT);
			settextcolor(YELLOW);
			outtextxy(FangAn[n].x + 15, FangAn[n].y + 40, FangAn[n].s);
			FangAn[n].y += 4;

			//底部擦除
			if (FangAn[n].y > (HEIGHT))
			{
				InitGame2Target(FangAn, n);
			}
			if (_kbhit())
			{
				char target = _getch(); //接受键盘输入
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

//难度3个字符 随机掉落
void mygame3()
{

	struct TARGET words[3];
	IMAGE imagebk;
	loadimage(&imagebk, "bk2.jpg", 800, 600);
	IMAGE LB1, LB2;


	//产生字符串
	for (int n = 0; n < 3; n++)
	{
		initTarget(words, n);
		words[n].y = -15 - n * 30; //不等高落下
	}


	int i = 0;//计数
	int speed = 10;
	while (1)
	{
		BeginBatchDraw();//预加载  防止闪耀 
		cleardevice();
		bkpicture2(); //重新画背景
		divWindow();  //重新画窗口
		drawScore();
		//打印文字
		for (int n = 0; n < 3; n++)
		{
			putimage(words[n].x, words[n].y, &LB2, SRCPAINT);//这两个不能放反
			putimage(words[n].x, words[n].y, &LB1, SRCAND);//三元光栅
			setbkmode(TRANSPARENT);
			settextcolor(YELLOW);
			outtextxy(words[n].x, words[n].y + 40, words[n].str);
			words[n].y += 2;

			//底部擦除
			if (words[n].y > (HEIGHT - 40 - textheight(words[n].str)))
			{
				initTarget(words, n);
				error++;
			}
		}
		if (_kbhit())
		{

			char target; //接受键盘输入
			target = _getch();

			//回退
			if (target == 8)  //如果回退了
			{

				if (i > 0)    //往前走一步
					i--;
				userkey.str[i] = '\0';  //当前字母为\0     /
			}
			//退出
			else if (target == 27)
			{
				EndBatchDraw();/// 
				goodbye();

				exit(0);
			}
			//暂停   加速 减速 复原
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
	HWND hwnd = GetHWnd();  // 获取绘图窗口句柄(HWND)
	SetWindowText(hwnd, "打字练习");  //使用 Windows API 修改窗口名称
	MYmusic();
	welcome();// 开始界面
	closegraph();

}