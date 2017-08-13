#include"bitmap.h"
#include<stdio.h>
#include<assert.h>
#include<math.h>

void LoadBmp(D3DCOLOR *surface)  //d3d9.h头文件支持；
{
	FILE  *bmpFile = fopen("C://Users//inkycherry//Desktop//directxpratice//C++fortank//bmpSource//4.bmp", "rb");
	char signature[2];
	fread(&signature, sizeof(char), 2, bmpFile);
	
	BitmapFileHeader fileHeader;
	fread(&fileHeader, sizeof(fileHeader), 1, bmpFile);
	BitmapInfoHeader infoHeader;
	fread(&infoHeader, sizeof(infoHeader), 1, bmpFile);
	
	fseek(bmpFile, fileHeader.offset, SEEK_SET);
	infoHeader.width = abs(infoHeader.width);
	infoHeader.height = abs(infoHeader.height);
	int nPixels = infoHeader.width*infoHeader.height;  //图像的像素数
	/*int nBytesPerRow = infoHeader.width * 3;          
	int nPaddingByresPerRow = 4 - (nBytesPerRow % 4);*/
	for (int y = infoHeader.height-1; y >=0; y--)
	{
		for (int x = 0; x < infoHeader.width; x++)
		{
			Piexl32 pixel;
			fread(&pixel, sizeof(pixel), 1, bmpFile);
			//surface[x+y*infoHeader.width] = D3DCOLOR_XRGB(pixel.red, pixel.green, pixel.blue);
			surface[x+y*infoHeader.width] = D3DCOLOR_ARGB(pixel.alpha,pixel.red, pixel.green, pixel.blue);
		
		}
	/*	fseek(bmpFile, nPaddingByresPerRow, SEEK_CUR);*/
	}
	fclose(bmpFile);
}