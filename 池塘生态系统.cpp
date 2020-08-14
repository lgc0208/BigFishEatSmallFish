//池塘生态系统.cpp
#include"Functions.h"

int main()
{
	player player1;
	fish bigfish[numB];
	fish littlefish[numL];
	fish shrimp[numS];
	srand(unsigned(time(0)));
	//玩家初始位置
	player* player2 = &player1;
	player2->x = rand() % (ScreenHeight - 50);
	player2->y = rand() % (ScreenWidth - 50);
	//鱼初始位置
	fish* shrimp1[15];//shrimp指针数组
	for (int i = 0; i < numS; i++)
	{
		shrimp1[i] = &shrimp[i];
		shrimp1[i]->x = rand() % (ScreenHeight - 50);
		shrimp1[i]->y = rand() % (ScreenWidth - 50);
		shrimp1[i]->size = 0;
	}
	fish* littlefish1[numL];//littlefish指针数组
	for (int i = 0; i < numL; i++)
	{
		littlefish1[i] = &littlefish[i];
		littlefish1[i]->x = rand() % (ScreenHeight - 50);
		littlefish1[i]->y = rand() % (ScreenWidth - 50);
		littlefish1[i]->size = 1;

	}
	fish* bigfish1[numB];
	for (int i = 0; i < numB; i++)
	{
		bigfish1[i] = &bigfish[i];
		bigfish1[i]->x = rand() % (ScreenHeight - 50);
		bigfish1[i]->y = rand() % (ScreenWidth - 50);
		bigfish1[i]->size = 2;

	}

	loadImages();//加载图片
	initgraph(ScreenHeight, ScreenWidth);//加载窗口界面
	putimage(0, 0, &background);//放置窗口背景板
	mciSendString(L"open  music.mp3 ", 0, NULL, NULL);//将音乐文件放在与源文件同一目录下，alias  music的意思就是将这个音乐文件重新命名为music
	mciSendString(L"play music.mp3 repeat", NULL, NULL, NULL);//播放音乐，play意为播放，同样可换做pause:暂停，stop:停止，close:关闭，Resume:继续。Repeat意为重复播放。
	////mciSendstring(“stop music repeat”, NULL, NULL, NULL)；//暂停播放音乐。
	setbkmode(TRANSPARENT);	//设置字体背景色为透明
	settextcolor(BLACK);		//设置字体颜色为红色
	/*****************游戏规则*****************/
	outtextxy(290, 200, L"游戏规则:");
	outtextxy(290, 230, L"玩家操作鱼吃比自己等级低的鱼");
	outtextxy(290, 260, L"遇到比自己等级高或同等级的鱼即死亡");
	outtextxy(290, 290, L"出界即死亡");
	outtextxy(290, 320, L"按回车键开始");
	outtextxy(290, 350, L"按P键暂停");
	outtextxy(290, 380, L"按ESC键自毁");
	outtextxy(290, 410, L"持续按C开启无敌模式");
	getchar();//使得开始界面静止，当用户按下Enter键时继续执行指令
	//char s[] = "blacksheepwall";
	
	//程序运行
	do
	{

		putimage(0, 0, &background);//放置游戏界面背景板
		ScorePrint(player2);//打印计分板

		//如果用户没有按C键，按此模式运行
		if (!(GetAsyncKeyState('C') & 0x8000))
		{
			//打印NPC-BOSS鱼
			for (int i = 0; i < numS; i++)
			{
				movefish(shrimp1[i]);//NPC移动函数
				changeImage(Fish[0], shrimp1[i]->x, shrimp1[i]->y);//制作掩码图
				iftouch(shrimp1[i], player2);//判断玩家与NPC是否相遇
				out(shrimp1[i]);//判断鱼是否出界
			}
			//打印NPC-小鱼
			for (int i = 0; i < numL; i++)
			{
				movefish(littlefish1[i]);
				changeImage(Fish[1], littlefish1[i]->x, littlefish1[i]->y);
				iftouch(littlefish1[i], player2);
				out(littlefish1[i]);
			}
			//打印NPC-大鱼
			for (int i = 0; i < numB; i++)
			{
				movefish(bigfish1[i]);
				changeImage2(Fish[2], bigfish1[i]->x, bigfish1[i]->y);
				iftouch(bigfish1[i], player2);
				out(bigfish1[i]);
			}
		}
		//若用户按下C键，进入无敌模式
		else
		{
			setbkmode(TRANSPARENT);	//设置字体背景色为透明
			settextcolor(BLACK);		//设置字体颜色为红色
			TCHAR str[32] = { 0 };
			_stprintf_s(str, _T("已开始作弊模式"));//提示操作者已进入无敌模式
			outtextxy(5, 45, str);
			for (int i = 0; i < numS; i++)
			{
				movefish(shrimp1[i]);
				changeImage(Fish[0], shrimp1[i]->x, shrimp1[i]->y);
				iftouch2(shrimp1[i], player2);//若接触，NPC必死
				out(shrimp1[i]);
			}
			for (int i = 0; i < numL; i++)
			{
				movefish(littlefish1[i]);
				changeImage(Fish[1], littlefish1[i]->x, littlefish1[i]->y);
				iftouch2(littlefish1[i], player2);//若接触，NPC必死
				out(littlefish1[i]);
			}
			for (int i = 0; i < numB; i++)
			{
				movefish(bigfish1[i]);
				changeImage2(Fish[2], bigfish1[i]->x, bigfish1[i]->y);
				iftouch2(bigfish1[i], player2);//若接触，NPC必死
				out(bigfish1[i]);
			}
		}

		//玩家的移动
		move(player2);
		if (Formerx > player2->x)//是否转弯
		{
			if (player2->size == 1)
				changeImage(lplayerfish[player2->size - 1], player2->x, player2->y);
			else changeImage2(lplayerfish[player2->size - 1], player2->x, player2->y);
		}
		else
		{
			if (player2->size == 1)
				changeImage(rplayerfish[player2->size - 1], player2->x, player2->y);
			else changeImage2(rplayerfish[1], player2->x, player2->y);
		}
		Formerx = player2->x;

		playerout(player2);
		if (GetAsyncKeyState('P') & 0x8000)//若按下P，则暂停
			ret = _getwch();
		Sleep(40);//帧率
	} while (player2->live == true && !(GetAsyncKeyState(VK_ESCAPE) & 0x8000));//在没有按下ESC或者玩家未死亡时，持续执行

	//设置结束页面
	putimage(0, 0, &background);
	setbkmode(TRANSPARENT);	//设置字体背景色为透明
	settextcolor(BLACK);		//设置字体颜色为红色
	outtextxy(290, 290, L"游戏结束:");
	outtextxy(290, 320, L"按任意键退出:");
	while (_kbhit())//键盘敲击，接受到任意键后退出
		ret = _getwch();
	ret = _getwch();
	closegraph();
	return 0;
}

