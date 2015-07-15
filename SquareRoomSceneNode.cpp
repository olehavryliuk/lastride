//Author Oleh Havryliuk 07.2015
#include "SquareRoomSceneNode.h"

SquareRoomSceneNode::SquareRoomSceneNode(irr::scene::ISceneNode* parent, 
					 irr::scene::ISceneManager* mgr,
					 irr::s32 id,
					 irr::video::ITexture* texture,
					 const irr::core::vector3df& halfSize,
					 const irr::core::vector3df& position,
					 const irr::core::vector3df& rotation,
					 const irr::core::vector3df& scale) :
					 irr::scene::ISceneNode(parent, mgr, id, position, rotation, scale)
{
	setAutomaticCulling(irr::scene::EAC_OFF);
	m_box.MaxEdge.set(0,0,0);
	m_box.MinEdge.set(0,0,0);

	// create indices

	m_indices[0] = 0;
	m_indices[1] = 1;
	m_indices[2] = 2;
	m_indices[3] = 3;

	// create m_material

	irr::video::SMaterial mat;
	mat.Lighting = true;
	//mat.ZBuffer = irr::video::ECFN_NEVER;
	//mat.ZWriteEnable = false;
	mat.AntiAliasing=0;
	mat.TextureLayer[0].TextureWrapU = irr::video::ETC_CLAMP_TO_EDGE;
	mat.TextureLayer[0].TextureWrapV = irr::video::ETC_CLAMP_TO_EDGE;

	/* 
       -314         314
          /4--------/7        y
         /  |      / |        ^  z
        /   |   31-4 |        | /
  -31-4 5---------6  |        |/
        |   1- - -| 3-14    *---->x
        | -3-14   |  /       1-------|2
        |/        | /         |    //|
        0---------3/          |  //  |
     -3-1-4     3-1-4         |//    |
	                     0--------3
	*/

	const irr::f32 hX = halfSize.X;
	const irr::f32 hY = halfSize.Y;
	const irr::f32 hZ = halfSize.Z;

	const irr::f32 t = 1.0f; //- onepixel;
	const irr::f32 o = 0.0f; //+ onepixel;

	// create bottom side

	m_material[0] = mat;
	m_material[0].setTexture(0, texture);
	m_vertices[0] = irr::video::S3DVertex(-hX,-hY,-hZ, 1,1,0, irr::video::SColor(255,255,255,255), o, o);
	m_vertices[1] = irr::video::S3DVertex(-hX,-hY, hZ, 1,1,0, irr::video::SColor(255,255,255,255), o, t);
	m_vertices[2] = irr::video::S3DVertex( hX,-hY, hZ,-1,1,0, irr::video::SColor(255,255,255,255), t, t);
	m_vertices[3] = irr::video::S3DVertex( hX,-hY,-hZ,-1,1,0, irr::video::SColor(255,255,255,255), t, o);

	// create left side

	//m_material[1] = mat;
	//m_material[1].setTexture(0, texture);
	m_vertices[4] = irr::video::S3DVertex(-hX,-hY,-hZ,  1, 1,0, irr::video::SColor(255,255,255,255), t, o);
	m_vertices[5] = irr::video::S3DVertex(-hX, hY,-hZ,  1,-1,0, irr::video::SColor(255,255,255,255), o, o);
	m_vertices[6] = irr::video::S3DVertex(-hX, hY, hZ,  1,-1,0, irr::video::SColor(255,255,255,255), o, t);
	m_vertices[7] = irr::video::S3DVertex(-hX,-hY, hZ,  1, 1,0, irr::video::SColor(255,255,255,255), t, t);

	// create top side

	//m_material[2] = mat;
	//m_material[2].setTexture(0, texture);
	m_vertices[8]  = irr::video::S3DVertex(-hX, hY, hZ, 1,-1, 0, irr::video::SColor(255,255,255,255), t, t);
	m_vertices[9]  = irr::video::S3DVertex(-hX, hY,-hZ, 1,-1, 0, irr::video::SColor(255,255,255,255), t, o);
	m_vertices[10] = irr::video::S3DVertex( hX, hY,-hZ,-1,-1, 0, irr::video::SColor(255,255,255,255), o, o);
	m_vertices[11] = irr::video::S3DVertex( hX, hY, hZ,-1,-1, 0, irr::video::SColor(255,255,255,255), o, t);

	// create right side

	//m_material[3] = mat;
	//m_material[3].setTexture(0, texture);
	m_vertices[12] = irr::video::S3DVertex( hX,-hY, hZ, -1, 1,0, irr::video::SColor(255,255,255,255), o, t);
	m_vertices[13] = irr::video::S3DVertex( hX, hY, hZ, -1,-1,0, irr::video::SColor(255,255,255,255), t, t);
	m_vertices[14] = irr::video::S3DVertex( hX, hY,-hZ, -1,-1,0, irr::video::SColor(255,255,255,255), t, o);
	m_vertices[15] = irr::video::S3DVertex( hX,-hY,-hZ, -1, 1,0, irr::video::SColor(255,255,255,255), o, o);


	/*
	m_box.reset(m_vertices[0].Pos);
	for (irr::s32 i = 1; i < 12; ++i)
		m_box.addInternalPoint(m_vertices[i].Pos);	*/					 
}

SquareRoomSceneNode::SquareRoomSceneNode(irr::scene::ISceneNode* parent, 
					 irr::scene::ISceneManager* mgr,
					 irr::s32 id,
					 irr::video::ITexture* bottom,
					 irr::video::ITexture* left,
					 irr::video::ITexture* top,
					 irr::video::ITexture* right,
					 const irr::core::vector3df& halfSize,
					 const irr::core::vector3df& position,
					 const irr::core::vector3df& rotation,
					 const irr::core::vector3df& scale) :
					 irr::scene::ISceneNode(parent, mgr, id, position, rotation, scale)
{
	setAutomaticCulling(irr::scene::EAC_OFF);
	m_box.MaxEdge.set(0,0,0);
	m_box.MinEdge.set(0,0,0);

	// create indices

	m_indices[0] = 0;
	m_indices[1] = 1;
	m_indices[2] = 2;
	m_indices[3] = 3;

	// create m_material

	irr::video::SMaterial mat;
	mat.Lighting = true;
	//mat.ZBuffer = irr::video::ECFN_NEVER;
	//mat.ZWriteEnable = false;
	mat.AntiAliasing=0;
	mat.TextureLayer[0].TextureWrapU = irr::video::ETC_CLAMP_TO_EDGE;
	mat.TextureLayer[0].TextureWrapV = irr::video::ETC_CLAMP_TO_EDGE;

	/* 
       -314         314
          /4--------/7        y
         /  |      / |        ^  z
        /   |   31-4 |        | /
  -31-4 5---------6  |        |/
        |   1- - -| 3-14    *---->x
        | -3-14   |  /       1-------|2
        |/        | /         |    //|
        0---------3/          |  //  |
     -3-1-4     3-1-4         |//    |
	                     0--------3
	*/

	const irr::f32 hX = halfSize.X;
	const irr::f32 hY = halfSize.Y;
	const irr::f32 hZ = halfSize.Z;

	const irr::f32 t = 1.0f; //- onepixel;
	const irr::f32 o = 0.0f; //+ onepixel;

	// create bottom side

	m_material[0] = mat;
	m_material[0].setTexture(0, bottom);
	m_vertices[0] = irr::video::S3DVertex(-hX,-hY,-hZ, 1,1,0, irr::video::SColor(255,255,255,255), o, o);
	m_vertices[1] = irr::video::S3DVertex(-hX,-hY, hZ, 1,1,0, irr::video::SColor(255,255,255,255), o, t);
	m_vertices[2] = irr::video::S3DVertex( hX,-hY, hZ,-1,1,0, irr::video::SColor(255,255,255,255), t, t);
	m_vertices[3] = irr::video::S3DVertex( hX,-hY,-hZ,-1,1,0, irr::video::SColor(255,255,255,255), t, o);

	// create left side

	m_material[1] = mat;
	m_material[1].setTexture(0, left);
	m_vertices[4] = irr::video::S3DVertex(-hX,-hY,-hZ,  1, 1,0, irr::video::SColor(255,255,255,255), t, o);
	m_vertices[5] = irr::video::S3DVertex(-hX, hY,-hZ,  1,-1,0, irr::video::SColor(255,255,255,255), o, o);
	m_vertices[6] = irr::video::S3DVertex(-hX, hY, hZ,  1,-1,0, irr::video::SColor(255,255,255,255), o, t);
	m_vertices[7] = irr::video::S3DVertex(-hX,-hY, hZ,  1, 1,0, irr::video::SColor(255,255,255,255), t, t);

	// create top side

	m_material[2] = mat;
	m_material[2].setTexture(0, top);
	m_vertices[8]  = irr::video::S3DVertex(-hX, hY, hZ, 1,-1, 0, irr::video::SColor(255,255,255,255), t, t);
	m_vertices[9]  = irr::video::S3DVertex(-hX, hY,-hZ, 1,-1, 0, irr::video::SColor(255,255,255,255), t, o);
	m_vertices[10] = irr::video::S3DVertex( hX, hY,-hZ,-1,-1, 0, irr::video::SColor(255,255,255,255), o, o);
	m_vertices[11] = irr::video::S3DVertex( hX, hY, hZ,-1,-1, 0, irr::video::SColor(255,255,255,255), o, t);

	// create right side

	m_material[3] = mat;
	m_material[3].setTexture(0, right);
	m_vertices[12] = irr::video::S3DVertex( hX,-hY, hZ, -1, 1,0, irr::video::SColor(255,255,255,255), o, t);
	m_vertices[13] = irr::video::S3DVertex( hX, hY, hZ, -1,-1,0, irr::video::SColor(255,255,255,255), t, t);
	m_vertices[14] = irr::video::S3DVertex( hX, hY,-hZ, -1,-1,0, irr::video::SColor(255,255,255,255), t, o);
	m_vertices[15] = irr::video::S3DVertex( hX,-hY,-hZ, -1, 1,0, irr::video::SColor(255,255,255,255), o, o);


	/*
	m_box.reset(m_vertices[0].Pos);
	for (irr::s32 i = 1; i < 12; ++i)
		m_box.addInternalPoint(m_vertices[i].Pos);	*/					 
}

void SquareRoomSceneNode::OnRegisterSceneNode()
{
	if (IsVisible)
		SceneManager->registerNodeForRendering(this);

	ISceneNode::OnRegisterSceneNode();
}

void SquareRoomSceneNode::render()
{
	irr::video::IVideoDriver* driver = SceneManager->getVideoDriver();

	if (!driver)
		return;

	//irr::core::matrix4 translate(AbsoluteTransformation);

	//irr::core::matrix4 scale;
	//scale.setScale(irr::core::vector3df(200.0, 200.0, 200.0));

	driver->setTransform(irr::video::ETS_WORLD, AbsoluteTransformation);

	driver->setMaterial(m_material[0]);
	for (irr::s32 i=0; i<4; ++i)
	{
		//driver->setMaterial(m_material[i]);
		driver->drawIndexedTriangleFan(&m_vertices[i*4], 4, m_indices, 2);
	}
}

const irr::core::aabbox3d<irr::f32>& SquareRoomSceneNode::getBoundingBox() const
{
	return m_box;
}

irr::u32 SquareRoomSceneNode::getMaterialCount() const
{
	return 4;
}

irr::video::SMaterial& SquareRoomSceneNode::getMaterial(irr::u32 i)
{
	return m_material[i];
}