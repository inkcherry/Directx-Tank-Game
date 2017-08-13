
#include "Game.h"
#include "bitmap.h"
#include   "D3DGraphics.h"
#include<thread>
Game::Game(HWND hWnd, const KeyboardServer& kServer)
	: gfx(hWnd),
	kbd(kServer),
	player1pointx(100),
	player1pointy(100),
	Player1State(D3DGraphics::UP){}

void Game::Go()
{

	LoadBmp(surface);
	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();
	Player1Move();

}

void Game::Player1Move()
{
	
	if (kbd.RightIsPressed() && !kbd.UpIsPressed() && !kbd.DownIsPressed())
	{
		
		if (Player1State != D3DGraphics::RIGHT)       //转向缓冲
			Sleep(20);
     if(player1pointx<BASEWIDTH)                       //边界检测
		player1pointx += 5;
		Player1State = D3DGraphics::RIGHT;
		Sleep(1);
		
	}
		if (kbd.LeftIsPressed()&&!kbd.UpIsPressed()&&!kbd.DownIsPressed())
		{
			
			if (Player1State != D3DGraphics::LEFT)
				Sleep(20);
			if(player1pointx>0)
			player1pointx -= 5;
			Player1State = D3DGraphics::LEFT;
			Sleep(1);
			
		}
		if (kbd.UpIsPressed())
		{
			
			if (Player1State != D3DGraphics::UP)
				Sleep(20);
		   if(player1pointy>0)
			player1pointy -= 5;
			Player1State = D3DGraphics::UP;
			Sleep(1);
			
		}
		if (kbd.DownIsPressed())
		{
			
			if (Player1State != D3DGraphics::DOWN)
				Sleep(20);
			if (player1pointy<BASEHEIGHT)
			player1pointy += 5;
			Player1State = D3DGraphics::DOWN;
			Sleep(1);
		

		//std::thread t1(&A::b(),this,参数表);

		}
		if (kbd.SpaceIsPressed())
		{
			Bullet *temp = getBuletState();
			PlayerBullet.push_back(temp);   //把子弹放进去
		}
	
}



void Game::ComposeFrame()
{
	// TODO: insert frame drawing code here
	/*gfx.PutPixel(100, 100, 255, 1, 255);*/
	gfx.DrawSurface(player1pointx, player1pointy, 55, 62, surface,Player1State);
	DrawBullet();
}
void Game:: DrawBullet()
{

	//for (auto iter : PlayerBullet)
	for(auto iter = PlayerBullet.begin();iter!=PlayerBullet.end();)
	{
		
	 	if((*iter)->pointx >=830||(*iter)->pointy>=530||(*iter)->pointx<4||(*iter)->pointy<4)   //子弹的边界检测
		{ 
			delete *iter;
			iter = PlayerBullet.erase(iter);   //把这颗子弹删除掉
		}

		else
		{
			Game::gfx.PutPixel((*iter)->pointx, (*iter)->pointy, 255, 1, 255);
			switch ((*iter)->dec)
			{
			case  D3DGraphics::DOWN:
				(*iter)->pointy += 4;
				break;

			case  D3DGraphics::UP:
				(*iter)->pointy -= 4;
				break;

			case  D3DGraphics::LEFT:
				(*iter)->pointx -= 4;
				break;

			case  D3DGraphics::RIGHT:
				(*iter)->pointx +=4;
				break;

			}
		
			iter++;
		}

	}
}

pair <int, int > Game::getgunpoint()
{
	switch (Player1State)
	{
	case  D3DGraphics::DOWN:
		return make_pair(player1pointx + 30, player1pointy + 60);
		break;

	case  D3DGraphics::UP:
		return make_pair(player1pointx + 30, player1pointy);
		break;

	case  D3DGraphics::LEFT:
		return make_pair(player1pointx, player1pointy + 30);
		break;

	case  D3DGraphics::RIGHT:
		return make_pair(player1pointx + 60, player1pointy + 30);
		break;

	}
}
void Game::test(int n)
{

}
