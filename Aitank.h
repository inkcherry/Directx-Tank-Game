#include "D3DGraphics.h"
#include <vector>
#include<stdlib.h>
#define Random(x) (rand() % 6) 
#define AIHEIGHT 7
#define AIWIDTH 7
#define distance 32
class Aitank
{
public:

	Aitank(int x, int y) { pointx = x; pointy = y; };
	int getpointx() { return pointx; }
	int getpointy() { return pointy; }
	D3DGraphics::DirectionState CurrentDirect = D3DGraphics::DOWN;
	/*pair<int, int> getpoint() { return make_pair(pointx, pointy); }*/
	bool BlankCheck(int AiId, Aitank *temp,const int &playerx, const int &playery,D3DGraphics::DirectionState dec_)
	{
		for (int i = 0; i < 3; i++)
		{
			if (i != AiId)    //对其他进行检测
			{
				switch (dec_)
				{
				case D3DGraphics::UP:    //0           0            0
					if (abs(this->getpointx()-temp[i].getpointx() ) < distance && this->getpointy() - temp[i].getpointy() < distance&&this->getpointy()>temp[i].getpointy())
						return false;
					if ((abs(this->getpointx() - playerx - 19) < 51) && (this->getpointy() - playery - 19) <=51&&this->getpointy()>playery)
						return false;
					break;
				case D3DGraphics::DOWN:   //1            0          1
					if (abs(temp[i].getpointx() - this->getpointx()) < distance && this->getpointy() - temp[i].getpointy() >-distance&&this->getpointy()<temp[i].getpointy())
						return false;
					if ((abs(this->getpointx() - playerx - 19) < 51) && (this->getpointy() - playery - 19) >=-51 && this->getpointy()<playery)
						return false;
					break;
				case D3DGraphics::LEFT:   //2           1         0
					if (this->getpointx()-temp[i].getpointx() <distance &&this->getpointx()>temp[i].getpointx()&& abs(this->getpointy() - temp[i].getpointy()) < distance)
						return false;
					if ((this->getpointx() - playerx - 19) <= 51 &&this->getpointx()>playerx&& (abs(this->getpointy() - playery - 19) < 51))
						return false;
					break;
				case D3DGraphics::RIGHT:  //3         1        1
					if (this->getpointx() -temp[i].getpointx()  >- distance &&this->getpointx()<temp[i].getpointx()&& abs(this->getpointy() - temp[i].getpointy())< distance)
						return false;
					if ((this->getpointx() - playerx - 19) >=- 51 && this->getpointx()<playerx && (abs(this->getpointy() - playery - 19) < 51))
						return false;
					break;
				
				}
			}
		}
		//int x1 = this->getpointx() + 16, y1 = this->getpointy() + 16;
		////int x2 = playerx + 35, y2 = playery + 35; 
	/*	if ((abs(this->getpointx() - playerx - 19) < 51) && (abs(this->getpointy() - playery - 19) < 51))
			return false;*/
		return true;
	}
	void move(int AiId,Aitank *temp,int playerx,int playery)     
	{
		switch (CurrentDirect)
		{
		case D3DGraphics::RIGHT:
          if(pointx<BASEWIDTH&& BlankCheck(AiId, temp, playerx, playery, D3DGraphics::RIGHT))
			pointx++;
			break;
		case D3DGraphics::DOWN:
			if(pointy<BASEHEIGHT&&BlankCheck(AiId, temp, playerx, playery, D3DGraphics::DOWN))
		   pointy++;
			break;
		case D3DGraphics::LEFT:
			if(pointx>AIHEIGHT&& BlankCheck(AiId, temp, playerx, playery, D3DGraphics::LEFT))
			pointx--;
			break;
		case D3DGraphics::UP:
			if(pointy>AIHEIGHT&& BlankCheck(AiId, temp, playerx, playery, D3DGraphics::UP))
			pointy--;
			break;
		default:
			break;
		}
	}
	
	void ChangeDec(const int&x,const int &y)
	{
		switch (Random(x))
		{
		case 0:                                       //对于x方向上的追击位移
		case 1:
		
				if (pointx < x&&pointx < BASEWIDTH)
					CurrentDirect = D3DGraphics::RIGHT;
				else if (pointx > x&&pointx>AIWIDTH)
				{
					CurrentDirect=D3DGraphics::LEFT;
				}
			break;
		case 2:                                       //对于y方向上的追击位移	
		case 3:		
			if (pointy < y&&pointy < BASEWIDTH)
					CurrentDirect = D3DGraphics::DOWN;
				else if (pointy > y&&pointy>AIHEIGHT)
				{
					CurrentDirect = D3DGraphics::UP;
				}	
			break;
		case 5:                                       //对于x方向上的调整位移
			if (pointx < x&&pointx < BASEWIDTH)
				CurrentDirect = D3DGraphics::LEFT;
			else if (pointx > x&&pointx > AIWIDTH)
			{
				CurrentDirect = D3DGraphics::RIGHT;
			}
		case 6:                                       //对于y方向上的调整位移
			if (pointy < y&&pointy < BASEWIDTH)
				CurrentDirect = D3DGraphics::DOWN;
			else if (pointy > y&&pointy > AIHEIGHT)
			{
				CurrentDirect = D3DGraphics::UP;
			}
		}
	}
	//pair <int,int> getgunpoint()
	//{
	//	return make_pair(pointx + 16, pointy + 16);
	//}
	void setpoint(int tempx, int tempy) { pointx = tempx; pointy = tempy; }
private:
	//D3DGraphics::DirectionState dec_;   //坦克的方向
	int pointx, pointy;                //坦克的坐标
	int life;
	
};