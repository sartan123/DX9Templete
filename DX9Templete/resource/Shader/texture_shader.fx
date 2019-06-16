//------------------------------------------------
// グローバル変数
//------------------------------------------------
float4x4 	g_world;
float4x4 	g_viewing;
float4x4 	g_projection;

float4		g_color;
texture 	g_texture;

//------------------------------------------------
// テクスチャサンプラ
//------------------------------------------------
sampler TextureSampler =
sampler_state
{
	Texture = <g_texture>;
};

//------------------------------------------------
// 頂点シェーダ
//------------------------------------------------
void BasicVS(float3 in_pos : POSITION,
	float2 in_tex : TEXCOORD0,
	out float4 out_pos : POSITION,
	out float4 out_color : COLOR0,
	out float2 out_tex : TEXCOORD0)
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
	out_tex = in_tex;

}

//------------------------------------------------
// ピクセルシェーダ
//------------------------------------------------
void BasicPS(float4 in_color : COLOR0,
	float4 in_tex : TEXCOORD0,
	out float4 out_color : COLOR0)
{
	// 色の出力
	out_color = tex2D(TextureSampler, in_tex) + in_color;
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
