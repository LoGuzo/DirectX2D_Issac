struct VertexInput
{
	float4 pos : POSITION; // Semantic : 반환값이나 매개변수가 어떻게 사용될지 나타내는것
	float4 color : COLOR;
};
struct PixelInput
{
	float4 pos : SV_Position; // RS단계 거친 값을 받을려면 SystemValue
	float4 color : COLOR;
};
// 프로그램 시작
///////////////////////////////////////
// 좌표변환(0), 조명, 스키닝
///////////////////////////////////////
PixelInput  VS(VertexInput input)
{
	PixelInput output;
	output.pos = input.pos;
	output.color = input.color;
	return output;
};
float4 PS(PixelInput input) : SV_TARGET  // RTV에 보내는 System Value
{
	return input.color;

};