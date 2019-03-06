#pragma once

class  PlayState : public GameState
{
protected:

	virtual void start();
public:
	PlayState();
	virtual ~PlayState();

	void update(unsigned int time);
	void render(unsigned int time);
	void handleInput(unsigned int time);
};