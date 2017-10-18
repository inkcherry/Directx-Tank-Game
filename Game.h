
#pragma once

#include "D3DGraphics.h"
#include "Keyboard.h"
#include <vector>
#include<atlimage.h>
#include "Aitank.h"
#define bulletwidth 29  
#define bulletheight 55
using namespace std;
class Bullet           //子弹
{
public:
	Bullet(int pointx_, int pointy_, int verx_,int very_,D3DGraphics::DirectionState dec_) :pointx(pointx_),pointy(pointy_),verx(verx),very(very),dec(dec_){}
	Bullet(pair<int, int >pointstate,D3DGraphics::DirectionState dec_) :pointx(pointstate.first), pointy(pointstate.second), dec(dec_)
	{
		switch (dec_)   //通过绘图坐标得出定点坐标
		{
		case 0:  //up
			very = pointy, verx = pointx + bulletwidth / 2;
			break;
		case 1:    //down
			very = pointy + bulletheight, verx = pointx + bulletwidth / 2;
			break;
		case 2:
			verx = pointx, very = pointy + bulletwidth / 2;
			break;
		case 3:
			verx = pointx + bulletheight, very = pointx + bulletwidth / 2;
			break;
		}

	}
	int pointx, pointy;  //绘图起点           
	int verx, very;      //图像定点 用于检测碰撞
	D3DGraphics::DirectionState dec;   //坐标和方向
};


class Game
{

public:
	
	static bool bulletlock;
	static UINT moveflag ;
	static UINT stateflag ;
	Aitank *TheAiTank[3] = { new Aitank(100,100),new Aitank(300,100),new Aitank(500,100) };
	 void AitankMove() { TheAiTank[0]->ChangeDec(player1pointx, player1pointy); TheAiTank[1]->ChangeDec(player1pointx, player1pointy), TheAiTank[2]->ChangeDec(player1pointx, player1pointy); }
	static void CALLBACK bulletinterval(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime);   //普通回掉函数
	void AiMove() { TheAiTank[0]->move(0,*TheAiTank,getpointx(),getpointy()), TheAiTank[1]->move(1,*TheAiTank, getpointx(), getpointy()), TheAiTank[2]->move(2,*TheAiTank, getpointx(), getpointy()); }
	HBITMAP bgbmp;
	void Paint();
	Game( HWND hWnd, KeyboardServer& kServer );
	void Go();
	int getpointx() { return player1pointx; }
	int getpointy() { return player1pointy; }
	pair<int, int> getcenterpoint(){return make_pair(player1pointx + 35, player1pointy+35);}
	D3DGraphics::DirectionState getdecstate() { return Player1State; }
	Bullet * getBuletState() { Bullet *temp = new Bullet(getgunpoint(), getdecstate()); return temp; }
	void load(Game &temp,HWND &hWnd);
	bool checkblank(D3DGraphics::DirectionState dec_);
	bool checkplayershot(vector<Bullet*>::iterator &temp);
	void AiRevive(int id) { TheAiTank[id]->setpoint(0, 0); };
	CImage TankSurface[17];
	CImage BulletSurface[4];
	CImage AiSurface[4];
private:
	bool Moveflag();
	int Realflag() { return Moveflag() + stateflag+Player1State*4; }   //这个没有右图像
	void DrawSurface(int xoff, int yoff, int width, int height, const D3DCOLOR *xsurf);
	void Player1Move();
	void DrawBullet();
	pair<int, int> getgunpoint();   //获取枪口绘图起点坐标的位置


	D3DGraphics::DirectionState Player1State;
	D3DGraphics gfx;
	KeyboardClient kbd;
	int player1pointx;
	int player1pointy;
	vector<Bullet*> PlayerBullet;
};