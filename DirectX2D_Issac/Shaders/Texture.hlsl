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
// �������  Matrix
/////////////////////////////////////////
cbuffer SpriteCutBuffer : register(b10)
{
	float2 Offset;
	float2 OffsetSize;
};
/////////////////////////////////////////////////////////////
// ������� ����  : PixelShader�ܰ迡�� ���
////////////////////////////////////////////////////////////
cbuffer ColorBuffer : register(b11)
{
	float4 TextColor;
	int    Path;
	float  Time;
	float  Time2;
	float  Time3;
}
/////////////////////////////////////////
// ��������
/////////////////////////////////////////
struct VertexInput
{
	float4 pos : POSITION; // Semantic : ��ȯ���̳� �Ű������� ��� ������ ��Ÿ���°�
	float2 uv : TEXCOORD;
};
struct PixelInput
{
	float4 pos : SV_Position; // RS�ܰ� ��ģ ���� �������� SystemValue
	float2 uv : TEXCOORD;
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
	
	output.pos = mul(input.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);
	output.uv.x = (input.uv.x * OffsetSize.x) + Offset.x;
	output.uv.y = (input.uv.y * OffsetSize.y) + Offset.y;
	return output;
	
};

float4 OutLine(PixelInput input)
{
	float4 diffuse = SourceTexture[0].Sample(Sampler, input.uv);
	float3 top = SourceTexture[0].Sample(Sampler, +float2(0, 32)).rgb;
	float3 edge = diffuse.rgb - top;
	float EdotD = dot(edge, float3(1, 1, 1)) * 0.6f;
	return diffuse + float4(EdotD, EdotD, EdotD, diffuse.a) * SourceTexture[1].Sample(Sampler, input.uv);
	
}


// Second Texture�ϰ� Merge
float4 Rainbow(PixelInput input)
{
	// �⺻ �ؽ���
	float4 color = SourceTexture[0].Sample(Sampler, input.uv);	
	float count = 0;
	
	
	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			count += SourceTexture[0].Sample(Sampler, input.uv ).a;
		}
	}	
	
	// ������ Color�� �ܰ��� ������
	if (count > 0 && count < 9)
		return SourceTexture[1].Sample(Sampler, input.uv);
	return color;
};



float4 PS(PixelInput input): SV_TARGET // RTV�� ������ System Value
{
	float4 color = SourceTexture[0].Sample(Sampler, input.uv);
	float4 returnColor = color;
	
	[forcecase]
	
	switch (Path)
		{
			case 0:
				returnColor = color;
				break;
			case 1:
				returnColor = float4(color.r * 2.0f, color.g * 0.5f, color.b * 0.5f, color.a * 0.6f);
				break;
			case 2:
				returnColor = float4(color.r, color.g, color.b, color.a * 0.6f);
				break;
			case 3:
			    returnColor = float4(0.9f, 0.7f, 0.1f, color.a * 0.8f);
				break;
			case 4:
                returnColor = float4(0.9f, 0.0f, 0.0f, color.a * 0.8f);
				break;
		    case 5:
				returnColor = OutLine(input);
				break;
			case 6:
				returnColor = Rainbow(input);
				break;
		
		}
	return returnColor;
};

