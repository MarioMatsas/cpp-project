#pragma once
#include <string>
#include "GameState.h"

class GameObject
{
	static int m_next_id;

protected:
	class GameState* m_state;
	int m_id = 0;
	bool m_active = true;
	graphics::Brush br; 
	

public:
	GameObject(const std::string& m_name = "", const std::string& m_class = "GameObject");
	virtual void update(float dt) {}
	virtual void init() {}
	virtual void draw() {}
	virtual ~GameObject() {}
	bool isActive() { return m_active; }
	void setActive(bool a) { m_active = a; }
	const std::string m_class;
	std::string m_name;
};