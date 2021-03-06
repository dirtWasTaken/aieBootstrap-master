#pragma once

#include "Application.h"
#include "Renderer2D.h"

/*
The struct for our target vector and the position definitions, better than a for loop/array 
*/

struct Target
{
	Target()
	{
		x = y = 0;
	}

	Target(float x_, float y_)
	{
		x = x_;
		y = y_;
	}

	float x = 0;
	float y = 0;
};

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;

	float m_cameraX, m_cameraY;
	float m_timer;
};