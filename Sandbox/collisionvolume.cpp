#include "collisionvolume.h"

using namespace component;

CollisionVolume::CollisionVolume(Entity& entity)
	: Component(entity)
{}

CollisionVolume::~CollisionVolume() = default;
