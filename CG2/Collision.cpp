#include "Collision.h"

bool Collision::CheckRay2Plane(const Ray& ray, Ray& nextRay, const Plane& plane, float* distance)
{
	const float epsilon = 1.0e-5f;//誤差吸収用の微小な値
	//面法線とレイの方向ベクトル
	float d1 = plane.normal.x * ray.dir.x + plane.normal.y * ray.dir.y + plane.normal.z * ray.dir.z;
	//裏面は当たらない
	if (d1 > -epsilon) { return false; }
	//始点と原点の距離（平面の法線方向）
	//面法線とレイの始点座標（位置ベクトル）の内積
	float d2 = plane.normal.x * ray.start.x + plane.normal.y * ray.start.y + plane.normal.z * ray.start.z;
	//始点と平面の距離（平面の法線方向）
	float dist = d2 - plane.distance;
	//始点と平面の距離（レイ方向）
	float t = dist / -d1;
	//交点が始点より後ろにあるので当たらない
	if (t < 0)return false;
	//交点座標計算
	Vector3 inter_ = ray.start + t * ray.dir;

	//もとより距離が近ければ書き込む
	if (*distance > t) {
		if (inter_.x >= plane.pos.x - (plane.size.x + 0.1f) && inter_.x <= plane.pos.x + (plane.size.x + 0.1f)) {
			if (inter_.y >= plane.pos.y - (plane.size.y + 0.1f) && inter_.y <= plane.pos.y + (plane.size.y + 0.1f)) {
				if (inter_.z >= plane.pos.z - (plane.size.z + 0.1f) && inter_.z <= plane.pos.z + (plane.size.z + 0.1f)) {

					*distance = t;

					//交点を計算
					nextRay.start = inter_;

					//レイを反射させる
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
	const float epsilon = 1.0e-5f;//誤差吸収用の微小な値
	//面法線とレイの方向ベクトル
	float d1 = plane.normal.x * ray.dir.x + plane.normal.y * ray.dir.y + plane.normal.z * ray.dir.z;
	//裏面は当たらない
	if (d1 > -epsilon) { return false; }
	//始点と原点の距離（平面の法線方向）
	//面法線とレイの始点座標（位置ベクトル）の内積
	float d2 = plane.normal.x * ray.start.x + plane.normal.y * ray.start.y + plane.normal.z * ray.start.z;
	//始点と平面の距離（平面の法線方向）
	float dist = d2 - plane.distance;
	//始点と平面の距離（レイ方向）
	float t = dist / -d1;
	//交点が始点より後ろにあるので当たらない
	if (t < 0)return false;
	//交点座標計算
	Vector3 inter_= ray.start + t * ray.dir;

	//もとより距離が近ければ書き込む
	if (*distance > t) {
		if (inter_.x >= plane.pos.x - (plane.size.x + 0.1f) && inter_.x <= plane.pos.x + (plane.size.x + 0.1f)) {
			if (inter_.y >= plane.pos.y - (plane.size.y + 0.1f) && inter_.y <= plane.pos.y + (plane.size.y + 0.1f)) {
				if (inter_.z >= plane.pos.z - (plane.size.z + 0.1f) && inter_.z <= plane.pos.z + (plane.size.z + 0.1f)) {

					*distance = t;

					//交点を計算
					nextRay.start = inter_;

					//レイを反射させる
					nextRay.dir = ray.dir + 2 * (-d1) * plane.normal;


					nextRay.dir.nomalize();

					nextRay.isReflection = true;
				}
			}
		}
	}

	return true;
}