// GameState.h //

#pragma once

#include "State.h"

class SceneObject;

class GameState : public State {
public:
	GameState();
	~GameState();

	bool Enter();
	void Exit();
	bool Update(float p_fDtime);  // Parameter_FloatingDtime
	void Draw();
	std::string Next();
	bool IsType(const std::string &p_sType);// Parameter_StringType

private:
	std::string m_sNext;

	SceneObject *m_xpScene;
};