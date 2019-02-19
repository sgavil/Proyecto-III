#include <iostream>
#include "PruebaLib/saluda.h"
#include <OgreRoot.h>
#include "initOgreApplication.h"



int main()
{
	Ogre::Root* root;
    #if _DEBUG
		root = new Ogre::Root("plugins_d.cfg");
    #else 	
		root = new Ogre::Root("plugins.cfg");
	#endif

	initOgreApplication* Ogreinit = new initOgreApplication(root);

	system("pause");


	return 0;
}
