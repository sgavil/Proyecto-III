#include "ProgressBar.h"

ProgressBar::ProgressBar(): progressBar_(nullptr)
{
	type = "Vanilla/Scrollbar";
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::load(json file)
{
	Widget::load(file);

	progressBar_ = static_cast<CEGUI::ProgressBar*>(window);
	string color = file["BarColor"];
	progressBar_->setProperty("EnabledColour", color);
}
