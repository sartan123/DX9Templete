//------------------------------------------------
// グローバル変数
//------------------------------------------------
float4x4 	g_world;
float4x4 	g_viewing;
float4x4 	g_projection;

//------------------------------------------------
// 頂点シェーダ
//------------------------------------------------
void BasicVS(float3 in_pos : POSITION,
	float4 in_col : COLOR0,
	out float4 out_pos : POSITION,
	out float4 out_color : COLOR0)
{
	// ワールド変換
	out_pos = mul(float4(in_pos, 1.0f), g_world);

	// ビューイング変換
	out_pos = mul(out_pos, g_viewing);

	// プロジェクション変換
	out_pos = mul(out_pos, g_projection);

	// 頂点の色の決定
	out_color = in_col;

}

//------------------------------------------------
// ピクセルシェーダ
//------------------------------------------------
void BasicPS(float4 in_color : COLOR0,
	out float4 out_color : COLOR0)
{
	// 入力された色情報をそのまま設定
	out_color = in_color;

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
