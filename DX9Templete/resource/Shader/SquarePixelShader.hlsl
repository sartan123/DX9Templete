struct VS_OUTPUT
{
	float4 Pos : POSITION;
	float4 Color : COLOR;
};

float4 main(VS_OUTPUT _In) : COLOR
{
	float4 out_color = _In.Color;// {1.0f, 1.0f, 1.0f, 1.0f};
	return out_color;
}