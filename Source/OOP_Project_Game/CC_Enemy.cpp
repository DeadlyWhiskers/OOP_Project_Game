
#include "CC_Enemy.h"

#include "CC_BulletParent.h"

ACC_Enemy::ACC_Enemy() {
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");
}

void ACC_Enemy::Attack()
{
	return;
}
