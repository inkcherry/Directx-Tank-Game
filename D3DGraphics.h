
#pragma once
#include <d3d9.h>
#define BASEWIDTH 930
#define BASEHEIGHT 530
class D3DGraphics
{
private:
	IDirect3D9*			pDirect3D;     //D3D����
	IDirect3DDevice9*	pDevice;      //��ȡ�豸�����ܣ�Ӳ���豸����  ���캯����ͨ��versionָ������汾 
	
	
public:
	enum DirectionState
	{
		UP,             //0
		DOWN,             //1
		LEFT,           //2
		RIGHT,         //3
	};
	D3DGraphics( HWND hWnd );
	~D3DGraphics();
	void PutPixel(int x, int y, int r, int g, int b);
	void BeginFrame();
	void EndFrame();
	void D3DGraphics::DrawSurface(int xoff, int yoff,int height	,int width ,const D3DCOLOR *xsurf, DirectionState dec);
	void D3DGraphics::DrawTank(int xoff, int yoff, const D3DCOLOR *xsurf, DirectionState dec);

	void PutPixel(int x, int y, D3DCOLOR c)    //����PutPixel
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