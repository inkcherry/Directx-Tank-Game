/****************************************************************************************** 
 *	D3DGraphics.h																		  *
 *	Copyright 2015 –Èª√¥Û—ß <http://www.oxox.work>								  *
 ******************************************************************************************/
#pragma once
#include <d3d9.h>
class D3DGraphics
{
private:
	IDirect3D9*			pDirect3D;
	IDirect3DDevice9*	pDevice;
	
	
public:
	enum DirectionState
	{
		UP,
		DOWN,
		RIGHT,
		LEFT
	};
	D3DGraphics( HWND hWnd );
	~D3DGraphics();
	void PutPixel(int x, int y, int r, int g, int b);

	
	void BeginFrame();
	void EndFrame();
	void D3DGraphics::DrawSurface(int xoff, int yoff, int width, int height, const D3DCOLOR *xsurf, DirectionState dec);
	void PutPixel(int x, int y, D3DCOLOR c)    //÷ÿ‘ÿPutPixel
	{

		IDirect3DSurface9* pBackBuffer = NULL;
		D3DLOCKED_RECT rect;
		D3DGraphics::pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
		pBackBuffer->LockRect(&rect, NULL, NULL);
		((D3DCOLOR*)rect.pBits)[x + (rect.Pitch >> 2) * y] = c;
		pBackBuffer->UnlockRect();
		pBackBuffer->Release();
	}

};