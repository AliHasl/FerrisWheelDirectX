////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_Input = 0;
	m_D3D = 0;
	m_Timer = 0;
	m_ShaderManager = 0;
	m_Light = 0;
	m_Position = 0;
	m_Camera = 0;
	m_Scene = 0;
	rideMode = false;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;

	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if(!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation of the viewer.
	m_Position->SetPosition(0.0f, 0.0f, -10.0f);
	m_Position->SetRotation(0.0f, 0.0f, 0.0f);

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	//m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, -0.75f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(64.0f);

	m_Scene = new SceneClass;

	m_Scene->Initialize(m_D3D, hwnd);


	return true;
}


void GraphicsClass::Shutdown()
{

	// Release the model objects.
	m_Scene->Shutdown();
	
	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the shader manager object.
	if(m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the input object.
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;

	// Update the system stats.
	m_Timer->Frame();

	// Read the user input.
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Do the frame input processing.
	result = HandleMovementInput(m_Timer->GetTime());
		if (!result)
		{
			return false;
		}

	// Render the graphics.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::HandleMovementInput(float frameTime)
{
	bool keyDown;
	float mouseX;
	float posX, posY, posZ, rotX, rotY, rotZ;

	if (keyDown = m_Input->IsF1Pressed()) {
		rideMode = true;
	}

	if (keyDown = m_Input->IsF2Pressed()) {
		rideMode = false;
	}

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	if (!rideMode) {

		// Handle the input.

		keyDown = m_Input->IsNum4Pressed();
		m_Position->TurnLeft(keyDown);

		keyDown = m_Input->IsNum6Pressed();
		m_Position->TurnRight(keyDown);

		keyDown = m_Input->IsLeftPressed();
		m_Position->StrafeLeft(keyDown);

		keyDown = m_Input->IsRightPressed();
		m_Position->StrafeRight(keyDown);

		keyDown = m_Input->IsUpPressed();
		m_Position->MoveForward(keyDown);

		keyDown = m_Input->IsDownPressed();
		m_Position->MoveBackward(keyDown);

		keyDown = m_Input->IsAPressed();
		m_Position->MoveUpward(keyDown);

		keyDown = m_Input->IsZPressed();
		m_Position->MoveDownward(keyDown);

		keyDown = m_Input->IsPgUpPressed();
		m_Position->LookUpward(keyDown);

		keyDown = m_Input->IsPgDownPressed();
		m_Position->LookDownward(keyDown);
	}
	// HandleMouse Rotations
	m_Position->MouseRotate(m_Input->GetMouseXDelta(), m_Input->GetMouseYDelta());

	if (!rideMode) {

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);
	}
	else
	{
		//Set Camera position fixed to the cart matrix
		m_Camera->SetPosition(cartMatrix(3,0), cartMatrix(3, 1), cartMatrix(3, 2));
		
		// Get the view point position/rotation.
		//m_Position->GetPosition(posX, posY, posZ);
		m_Position->GetRotation(rotX, rotY, rotZ);

		// Set the position of the camera.
		//m_Camera->SetPosition(0.0f, 0.0f, 0.0f);
		m_Camera->SetRotation(rotX, rotY, rotZ);
	}
	return true;
}

bool GraphicsClass::Render()
{
	static XMMATRIX worldMatrix, viewMatrix, projectionMatrix, bearPositionMatrix;
	float m_X, m_Y, m_Z;
	bool result;

	static float rotation = 0.0f;

	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.00005f * m_Timer->GetTime();

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	//Get the coordinates for the player position
	m_Position->GetPosition(m_X, m_Y,m_Z);
	//Render the Skybox
	m_D3D->GetWorldMatrix(worldMatrix);
	//Turn off Culling
	m_D3D->TurnOffCulling();
	//Turn off Z buffer
	m_D3D->TurnZBufferOff();
	
	worldMatrix = XMMatrixMultiply(XMMatrixTranslation(m_X, m_Y, m_Z), worldMatrix);
	worldMatrix = XMMatrixMultiply(XMMatrixScaling(-10.0f, 10.0f, 10.0f), worldMatrix);
	
	// Render the Skyboxs using the texture shader.
	m_Scene->m_models[0]->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Scene->m_models[0], m_D3D->GetDeviceContext(), 
												  worldMatrix, viewMatrix, projectionMatrix);

	if (!result)
	{
		return false;
	}
	//Turn On Culling
	m_D3D->TurnOnCulling();
	//Turn On Z Buffer
	m_D3D->TurnZBufferOn();

	//Rendering the ground
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, -24.0f, 120.0f));
	worldMatrix = XMMatrixMultiply(XMMatrixScaling(2.0f, 2.0f, 2.0f), worldMatrix);

	m_Scene->m_models[1]->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Scene->m_models[1], m_D3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the ferrisWheelBase model.
	m_D3D->GetWorldMatrix(worldMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.3f, 0.3f, 0.3f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(-(float)XM_PIDIV2));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 140.0f, 200.0f));

	//Set the ferrisPositionMatrix to be used for other components later
	ferrisPositionMatrix = worldMatrix;

	// Render the second model using the light shader.
	m_Scene->m_models[2]->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_Scene->m_models[2], m_D3D->GetDeviceContext(), 
												worldMatrix, viewMatrix, projectionMatrix, m_Light->GetDirection(), 
												m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), 
												m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the ferrisWheel Wheel model.
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationX(rotation));
	worldMatrix = XMMatrixMultiply(worldMatrix, ferrisPositionMatrix);
	
	// Render the third model using the light shader.
	m_Scene->m_models[3]->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_Scene->m_models[3], m_D3D->GetDeviceContext(), worldMatrix, viewMatrix, 
												projectionMatrix, m_Light->GetDirection(), m_Light->GetAmbientColor(), 
												m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), 
												m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}
	
	//set cart matrix here test
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(cos(rotation)* 110.5f, sin(rotation)* 110.5f, 0.0f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, -10.0f, 0.0f));
	cartMatrix = worldMatrix;


	//Render instances of carts
	float t = 0;
	int nSegment = 32;
	float dt = ((2 * (float)XM_PI) / nSegment);

	//Repeat for 32 times in a circle
	while (t < (2 * (float)XM_PI)) {
		// Setup the rotation and translation of the first cart model.
		m_D3D->GetWorldMatrix(worldMatrix);

		worldMatrix = XMMatrixMultiply(ferrisPositionMatrix, worldMatrix);		
		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(cosf(rotation + t)* 110.5f, 
																		sinf(rotation + t)* 110.5f, 0.0f));
		worldMatrix = XMMatrixMultiply(XMMatrixRotationY((float)XM_PI), worldMatrix);

		// Render the first cart model using the light shader.
		m_Scene->m_models[4]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_Scene->m_models[4], m_D3D->GetDeviceContext(), worldMatrix, 
													viewMatrix, projectionMatrix, m_Light->GetDirection(), 
													m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
													m_Camera->GetPosition(), m_Light->GetSpecularColor(), 
													m_Light->GetSpecularPower());
		if (!result)
		{
			return false;
		}

		// Setup the rotation and translation of the second cart model.
		m_D3D->GetWorldMatrix(worldMatrix);

		worldMatrix = XMMatrixMultiply(ferrisPositionMatrix, worldMatrix);		
		worldMatrix = XMMatrixMultiply(ferrisPositionMatrix, XMMatrixTranslation(cosf(rotation + (t + dt))* 110.5f, sinf(rotation + (t + dt))* 110.5f, 0.0f));
		worldMatrix = XMMatrixMultiply(XMMatrixRotationY((float)XM_PI), worldMatrix);

		// Render the second cart model using the light shader.
		m_Scene->m_models[5]->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_Scene->m_models[5], m_D3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix,
													m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
													m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

		if (!result)
		{
			return false;
		}

		//Iterate t for next cycle
		t += 2*dt;
	
	}

	//Do the Bear
	m_D3D->GetWorldMatrix(worldMatrix);
	
	worldMatrix = XMMatrixRotationX((float)XM_PIDIV2);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.03f, 0.03f, 0.03f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, -2.0f, 20.0f));

	//Set the bearPositionMatrix
	bearPositionMatrix = worldMatrix;

	//Render the bear
	m_Scene->m_models[8]->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Scene->m_models[8], m_D3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	//Render the Hat
	m_Scene->m_models[10]->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Scene->m_models[10], m_D3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	//Position the Ball
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixRotationX(rotation);
	worldMatrix = XMMatrixMultiply(worldMatrix, bearPositionMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 1.0f, 0.0f));

	//Render the Ball
	m_Scene->m_models[9]->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_Scene->m_models[9], m_D3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}
	
	// Setup the rotation and translation of the Balloon model.
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixRotationY(rotation / 3.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.03f, 0.03f, 0.03f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(-50.0f, 200.0f, 400.0f));

	// Render the Balloon model using the bump map shader.
	m_Scene->m_models[11]->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderBumpMapShader(m_Scene->m_models[11], m_D3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, 
												  m_Light->GetDirection(), m_Light->GetDiffuseColor());
	if(!result)
	{
		return false;
	}
	
	// Render the Basket model using the bump map shader.
	m_Scene->m_models[12]->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderBumpMapShader(m_Scene->m_models[12], m_D3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix,
												  m_Light->GetDirection(), m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	// Render the Fastener model using the bump map shader.
	m_Scene->m_models[13]->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderBumpMapShader(m_Scene->m_models[13], m_D3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix,
												  m_Light->GetDirection(), m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}
	
	// Present the rendered scene to the screen.
	m_D3D->EndScene();


	return true;
}