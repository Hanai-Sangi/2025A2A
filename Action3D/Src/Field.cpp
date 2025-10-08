#include "Field.h"

Field::Field()
{
	mesh = new CFbxMesh();
	mesh->Load("Data/Map/map50Field1.mesh");
}

Field::~Field()
{
}

void Field::Update()
{
}
