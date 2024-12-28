/////////////////////////////////////////
// �������  Matrix
/////////////////////////////////////////
cbuffer WORLD : register(b0) // slot 0-14
{
	matrix world; // Object ��ġ��,ȸ����,Ȯ�밪
};
cbuffer VIEW : register(b1) // slot 0-14
{
	matrix view; // Camera 
};
cbuffer PROJECTION : register(b2) // slot 0-14
{
	matrix projection; // ȭ��Size �� NCD�� ����
};
/////////////////////////////////////////
// ��������
/////////////////////////////////////////
struct VertexInput
{
	float4 pos : POSITION; // Semantic : ��ȯ���̳� �Ű������� ��� ������ ��Ÿ���°�
	float2 uv : TEXCOORD;
	matrix transform : INSTANCE_TRANSFORM;
	float2 offset : INSTANCE_OFFSET;
	float2 offetSize : INSTANCE_OFFSETSIZE;
	int exist : INSTANCE_EXIST;
	int SRTNO : INSTANCE_SRTNO;
};
struct PixelInput
{
	float4 pos : SV_Position; // RS�ܰ� ��ģ ���� �������� SystemValue
	float2 uv : TEXCOORD;
	int exist : INSTANCE_EXIST;
	int SRTNO : INSTANCE_SRTNO;
};

Texture2D SourceTexture[5] : register(t0); // �ؽ����ڿ�(128)
SamplerState Sampler : register(s0); // ���ø� ����(16)

// ���α׷� ����
///////////////////////////////////////
// ��ǥ��ȯ(0), ����, ��Ű��
///////////////////////////////////////
PixelInput VS(VertexInput input)
{
	PixelInput output;
	

	
//	output.pos = mul(input.pos, world);
	output.pos = mul(input.pos, input.transform);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);
	
	output.uv.x = (input.uv.x * input.offetSize.x) + input.offset.x;
	output.uv.y = (input.uv.y * input.offetSize.y) + input.offset.y;
	output.exist = input.exist;
	output.SRTNO = input.SRTNO;
	
	return output;
	
};
float4 PS(PixelInput input) : SV_TARGET // RTV�� ������ System Value
{
	float4 color;
	
	
	[forcecase]
	switch (input.SRTNO)
	{
		case 0:
			color = SourceTexture[0].Sample(Sampler, input.uv);
			break;
		case 1:
			color = SourceTexture[1].Sample(Sampler, input.uv);
			break;
		case 2:
			color = SourceTexture[2].Sample(Sampler, input.uv);
			break;
		
		
	}
	
	float4 returnColor = color;
	
	if (input.exist < 1)
		discard;
	
	
	return returnColor;
};