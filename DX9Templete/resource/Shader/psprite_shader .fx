//------------------------------------------------
// グローバル変数
//------------------------------------------------
float4x4 	g_world;
float4x4 	g_viewing;
float4x4 	g_projection;
float		g_time;
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
	float in_size : PSIZE,
	float3 in_dir : TEXCOORD0,
	float in_life : TEXCOORD1,
	float in_start : TEXCOORD2,
	out float4 out_pos : POSITION,
	out float2 out_tex : TEXCOORD0,
	out float out_size : PSIZE)
{
	// 時間の計測
	float time = g_time - in_start;

	// アニメーションの繰返しを考慮する
	time = fmod(time, in_life);

	// 重力
	float3 accel = float3(0.0, -9.8, 0.0);

	// ポイントスプライトの位置計算
	float3 pos;
	pos = in_pos + in_dir * time + 0.5*accel*time*time;

	// ワールド変換
	out_pos = mul(float4(pos, 1.0f), g_world);

	// ビューイング変換
	out_pos = mul(out_pos, g_viewing);

	// プロジェクション変換
	out_pos = mul(out_pos, g_projection);

	// 頂点の色の決定
	out_size = in_size;

	// テクスチャ座標はコピーするだけ
	out_tex = 0.0;

}

//------------------------------------------------
// ピクセルシェーダ
//------------------------------------------------
void BasicPS(float2 in_tex : TEXCOORD0,
	out float4 out_color : COLOR0)
{
	// 色の出力
	out_color = tex2D(TextureSampler, in_tex);
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

		PointSpriteEnable = TRUE;
		PointScaleEnable = TRUE;
		PointSize_MIN = 0.0;
		PointScale_A = 0.0;
		PointScale_B = 0.0;
		PointScale_C = 1.0;

		ALPHABLENDENABLE = TRUE;
		SRCBLEND = ONE;
		DESTBLEND = ONE;
		ZWRITEENABLE = FALSE;
	}
}
