////////////////////////////////////////////////////////////////////////////////
// Filename: shadermanagerclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "shadermanagerclass.h"


ShaderManagerClass::ShaderManagerClass()
{
	m_TextureShader = 0;
	m_LightShader = 0;
	m_BumpMapShader = 0;
}


ShaderManagerClass::ShaderManagerClass(const ShaderManagerClass& other)
{
}


ShaderManagerClass::~ShaderManagerClass()
{
}


bool ShaderManagerClass::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;


	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if(!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the bump map shader object.
	m_BumpMapShader = new BumpMapShaderClass;
	if(!m_BumpMapShader)
	{
		return false;
	}

	// Initialize the bump map shader object.
	result = m_BumpMapShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the bump map shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void ShaderManagerClass::Shutdown()
{
	// Release the bump map shader object.
	if(m_BumpMapShader)
	{
		m_BumpMapShader->Shutdown();
		delete m_BumpMapShader;
		m_BumpMapShader = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the texture shader object.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	return;
}


bool ShaderManagerClass::RenderTextureShader(ModelsParent* target, ID3D11DeviceContext* device, const XMMATRIX &worldMatrix, const XMMATRIX &viewMatrix, const XMMATRIX &projectionMatrix)
{
	bool result;


	// Render the model using the texture shader.
	result = m_TextureShader->Render(device, target->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, target->GetTexture());
	if(!result)
	{
		return false;
	}

	return true;
}


bool ShaderManagerClass::RenderLightShader(ModelsParent* target, ID3D11DeviceContext* deviceContext, const XMMATRIX &worldMatrix, const XMMATRIX &viewMatrix, const XMMATRIX &projectionMatrix, XMFLOAT3 lightDirection, XMFLOAT4 ambient, XMFLOAT4 diffuse,
	XMFLOAT3 cameraPosition, XMFLOAT4 specular, float specularPower)
{
	bool result;


	// Render the model using the light shader.
	result = m_LightShader->Render(deviceContext, target->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, target->GetTexture(), lightDirection, ambient, diffuse, cameraPosition, 
								   specular, specularPower);
	if(!result)
	{
		return false;
	}

	return true;
}


bool ShaderManagerClass::RenderBumpMapShader(ModelsParent* target, ID3D11DeviceContext* deviceContext, const XMMATRIX &worldMatrix, const XMMATRIX &viewMatrix, const XMMATRIX &projectionMatrix,
											XMFLOAT3 lightDirection, XMFLOAT4 diffuse)
{
	bool result;


	// Render the model using the bump map shader.
	result = m_BumpMapShader->Render(deviceContext, target->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, target->GetColorTexture(), target->GetNormalMapTexture(), lightDirection, diffuse);
	if(!result)
	{
		return false;
	}

	return true;
}