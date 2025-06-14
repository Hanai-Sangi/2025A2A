#include "Object3D.h"
#include "Animator.h"

Object3D::Object3D()
{
	animator = nullptr;
	mesh = nullptr;
}

Object3D::~Object3D()
{
	if (animator != nullptr) {
		delete animator;
		animator = nullptr;
	}
	if (mesh != nullptr) {
		delete mesh;
		mesh = nullptr;
	}
}

void Object3D::Update()
{
	if (animator != nullptr)
	{
		animator->Update();
	}
}

void Object3D::Draw()
{
	if (mesh == nullptr)  return;
	if (animator == nullptr)
	{
		mesh->Render(transform.matrix());
	}
	else {
		mesh->Render(animator, transform.matrix());
	}
}
