#include"Block.h"
#include"Collision.h"


Block::Block() {

}

Block::~Block() {

}


void Block::Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection, WorldTransform& worldTransform) {
	obj = new GameObject3D();
	obj->PreLoadModel("Resources/tofu/tofu.obj");
	obj->PreLoadTexture(L"Resources/tofu/block.png");
	obj->SetViewProjection(viewProjection);
	obj->SetMatProjection(matProjection);
	obj->Initialize();
	obj->worldTransform = worldTransform;
	obj->worldTransform.UpdateMatWorld();

	//‘O
	frontPlane.normal = { 0, 0, 1 };

	frontPlane.distance = worldTransform.translation.z + worldTransform.scale.z;

	frontPlane.pos.x = worldTransform.translation.x;
	frontPlane.pos.y = worldTransform.translation.y;
	frontPlane.pos.z = worldTransform.translation.z + worldTransform.scale.z;

	frontPlane.size.x = worldTransform.scale.x;
	frontPlane.size.y = worldTransform.scale.y;
	frontPlane.size.z = 0;


	//Œã‚ë
	backPlane.normal = { 0, 0, -1 };

	backPlane.distance = -(worldTransform.translation.z - worldTransform.scale.z);

	backPlane.pos.x = worldTransform.translation.x;
	backPlane.pos.y = worldTransform.translation.y;
	backPlane.pos.z = worldTransform.translation.z - worldTransform.scale.z;

	backPlane.size.x = worldTransform.scale.x;
	backPlane.size.y = worldTransform.scale.y;
	backPlane.size.z = 0;


	//¶
	leftPlane.normal = { -1, 0, 0 };

	leftPlane.distance = -(worldTransform.translation.x - worldTransform.scale.x);

	leftPlane.pos.x = worldTransform.translation.x - worldTransform.scale.x;
	leftPlane.pos.y = worldTransform.translation.y;
	leftPlane.pos.z = worldTransform.translation.z;

	leftPlane.size.x = 0;
	leftPlane.size.y = worldTransform.scale.y;
	leftPlane.size.z = worldTransform.scale.z;

	//‰E
	rightPlane.normal = { 1, 0, 0 };

	rightPlane.distance = worldTransform.translation.x + worldTransform.scale.x;

	rightPlane.pos.x = worldTransform.translation.x + worldTransform.scale.x;
	rightPlane.pos.y = worldTransform.translation.y;
	rightPlane.pos.z = worldTransform.translation.z;

	rightPlane.size.x = 0;
	rightPlane.size.y = worldTransform.scale.y;
	rightPlane.size.z = worldTransform.scale.z;

	//ã
	upPlane.normal = { 0, 1, 0 };

	upPlane.distance = worldTransform.translation.y + worldTransform.scale.y;

	upPlane.pos.x = worldTransform.translation.x;
	upPlane.pos.y = worldTransform.translation.y + worldTransform.scale.y;
	upPlane.pos.z = worldTransform.translation.z;

	upPlane.size.x = worldTransform.scale.x;
	upPlane.size.y = 0;
	upPlane.size.z = worldTransform.scale.z;

	//‰º
	downPlane.normal = { 0, -1, 0 };

	downPlane.distance = -(worldTransform.translation.y - worldTransform.scale.y);

	downPlane.pos.x = worldTransform.translation.x;
	downPlane.pos.y = worldTransform.translation.y - worldTransform.scale.y;
	downPlane.pos.z = worldTransform.translation.z;

	downPlane.size.x = worldTransform.scale.x;
	downPlane.size.y = 0;
	downPlane.size.z = worldTransform.scale.z;

}

void Block::Update() {
	obj->Update();
}

void Block::CheckCollision(Ray* ray,int i,float* dis) {
	Collision::CheckRay2Plane(ray[i], ray[i + 1] , frontPlane, dis);
	Collision::CheckRay2Plane(ray[i], ray[i + 1], backPlane, dis);
	Collision::CheckRay2Plane(ray[i], ray[i + 1], leftPlane, dis);
	Collision::CheckRay2Plane(ray[i], ray[i + 1], rightPlane, dis);
	Collision::CheckRay2Plane(ray[i], ray[i + 1], upPlane, dis);
	Collision::CheckRay2Plane(ray[i], ray[i + 1], downPlane, dis);
}

void Block::Draw() {
	obj->Draw();
}