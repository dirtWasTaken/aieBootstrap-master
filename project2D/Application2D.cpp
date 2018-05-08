#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include<time.h>
#include <assert.h>
#include <vector>
#include <list>

/***********************************************************************************************
an added vector used through the project to contain the number of sprites used.
***********************************************************************************************/
using TargetArray = std::vector<Target>;

TargetArray g_targets;



Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {

	//seeding for the randomisation of sprite locations
	srand(unsigned(time(NULL)));

	m_2dRenderer = new aie::Renderer2D();

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);
	
	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	/***********************************************************************************************
	Start off with x targets using the global tagets variable referencing the target vector(set to 30)
	***********************************************************************************************/
	g_targets.resize(30);


	return true;
}

void Application2D::shutdown() {
	
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;
}

/***********************************************************************************************
Update function used every frame through the delta time game loop
to update our game state include input and randomisation of the spites 
***********************************************************************************************/
void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	/***********************************************************************************************
	Attempted to add a restart will try to fix it if I have time.
	***********************************************************************************************/

	//if (input->isKeyDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
	//{
	//	g_targets.resize(30);
	//}
	
	/***********************************************************************************************
	Input and detection for the left mouse button responsible
	for clicking on and deleting sprites 
	***********************************************************************************************/

	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		float xMouse = (float)input->getMouseX();
		float yMouse = (float)input->getMouseY();

		size_t index = -1;
		for (size_t i = 0; i < g_targets.size(); i++)
		{
			Target & target = g_targets[i];
			/*
			using pythagoras theorem to crudely determine the hitbox of our tagets  
			*/
			float distance = sqrtf(    (xMouse - target.x) * (xMouse - target.x)  + (yMouse - target.y) * (yMouse - target.y)  );
			if (distance < 40)
			{
				index = i;
				break;
			}

		}

		if (index != -1)
		{
			g_targets.erase(g_targets.begin() + index);
		}

	}
	/*
	every 2 seconds randomise our targets locations through our for loop (Loop within a loop)
	*/
	if (m_timer > 2.0f)
	{
		for (size_t i = 0; i < g_targets.size(); i++)
		{
			Target & target = g_targets[i];

			target.x = (float)(rand() % 1700 + 1);
			target.y = (float)(rand() % 1000 + 1);
		}

		m_timer = 0;

	}

}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();
	
/***************jeff
	aie::Renderer2D::clickableBox * clickableBox = new aie::Renderer2D::clickableBox;
*************/


/***********************
	//allocation of Random x/y positions
	for (size_t i = 0; i < clickableBox->spriteNUM; i++)
	{
		clickableBox->spriteLocationY[i] = rand() % 1700 + 1;
		clickableBox->spriteLocationX[i] = rand() % 1000 + 1;
	}
	
	for (size_t i = 0; i < clickableBox->spriteNUM; i++)
	{
	// draw a slightly rotated sprite with no texture, coloured yellow
	m_2dRenderer->setRenderColour(1, 1, 0, 1);
	m_2dRenderer->drawSprite(nullptr, clickableBox->spriteLocationY[i], clickableBox->spriteLocationX[i], 50, 50, 3.14159f * 0.25f, 1);
	}
**********************/

	/*
	and then draw the boxes in our predetermined randomised positions 
	*/
	for (size_t i = 0; i < g_targets.size(); i++)
	{
		Target & target = g_targets[i];

		// draw a slightly rotated sprite with no texture, coloured yellow
		m_2dRenderer->setRenderColour(1, 1, 0, 1);
		m_2dRenderer->drawSprite(nullptr, target.x, target.y, 50, 50, 3.14159f * 0.25f, 1);

	}

	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 50, 50);

	// done drawing sprites
	m_2dRenderer->end();

	
}