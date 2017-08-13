/****************************************************************************************** 
 *	D3DGraphics.cpp																		  *
	Copyright 2015 –Èª√¥Û—ß <http://www.oxox.work>
 ******************************************************************************************/
#include "D3DGraphics.h"
#include "Game.h"
D3DGraphics::D3DGraphics( HWND hWnd )
{
	pDirect3D = Direct3DCreate9( D3D_SDK_VERSION );

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp,sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

    pDirect3D->CreateDevice( D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE,&d3dpp,&pDevice );
}

D3DGraphics::~D3DGraphics()
{
	if( pDevice )
	{
		pDevice->Release();
		pDevice = NULL;
	}
	if( pDirect3D )
	{
		pDirect3D->Release();
		pDirect3D = NULL;
	}
}



void D3DGraphics::PutPixel( int x,int y,int r,int g,int b )
{

	IDirect3DSurface9* pBackBuffer = NULL;
	D3DLOCKED_RECT rect;

	pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	pBackBuffer->LockRect(&rect, NULL, NULL);
	((D3DCOLOR*)rect.pBits)[x + (rect.Pitch >> 2) * y] = D3DCOLOR_XRGB(r, g, b);
	pBackBuffer->UnlockRect();
	pBackBuffer->Release();
}



void D3DGraphics::BeginFrame()
{
	pDevice->Clear( 0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,0),0.0f,0 );
}

void D3DGraphics::EndFrame()
{
	pDevice->Present( NULL,NULL,NULL,NULL );
}
void D3DGraphics::DrawSurface(int xoff, int yoff, int width, int height, const D3DCOLOR *xsurf, DirectionState dec)
{
	int AllPixel = (width)*(height);
	if (dec == UP)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				PutPixel(x + xoff,  yoff+y, xsurf[x + y*width]);
			}
		}
	}
	if (dec == DOWN)
	{
		for (int y = height-1 ; y >=0; y--)
		{
			for (int x = width-1; x>=0; x--)
			{
				PutPixel(x + xoff, yoff+y, xsurf[AllPixel-y*width-x]);
			}
		}
	}
	if (dec == LEFT)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				PutPixel(y + xoff, yoff + x, xsurf[x + y*width]);
			}
		}
	}
	if (dec == RIGHT)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				PutPixel(y + xoff, yoff + x, xsurf[AllPixel - y*width - x]);
			}
		}
		
	}
}