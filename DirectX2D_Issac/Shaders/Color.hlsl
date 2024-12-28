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
cbuffer ColorBuffer : register(b11)
{
	float4 Color;
};
/////////////////////////////////////////
// 정점정의
/////////////////////////////////////////
struct VertexInput
{
	float4 pos : POSITION; // Semantic : 반환값이나 매개변수가 어떻게 사용될지 나타내는것
};
struct PixelInput
{
	float4 pos : SV_Position; // RS단계 거친 값을 받을려면 SystemValue
};


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
	return output;
	
};
float4 PS(PixelInput input) : SV_TARGET // RTV에 보내는 System Value
{
	float4 color = Color;
	return color;
};
