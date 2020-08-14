//Functions.h
#ifndef _Functions_H
#define _Functions_H
	
#include <easyx.h>
#include <conio.h>
#include <time.h>
#include <iostream>                //ͷ�ļ�
#pragma  comment(lib,"winmm.lib")        //���þ�̬��
#include"Struct.h"
using namespace std;
/*************************************ȫ�ֱ���****************************************************/
const short ScreenWidth = 480;
const short ScreenHeight = 640;
short ret = 0;
int ToBig = 10;
/**************NPC�������****************/
const int numB = 1;//��������
const int numL = 2;//С������
const int numS = 3;//Ϻ������
IMAGE Fish[3];//���ͼƬ
IMAGE lplayerfish[2];//������ͼƬ
IMAGE rplayerfish[2];//������ͼƬ
IMAGE background;//����
short Formerx = 0;//����ת��
short Formery = 0;//����ת��
const int N = 50;//ͼƬ��С

//����ͼƬ
extern void loadImages() 
{
	loadimage(&Fish[2], L"bigfish.jpg", 2 * N, 2 * N);
	loadimage(&Fish[1], L"littlefish.jpg", N, N);
	loadimage(&Fish[0], L"shrimp.jpg", N, N);
	loadimage(&background, L"background.jpg", ScreenHeight, ScreenWidth);
	loadimage(&lplayerfish[0], L"lplayerlittlefish.jpg", N, N);
	loadimage(&lplayerfish[1], L"lplayerbigfish.jpg", 2 * N, 2 * N);
	loadimage(&rplayerfish[0], L"rplayerlittlefish.jpg", N, N);
	loadimage(&rplayerfish[1], L"rplayerbigfish.jpg", 2 * N, 2 * N);
}

//��������ͼ
extern void changeImage(IMAGE imagePut, int x, int y)
{
	IMAGE image(N, N); //�洢����
	DWORD* pmemflower = GetImageBuffer(&imagePut);
	DWORD* image1 = GetImageBuffer(&image);
	DWORD* fish1 = GetImageBuffer(&imagePut);
	COLORREF backcolor = pmemflower[0];
	for (int i = 0; i < N * N; i++)
	{
		if (pmemflower[i] >= backcolor)
			image1[i] = WHITE;
		else
			image1[i] = BLACK;
	}
	for (int i = 0; i < N * N; i++)
	{
		if (pmemflower[i] >= backcolor)
			fish1[i] = BLACK;
	}
	putimage(x, y, &image, SRCAND);
	putimage(x, y, &imagePut, SRCPAINT);
}

//�����ض��������ͼ
extern void changeImage2(IMAGE imagePut, int x, int y)
{
	IMAGE image(100, 100); //�洢����
	DWORD* pmemflower = GetImageBuffer(&imagePut);
	DWORD* image1 = GetImageBuffer(&image);
	DWORD* fish1 = GetImageBuffer(&imagePut);
	COLORREF backcolor = pmemflower[0];
	for (int i = 0; i < 100 * 100; i++)
	{
		if (pmemflower[i] >= backcolor)
			image1[i] = WHITE;
		else
			image1[i] = BLACK;
	}
	for (int i = 0; i < 100 * 100; i++)
	{
		if (pmemflower[i] >= backcolor)
			fish1[i] = BLACK;
	}
	putimage(x, y, &image, SRCAND);
	putimage(x, y, &imagePut, SRCPAINT);
}

//����ƶ�
extern void move(player* player2)
{
	if (GetAsyncKeyState(65) & 0x8000)  player2->x -= 10;	// ���
	if (GetAsyncKeyState(87) & 0x8000)  player2->y -= 10;	// ����
	if (GetAsyncKeyState(83) & 0x8000)  player2->y += 10;	// ����
	if (GetAsyncKeyState(68) & 0x8000)  player2->x += 10;	// �ұ�
}

//NPC�ƶ�
extern void movefish(fish* fish1)
{
	fish1->x += (rand() % 21) - 10;
	fish1->y += (rand() & 21) - 10;
}

//��̬����
extern void biggerplayer(player* player2)
{
	if (player2->score > ToBig)
		player2->size = 2;
}

//NPC����
extern void reborn(fish* fish1)
{
	fish1->x = rand() % (ScreenHeight - 50);
	fish1->y = rand() % (ScreenWidth - 50);
}

//�ж�����Ƿ�����
extern void ifDead(fish* fish1, player* player2)
{
	if (fish1->size < player2->size)
	{
		player2->score++;
		biggerplayer(player2);
		reborn(fish1);
	}
	else if (fish1->size >= player2->size)
	{
		player2->live = false;
	}
}

//�ж������NPC�Ƿ�����
extern void iftouch(fish* fish1, player* player2)
{
	if (((abs(fish1->x - player2->x) < N)) && (abs(fish1->y - player2->y) < N))//����С��N��������
		ifDead(fish1, player2);
}

extern void iftouch2(fish* fish1, player* player2)
{
	if (((abs(fish1->x - player2->x) < N)) && (abs(fish1->y - player2->y) < N))//����С��N��������
	{
		player2->score++;
		biggerplayer(player2);
		reborn(fish1);
	}
}

//�ж����Ƿ����
extern void out(fish* fish1)
{
	if ((fish1->x < 0) || (fish1->x > (ScreenHeight - 50)))
	{
		reborn(fish1);
	}
	if ((fish1->y < 0) || (fish1->y > (ScreenWidth - 50)))
	{
		reborn(fish1);
	}
}

//�ж�����Ƿ����
extern void playerout(player* player2)
{
	if ((player2->x < 0) || (player2->x > ScreenHeight - 50))
		player2->live = false;
	if ((player2->y < 0) || (player2->y > ScreenWidth - 50))
		player2->live = false;
}

//��ӡ�Ʒְ�
extern void ScorePrint(player* player2)
{
	setbkmode(TRANSPARENT);	//�������屳��ɫΪ͸��
	settextcolor(BLACK);		//����������ɫΪ��ɫ
	TCHAR str[32] = { 0 };
	_stprintf_s(str, _T("��ɱ��%d"), player2->score);
	outtextxy(5, 5, str);
	_stprintf_s(str, _T("��̬��%d"), player2->size);
	outtextxy(5, 25, str);
}

#endif // !_Functions_H

