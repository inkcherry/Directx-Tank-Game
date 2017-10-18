#include"bitmap.h"
#include<stdio.h>
#include<assert.h>
#include<math.h>


void LoadBmp(D3DCOLOR **surfacee,std::string src)  //d3d9.h头文件支持；
{  
	FILE  *bmpFile = fopen(("C://Users//inkycherry//Desktop//directxpratice//C++fortank2//bmpSource//"+src).data(), "rb");
	
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
	*surfacee = new D3DCOLOR[nPixels];
	D3DCOLOR *surface = *surfacee;
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
	}
	fclose(bmpFile);
}
void LoadBmp4(D3DCOLOR **surfacee, std::string src)  //d3d9.h头文件支持；
{
	RGBQUAD ColorPla[256];
	FILE  *bmpFile = fopen(("C://Users//inkycherry//Desktop//directxpratice//C++fortank2//bmpSource//" + src).data(), "rb");

	char signature[2];
	fread(&signature, sizeof(char), 2, bmpFile);


	BitmapFileHeader fileHeader;
	fread(&fileHeader, sizeof(fileHeader), 1, bmpFile);
	BitmapInfoHeader infoHeader;
	fread(&infoHeader, sizeof(infoHeader), 1, bmpFile);
	for (unsigned int nCounti = 0; nCounti < infoHeader.ncolours; nCounti++)  //读取调色板
	{
		fread((char *)&(ColorPla[nCounti].rgbBlue), 1, sizeof(BYTE), bmpFile);
		fread((char *)&(ColorPla[nCounti].rgbGreen), 1, sizeof(BYTE), bmpFile);
		fread((char *)&(ColorPla[nCounti].rgbRed), 1, sizeof(BYTE), bmpFile);
		fread((char *)&(ColorPla[nCounti].rgbReserved), 1, sizeof(BYTE), bmpFile);
	}
	infoHeader.width = abs(infoHeader.width);
	infoHeader.height = abs(infoHeader.height);
	fclose(bmpFile);
}