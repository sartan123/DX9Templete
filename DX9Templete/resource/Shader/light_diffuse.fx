//------------------------------------------------
// �O���[�o���ϐ�
//------------------------------------------------
float4x4 	g_world;
float4x4 	g_world_inv;
float4x4 	g_view;
float4x4 	g_proj;
float4		g_color0;
float4		g_color1;
float4		g_light_dir;
texture		g_texture;

//------------------------------------------------
// �e�N�X�`���T���v��
//------------------------------------------------
sampler TextureSampler = 
sampler_state
{
    Texture = <g_texture>;
	MipFilter = NONE;
    MinFilter = LINEAR;
    MagFilter = LINEAR;

	AddressU =Clamp;
	AddressV =Clamp;
};	

//------------------------------------------------
// ���_�V�F�[�_
//------------------------------------------------
void BasicVS( 	float3 in_pos : POSITION,
				float3 in_normal : NORMAL,
				float2 in_tex : TEXCOORD0,
 				out float4 out_pos : POSITION,
 				out float4 out_color :COLOR0,
 				out float2 out_tex : TEXCOORD0)
{
	// ���W�ϊ�
	float4 world_pos;
	world_pos = mul(float4(in_pos, 1.0f), g_world);
	out_pos = mul(world_pos, g_view);
	out_pos = mul(out_pos, g_proj);

	// �e�N�X�`�����W
	out_tex = in_tex;
	
	// ���_���Ƃ̐F�̌v�Z
	float4 local_light;
	local_light =  normalize( mul(g_light_dir, g_world_inv));
	out_color = saturate(g_color0 + g_color1 * max(0.2, dot(local_light, in_normal)));
}

//------------------------------------------------
// �s�N�Z���V�F�[�_
//------------------------------------------------
void BasicPS( float4 in_color : COLOR0,
 			  float2 in_tex : TEXCOORD0,
			  out float4 out_color : COLOR0,
			  uniform bool b_tex)
{
	if(b_tex){
		out_color = in_color * tex2D(TextureSampler,in_tex);
	}
	else{
		out_color = in_color;
	}
}

//------------------------------------------------
// �e�N�j�b�N�錾
//------------------------------------------------
technique BasicTech
{
    pass P0
    {
        vertexShader = compile vs_3_0 BasicVS();
        pixelShader  = compile ps_3_0 BasicPS(true);
        
	}
    pass P1
    {
        vertexShader = compile vs_3_0 BasicVS();
        pixelShader  = compile ps_3_0 BasicPS(false);
        
	}

}
