#ifndef PHYSICS_H
#define PHYSICS_H

#include <d3dx9.h>
#include "btBulletDynamicsCommon.h"

D3DXVECTOR3 BT2DX_VECTOR3(const btVector3 &v)
{
	return D3DXVECTOR3(v.x(), v.y(), v.z());
}

D3DXQUATERNION BT2DX_QUATERNION(const btQuaternion &q)
{
	return D3DXQUATERNION(q.x(), q.y(), q.z(), q.w());
}



D3DXMATRIX BT2DX_MATRIX(const btTransform &ms)
{
	btQuaternion q = ms.getRotation();
	btVector3 p = ms.getOrigin();

	D3DXMATRIX pos, rot, world;
	D3DXMatrixTranslation(&pos, p.x(), p.y(), p.z());
	D3DXMatrixRotationQuaternion(&rot, &BT2DX_QUATERNION(q));
	D3DXMatrixMultiply(&world, &rot, &pos);

	return world;
}

D3DXMATRIX BT2DX_MATRIX(const btMotionState &ms)
{
	btTransform world;
	ms.getWorldTransform(world);
	return BT2DX_MATRIX(world);
}
#endif