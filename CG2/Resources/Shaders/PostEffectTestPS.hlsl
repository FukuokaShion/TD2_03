#include "PostEffectTest.hlsli"

Texture2D<float4> tex0 : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

Texture2D<float4> tex1 : register(t1);

float4 main(VSOutput input) : SV_TARGET
{
	float4 texcolor = tex1.Sample(smp,input.uv);

	return float4(texcolor.rgb,1);
}

//float4 main(VSOutput input) : SV_TARGET
//{
//	float4 colortex0 = tex0.Sample(smp, input.uv);
//	float4 colortex1 = tex1.Sample(smp, input.uv);
//	
//	float4 color = colortex0;
//	if (fmod(input.uv.y, 0.1f) < 0.05f) {
//		color = colortex1;
//	}
//
//	return float4(color.rgb,1 );
//
//}


//float WhiteNoise(float2 coord) {
//	return frac(sin(dot(coord, float2(8.7819, 3.255))) * 437.645);
//}

//float4 main(VSOutput input) : SV_TARGET
//{
//
//	float4 samplePoint = tex0.Sample(smp, input.uv);
//	float4 Tex = tex1.Sample(mainSampler, input.uv);
//	float noise = WhiteNoise(pixel.uv * Time) - 0.5;
//	Tex.rgb += float3(noise, noise, noise);
//	return Tex;
//}