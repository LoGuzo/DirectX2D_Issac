struct VertexInput
{
	float4 pos : POSITION; // Semantic : ��ȯ���̳� �Ű������� ��� ������ ��Ÿ���°�
	float4 color : COLOR;
};
struct PixelInput
{
	float4 pos : SV_Position; // RS�ܰ� ��ģ ���� �������� SystemValue
	float4 color : COLOR;
};
// ���α׷� ����
///////////////////////////////////////
// ��ǥ��ȯ(0), ����, ��Ű��
///////////////////////////////////////
PixelInput  VS(VertexInput input)
{
	PixelInput output;
	output.pos = input.pos;
	output.color = input.color;
	return output;
};
float4 PS(PixelInput input) : SV_TARGET  // RTV�� ������ System Value
{
	return input.color;

};