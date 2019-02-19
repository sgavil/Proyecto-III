#include "Component.h"
#include <vector>
#include "Messages.h"

class Entity
{
public:
	Entity();
	void addComponent(Component comp);
	void delComponent(Component comp);
	virtual ~Entity();
private:
	std::vector<Component> components_;
		
};
