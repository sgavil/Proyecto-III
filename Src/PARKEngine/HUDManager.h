#pragma once
#include <memory>

class HUDManager
{
private:
	static std::unique_ptr<HUDManager> instance_;

	HUDManager();
public:	
	static HUDManager* instance();

	void init();

	~HUDManager();
};
