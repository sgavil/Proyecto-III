#pragma once
#include "Widget.h"

class ProgressBar : public Widget
{

public:
	ProgressBar();
	~ProgressBar();

	void load(json file);

	virtual void receive(Message* msg) {};

	virtual void save(json& file) {};

	virtual void setProgress(float progress);

	CEGUI::ProgressBar* getProgressBar() { return progressBar_; };

private:
	CEGUI::ProgressBar* progressBar_;
};

REGISTER_TYPE(ProgressBar)