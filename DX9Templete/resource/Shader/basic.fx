//------------------------------------------------
// �O���[�o���ϐ�
//------------------------------------------------
float4x4 	g_world;
float4x4 	g_viewing;
float4x4 	g_projection;

//------------------------------------------------
// ���_�V�F�[�_
//------------------------------------------------
void BasicVS(float3 in_pos : POSITION,
	float4 in_col : COLOR0,
	out float4 out_pos : POSITION,
	out float4 out_color : COLOR0)
{
	// ���[���h�ϊ�
	out_pos = mul(float4(in_pos, 1.0f), g_world);

	// �r���[�C���O�ϊ�
	out_pos = mul(out_pos, g_viewing);

	// �v���W�F�N�V�����ϊ�
	out_pos = mul(out_pos, g_projection);

	// ���_�̐F�̌���
	out_color = in_col;

}

//------------------------------------------------
// �s�N�Z���V�F�[�_
//------------------------------------------------
void BasicPS(float4 in_color : COLOR0,
	out float4 out_color : COLOR0)
{
	// ���͂��ꂽ�F�������̂܂ܐݒ�
	out_color = in_color;

}

//------------------------------------------------
// �e�N�j�b�N�錾
//------------------------------------------------
technique BasicTech
{
	pass P0
	{
		vertexShader = compile vs_3_0 BasicVS();
		pixelShader = compile ps_3_0 BasicPS();
	}
}
