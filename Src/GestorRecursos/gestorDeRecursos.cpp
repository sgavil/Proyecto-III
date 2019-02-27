#include "gestorDeRecursos.h"

Ogre::Camera*  GestorRecursos::createCamera(Ogre::SceneManager* scnMgn, std::string name, Ogre::SceneNode* FatherNode, Ogre::Real NearClipDist, Ogre::Real FarClipDist, bool autoAspectRatio, Ogre::Real AspectRatio)
{
	Ogre::Camera* cam_ = scnMgn->createCamera(name);
	cam_->setNearClipDistance(NearClipDist);
	cam_->setFarClipDistance(FarClipDist);
	FatherNode->attachObject(cam_);
	if(autoAspectRatio)cam_->setAutoAspectRatio(autoAspectRatio);
	else cam_->setAspectRatio(AspectRatio);
	return cam_;
}

Ogre::Entity * GestorRecursos::createPlane(Ogre::SceneManager * scnMgn, std::string name, std::string MaterialName, Ogre::Real width, Ogre::Real height, int Xsegments, int Ysegments, Ogre::SceneNode* FatherNode, std::string groupName)
{
	Ogre::Entity* plane;
	Ogre::MeshManager::getSingleton().createPlane(name, groupName, Ogre::Plane(Ogre::Vector3::UNIT_Y, 0), width, height,
		Xsegments, Ysegments, true, 1, 1.0, 1.0, Ogre::Vector3::NEGATIVE_UNIT_Z);
	plane = scnMgn->createEntity(name);
	plane->setMaterialName(MaterialName);
	FatherNode->attachObject(plane);
	return plane;
}

void GestorRecursos::initGestor()
{
	new JsonManager();
}

JsonManager * GestorRecursos::jsonManager(void)
{
	return JsonManager::getSingletonPtr();
}

void GestorRecursos::initializeResources()
{
	Ogre::ConfigFile cf;

	Ogre::FileSystemLayer* mFSLayer = new Ogre::FileSystemLayer("cfLayerSystem");
	//Este metodo ya agrega '_d' si se compila en debug
	Ogre::String resourcesPath = mFSLayer->getConfigFilePath("resources.cfg");

	if (Ogre::FileSystemLayer::fileExists(resourcesPath))
		cf.load(resourcesPath);

	else
		throw::std::invalid_argument("Archivo resources.cfg no encontrado");

	Ogre::String sec, type, arch;

	// Recorre todos los grupos de recursos definidos en el archivo
	Ogre::ConfigFile::SettingsBySection_::const_iterator seci;

	for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci)
	{
		sec = seci->first;

		const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
		Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

		// Recorre todos los path
		for (i = settings.begin(); i != settings.end(); i++)
		{
			type = i->first;
			std::string auxPath = resourcesPath;
			auxPath.erase(auxPath.find_last_of("\\") + 1, auxPath.size() - 1);
			arch = auxPath + Ogre::FileSystemLayer::resolveBundlePath(i->second);

			//Va agregando las ubicaciones definidas en el cfg
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
		}
	}

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

}

