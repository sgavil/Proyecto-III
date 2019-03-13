#pragma once

class MainMenuState : public GameState
{
protected:

	virtual void start();
public:
	MainMenuState();
	~MainMenuState();

	void update(unsigned int time);
	void render(unsigned int time);
	bool handleInput(unsigned int time);
};