//Author Oleh Havryliuk 07.2015
#include "CubicSceneNode.h"
#include "Constants.h"

CubicSceneNode::CubicSceneNode(irr::scene::ISceneNode* parent, 
								irr::scene::ISceneManager* mgr,
								irr::s32 id,
								irr::video::ITexture* diffuseTexture,
								irr::video::ITexture* normalMapTexture,
								const irr::core::vector3df& halfSize,
								const irr::core::vector3df& position,
								const irr::core::vector3df& rotation,
								const irr::core::vector3df& scale) :
								irr::scene::ISceneNode(parent, mgr, id, position, rotation, scale)
{
	setAutomaticCulling(irr::scene::EAC_OFF);

// create m_material
	//lighting
	if (!USE_OWN_SHADER_LIGHTING)
		m_material.Lighting = true;
	else
		m_material.Lighting = false;

	//bump mapping and parallax mapping
	if (USE_BUMP_MAPPING)
		m_material.MaterialType = irr::video::EMT_NORMAL_MAP_SOLID;
	else if (USE_PARALLAX_MAPPING)
	{
		m_material.MaterialType = irr::video::EMT_PARALLAX_MAP_SOLID;
		m_material.MaterialTypeParam = ADJUST_HEIGHT_FOR_PARALLAX;
	}
	else
		m_material.MaterialType = irr::video::EMT_SOLID;

	m_material.setTexture(0, diffuseTexture);
	if (normalMapTexture)
		m_material.setTexture(1, normalMapTexture);
	m_material.TextureLayer[0].TextureWrapU = irr::video::ETC_CLAMP_TO_BORDER;
	m_material.TextureLayer[0].TextureWrapV = irr::video::ETC_CLAMP_TO_BORDER;
	m_material.AntiAliasing=0;

	const irr::f32 hX = halfSize.X;
	const irr::f32 hY = halfSize.Y;
	const irr::f32 hZ = halfSize.Z;

	const irr::f32 t = 1.0f;
	const irr::f32 o = 0.0f;

	irr::video::SColor vertexColor = irr::video::SColor(255,255,255,255);
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
	m_vertices[0] = irr::video::S3DVertexTangents(-hX,-hY,-hZ,  0.0f,-1.0f,-1.0f, vertexColor, o, o,	  1.0f, 0.0f, 0.0f,  0.0f,-1.0f, 1.0f);
	m_vertices[1] = irr::video::S3DVertexTangents( hX,-hY,-hZ,  0.0f,-1.0f,-1.0f, vertexColor, t, o,	  1.0f, 0.0f, 0.0f,  0.0f,-1.0f, 1.0f);
	m_vertices[2] = irr::video::S3DVertexTangents( hX, hY,-hZ,  0.0f, 1.0f,-1.0f, vertexColor, t, 0.5f,  1.0f, 0.0f, 0.0f,  0.0f,-1.0f,-1.0f);
	m_vertices[3] = irr::video::S3DVertexTangents(-hX, hY,-hZ,  0.0f, 1.0f,-1.0f, vertexColor, o, 0.5f,  1.0f, 0.0f, 0.0f,  0.0f,-1.0f,-1.0f);
	m_vertices[4] = irr::video::S3DVertexTangents(-hX,-hY, hZ,  0.0f,-1.0f, 1.0f, vertexColor, o, 0.1f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 1.0f);
	m_vertices[5] = irr::video::S3DVertexTangents( hX,-hY, hZ,  0.0f,-1.0f, 1.0f, vertexColor, t, 0.1f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 1.0f);
	m_vertices[6] = irr::video::S3DVertexTangents( hX, hY, hZ,  0.0f, 1.0f, 1.0f, vertexColor, t, 0.6f,	  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,-1.0f);
	m_vertices[7] = irr::video::S3DVertexTangents(-hX, hY, hZ,  0.0f, 1.0f, 1.0f, vertexColor, o, 0.6,	  1.0f, 0.0f, 0.0f,	 0.0f, 1.0f,-1.0f);

	// create indices
	for (irr::s32 i = 0; i < 3; i++)
	{
		m_indices[0+6*i] = 0 + i;
		m_indices[1+6*i] = 5 + i;
		m_indices[2+6*i] = 4 + i;
		m_indices[3+6*i] = 0 + i;
		m_indices[4+6*i] = 1 + i;
		m_indices[5+6*i] = 5 + i;
	}
	m_indices[18] = 3;
	m_indices[19] = 4;
	m_indices[20] = 7;
	m_indices[21] = 3;
	m_indices[22] = 0;
	m_indices[23] = 4;
	m_indices[24] = 0;
	m_indices[25] = 3;
	m_indices[26] = 2;
	m_indices[27] = 0;
	m_indices[28] = 2;
	m_indices[29] = 1;
	m_indices[30] = 5;
	m_indices[31] = 6;
	m_indices[32] = 7;
	m_indices[33] = 5;
	m_indices[34] = 7;
	m_indices[35] = 4;

	m_box.reset(m_vertices[0].Pos);
	m_box.addInternalPoint(m_vertices[6].Pos);

	//setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
}

void CubicSceneNode::OnRegisterSceneNode()
{
	if (IsVisible)
		SceneManager->registerNodeForRendering(this);

	ISceneNode::OnRegisterSceneNode();
}

void CubicSceneNode::render()
{
	irr::video::IVideoDriver* driver = SceneManager->getVideoDriver();
	if (!driver)
		return;

	driver->setTransform(irr::video::ETS_WORLD, AbsoluteTransformation);
	driver->setMaterial(m_material);
	driver->drawIndexedTriangleList(m_vertices, 8, m_indices, 12);
}

const irr::core::aabbox3d<irr::f32>& CubicSceneNode::getBoundingBox() const
{
	return m_box;
}

irr::u32 CubicSceneNode::getMaterialCount() const
{
	return 1;
}

irr::video::SMaterial& CubicSceneNode::getMaterial(irr::u32 i)
{
	return m_material;
}