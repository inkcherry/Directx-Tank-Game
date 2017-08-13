
#pragma once

#include "D3DGraphics.h"
#include "Keyboard.h"
#include <vector>

#define BASEWIDTH 930
#define BASEHEIGHT 530
using namespace std;
class Bullet           //子弹
{
public:
	Bullet(int pointx_, int pointy_, D3DGraphics::DirectionState dec_) :pointx(pointx_),pointy(pointy_),dec(dec_){}
	Bullet(pair<int, int >pointstate, D3DGraphics::DirectionState dec_) :pointx(pointstate.first), pointy(pointstate.second), dec(dec_) {}
	int pointx, pointy;           
	D3DGraphics::DirectionState dec;   //坐标和方向
};
class Game
{
	
public:
	Game( HWND hWnd,const KeyboardServer& kServer );
	void Go();
	int getpointx() { return player1pointx; }
	int getpointy() { return player1pointy; }
	D3DGraphics::DirectionState getdecstate() { return Player1State; }
	Bullet * getBuletState() { Bullet *temp = new Bullet(getgunpoint(), getdecstate()); return temp; }
private:

	void ComposeFrame();
	void test(int n);
	void DrawSurface(int xoff, int yoff, int width, int height, const D3DCOLOR *xsurf);
	void Player1Move();
	void DrawBullet();
	pair<int, int> getgunpoint();   //获取枪口坐标的位置
	
	/*void bullet(int pointx,int pointy,int from, D3DGraphics::DirectionState dec, int speed);*/
	D3DGraphics::DirectionState Player1State;
	D3DGraphics gfx;
	KeyboardClient kbd;
	D3DCOLOR surface[200000];
	int player1pointx;
	int player1pointy;
	bool lock;
	vector<Bullet*> PlayerBullet;
	
	/********************* ***********/
	/*  User Variables              */
	
	// TODO: User variables go here

	/********************************/
};