cbuffer ConstantBuffer{
    float4x4 WVP;
	float4x4 World;  
	float4x4 WorldView;
}

struct VS_OUTPUT{
    float4 hposition : SV_POSITION;
	float4 hnormal : NORMAL;
    float2 texture0  : TEXCOORD;
};

float4 FS( VS_OUTPUT input ) : SV_TARGET {
	return float4(input.hnormal.xyz,1.0);
}

