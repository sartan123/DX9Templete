//------------------------------------------------
// グローバル変数
//------------------------------------------------
float4x4 	g_world;
float4x4 	g_viewing;
float4x4 	g_projection;

float4		g_color;
texture 	g_texture0;
texture 	g_texture1;

//------------------------------------------------
// テクスチャサンプラ
//------------------------------------------------
sampler TextureSampler0 =
sampler_state
{
	Texture = <g_texture0>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

sampler TextureSampler1 =
sampler_state
{
	Texture = <g_texture1>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

//------------------------------------------------
// 頂点シェーダ
//------------------------------------------------
void BasicVS(float3 in_pos : POSITION,
	float2 in_tex0 : TEXCOORD0,
	float2 in_tex1 : TEXCOORD0,
	out float4 out_pos : POSITION,
	out float4 out_color : COLOR0,
	out float2 out_tex0 : TEXCOORD0,
	out float2 out_tex1 : TEXCOORD1)
{
	// ワールド変換
	out_pos = mul(float4(in_pos, 1.0f), g_world);

	// ビューイング変換
	out_pos = mul(out_pos, g_viewing);

	// プロジェクション変換
	out_pos = mul(out_pos, g_projection);

	// 頂点の色の決定
	out_color = g_color;

	// テクスチャ座標はコピーするだけ
	out_tex0 = in_tex0;
	out_tex1 = in_tex1;

}

//------------------------------------------------
// ピクセルシェーダ
//------------------------------------------------
void BasicPS(float4 in_color : COLOR0,
	float4 in_tex0 : TEXCOORD0,
	float4 in_tex1 : TEXCOORD1,
	out float4 out_color : COLOR0)
{
	// 色の出力
	out_color = tex2D(TextureSampler0, in_tex0) * tex2D(TextureSampler1, in_tex1);
}

//------------------------------------------------
// テクニック宣言
//------------------------------------------------
technique BasicTech
{
	pass P0
	{
		vertexShader = compile vs_3_0 BasicVS();
		pixelShader = compile ps_3_0 BasicPS();
	}
}
