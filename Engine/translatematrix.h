#pragma once
#ifndef _TRANSLATEMATRIX_H_
#define _TRANSLATEMATRIX_H_


class TranslateMatrix
{
public:
	TranslateMatrix();
	TranslateMatrix(float, float, float);
	~TranslateMatrix();

	float x, y, z;
};

#endif
