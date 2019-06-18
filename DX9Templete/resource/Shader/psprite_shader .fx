//------------------------------------------------
// �O���[�o���ϐ�
//------------------------------------------------
float4x4 	g_world;
float4x4 	g_viewing;
float4x4 	g_projection;
float		g_time;
texture 	g_texture;

//------------------------------------------------
// �e�N�X�`���T���v��
//------------------------------------------------
sampler TextureSampler =
sampler_state
{
	Texture = <g_texture>;
};

//------------------------------------------------
// ���_�V�F�[�_
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
	// ���Ԃ̌v��
	float time = g_time - in_start;

	// �A�j���[�V�����̌J�Ԃ����l������
	time = fmod(time, in_life);

	// �d��
	float3 accel = float3(0.0, -9.8, 0.0);

	// �|�C���g�X�v���C�g�̈ʒu�v�Z
	float3 pos;
	pos = in_pos + in_dir * time + 0.5*accel*time*time;

	// ���[���h�ϊ�
	out_pos = mul(float4(pos, 1.0f), g_world);

	// �r���[�C���O�ϊ�
	out_pos = mul(out_pos, g_viewing);

	// �v���W�F�N�V�����ϊ�
	out_pos = mul(out_pos, g_projection);

	// ���_�̐F�̌���
	out_size = in_size;

	// �e�N�X�`�����W�̓R�s�[���邾��
	out_tex = 0.0;

}

//------------------------------------------------
// �s�N�Z���V�F�[�_
//------------------------------------------------
void BasicPS(float2 in_tex : TEXCOORD0,
	out float4 out_color : COLOR0)
{
	// �F�̏o��
	out_color = tex2D(TextureSampler, in_tex);
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
