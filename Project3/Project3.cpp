// Project3.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>

#include "./gdal/gdal_priv.h"

#pragma comment(lib,"gdal_i.lib")

using namespace std;
int main()

{

	//����ͼ��,̫��

	GDALDataset* poSrcSpaceDs;

	//����ͼ��,����

	GDALDataset* poSrcSuperDs;

	//���ͼ��

	GDALDataset* poDstDs;

	//��ʼλ�õ�����

	int startX = 0, startY = 0;

	//ͼ��Ŀ�Ⱥ͸߶�

	int imgXlen, imgYlen;

	//�ڴ� 

	GByte* buffTmp;

	//SUPER�ڴ�

	GByte* buffTmpSpaceR;

	GByte* buffTmpSpaceB;

	GByte* buffTmpSpaceG;

	//space�ڴ�

	GByte* buffTmpSuperR;

	GByte* buffTmpSuperG;

	GByte* buffTmpSuperB;

	//����ͼ��space��·��

	const char* srcSpacePath = "space.jpg";

	//����ͼ��superman��·��

	const char* srcSuperPath = "superman.jpg";

	//����

	const char* dstPath = "ok.tif";

	int i, j, bandNum;



	//ע������

	GDALAllRegister();



	//��ͼ��

	poSrcSpaceDs = (GDALDataset*)GDALOpenShared(srcSpacePath, GA_ReadOnly);

	poSrcSuperDs = (GDALDataset*)GDALOpenShared(srcSuperPath, GA_ReadOnly);



	/*

	�ȴ���һ��ֻ��superman��ͼ��

	*/



	//��ȡsuperͼ��Ŀ��,�߶ȺͲ�������

	imgXlen = poSrcSuperDs->GetRasterXSize();

	imgYlen = poSrcSuperDs->GetRasterYSize();

	bandNum = poSrcSuperDs->GetRasterCount();



	//�������ͼ��

	poDstDs = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(

		dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);



	//��ʼ�����ڴ�,���˵�

	buffTmpSuperR = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));

	buffTmpSuperG = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));

	buffTmpSuperB = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));



	//����space�ڴ�

	buffTmpSpaceR = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));

	buffTmpSpaceG = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));

	buffTmpSpaceB = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));



	//��ȡ������buffTmpSpace��

	poSrcSpaceDs->GetRasterBand(1)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen,

		buffTmpSpaceR, imgXlen, imgYlen, GDT_Byte, 0, 0);

	poSrcSpaceDs->GetRasterBand(2)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen,

		buffTmpSpaceG, imgXlen, imgYlen, GDT_Byte, 0, 0);

	poSrcSpaceDs->GetRasterBand(3)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen,

		buffTmpSpaceB, imgXlen, imgYlen, GDT_Byte, 0, 0);



	//��ȡ������buffTmpSuper

	poSrcSuperDs->GetRasterBand(1)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen,

		buffTmpSuperR, imgXlen, imgYlen, GDT_Byte, 0, 0);

	poSrcSuperDs->GetRasterBand(2)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen,

		buffTmpSuperG, imgXlen, imgYlen, GDT_Byte, 0, 0);

	poSrcSuperDs->GetRasterBand(3)->RasterIO(GF_Read, 0, 0, imgXlen, imgYlen,

		buffTmpSuperB, imgXlen, imgYlen, GDT_Byte, 0, 0);







	//����

	for (j = 0; j < imgYlen; j++)

	{

		for (i = 0; i < imgXlen; i++)

		{

			if (!(buffTmpSuperR[j*imgXlen + i] >(GByte)10 && buffTmpSuperR[j*imgXlen + i] < (GByte)160 && buffTmpSuperG[j*imgXlen + i]>(GByte)100 && buffTmpSuperG[j*imgXlen

				+ i] < (GByte)220 && buffTmpSuperB[j*imgXlen + i]>(GByte)10 && buffTmpSuperB[j*imgXlen + i] < (GByte)110))

			{

				buffTmpSpaceR[j*imgXlen + i] = buffTmpSuperR[j*imgXlen + i];

				buffTmpSpaceG[j*imgXlen + i] = buffTmpSuperG[j*imgXlen + i];

				buffTmpSpaceB[j*imgXlen + i] = buffTmpSuperB[j*imgXlen + i];

			}

		}

	}

	//��ʼ���

	poDstDs->GetRasterBand(1)->RasterIO(GF_Write,

		0, 0, imgXlen, imgYlen, buffTmpSpaceR, imgXlen, imgYlen, GDT_Byte, 0, 0);

	poDstDs->GetRasterBand(2)->RasterIO(GF_Write,

		0, 0, imgXlen, imgYlen, buffTmpSpaceG, imgXlen, imgYlen, GDT_Byte, 0, 0);

	poDstDs->GetRasterBand(3)->RasterIO(GF_Write,

		0, 0, imgXlen, imgYlen, buffTmpSpaceB, imgXlen, imgYlen, GDT_Byte, 0, 0);



	//����ڴ�

	CPLFree(buffTmpSpaceR);

	CPLFree(buffTmpSpaceG);

	CPLFree(buffTmpSpaceB);

	CPLFree(buffTmpSuperR);

	CPLFree(buffTmpSuperG);

	CPLFree(buffTmpSuperB);

	//�ر�datatset

	GDALClose(poDstDs);

	GDALClose(poSrcSpaceDs);

	GDALClose(poSrcSuperDs);



	system("pause");

	return 0;







	return 0;

}

