//Author Oleh Havryliuk 08.2015

#include "Mine.h"
#include "Constants.h"
#include <ISceneManager.h>
#include <IMeshManipulator.h>

Mine::Mine()
{
	m_sceneNode = nullptr;
}
	
Mine::~Mine()
{

}

bool Mine::initMine(irr::scene::ISceneNode* parent, 
					irr::scene::ISceneManager* sceneManager,
					irr::s32 id,
					irr::scene::IMesh* tangentMesh,
					irr::video::ITexture* diffuseTexture,
					irr::video::ITexture* normalMapTexture,
					const irr::core::vector3df& position,
					const irr::core::vector3df& rotation,
					const irr::core::vector3df& scale)
{
    m_sceneNode = sceneManager->addMeshSceneNode(tangentMesh, parent, id, position, rotation, scale);

	if (diffuseTexture)
		m_sceneNode->setMaterialTexture(0, diffuseTexture);
	if (normalMapTexture)
		m_sceneNode->setMaterialTexture(1, normalMapTexture);

//lighting
	if (USE_OWN_SHADER_LIGHTING)
		m_sceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	else
	{
		m_sceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);

	//bump mapping and parallax mapping
		if (USE_BUMP_MAPPING)
			m_sceneNode->setMaterialType(irr::video::EMT_NORMAL_MAP_SOLID);
		else if (USE_PARALLAX_MAPPING)
		{
			m_sceneNode->setMaterialType(irr::video::EMT_PARALLAX_MAP_SOLID);
			m_sceneNode->getMaterial(0).MaterialTypeParam = ADJUST_HEIGHT_FOR_PARALLAX;
		}
		else
			m_sceneNode->setMaterialType(irr::video::EMT_SOLID);
	}

	m_sceneNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);

	return true;
}

irr::scene::IMeshSceneNode* Mine::getSceneNode()
{
	return m_sceneNode;
}

bool Mine::intersectsWithObject(irr::scene::ISceneNode* object)
{
	irr::core::aabbox3d<irr::f32> thisNodeBox = m_sceneNode->getTransformedBoundingBox();
	irr::core::aabbox3d<irr::f32> objectNodeBox = object->getTransformedBoundingBox();
	thisNodeBox.repair();
	objectNodeBox.repair();

	return thisNodeBox.intersectsWithBox(objectNodeBox);
}

bool Mine::isNearObject(irr::scene::ISceneNode* object)
{
	irr::core::aabbox3d<irr::f32> objectNodeBox = object->getTransformedBoundingBox();
	irr::core::aabbox3d<irr::f32> increasedBoundingBox = m_sceneNode->getBoundingBox();
	increasedBoundingBox.MinEdge *= BOX_INCREASE_MULTIPLIER * 2;
	increasedBoundingBox.MaxEdge *= BOX_INCREASE_MULTIPLIER * 2;
	m_sceneNode->getAbsoluteTransformation().transformBoxEx(increasedBoundingBox);
	increasedBoundingBox.repair();
	objectNodeBox.repair();

	return increasedBoundingBox.intersectsWithBox(objectNodeBox);
}