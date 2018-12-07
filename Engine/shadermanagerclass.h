////////////////////////////////////////////////////////////////////////////////
// Filename: shadermanagerclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SHADERMANAGERCLASS_H_
#define _SHADERMANAGERCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "textureshaderclass.h"
#include "lightshaderclass.h"
#include "bumpmapshaderclass.h"
//#include "modelclass.h"
//#include "bumpmodelclass.h"
#include "modelsParent.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: ShaderManagerClass
////////////////////////////////////////////////////////////////////////////////
class ShaderManagerClass
{
public:
	ShaderManagerClass();
	ShaderManagerClass(const ShaderManagerClass&);
	~ShaderManagerClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();

	bool RenderTextureShader(ModelsParent*, ID3D11DeviceContext*, const XMMATRIX&, const XMMATRIX&, const XMMATRIX&);

	bool RenderLightShader(ModelsParent*, ID3D11DeviceContext*, const XMMATRIX&, const XMMATRIX&, const XMMATRIX&,
		XMFLOAT3, XMFLOAT4, XMFLOAT4, XMFLOAT3, XMFLOAT4, float);

	bool RenderBumpMapShader(ModelsParent*, ID3D11DeviceContext*, const XMMATRIX&, const XMMATRIX&, const XMMATRIX&, XMFLOAT3, XMFLOAT4);

private:
	TextureShaderClass* m_TextureShader;
	LightShaderClass* m_LightShader;
	BumpMapShaderClass* m_BumpMapShader;
};

#endif