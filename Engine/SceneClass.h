#pragma once


///////////////////////////////////
///////////////////////////////////
//
//		NIE2211 : CourseWork 1
//	"Beautiful Magical Ferris Wheel"
//
//		 by Alistair Haslam
//
///////////////////////////////////
///////////////////////////////////

#include "modelclass.h"
#include "modelsParent.h"
#include "bumpmodelclass.h"
#include "translatematrix.h"
#include "d3dclass.h"

class SceneClass
{

public:
	SceneClass();
	bool Initialize(D3DClass*, HWND);
	~SceneClass();

	void Shutdown();
	void Transform(XMMATRIX*, ModelsParent*);
	bool RenderScene(ID3D11DeviceContext*);


	ModelClass * model1, *model2, *model3;
	ModelsParent *m_models[13];
	BumpModelClass *bModel1, *bModel2, *bModel3;
	//D3DClass* m_D3D;
	
};

