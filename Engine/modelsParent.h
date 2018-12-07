#pragma once
#include <d3d11_1.h>
//#include "modelclass.h"
//#include "bumpmodelclass.h"
//#include "shadermanagerclass.h"

class ModelsParent
{
public:
	ModelsParent();
	~ModelsParent();
	virtual void Shutdown() = 0;
	virtual bool Initialize(ID3D11Device*, char*, WCHAR*) = 0;
	virtual bool Initialize(ID3D11Device*, char*, WCHAR*, WCHAR*) = 0;
	virtual void Render(ID3D11DeviceContext *) = 0;
	virtual int GetIndexCount() = 0;
	virtual ID3D11ShaderResourceView* GetTexture() = 0;
	virtual void ReleaseTexture() = 0;
	//virtual XMMATRIX GetScale() = 0;
	virtual ID3D11ShaderResourceView* GetColorTexture() = 0;
	virtual ID3D11ShaderResourceView* GetNormalMapTexture() = 0;
	//virtual void ReleaseTextures() = 0;
	//virtual void ShutdownBuffers() = 0;
	//virtual void ReleaseModel() = 0;
	virtual void RenderBuffers(ID3D11DeviceContext*) = 0;
	
};
