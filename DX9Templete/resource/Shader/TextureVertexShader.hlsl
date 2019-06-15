texture tex;

sampler smp = sampler_state {
	texture = <tex>;
};

struct VS_INPUT
{
	float3  pos : POSITION;
	float2 uv : TEXCOORD0;
};
struct VS_OUTPUT
{
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
};

matrix mtxWVP : register(c0);
VS_OUTPUT main(VS_INPUT _In){
	VS_OUTPUT Out = (VS_OUTPUT)0;

	Out.pos = mul(float4(_In.pos, 1.0f), mtxWVP);
	Out.uv = _In.uv;

	return Out;
}