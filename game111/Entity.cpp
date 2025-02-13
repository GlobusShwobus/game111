#include "Entity.h"

void Entity::Draw(SDL_Renderer* renderer)const {
	SDL_RenderTexture(renderer, texture, &bb, &bb);
}
EntityType Entity::GetType()const {
	return type;
}
int Entity::GetID()const {
	return ID;
}
const SDL_FRect Entity::GetBoundingBox()const {
	return bb;
}
void Entity::Kill() {
	isActive = false;
}
bool Entity::IsActive()const {
	return isActive;
}
vec2f Entity::GetPosition()const {
	return { bb.x, bb.y };
}