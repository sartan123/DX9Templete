//------------------------------------------------
// �O���[�o���ϐ�
//------------------------------------------------
float4x4 	g_world;
float4x4 	g_viewing;
float4x4 	g_projection;

float4		g_color;
texture 	g_texture0;
texture 	g_texture1;

//------------------------------------------------
// �e�N�X�`���T���v��
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
// ���_�V�F�[�_
//------------------------------------------------
void BasicVS(float3 in_pos : POSITION,
	float2 in_tex0 : TEXCOORD0,
	float2 in_tex1 : TEXCOORD0,
	out float4 out_pos : POSITION,
	out float4 out_color : COLOR0,
	out float2 out_tex0 : TEXCOORD0,
	out float2 out_tex1 : TEXCOORD1)
{
	// ���[���h�ϊ�
	out_pos = mul(float4(in_pos, 1.0f), g_world);

	// �r���[�C���O�ϊ�
	out_pos = mul(out_pos, g_viewing);

	// �v���W�F�N�V�����ϊ�
	out_pos = mul(out_pos, g_projection);

	// ���_�̐F�̌���
	out_color = g_color;

	// �e�N�X�`�����W�̓R�s�[���邾��
	out_tex0 = in_tex0;
	out_tex1 = in_tex1;

}

//------------------------------------------------
// �s�N�Z���V�F�[�_
//------------------------------------------------
void BasicPS(float4 in_color : COLOR0,
	float4 in_tex0 : TEXCOORD0,
	float4 in_tex1 : TEXCOORD1,
	out float4 out_color : COLOR0)
{
	// �F�̏o��
	out_color = tex2D(TextureSampler0, in_tex0) * tex2D(TextureSampler1, in_tex1);
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
