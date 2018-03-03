cbuffer ConstantBuffer{
    float4x4 WVP;
	float4x4 World;  
	float4x4 WorldView;
}

struct VS_OUTPUT{
    float4 hposition : SV_POSITION;
    float2 texture0  : TEXCOORD;
};

float4 FS( VS_OUTPUT input ) : SV_TARGET {
	return float4(1.0,1.0,0.0,1.0);
}

