
#include "Game.h"
#include "bitmap.h"
#include  "D3DGraphics.h"
#include<assert.h>

#include <thread>
#define  adddistance 51
#define  divdistance 19
#define aitobullet 20
#define aitankr 16
Game* TheCurrentObject;
int Dieid=0;

Game::Game(HWND hWnd,  KeyboardServer& kServer)
	: gfx(hWnd),
	kbd(kServer),
	player1pointx(0),
	player1pointy(0),
	Player1State(D3DGraphics::UP){}
bool Game::bulletlock = true;
 UINT Game:: moveflag=0;
 UINT Game::stateflag=0;
 HDC  hdc, bufdc;   //hdc贴图双缓冲
void Game::Go()
{
	gfx.BeginFrame();
	//ComposeFrame();
	gfx.EndFrame();

	Player1Move();    //键位处理函数
	Paint();         //主要的绘图函数
	AiMove();        //敌坦克移动函数
}
UINT_PTR  BulletTimer;    //3
UINT_PTR  AiMoveTimer;
UINT_PTR  AiReviveTimer;  //10 11 12

void Game::Player1Move()
{
	
	if (kbd.RightIsPressed() && !kbd.UpIsPressed() && !kbd.DownIsPressed())
	{

		if (Player1State != D3DGraphics::RIGHT)       //转向缓冲
		{}
        if(player1pointx<BASEWIDTH&&checkblank(D3DGraphics::RIGHT))                       //边界检测
		player1pointx += 1;
		Player1State = D3DGraphics::RIGHT;
		
	}
		else if (kbd.LeftIsPressed()&&!kbd.UpIsPressed()&&!kbd.DownIsPressed())
		{
			

			if(player1pointx>0&& checkblank(D3DGraphics::LEFT))
			player1pointx -= 1;
			Player1State = D3DGraphics::LEFT;
		}
		else if (kbd.UpIsPressed())
		{
			
		   if(player1pointy>0&&checkblank(D3DGraphics::UP))
			player1pointy -= 1;

			Player1State = D3DGraphics::UP;
		
			
		}
		else if (kbd.DownIsPressed())
		{
			
			if (player1pointy<BASEHEIGHT&&checkblank(D3DGraphics::DOWN))
			player1pointy += 1;
			Player1State = D3DGraphics::DOWN;
	

		}
		else if (kbd.SpaceIsPressed()&&(Game::bulletlock==true))
		{
			    this->stateflag = 2;

				Game::bulletlock = false;
				Bullet *temp = getBuletState();
				PlayerBullet.push_back(temp);
				/*KillTimer(0,3);*/
   				BulletTimer=SetTimer(0, 3, 1000, bulletinterval);

		}
	
}
void Game::bulletinterval(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	Game::stateflag = 0;
	Game::bulletlock = true;
	KillTimer(NULL, BulletTimer);
}
void Game:: DrawBullet()
{
	for(vector<Bullet*> ::iterator iter = PlayerBullet.begin();iter!=PlayerBullet.end();)
	{
		
	 	if((*iter)->pointx >=830||(*iter)->pointy>=530||(*iter)->pointx<4||(*iter)->pointy<4||checkplayershot(iter))   //子弹的边界检测
		{ 
			delete *iter;
			iter = PlayerBullet.erase(iter);   //把这颗子弹删除掉
		}

		else
		{
		
			switch ((*iter)->dec)
			{
			case  D3DGraphics::DOWN:
				BulletSurface[1].TransparentBlt(hdc, (*iter)->pointx, (*iter)->pointy, 29, 55,RGB(255, 255, 255));
				(*iter)->pointy += 3;
				break;

			case  D3DGraphics::UP:
				BulletSurface[0].TransparentBlt(hdc, (*iter)->pointx, (*iter)->pointy, 29, 55, RGB(255, 255, 255));
				(*iter)->pointy -= 3;
				break;

			case  D3DGraphics::LEFT:
				BulletSurface[2].TransparentBlt(hdc, (*iter)->pointx, (*iter)->pointy, 55,29, RGB(255, 255, 255));
				(*iter)->pointx -= 3;
				break;

			case  D3DGraphics::RIGHT:
				BulletSurface[3].TransparentBlt(hdc, (*iter)->pointx, (*iter)->pointy, 55, 29, RGB(255, 255, 255));
				(*iter)->pointx +=3;
				break;

			}
			++iter;
		}

	}
}

pair <int, int > Game::getgunpoint()
{
	switch (Player1State)
	{
	case  D3DGraphics::DOWN:
		return make_pair(player1pointx + 15, player1pointy + 70);
		break;

	case  D3DGraphics::UP:
		return make_pair(player1pointx + 15, player1pointy-50);
		break;

	case  D3DGraphics::LEFT:
		return make_pair(player1pointx-50, player1pointy + 15);
		break;

	case  D3DGraphics::RIGHT:
		return make_pair(player1pointx + 70, player1pointy + 15);
		break;

	}
	return make_pair(0, 0);
}

void CALLBACK AiMoveInterval(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	TheCurrentObject->AitankMove();  //移动方向的计时器
}
void CALLBACK AiTankRevive(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	TheCurrentObject->AiRevive(Dieid);
	KillTimer(NULL, AiReviveTimer);
}
void Game::Paint()  //绘制AI坦克图像
{
	BitBlt(hdc, 0, 0, 941, 600, bufdc, 0, 0, SRCCOPY);  //背景
	for (int i = 0; i < 3; i++)
		AiSurface[TheAiTank[i]->CurrentDirect].TransparentBlt(hdc, TheAiTank[i]->getpointx(), TheAiTank[i]->getpointy(), 32, 32, RGB(255, 255, 255));
	TankSurface[Realflag()].TransparentBlt(hdc, player1pointx, player1pointy, 70, 70, RGB(255, 255, 255));
	DrawBullet();
}
bool Game::checkplayershot(vector<Bullet*>::iterator &temp)
{
	switch ((*temp)->dec)
	{
	case 0:   //up
		for (int i = 0; i < 3; i++)
			if (TheAiTank[i]->getpointy() < (*temp)->pointy&&abs(TheAiTank[i]->getpointx() - (*temp)->pointx) < aitobullet && (*temp)->pointy - TheAiTank[i]->getpointy() < aitankr)  //碰撞
			{
				Dieid = i;
				AiReviveTimer = SetTimer(0, 10 + i, 100, AiTankRevive);
				return true;
			}																					   //坦克在子弹上方  
		break;
	case 1:   //down
		for (int i = 0; i < 3; i++)
			if (TheAiTank[i]->getpointy() > (*temp)->pointy&&abs(TheAiTank[i]->getpointx() - (*temp)->pointx) < aitobullet && (*temp)->pointy - TheAiTank[i]->getpointy() > -aitankr)  //碰撞
			{
				return true;
			}
		break;
	case 2:
		for (int i = 0; i < 3; i++)
			if (TheAiTank[i]->getpointx() < (*temp)->pointx&&abs(TheAiTank[i]->getpointy() - (*temp)->pointy) < aitobullet && (*temp)->pointx - TheAiTank[i]->getpointx() < aitankr)  //碰撞
			{
				return true;
			}
		break;
	case 3:
		for (int i = 0; i < 3; i++)
			if (TheAiTank[i]->getpointx() > (*temp)->pointx&&abs(TheAiTank[i]->getpointy() - (*temp)->pointy) < aitobullet && (*temp)->pointx - TheAiTank[i]->getpointx() > -aitankr)  //碰撞
			{
				return true;
			}
		break;
	}
	return false;
}
void Game::load(Game &temp, HWND &hWnd)
{
	hdc = GetDC(hWnd);
	bufdc = CreateCompatibleDC(hdc);

	this->TankSurface[0].Load("bmpSource//up1.png");
	this->TankSurface[1].Load("bmpSource//up2.png");
	this->TankSurface[2].Load("bmpSource//uppre.png");
	this->TankSurface[3].Load("bmpSource//upshut.png");
	
	this->TankSurface[4].Load("bmpSource//down1.png");
	this->TankSurface[5].Load("bmpSource//down2.png");
	this->TankSurface[6].Load("bmpSource//downpre.png");
	this->TankSurface[7].Load("bmpSource//downshut.png");

	this->TankSurface[8].Load("bmpSource//left1.png");
	this->TankSurface[9].Load("bmpSource//left2.png");
	this->TankSurface[10].Load("bmpSource//leftpre.png");
	this->TankSurface[11].Load("bmpSource//leftshut.png");

	this->TankSurface[12].Load("bmpSource//right1.png");
	this->TankSurface[13].Load("bmpSource//right2.png");
	this->TankSurface[14].Load("bmpSource//rightpre.png");
	this->TankSurface[15].Load("bmpSource//rightshut.png");

	this->BulletSurface[0].Load("bmpSource//bullet1.png");
	this->BulletSurface[1].Load("bmpSource//bullet2.png");
	this->BulletSurface[2].Load("bmpSource//bullet3.png");
	this->BulletSurface[3].Load("bmpSource//bullet4.png");

	this->AiSurface[0].Load("bmpSource//ai1.png");
    this->AiSurface[1].Load("bmpSource//ai2.png");
	this->AiSurface[2].Load("bmpSource//ai3.png");
	this->AiSurface[3].Load("bmpSource//ai4.png");

	this->bgbmp = (HBITMAP)LoadImage(NULL, "C://Users//inkycherry//Desktop//directxpratice//C++fortank2//bmpSource//bg.bmp", IMAGE_BITMAP, 961, 600, LR_LOADFROMFILE);
	
	AiMoveTimer = SetTimer(0, 3, 3000, AiMoveInterval);
	TheCurrentObject = &temp;
	//imagetest.Load("C://Users//inkycherry//Desktop//directxpratice//C++fortank2//bmpSource//bullet1.png");
	SelectObject(bufdc, this->bgbmp);
	
	 
}

bool Game::Moveflag()  //通过刷新次数记录坦克的待机
{
	if (moveflag < 50)
	{     moveflag++;
		if (moveflag < 25)
			return 0;
		else return 1;
	}
	else 
	{ moveflag = 0;}
	return 0;
}
bool Game::checkblank(D3DGraphics::DirectionState dec_)
{

	switch (dec_)
	{
	case D3DGraphics::UP:
		for (int i = 0; i < 3; i++)
		{
			if (abs(getpointx() - TheAiTank[i]->getpointx() + divdistance) < 51 && (getpointy() > TheAiTank[i]->getpointy()) && getpointy() - TheAiTank[i]->getpointy() + divdistance <= adddistance)
			{
				
					return false;
			}
		}
		break;
	case D3DGraphics::DOWN:
		for (int i = 0; i < 3; i++)
		{
			if (abs(getpointx() - TheAiTank[i]->getpointx() + divdistance) < 51 && (getpointy() <TheAiTank[i]->getpointy()) && getpointy() - TheAiTank[i]->getpointy() + divdistance >=-adddistance)
			{   
				
				return false;
			}
		}
		break;
	case D3DGraphics::LEFT:
		for (int i = 0; i < 3; i++)
		{
			if (abs(getpointy() - TheAiTank[i]->getpointy() + divdistance) < 51 && (getpointx() > TheAiTank[i]->getpointx()) && getpointx() - TheAiTank[i]->getpointx() + divdistance <= adddistance)
			{   
				
				return false;
			}
		}
		break;
	case  D3DGraphics::RIGHT:
		for (int i = 0; i < 3; i++)
		{
			if (abs(getpointy() - TheAiTank[i]->getpointy() + divdistance) < 51 && (getpointx() < TheAiTank[i]->getpointx()) && getpointx() - TheAiTank[i]->getpointx() + divdistance >= -adddistance)
			{
			
				return false;
			}
		}
		break;
	}

			return true;
}


//void Game::Collisiondetection()
//{
//}


