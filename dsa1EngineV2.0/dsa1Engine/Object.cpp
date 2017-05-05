#include "Object.h"


Object::Object()
{
	tag = "";
}


Object::~Object()
{
}

void Object::Render()
{
	printf("Rendering %s", &tag[0]);
}
