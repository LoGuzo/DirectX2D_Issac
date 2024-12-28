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
// 정점정의
/////////////////////////////////////////
struct VertexInput
{
	float4 pos : POSITION; // Semantic : 반환값이나 매개변수가 어떻게 사용될지 나타내는것
	float2 uv : TEXCOORD;
	matrix transform : INSTANCE_TRANSFORM;
	float2 offset : INSTANCE_OFFSET;
	float2 offetSize : INSTANCE_OFFSETSIZE;
	int exist : INSTANCE_EXIST;
	int SRTNO : INSTANCE_SRTNO;
};
struct PixelInput
{
	float4 pos : SV_Position; // RS단계 거친 값을 받을려면 SystemValue
	float2 uv : TEXCOORD;
	int exist : INSTANCE_EXIST;
	int SRTNO : INSTANCE_SRTNO;
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
float4 PS(PixelInput input) : SV_TARGET // RTV에 보내는 System Value
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