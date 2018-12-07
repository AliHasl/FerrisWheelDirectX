#include "SceneClass.h"



SceneClass::SceneClass()
{
	// Create the model object.
	
	m_models[0] = new ModelClass(TranslateMatrix(-3.5f, 0.0f, 0.0f), TranslateMatrix(-1.0f, 1.0f, 1.0f), 0.0f);
	m_models[1] = new ModelClass;		//Ground
	m_models[2] = new ModelClass;		//FerrisWheelBase
	m_models[3] = new ModelClass;		//FerrisWheelWheel
	m_models[4] = new ModelClass;		//Cart1
	m_models[5] = new ModelClass;		//Cart2
	m_models[6] = new ModelClass;		//Cart3
	m_models[7] = new ModelClass;		//Cart4
	m_models[8] = new ModelClass;		//Bear
	m_models[9] = new ModelClass;		//Ball
	m_models[10] = new ModelClass;		//Hat
	m_models[11] = new BumpModelClass;	//Balloon
	m_models[12] = new BumpModelClass;	//Basket
	m_models[13] = new BumpModelClass;	//Fastener
}

bool SceneClass::Initialize(D3DClass* m_D3D, HWND hwnd) {

	bool result = true;

	
	// Initialize the model object.
	result = m_models[0]->Initialize(m_D3D->GetDevice(), "../Engine/data/SkyBoxMesh.txt", L"../Engine/data/SkyBoxTexture.dds");
	if (!result)
	{
	MessageBox(hwnd, L"Could not initialize the skybox model object.", L"Error", MB_OK);
	return false;
	}
	
	// Initialize the model object.
	result = m_models[1]->Initialize(m_D3D->GetDevice(), "../Engine/data/LandCylinder.txt", L"../Engine/data/grassTexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the ground model object.", L"Error", MB_OK);
		return false;
	}
	
	// Initialize the second object
	result = m_models[2]->Initialize(m_D3D->GetDevice(), "../Engine/data/FerrisWheel1_Base_Only.txt", L"../Engine/data/metal.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the ferrisWheelBase model object.", L"Error", MB_OK);
		return false;
	}

	//Initialize the third object
	result = m_models[3]->Initialize(m_D3D->GetDevice(), "../Engine/data/FerrisWheel1_Wheel_Only.txt", L"../Engine/data/metal.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the ferrisWheelWheel model object.", L"Error", MB_OK);
		return false;
	}

	//Initialize the fourth object
	result = m_models[4]->Initialize(m_D3D->GetDevice(), "../Engine/data/FerrisWheel1_Cart_Only.txt", L"../Engine/data/AllRed.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the FerrisWheelCart1 model object.", L"Error", MB_OK);
		return false;
	}

	//Initialize the fith object
	result = m_models[5]->Initialize(m_D3D->GetDevice(), "../Engine/data/FerrisWheel1_Cart_Only.txt", L"../Engine/data/AllYellow.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the FerrisWheelCart2 model object.", L"Error", MB_OK);
		return false;
	}

	//Initialize the sixth object
	result = m_models[6]->Initialize(m_D3D->GetDevice(), "../Engine/data/FerrisWheel1_Cart_Only.txt", L"../Engine/data/normal.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the FerrisWheelCart3 model object.", L"Error", MB_OK);
		return false;
	}

	//Initialize the seventh object
	result = m_models[7]->Initialize(m_D3D->GetDevice(), "../Engine/data/FerrisWheel1_Cart_Only.txt", L"../Engine/data/normal.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the FerrisWheelCart4 model object.", L"Error", MB_OK);
		return false;
	}

	//Initialize the eighth object
	result = m_models[8]->Initialize(m_D3D->GetDevice(), "../Engine/data/bear_Only.txt", L"../Engine/data/bear.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bear model object.", L"Error", MB_OK);
		return false;
	}

	//Initialize the ninth object
	result = m_models[9]->Initialize(m_D3D->GetDevice(), "../Engine/data/bearBall_Only.txt", L"../Engine/data/ball.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bearBall model object.", L"Error", MB_OK);
		return false;
	}
	//Initialize the tenth object
	result = m_models[10]->Initialize(m_D3D->GetDevice(), "../Engine/data/bearHat_Only.txt", L"../Engine/data/hat.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bearHat model object.", L"Error", MB_OK);
		return false;
	}
	// initialize the eleventh object
	result = m_models[11]->Initialize(m_D3D->GetDevice(), "../Engine/data/hotAirBalloon_Balloon.txt", L"../Engine/data/hotAirBalloon_Balloon.dds", L"../Engine/data/hotAirBalloon_Balloon_Normal.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the hotAirBalloon_Balloon model object.", L"Error", MB_OK);
		return false;
	}

	// initialize the twelth object
	result = m_models[12]->Initialize(m_D3D->GetDevice(), "../Engine/data/hotAirBalloon_Basket.txt", L"../Engine/data/hotAirBalloon_Basket.dds", L"../Engine/data/hotAirBalloon_Basket_Normal.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the hotAirBalloon_Basket model object.", L"Error", MB_OK);
		return false;
	}

	// initialize the thirteenth object
	result = m_models[13]->Initialize(m_D3D->GetDevice(), "../Engine/data/hotAirBalloon_Fastener.txt", L"../Engine/data/hotAirBalloon_Fastener.dds", L"../Engine/data/hotAirBalloon_Fastener_Normal.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the hotAirBalloon_Fastener model object.", L"Error", MB_OK);
		return false;
	}
	
	return result;
}


void SceneClass::Transform(XMMATRIX* input, ModelsParent* model) {
	
	static XMMATRIX tempMatrix;
	//*input = XMMatrixRotationZ(rotation * 3.0f);
	//translateMatrix = XMMatrixTranslation(-3.5f, 0.0f, 0.0f);
	
	//*input = XMMatrixMultiply(*input, model->GetScale());
	
}

SceneClass::~SceneClass()
{
}

void SceneClass::Shutdown() {
	// Release the model objects.

	int i;
	for (i = 0; i < 5; i++) {
		m_models[i]->Shutdown();
		delete m_models[i];
		m_models[i] = NULL;
	}

	//delete m_models;
}

bool SceneClass::RenderScene(ID3D11DeviceContext* deviceContext) {
	/*
	bool result;
		m_models[0]->RenderBuffers(deviceContext);

		result = m_ShaderManager->RenderLightShader(m_Scene->m_models[1], m_D3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix,
			m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result)
		{
			return false;
		}
		*/

		m_models[1]->RenderBuffers(deviceContext);
		m_models[3]->RenderBuffers(deviceContext);


	return true;
}
