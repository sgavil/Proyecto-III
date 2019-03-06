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
	void handleInput(unsigned int time);
};