//Author Oleh Havryliuk 07.2015

#include "CurveRoomSceneNode.h"

CurveRoomSceneNode::CurveRoomSceneNode(irr::scene::ISceneNode* parent, 
										irr::scene::ISceneManager* mgr,
										DIRECTION direction,
										irr::f32 angle,
										irr::f32 radius,
										irr::u8 sectionCount,
										irr::s32 id,
										irr::video::ITexture* texture,
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
	m_material.Lighting = true;
	//m_material.ZBuffer = irr::video::ECFN_NEVER;
	//m_material.ZWriteEnable = false;
	m_material.AntiAliasing = ANTIALIASING;
	m_material.setTexture(0, texture);
	m_material.TextureLayer[0].TextureWrapU = irr::video::ETC_REPEAT;
	m_material.TextureLayer[0].TextureWrapV = irr::video::ETC_REPEAT;


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
	irr::f32 sign = 1.0f;
	irr::f32 sinus, cosinus, wideRadius, shortRadius;
	irr::video::SColor vertexColor = irr::video::SColor(255,255,255,255);
	irr::video::S3DVertex swapVertex;

	if (m_direction == D_RIGHT || m_direction == D_LEFT)
	{
		sign = (m_direction == D_RIGHT) ? -1.0f : 1.0f;
		irr::f32 x_0_3, x_1_2, z_0_3, z_1_2;

		for (irr::s32 i = 0; i < m_sectionCount + 1; i++)
		{
			cosinus = cos(m_sectionAngle * i);
			sinus = sin(m_sectionAngle * i);
			wideRadius = m_radius + hX;
			shortRadius = m_radius - hX;

			x_0_3 = sign * (shortRadius * cosinus - m_radius);
			x_1_2 =	sign * (wideRadius * cosinus - m_radius);
			z_0_3 = shortRadius * sinus;
			z_1_2 =	wideRadius * sinus;

			m_vertices[0+4*i] = irr::video::S3DVertex(x_0_3,
													  -hY,
													  z_0_3, 
													  sign * cosinus, 1.0f, sinus, 
													  vertexColor,
													  o, o + t * (float)i);
			m_vertices[1+4*i] = irr::video::S3DVertex(x_1_2,
													  -hY,
													  z_1_2,
													  -sign * cosinus, 1.0f, -sinus, 
													  vertexColor,
													  t, o + t * (float)i);
			m_vertices[2+4*i] = irr::video::S3DVertex(x_1_2,
													  hY,
													  z_1_2, 
													  -sign * cosinus, -1.0f, -sinus, 
													  vertexColor,
													  2 * t, o + t * (float)i);
			m_vertices[3+4*i] = irr::video::S3DVertex(x_0_3,
													  hY,
													  z_0_3, 
													  sign * cosinus, -1.0f, sinus, 
													  vertexColor,
													  //3 * t, o + t * (float)i);
													  t, o + t * (float)i);

			if (m_direction == D_RIGHT)
			{
				swapVertex = m_vertices[0+4*i];
				m_vertices[0+4*i].Pos = m_vertices[1+4*i].Pos;
				m_vertices[0+4*i].Normal = m_vertices[1+4*i].Normal;
				m_vertices[0+4*i].Color = m_vertices[1+4*i].Color;
				m_vertices[1+4*i].Pos = swapVertex.Pos;
				m_vertices[1+4*i].Normal = swapVertex.Normal;
				m_vertices[1+4*i].Color = swapVertex.Color;

				swapVertex = m_vertices[2+4*i];
				m_vertices[2+4*i].Pos = m_vertices[3+4*i].Pos;
				m_vertices[2+4*i].Normal = m_vertices[3+4*i].Normal;
				m_vertices[2+4*i].Color = m_vertices[3+4*i].Color;
				m_vertices[3+4*i].Pos = swapVertex.Pos;
				m_vertices[3+4*i].Normal = swapVertex.Normal;
				m_vertices[3+4*i].Color = swapVertex.Color;
			}
		}
	}
	else
	{
		sign = (m_direction == D_UP) ? -1.0f : 1.0f;
		irr::f32 y_1_2, y_3_4, z_1_2, z_3_4;

		for (irr::s32 i = 0; i < m_sectionCount + 1; i++)
		{
			cosinus = cos(m_sectionAngle * i);
			sinus = sin(m_sectionAngle * i);
			wideRadius = m_radius + hY;
			shortRadius = m_radius - hY;

			y_1_2 = sign * (shortRadius * cosinus - m_radius);
			y_3_4 = sign * (wideRadius * cosinus - m_radius);
			z_1_2 = shortRadius * sinus;
			z_3_4 = wideRadius * sinus;

			m_vertices[0+4*i] = irr::video::S3DVertex(-hX,
													  y_1_2,
													  z_1_2, 
													  1.0f, cosinus, sign * sinus, 
													  vertexColor,
													  o, o + t * (float)i);
			m_vertices[1+4*i] = irr::video::S3DVertex(hX,
													  y_1_2,
													  z_1_2, 
													  -1.0f, cosinus, sign * sinus, 
													  vertexColor,
													  t, o + t * (float)i);
			m_vertices[2+4*i] = irr::video::S3DVertex(hX,
													  y_3_4,
													  z_3_4, 
													  -1.0f, -cosinus, -sign * sinus,
													  vertexColor,
													  2 * t, o + t * (float)i);
			m_vertices[3+4*i] = irr::video::S3DVertex(-hX,
													  y_3_4,
													  z_3_4, 
													  1.0f, -cosinus, -sign * sinus,
													  vertexColor,
													  //3 * t, o + t * (float)i);
													  t, o + t * (float)i);
			if (m_direction == D_UP)
			{
				swapVertex = m_vertices[0+4*i];
				m_vertices[0+4*i].Pos = m_vertices[3+4*i].Pos;
				m_vertices[0+4*i].Color = m_vertices[3+4*i].Color;
				m_vertices[3+4*i].Pos = swapVertex.Pos;
				m_vertices[3+4*i].Color = swapVertex.Color;

				swapVertex = m_vertices[2+4*i];
				m_vertices[2+4*i].Pos = m_vertices[1+4*i].Pos;
				m_vertices[2+4*i].Color = m_vertices[1+4*i].Color;
				m_vertices[1+4*i].Pos = swapVertex.Pos;
				m_vertices[1+4*i].Color = swapVertex.Color;
			}
		}
	}

	// create indices
	for (irr::s32 i = 0; i < 4 * m_sectionCount; i++)
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