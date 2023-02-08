#include "Collision.h"

bool Collision::CheckRay2Plane(const Ray& ray, Ray& nextRay, const Plane& plane, float* distance)
{
	const float epsilon = 1.0e-5f;//�덷�z���p�̔����Ȓl
	//�ʖ@���ƃ��C�̕����x�N�g��
	float d1 = plane.normal.x * ray.dir.x + plane.normal.y * ray.dir.y + plane.normal.z * ray.dir.z;
	//���ʂ͓�����Ȃ�
	if (d1 > -epsilon) { return false; }
	//�n�_�ƌ��_�̋����i���ʂ̖@�������j
	//�ʖ@���ƃ��C�̎n�_���W�i�ʒu�x�N�g���j�̓���
	float d2 = plane.normal.x * ray.start.x + plane.normal.y * ray.start.y + plane.normal.z * ray.start.z;
	//�n�_�ƕ��ʂ̋����i���ʂ̖@�������j
	float dist = d2 - plane.distance;
	//�n�_�ƕ��ʂ̋����i���C�����j
	float t = dist / -d1;
	//��_���n�_�����ɂ���̂œ�����Ȃ�
	if (t < 0)return false;
	//��_���W�v�Z
	Vector3 inter_ = ray.start + t * ray.dir;

	//���Ƃ�苗�����߂���Ώ�������
	if (*distance > t) {
		if (inter_.x >= plane.pos.x - (plane.size.x + 0.1f) && inter_.x <= plane.pos.x + (plane.size.x + 0.1f)) {
			if (inter_.y >= plane.pos.y - (plane.size.y + 0.1f) && inter_.y <= plane.pos.y + (plane.size.y + 0.1f)) {
				if (inter_.z >= plane.pos.z - (plane.size.z + 0.1f) && inter_.z <= plane.pos.z + (plane.size.z + 0.1f)) {

					*distance = t;

					//��_���v�Z
					nextRay.start = inter_;

					//���C�𔽎˂�����
					nextRay.dir = ray.dir + 2 * (-d1) * plane.normal;


					nextRay.dir.nomalize();

					nextRay.isReflection = false;
					return true;
				}
			}
		}
	}

	return false;
}

bool Collision::CheckRay2Mirror(const Ray& ray, Ray& nextRay, const Plane& plane, float* distance)
{
	const float epsilon = 1.0e-5f;//�덷�z���p�̔����Ȓl
	//�ʖ@���ƃ��C�̕����x�N�g��
	float d1 = plane.normal.x * ray.dir.x + plane.normal.y * ray.dir.y + plane.normal.z * ray.dir.z;
	//���ʂ͓�����Ȃ�
	if (d1 > -epsilon) { return false; }
	//�n�_�ƌ��_�̋����i���ʂ̖@�������j
	//�ʖ@���ƃ��C�̎n�_���W�i�ʒu�x�N�g���j�̓���
	float d2 = plane.normal.x * ray.start.x + plane.normal.y * ray.start.y + plane.normal.z * ray.start.z;
	//�n�_�ƕ��ʂ̋����i���ʂ̖@�������j
	float dist = d2 - plane.distance;
	//�n�_�ƕ��ʂ̋����i���C�����j
	float t = dist / -d1;
	//��_���n�_�����ɂ���̂œ�����Ȃ�
	if (t < 0)return false;
	//��_���W�v�Z
	Vector3 inter_= ray.start + t * ray.dir;

	//���Ƃ�苗�����߂���Ώ�������
	if (*distance > t) {
		if (inter_.x >= plane.pos.x - (plane.size.x + 0.1f) && inter_.x <= plane.pos.x + (plane.size.x + 0.1f)) {
			if (inter_.y >= plane.pos.y - (plane.size.y + 0.1f) && inter_.y <= plane.pos.y + (plane.size.y + 0.1f)) {
				if (inter_.z >= plane.pos.z - (plane.size.z + 0.1f) && inter_.z <= plane.pos.z + (plane.size.z + 0.1f)) {

					*distance = t;

					//��_���v�Z
					nextRay.start = inter_;

					//���C�𔽎˂�����
					nextRay.dir = ray.dir + 2 * (-d1) * plane.normal;


					nextRay.dir.nomalize();

					nextRay.isReflection = true;
				}
			}
		}
	}

	return true;
}