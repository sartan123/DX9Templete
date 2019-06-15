texture tex;

sampler smp = sampler_state {
	texture = <tex>;
};

struct VS_IN {
	float3 pos : POSITION;
	float2 uv : TEXCOORD0;

};

struct VS_OUT {
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
};

float4 main(VS_OUT In) : COLOR0{
	return tex2D(smp, In.uv);
}
