#include "LoadJson.h"
std::string defaultPath = "Resources/json/";

void LoadJson::LoadFromJson(int stage,std::string fileName) {
	std::string fullPath = defaultPath + fileName;
	std::ifstream reading(fullPath, std::ios::in);
	reading >> j;
	reading.close();
	std::string stageStr = "1";
	switch (stage)
	{
	case 1:
		stageStr = "1";
		break;
	case 2:
		stageStr = "2";
		break;
	case 3:
		stageStr = "3";
		break;
	case 4:
		stageStr = "4";
		break;

	default:
		break;
	}
	

	for (json::iterator i = j[stageStr].begin(); i != j[stageStr].end(); ++i)
	{
		if (i.key() == "pos")
		{
			int num = vec3::x;//xyz���ꂼ��Ɋi�[���邽�߂̕ϐ�
			for (json::iterator pos = j[stageStr]["pos"].begin(); pos < j[stageStr]["pos"].end(); pos++)
			{
				//�l���i�[
				if (num== vec3::x)
				{
					//x���W
					trans_x.push_back(pos.value());
					num = vec3::y;
				}
				else if (num == vec3::y)
				{
					//y���W
					trans_y.push_back(pos.value());
					num = vec3::z;
				}
				else if (num == vec3::z)
				{
					//z���W
					trans_z.push_back(pos.value());
					num = vec3::x;
				}
			}
		}
		if (i.key() == "scale")
		{
			int num = vec3::x;//xyz���ꂼ��Ɋi�[���邽�߂̕ϐ�
			for (json::iterator pos = j[stageStr]["scale"].begin(); pos < j[stageStr]["scale"].end(); pos++)
			{
				//�l���i�[
				if (num == vec3::x)
				{
					//x���W
					scale_x.push_back(pos.value());
					num = vec3::y;
				}
				else if (num == vec3::y)
				{
					//y���W
					scale_y.push_back(pos.value());

					num = vec3::z;
				}
				else if (num == vec3::z)
				{
					//y���W
					scale_z.push_back(pos.value());
					num = vec3::x;
				}

			}
		}
	}

	//
	if (trans_x.size()== trans_y.size()&&trans_z.size() == trans_y.size()&&
		scale_x.size() == scale_y.size()&&scale_z.size() == scale_y.size()&&
		trans_x.size() ==scale_x.size())
	{
		for (size_t i = 0; i < trans_x.size(); i++)
		{
			WorldTransform matWorld_;
			matWorld_.initialize();
			matWorld_.translation = { trans_x[i],trans_y[i],trans_z[i]};
			matWorld_.scale = { scale_x[i],scale_y[i] ,scale_z[i] };
			worldTrans.push_back(matWorld_);
		}
	}
	

	
	/*if ()
	{

	}*/
}