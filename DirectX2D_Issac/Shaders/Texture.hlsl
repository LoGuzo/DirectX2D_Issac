/////////////////////////////////////////
// 상수버퍼  Matrix
/////////////////////////////////////////
cbuffer WORLD : register(b0) // slot 0-14
{
	matrix world; // Object 위치점,회전값,확대값
};
cbuffer VIEW : register(b1) // slot 0-14
{
	matrix view; // Camera 
};
cbuffer PROJECTION : register(b2) // slot 0-14
{
	matrix projection; // 화면Size 와 NCD의 비율
};
/////////////////////////////////////////
// 상수버퍼  Matrix
/////////////////////////////////////////
cbuffer SpriteCutBuffer : register(b10)
{
	float2 Offset;
	float2 OffsetSize;
};
/////////////////////////////////////////////////////////////
// 상수버퍼 선언  : PixelShader단계에서 사용
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
// 정점정의
/////////////////////////////////////////
struct VertexInput
{
	float4 pos : POSITION; // Semantic : 반환값이나 매개변수가 어떻게 사용될지 나타내는것
	float2 uv : TEXCOORD;
};
struct PixelInput
{
	float4 pos : SV_Position; // RS단계 거친 값을 받을려면 SystemValue
	float2 uv : TEXCOORD;
};

Texture2D SourceTexture[5] : register(t0); // 텍스쳐자원(128)
SamplerState Sampler : register(s0); // 샘플링 정보(16)

// 프로그램 시작
///////////////////////////////////////
// 좌표변환(0), 조명, 스키닝
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


// Second Texture하고 Merge
float4 Rainbow(PixelInput input)
{
	// 기본 텍스쳐
	float4 color = SourceTexture[0].Sample(Sampler, input.uv);	
	float count = 0;
	
	
	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			count += SourceTexture[0].Sample(Sampler, input.uv ).a;
		}
	}	
	
	// 무지개 Color는 외곽에 렌더링
	if (count > 0 && count < 9)
		return SourceTexture[1].Sample(Sampler, input.uv);
	return color;
};



float4 PS(PixelInput input): SV_TARGET // RTV에 보내는 System Value
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

