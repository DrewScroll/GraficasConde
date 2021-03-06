cbuffer ConstantBuffer{
    float4x4 WVP;
	float4x4 World;  
	float4x4 WorldView;
}

struct VS_INPUT{
    float4 position : POSITION;
	float4 normal : NORMAL;
    float2 texture0 : TEXCOORD;
};

struct VS_OUTPUT{
    float4 hposition : SV_POSITION;
	float4 hnormal : NORMAL;
    float2 texture0  : TEXCOORD;
};

VS_OUTPUT VS( VS_INPUT input ){
    VS_OUTPUT OUT;
    OUT.hposition = mul( WVP, input.position);
	OUT.hnormal = input.normal;
    OUT.texture0  = input.texture0;
	return OUT;
}
