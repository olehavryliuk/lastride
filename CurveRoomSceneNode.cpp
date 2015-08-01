//Author Oleh Havryliuk 07.2015

#include "CurveRoomSceneNode.h"

CurveRoomSceneNode::CurveRoomSceneNode(irr::scene::ISceneNode* parent, 
										irr::scene::ISceneManager* mgr,
										DIRECTION direction,
										irr::f32 angle,
										irr::f32 radius,
										irr::u8 sectionCount,
										irr::s32 id,
										irr::video::ITexture* diffuseTexture,
										irr::video::ITexture* normalMapTexture,
										const irr::core::vector3df& halfSize,
										const irr::core::vector3df& position,
										const irr::core::vector3df& rotation,
										const irr::core::vector3df& scale) :
										irr::scene::ISceneNode(parent, mgr, id, position, rotation, scale)
{
	m_direction = direction;
	if (sectionCount > MAX_CURVE_SECTIONS)
		m_sectionCount = MAX_CURVE_SECTIONS;
	else if (sectionCount < 2)
		m_sectionCount = 2;
	else
		m_sectionCount = sectionCount;
	if (angle > 180.0f)
		m_angle = 180.0f;
	else if (angle < 0.0f)
		m_angle = 0.0f;
	else
		m_angle = angle;
	m_radius = radius;
	m_sectionAngle = m_angle * irr::core::PI / ((float)(m_sectionCount) * 180.0f) ;
	m_verticesCount = 4 * (m_sectionCount + 1);

	setAutomaticCulling(irr::scene::EAC_OFF);
	m_box.MaxEdge.set(0,0,0);
	m_box.MinEdge.set(0,0,0);

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

//set Textures
	m_material.setTexture(0, diffuseTexture);
	if (normalMapTexture)
		m_material.setTexture(1, normalMapTexture);

	m_material.TextureLayer[0].TextureWrapU = irr::video::ETC_REPEAT;
	m_material.TextureLayer[0].TextureWrapV = irr::video::ETC_REPEAT;
	m_material.AntiAliasing = ANTIALIASING;

	const irr::f32 hX = halfSize.X;
	const irr::f32 hY = halfSize.Y;
	const irr::f32 hZ = halfSize.Z;

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
	irr::f32 sinus, cosinus, wideRadius, shortRadius;
	irr::video::SColor vertexColor = irr::video::SColor(255,255,255,255);
	irr::video::S3DVertex swapVertex;

	wideRadius = m_radius + hX;
	shortRadius = m_radius - hX;

	if (m_direction == D_LEFT)
	{
		irr::f32 x_0_3, x_1_2, z_0_3, z_1_2;

		for (irr::u8 i = 0; i < m_sectionCount + 1; i++)
		{
			cosinus = cos(m_sectionAngle * i);
			sinus = sin(m_sectionAngle * i);
			x_0_3 = shortRadius * cosinus - m_radius;
			x_1_2 =	wideRadius * cosinus - m_radius;
			z_0_3 = shortRadius * sinus;
			z_1_2 =	wideRadius * sinus;

			m_vertices[0+4*i] = irr::video::S3DVertexTangents(x_0_3, -hY, z_0_3, 
													  cosinus, 1.0f, sinus, 
													  vertexColor,
													  o, o + t * (float)i,
													  cosinus, -1.0f, sinus,
													  sinus, 0.0f, -cosinus);
			m_vertices[1+4*i] = irr::video::S3DVertexTangents(x_1_2, -hY, z_1_2,
													  -cosinus, 1.0f, -sinus, 
													  vertexColor,
													  t, o + t * (float)i,
													  cosinus, 1.0f, -sinus,
													  sinus, 0.0f, -cosinus);
			m_vertices[2+4*i] = irr::video::S3DVertexTangents(x_1_2, hY, z_1_2, 
													  -cosinus, -1.0f, -sinus, 
													  vertexColor,
													  2 * t, o + t * (float)i,
													  -cosinus, 1.0f, -sinus,
													  sinus, 0.0f, -cosinus);
			m_vertices[3+4*i] = irr::video::S3DVertexTangents(x_0_3, hY, z_0_3, 
													  cosinus, -1.0f, sinus, 
													  vertexColor,
													  t, o + t * (float)i,
													  -cosinus, -1.0f, sinus,
													  sinus, 0.0f, -cosinus);
		}
	}
	else if (m_direction == D_RIGHT)
	{
		irr::f32 x_0_3, x_1_2, z_0_3, z_1_2;
		
		for (irr::u8 i = 0; i < m_sectionCount + 1; i++)
		{
			cosinus = cos(m_sectionAngle * i);
			sinus = sin(m_sectionAngle * i);
			x_0_3 = -wideRadius * cosinus + m_radius;
			x_1_2 =	-shortRadius * cosinus + m_radius;
			z_0_3 = wideRadius * sinus;
			z_1_2 =	shortRadius * sinus;

			m_vertices[0+4*i] = irr::video::S3DVertexTangents(x_0_3, -hY, z_0_3, 
													  cosinus, 1.0f, -sinus, 
													  vertexColor,
													  o, o + t * (float)i,
													  cosinus, -1.0f, -sinus,
													  -sinus, 0.0f, -cosinus);
			m_vertices[1+4*i] = irr::video::S3DVertexTangents(x_1_2, -hY, z_1_2,
													  -cosinus, 1.0f, sinus, 
													  vertexColor,
													  t, o + t * (float)i,
													  cosinus, 1.0f, sinus,
													  -sinus, 0.0f, -cosinus);
			m_vertices[2+4*i] = irr::video::S3DVertexTangents(x_1_2, hY, z_1_2, 
													  -cosinus, -1.0f, sinus, 
													  vertexColor,
													  2 * t, o + t * (float)i,
													  -cosinus, 1.0f, sinus,
													  -sinus, 0.0f, -cosinus);
			m_vertices[3+4*i] = irr::video::S3DVertexTangents(x_0_3, hY, z_0_3, 
													  cosinus, -1.0f, -sinus, 
													  vertexColor,
													  t, o + t * (float)i,
													  -cosinus, -1.0f, -sinus,
													  -sinus, 0.0f, -cosinus);		
		}
	}
	else if (m_direction == D_DOWN)
	{
		irr::f32 y_0_1, y_2_3, z_1_2, z_3_4;

		for (irr::u8 i = 0; i < m_sectionCount + 1; i++)
		{
			cosinus = cos(m_sectionAngle * i);
			sinus = sin(m_sectionAngle * i);
			wideRadius = m_radius + hY;
			shortRadius = m_radius - hY;

			y_0_1 = shortRadius * cosinus - m_radius;
			y_2_3 = wideRadius * cosinus - m_radius;
			z_1_2 = shortRadius * sinus;
			z_3_4 = wideRadius * sinus;

			m_vertices[0+4*i] = irr::video::S3DVertexTangents(-hX, y_0_1, z_1_2, 
													  1.0f, cosinus, sinus, 
													  vertexColor,
													  o, o + t * (float)i,
													  1.0f, -cosinus, -sinus,
													  0.0f, sinus, -cosinus);
			m_vertices[1+4*i] = irr::video::S3DVertexTangents(hX, y_0_1, z_1_2, 
													  -1.0f, cosinus, sinus, 
													  vertexColor,
													  t, o + t * (float)i,
													  1.0f, cosinus, sinus,
													  0.0f, sinus, -cosinus);
			m_vertices[2+4*i] = irr::video::S3DVertexTangents(hX, y_2_3, z_3_4, 
													  -1.0f, -cosinus, -sinus,
													  vertexColor,
													  2 * t, o + t * (float)i,
													  -1.0f, cosinus, sinus,
													  0.0f, sinus, -cosinus);
			m_vertices[3+4*i] = irr::video::S3DVertexTangents(-hX, y_2_3, z_3_4, 
													  1.0f, -cosinus, -sinus,
													  vertexColor,
													  t, o + t * (float)i,
													  -1.0f, -cosinus, -sinus,
													  0.0f, sinus, -cosinus);
		}
	}
	else if(m_direction == D_UP)
	{
		irr::f32 y_0_1, y_2_3, z_1_2, z_3_4;

		for (irr::u8 i = 0; i < m_sectionCount + 1; i++)
		{
			cosinus = cos(m_sectionAngle * i);
			sinus = sin(m_sectionAngle * i);
			wideRadius = m_radius + hY;
			shortRadius = m_radius - hY;

			y_0_1 = -wideRadius * cosinus + m_radius;
			y_2_3 = -shortRadius * cosinus + m_radius;
			z_1_2 = wideRadius * sinus;
			z_3_4 = shortRadius * sinus;

			m_vertices[0+4*i] = irr::video::S3DVertexTangents(-hX, y_0_1, z_1_2, 
													  1.0f, cosinus, -sinus, 
													  vertexColor,
													  o, o + t * (float)i,
													  1.0f, -cosinus, sinus,
													  0.0f, -sinus, -cosinus);
			m_vertices[1+4*i] = irr::video::S3DVertexTangents(hX, y_0_1, z_1_2, 
													  -1.0f, cosinus, -sinus, 
													  vertexColor,
													  t, o + t * (float)i,
													  1.0f, cosinus, -sinus,
													  0.0f, -sinus, -cosinus);
			m_vertices[2+4*i] = irr::video::S3DVertexTangents(hX, y_2_3, z_3_4, 
													  -1.0f, -cosinus, sinus,
													  vertexColor,
													  2 * t, o + t * (float)i,
													  -1.0f, cosinus, -sinus,
													  0.0f, -sinus, -cosinus);
			m_vertices[3+4*i] = irr::video::S3DVertexTangents(-hX, y_2_3, z_3_4, 
													  1.0f, -cosinus, sinus,
													  vertexColor,
													  t, o + t * (float)i,
													  -1.0f, -cosinus, sinus,
													  0.0f, -sinus, -cosinus);
		}
	}

	// create indices
	for (irr::u8 i = 0; i < 4 * m_sectionCount; i++)
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

void CurveRoomSceneNode::OnRegisterSceneNode()
{
	if (IsVisible)
		SceneManager->registerNodeForRendering(this);

	ISceneNode::OnRegisterSceneNode();
}

void CurveRoomSceneNode::render()
{
	irr::video::IVideoDriver* driver = SceneManager->getVideoDriver();

	if (!driver)
		return;

	driver->setTransform(irr::video::ETS_WORLD, AbsoluteTransformation);
	driver->setMaterial(m_material);
	driver->drawIndexedTriangleList(m_vertices, m_verticesCount, m_indices, 8 * m_sectionCount);
}

const irr::core::aabbox3d<irr::f32>& CurveRoomSceneNode::getBoundingBox() const
{
	return m_box;
}

irr::u32 CurveRoomSceneNode::getMaterialCount() const
{
	return 1;
}

irr::video::SMaterial& CurveRoomSceneNode::getMaterial(irr::u32 i)
{
	return m_material;
}

irr::u32 CurveRoomSceneNode::getVertexCount() const
{
	return m_verticesCount;
}

const irr::video::S3DVertexTangents* CurveRoomSceneNode::getVertices() const
{
	return m_vertices;
}