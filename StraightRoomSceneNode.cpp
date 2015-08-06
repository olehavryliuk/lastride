//Author Oleh Havryliuk 07.2015

#include "StraightRoomSceneNode.h"

StraightRoomSceneNode::StraightRoomSceneNode(irr::scene::ISceneNode* parent,
						irr::scene::ISceneManager* mgr,
						irr::s32 id,
						irr::video::ITexture* diffuseTexture,
						irr::video::ITexture* normalMapTexture,
						irr::u32 sectionCount,
						const irr::core::vector3df& halfSize,
						const irr::core::vector3df& position,
						const irr::core::vector3df& rotation,
						const irr::core::vector3df& scale) :
						irr::scene::ISceneNode(parent, mgr, id, position, rotation, scale)
{
	if (sectionCount > MAX_STRAIGHT_SECTIONS)
		m_sectionCount = MAX_STRAIGHT_SECTIONS;
	else if (sectionCount < 1)
		m_sectionCount = 1;
	else
		m_sectionCount = sectionCount;
	m_verticesCount = 4 * (m_sectionCount + 1);

	setAutomaticCulling(irr::scene::EAC_OFF);
	m_box.MaxEdge.set(0,0,0);
	m_box.MinEdge.set(0,0,0);

// create m_material
	//lighting
	if (USE_OWN_SHADER_LIGHTING)
	{
		m_material.Lighting = false;
	}
	else
	{
		m_material.Lighting = true;

		//bump mapping and parallax mapping
		if (USE_BUMP_MAPPING)
		{
			m_material.MaterialType = irr::video::EMT_NORMAL_MAP_SOLID;
		}
		else if (USE_PARALLAX_MAPPING)
		{
			m_material.MaterialType = irr::video::EMT_PARALLAX_MAP_SOLID;
			m_material.MaterialTypeParam = ADJUST_HEIGHT_FOR_PARALLAX;
		}
		else
			m_material.MaterialType = irr::video::EMT_SOLID;
	}

// set no glitter
//	m_material.SpecularColor.set(0, 0, 0, 0);
//	m_material.Shininess = 0.0f;

//set Textures
	m_material.setTexture(0, diffuseTexture);
	if (normalMapTexture)
		m_material.setTexture(1, normalMapTexture);
	m_material.TextureLayer[0].TextureWrapU = irr::video::ETC_REPEAT;
	m_material.TextureLayer[0].TextureWrapV = irr::video::ETC_REPEAT;
	m_material.AntiAliasing = ANTIALIASING;

	m_halfSize = halfSize;
	const irr::f32 hX = m_halfSize.X;
	const irr::f32 hY = m_halfSize.Y;
	const irr::f32 Z = 2.0f * m_halfSize.Z;

	const irr::f32 t = 1.0f;
	const irr::f32 o = 0.0f;
	/* 
       -314         314
          /7--------/6        y
         /  |      / |        ^  z
        /   |   31-4 |        | /
  -31-4 3---------2  |        |/
        |   4- - -| 3-14    *---->x
        | -3-14   |  /       4-------|5
        |/        | /         |    //|
        0---------1/          |  //  |
     -3-1-4     3-1-4         |//    |
	                     0--------1
	*/
	irr::video::SColor vertexColor = irr::video::SColor(255,255,255,255);
/*
	for (irr::u32 i = 0; i < m_sectionCount + 1; i++)
	{
		m_vertices[0+4*i] = irr::video::S3DVertex(-hX, -hY, (float)i * Z,
												  1.0f, 1.0f, 0.0f,
												  vertexColor,
												  o, o + t * (float)i);
		m_vertices[1+4*i] = irr::video::S3DVertex( hX, -hY, (float)i * Z,
												  -1.0f, 1.0f, 0.0f,
												  vertexColor,
												  t, o + t * (float)i);
		m_vertices[2+4*i] = irr::video::S3DVertex( hX, hY, (float)i * Z,
												  -1.0f, -1.0f, 0.0f,
												  vertexColor,
												  2 * t, o + t * (float)i);
		m_vertices[3+4*i] = irr::video::S3DVertex(-hX, hY, (float)i * Z,
												  1.0f, -1.0f, 0.0f,
												  vertexColor,
												  t, o + t * (float)i);
	}*/

	for (irr::u32 i = 0; i < m_sectionCount + 1; i++)
	{
		m_vertices[0+4*i] = irr::video::S3DVertexTangents(-hX, -hY, (float)i * Z,
														1.0f, 1.0f, 0.0f,
														vertexColor,
														o, o + t * (float)i,
														1.0f, -1.0f, 0.0f,
														0.0f,  0.0f, -1.0f);
		m_vertices[1+4*i] = irr::video::S3DVertexTangents( hX, -hY, (float)i * Z,
														-1.0f, 1.0f, 0.0f,
														vertexColor,
														t, o + t * (float)i,
														1.0f, 1.0f, 0.0f,
														0.0f,  0.0f, -1.0f);
		m_vertices[2+4*i] = irr::video::S3DVertexTangents( hX, hY, (float)i * Z,
														 -1.0f, -1.0f, 0.0f,
														 vertexColor,
														 2 * t, o + t * (float)i,
														 -1.0f, 1.0f, 0.0f,
														 0.0f,  0.0f, -1.0f);
		m_vertices[3+4*i] = irr::video::S3DVertexTangents(-hX, hY, (float)i * Z,
														 1.0f, -1.0f, 0.0f,
														 vertexColor,
														 t, o + t * (float)i,
														 -1.0f, -1.0f, 0.0f,
														 0.0f,  0.0f, -1.0f);
	}

	// create indices
	for (irr::u32 i = 0; i < 4 * m_sectionCount; i++)
	{
		m_indices[0+6*i] = 0 + i;
		m_indices[1+6*i] = 4 + i;
		m_indices[2+6*i] = 5 + i;
		m_indices[3+6*i] = 0 + i;
		m_indices[4+6*i] = 5 + i;
		m_indices[5+6*i] = 1 + i;

		if (((i - 3) % 4) == 0)
		{
			m_indices[2+6*i] = 1 + i;
			m_indices[4+6*i] = 1 + i;
			m_indices[5+6*i] = i - 3;
		}
	}
}

void StraightRoomSceneNode::OnRegisterSceneNode()
{
	if (IsVisible)
		SceneManager->registerNodeForRendering(this);

	ISceneNode::OnRegisterSceneNode();
}

void StraightRoomSceneNode::render()
{
	irr::video::IVideoDriver* driver = SceneManager->getVideoDriver();

	if (!driver)
		return;

	driver->setTransform(irr::video::ETS_WORLD, AbsoluteTransformation);
	driver->setMaterial(m_material);
	driver->drawIndexedTriangleList(m_vertices, m_verticesCount, m_indices, 8 * m_sectionCount);
}

const irr::core::aabbox3d<irr::f32>& StraightRoomSceneNode::getBoundingBox() const
{
	return m_box;
}

irr::u32 StraightRoomSceneNode::getMaterialCount() const
{
	return 1;
}

irr::video::SMaterial& StraightRoomSceneNode::getMaterial(irr::u32 i)
{
	return m_material;
}

irr::u32 StraightRoomSceneNode::getVertexCount() const
{
	return m_verticesCount;
}

const irr::video::S3DVertexTangents* StraightRoomSceneNode::getVertices() const
{
	return m_vertices;
}

irr::core::vector3df StraightRoomSceneNode::centerPositionTransformedForSection(irr::u32 sectionNumber)
{
	irr::core::vector3df result = irr::core::vector3df(0.0f, 0.0f, m_halfSize.Z * (float)(2 * sectionNumber + 1));
	AbsoluteTransformation.transformVect(result);
	return result;
}

irr::core::vector3df StraightRoomSceneNode::centerPositionForSection(irr::u32 sectionNumber)
{
	return irr::core::vector3df(0.0f, 0.0f, m_halfSize.Z * (float)(2 * sectionNumber + 1));
}