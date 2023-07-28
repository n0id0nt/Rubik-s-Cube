#include "RubiksCube.h"

#include "glm\glm.hpp"

RubiksCube::RubiksCube(unsigned int layerCount, Camera* camera)
	: m_LayerCount(layerCount), m_Camera(camera), m_IsLerping(false), m_Dir(0), m_Transform(), m_MoveTransform(), m_ColorScheme {
	blue,		// Back		- Blue
	green,		// Front	- Green
	orange,		// Left		- Orange
	red,		// Right	- Red
	yellow,		// Bottom	- Yellow
	white,		// Top		- White
	black		// Inside	- Black
	}		
{
	m_MoveTransform.SetParent(&m_Transform);

	// Declare the cubelet array
	m_Cubelets = new Cubelet * * *[layerCount];
	for (int x = 0; x < layerCount; x++)
	{
		m_Cubelets[x] = new Cubelet * * [layerCount];
		for (int y = 0; y < layerCount; y++)
		{
			m_Cubelets[x][y] = new Cubelet * [layerCount];
			for (int z = 0; z < layerCount; z++)
			{
				// calculate color scheme of face
				glm::vec3* colorScheme[FACE_COUNT];
				for (int i = 0; i < FACE_COUNT; i++)
				{
					colorScheme[i] = &m_ColorScheme[i];
				}
				// calculate cubelet parameters
				m_Cubelets[x][y][z] = new Cubelet(colorScheme, glm::vec3(1 - x, 1 - y, 1 - z), &m_Transform);
			}
				
		}
	}

}

RubiksCube::~RubiksCube()
{
	// delete the cubelet array
	for (int x = 0; x < m_LayerCount; x++)
	{
		for (int y = 0; y < m_LayerCount; y++)
		{
			for (int z = 0; z < m_LayerCount; z++)
				delete[] m_Cubelets[x][y][z];
		}
	}
	for (int x = 0; x < m_LayerCount; x++)
	{
		for (int y = 0; y < m_LayerCount; y++)
		{
			delete[] m_Cubelets[x][y];
		}
	}
	for (int x = 0; x < m_LayerCount; x++)
	{
		delete[] m_Cubelets[x];
	}
	delete[] m_Cubelets;
}

void RubiksCube::Move(unsigned int layer, Axis axis, MoveDir moveDir)
{
	// set the rotate variables
	m_IsLerping = true;
	m_CurRot = 0;
	m_InitRot = 0;
	m_CurAxis = axis;
	m_Dir = 1;



	if (moveDir == MoveDir::Anticlockwise)
	{
		if (axis == Axis::X)
		{
			// Swap Corners
			Cubelet* temp;
			temp = m_Cubelets[layer][0][0];
			m_Cubelets[layer][0][0] = m_Cubelets[layer][2][0];
			m_Cubelets[layer][2][0] = m_Cubelets[layer][2][2];
			m_Cubelets[layer][2][2] = m_Cubelets[layer][0][2];
			m_Cubelets[layer][0][2] = temp;

			// Swap Edges
			temp = m_Cubelets[layer][0][1];
			m_Cubelets[layer][0][1] = m_Cubelets[layer][1][0];
			m_Cubelets[layer][1][0] = m_Cubelets[layer][2][1];
			m_Cubelets[layer][2][1] = m_Cubelets[layer][1][2];
			m_Cubelets[layer][1][2] = temp;

			// Rotate Pieces
			//m_Cubelets[layer][0][0]->Rotate(90.0f, Axis::X);
			//m_Cubelets[layer][2][0]->Rotate(90.0f, Axis::X);
			//m_Cubelets[layer][2][2]->Rotate(90.0f, Axis::X);
			//m_Cubelets[layer][0][2]->Rotate(90.0f, Axis::X);
			//m_Cubelets[layer][0][1]->Rotate(90.0f, Axis::X);
			//m_Cubelets[layer][1][0]->Rotate(90.0f, Axis::X);
			//m_Cubelets[layer][2][1]->Rotate(90.0f, Axis::X);
			//m_Cubelets[layer][1][2]->Rotate(90.0f, Axis::X);

			m_TarRot = 90;
			m_MoveTransform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));

			// Rotate Pieces
			m_Cubelets[layer][0][0]->GetTransform()->SetParent(&m_MoveTransform);
			m_Cubelets[layer][2][0]->GetTransform()->SetParent(&m_MoveTransform);
			m_Cubelets[layer][2][2]->GetTransform()->SetParent(&m_MoveTransform);
			m_Cubelets[layer][0][2]->GetTransform()->SetParent(&m_MoveTransform);
			m_Cubelets[layer][0][1]->GetTransform()->SetParent(&m_MoveTransform);
			m_Cubelets[layer][1][0]->GetTransform()->SetParent(&m_MoveTransform);
			m_Cubelets[layer][2][1]->GetTransform()->SetParent(&m_MoveTransform);
			m_Cubelets[layer][1][2]->GetTransform()->SetParent(&m_MoveTransform);
		}
		else if (axis == Axis::Y)
		{
			// Swap Corners
			Cubelet* temp;
			temp = m_Cubelets[0][layer][0];
			m_Cubelets[0][layer][0] = m_Cubelets[2][layer][0];
			m_Cubelets[2][layer][0] = m_Cubelets[2][layer][2];
			m_Cubelets[2][layer][2] = m_Cubelets[0][layer][2];
			m_Cubelets[0][layer][2] = temp;

			// Swap Edges
			temp = m_Cubelets[0][layer][1];
			m_Cubelets[0][layer][1] = m_Cubelets[1][layer][0];
			m_Cubelets[1][layer][0] = m_Cubelets[2][layer][1];
			m_Cubelets[2][layer][1] = m_Cubelets[1][layer][2];
			m_Cubelets[1][layer][2] = temp;

			// Rotate Pieces
			//m_Cubelets[0][layer][0]->Rotate(90.0f, Axis::Y);
			//m_Cubelets[2][layer][0]->Rotate(90.0f, Axis::Y);
			//m_Cubelets[2][layer][2]->Rotate(90.0f, Axis::Y);
			//m_Cubelets[0][layer][2]->Rotate(90.0f, Axis::Y);
			//m_Cubelets[0][layer][1]->Rotate(90.0f, Axis::Y);
			//m_Cubelets[1][layer][0]->Rotate(90.0f, Axis::Y);
			//m_Cubelets[2][layer][1]->Rotate(90.0f, Axis::Y);
			//m_Cubelets[1][layer][2]->Rotate(90.0f, Axis::Y);

			m_TarRot = 90;
			m_MoveTransform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));

			m_Cubelets[0][layer][0]->GetTransform()->SetParent(&m_MoveTransform);
			m_Cubelets[2][layer][0]->GetTransform()->SetParent(&m_MoveTransform);
			m_Cubelets[2][layer][2]->GetTransform()->SetParent(&m_MoveTransform);
			m_Cubelets[0][layer][2]->GetTransform()->SetParent(&m_MoveTransform);
			m_Cubelets[0][layer][1]->GetTransform()->SetParent(&m_MoveTransform);
			m_Cubelets[1][layer][0]->GetTransform()->SetParent(&m_MoveTransform);
			m_Cubelets[2][layer][1]->GetTransform()->SetParent(&m_MoveTransform);
			m_Cubelets[1][layer][2]->GetTransform()->SetParent(&m_MoveTransform);
		}
		else if (axis == Axis::Z)
		{
			// Swap Corners
			Cubelet* temp;
			temp = m_Cubelets[0][0][layer];
			m_Cubelets[0][0][layer] = m_Cubelets[2][0][layer];
			m_Cubelets[2][0][layer] = m_Cubelets[2][2][layer];
			m_Cubelets[2][2][layer] = m_Cubelets[0][2][layer];
			m_Cubelets[0][2][layer] = temp;

			// Swap Edges
			temp = m_Cubelets[0][1][layer];
			m_Cubelets[0][1][layer] = m_Cubelets[1][0][layer];
			m_Cubelets[1][0][layer] = m_Cubelets[2][1][layer];
			m_Cubelets[2][1][layer] = m_Cubelets[1][2][layer];
			m_Cubelets[1][2][layer] = temp;

			// Rotate Pieces
			//m_Cubelets[0][0][layer]->Rotate(-90.0f, Axis::Z);
			//m_Cubelets[2][0][layer]->Rotate(-90.0f, Axis::Z);
			//m_Cubelets[2][2][layer]->Rotate(-90.0f, Axis::Z);
			//m_Cubelets[0][2][layer]->Rotate(-90.0f, Axis::Z);
			//m_Cubelets[0][1][layer]->Rotate(-90.0f, Axis::Z);
			//m_Cubelets[1][0][layer]->Rotate(-90.0f, Axis::Z);
			//m_Cubelets[2][1][layer]->Rotate(-90.0f, Axis::Z);
			//m_Cubelets[1][2][layer]->Rotate(-90.0f, Axis::Z);

			m_TarRot = -90;
			m_MoveTransform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));

			m_Cubelets[0][0][layer]->GetTransform()->SetParent(&m_MoveTransform);
			m_Cubelets[2][0][layer]->GetTransform()->SetParent(&m_MoveTransform);
			m_Cubelets[2][2][layer]->GetTransform()->SetParent(&m_MoveTransform);
			m_Cubelets[0][2][layer]->GetTransform()->SetParent(&m_MoveTransform);
			m_Cubelets[0][1][layer]->GetTransform()->SetParent(&m_MoveTransform);
			m_Cubelets[1][0][layer]->GetTransform()->SetParent(&m_MoveTransform);
			m_Cubelets[2][1][layer]->GetTransform()->SetParent(&m_MoveTransform);
			m_Cubelets[1][2][layer]->GetTransform()->SetParent(&m_MoveTransform);
		}
	}
	else
	{
		if (axis == Axis::X)
		{
			// Swap Corners
			Cubelet* temp;
			temp = m_Cubelets[layer][0][0];
			m_Cubelets[layer][0][0] = m_Cubelets[layer][0][2];
			m_Cubelets[layer][0][2] = m_Cubelets[layer][2][2];
			m_Cubelets[layer][2][2] = m_Cubelets[layer][2][0];
			m_Cubelets[layer][2][0] = temp;

			// Swap Edges
			temp = m_Cubelets[layer][0][1];
			m_Cubelets[layer][0][1] = m_Cubelets[layer][1][2];
			m_Cubelets[layer][1][2] = m_Cubelets[layer][2][1];
			m_Cubelets[layer][2][1] = m_Cubelets[layer][1][0];
			m_Cubelets[layer][1][0] = temp;

			// Rotate Pieces
			//m_Cubelets[layer][0][0]->Rotate(-90.0f, Axis::X);
			//m_Cubelets[layer][2][0]->Rotate(-90.0f, Axis::X);
			//m_Cubelets[layer][2][2]->Rotate(-90.0f, Axis::X);
			//m_Cubelets[layer][0][2]->Rotate(-90.0f, Axis::X);
			//m_Cubelets[layer][0][1]->Rotate(-90.0f, Axis::X);
			//m_Cubelets[layer][1][0]->Rotate(-90.0f, Axis::X);
			//m_Cubelets[layer][2][1]->Rotate(-90.0f, Axis::X);
			//m_Cubelets[layer][1][2]->Rotate(-90.0f, Axis::X);
		}
		else if (axis == Axis::Y)
		{
			// Swap Corners
			Cubelet* temp;
			temp = m_Cubelets[0][layer][0];
			m_Cubelets[0][layer][0] = m_Cubelets[0][layer][2];
			m_Cubelets[0][layer][2] = m_Cubelets[2][layer][2];
			m_Cubelets[2][layer][2] = m_Cubelets[2][layer][0];
			m_Cubelets[2][layer][0] = temp;

			// Swap Edges
			temp = m_Cubelets[0][layer][1];
			m_Cubelets[0][layer][1] = m_Cubelets[1][layer][2];
			m_Cubelets[1][layer][2] = m_Cubelets[2][layer][1];
			m_Cubelets[2][layer][1] = m_Cubelets[1][layer][0];
			m_Cubelets[1][layer][0] = temp;

			// Rotate Pieces
			//m_Cubelets[0][layer][0]->Rotate(-90.0f, Axis::Y);
			//m_Cubelets[2][layer][0]->Rotate(-90.0f, Axis::Y);
			//m_Cubelets[2][layer][2]->Rotate(-90.0f, Axis::Y);
			//m_Cubelets[0][layer][2]->Rotate(-90.0f, Axis::Y);
			//m_Cubelets[0][layer][1]->Rotate(-90.0f, Axis::Y);
			//m_Cubelets[1][layer][0]->Rotate(-90.0f, Axis::Y);
			//m_Cubelets[2][layer][1]->Rotate(-90.0f, Axis::Y);
			//m_Cubelets[1][layer][2]->Rotate(-90.0f, Axis::Y);
		}
		else if (axis == Axis::Z)
		{
			// Swap Corners
			Cubelet* temp;
			temp = m_Cubelets[0][0][layer];
			m_Cubelets[0][0][layer] = m_Cubelets[0][2][layer];
			m_Cubelets[0][2][layer] = m_Cubelets[2][2][layer];
			m_Cubelets[2][2][layer] = m_Cubelets[2][0][layer];
			m_Cubelets[2][0][layer] = temp;

			// Swap Edges
			temp = m_Cubelets[0][1][layer];
			m_Cubelets[0][1][layer] = m_Cubelets[1][2][layer];
			m_Cubelets[1][2][layer] = m_Cubelets[2][1][layer];
			m_Cubelets[2][1][layer] = m_Cubelets[1][0][layer];
			m_Cubelets[1][0][layer] = temp;

			// Rotate Pieces
			//m_Cubelets[0][0][layer]->Rotate(90.0f, Axis::Z);
			//m_Cubelets[2][0][layer]->Rotate(90.0f, Axis::Z);
			//m_Cubelets[2][2][layer]->Rotate(90.0f, Axis::Z);
			//m_Cubelets[0][2][layer]->Rotate(90.0f, Axis::Z);
			//m_Cubelets[0][1][layer]->Rotate(90.0f, Axis::Z);
			//m_Cubelets[1][0][layer]->Rotate(90.0f, Axis::Z);
			//m_Cubelets[2][1][layer]->Rotate(90.0f, Axis::Z);
			//m_Cubelets[1][2][layer]->Rotate(90.0f, Axis::Z);
		}
	}
}

void RubiksCube::Rotate(float degrees, Axis axis)
{
	// set the rotate variables
	m_IsLerping = true;
	m_TarRot = degrees;
	m_CurRot = 0;
	m_InitRot = 0;
	m_CurAxis = axis;
	m_Dir = degrees > 0 ? 1 : degrees < 0 ? -1 : 0;


}

void RubiksCube::Input(const SDL_Event& e)
{
	if (e.type == SDL_KEYUP && !m_IsLerping)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			Rotate(45.0f, Axis::X);
			break;
		case SDLK_DOWN:
			Rotate(-45.0f, Axis::X);
			break;
		case SDLK_LEFT:
			Rotate(45.0f, Axis::Y);
			break;
		case SDLK_RIGHT:
			Rotate(-45.0f, Axis::Y);
			break;
		case SDLK_f:
			Move(0, Axis::Z, MoveDir::Anticlockwise);
			break;
		case SDLK_b:
			Move(2, Axis::Z, MoveDir::Clockwise);
			break;
		case SDLK_r:
			Move(0, Axis::X, MoveDir::Clockwise);
			break;
		case SDLK_l:
			Move(2, Axis::X, MoveDir::Anticlockwise);
			break;
		case SDLK_u:
			Move(0, Axis::Y, MoveDir::Clockwise);
			break;
		case SDLK_d:
			Move(2, Axis::Y, MoveDir::Anticlockwise);
			break;
		}

	}
}

void RubiksCube::Update()
{
	if (m_IsLerping)
	{
		//m_Model = glm::rotate(m_Model, glm::radians(m_Dir * ROTATE_SPEED), m_CurAxis == Axis::X ? glm::vec3(1.0f, 0.0f, 0.0f) : m_CurAxis == Axis::Y ? glm::vec3(0.0f, 1.0f, 0.0f) : glm::vec3(0.0f, 0.0f, 1.0f));
		//
		//m_Transform.SetRotation(glm::vec3(m_Transform.GetRotation().x + ROTATE_SPEED, m_Transform.GetRotation().y, m_Transform.GetRotation().z));
		//


		m_MoveTransform.SetRotation(glm::vec3(m_Transform.GetRotation().x + ROTATE_SPEED, m_Transform.GetRotation().y, m_Transform.GetRotation().z));



		if (m_CurRot == m_TarRot)
		{
			m_IsLerping = false;
		}
		else
		{
			m_CurRot += m_Dir * ROTATE_SPEED;
		}


	}
}

void RubiksCube::Render()
{
	glm::mat4 projection;
	projection = glm::perspective(m_Camera->GetFov(), (GLfloat)m_Camera->GetWidth() / (GLfloat)m_Camera->GetHeight(), 0.1f, 1000.0f);

	// Create camera transformation
	glm::mat4 view;
	view = m_Camera->GetViewMatrix();

	for (int x = 0; x < m_LayerCount; x++)
	{
		for (int y = 0; y < m_LayerCount; y++)
		{
			for (int z = 0; z < m_LayerCount; z++)
			{
				m_Cubelets[x][y][z]->Render(view, projection);
			}
		}
	}
}
