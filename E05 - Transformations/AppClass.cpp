#include "AppClass.h"
void Application::InitVariables(void)
{
	//init the mesh
	m_pMesh = new MyMesh();
	m_pMesh->GenerateCube(1.0f, C_WHITE);

	for (int i = 0; i < 46; i++) 
	{
		m_pMesh->GenerateCube(1.0f, C_WHITE);
		cubesVector.push_back(m_pMesh);
	}

	//m_pMesh->GenerateSphere(1.0f, 5, C_WHITE);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	
	matrix4 m4Scale = glm::scale(IDENTITY_M4, vector3(2.0f,2.0f,2.0f));			//same for all cubes
	
	/////////////////////////////////////////
	//handling translations + rendering
	static float value = 0.0f;
	
	matrix4 m4Translate = glm::translate(IDENTITY_M4, vector3(value, 2.0f, 3.0f));
	
	//handles left and right motion
	static float turn = .1f;
	value += turn;
	if (value >= 10.0f || value <= -10.0f)
		turn *= -1;

	

	//matrix4 m4Model = m4Translate * m4Scale;
	matrix4 m4Model = m4Scale * m4Translate;

	m_pMesh->Render(m4Projection, m4View, m4Model);
	/////////////////////////////////////////

	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	for (int i = 0; i < 46; i++) 
	{
		SafeDelete(cubesVector[i]);
	}

	//SafeDelete(m_pMesh);

	//release GUI
	ShutdownGUI();
}