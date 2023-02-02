#pragma once
#include"nlohmann/json.hpp"
#include<vector>
#include<memory>
#include"Vector3.h"
#include"WorldTransform.h"
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<DirectXMath.h>

using json = nlohmann::json;
using namespace DirectX;

class LoadJson
{
public:
	void LoadFromJson(int stage,std::string fileName);
	std::vector<WorldTransform>worldTrans;

private:
	std::vector<float> trans_x;
	std::vector<float> trans_y;
	std::vector<float> trans_z;

	std::vector<float> scale_x;
	std::vector<float> scale_y;
	std::vector<float> scale_z;


	enum vec3
	{
		x,
		y,
		z
	};
};

