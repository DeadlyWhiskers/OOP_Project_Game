

#include "CC_Enemy.h"

#include "CC_BulletParent.h"

ACC_Enemy::ACC_Enemy() {
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACC_Enemy::OnOverlapEnemy);
}