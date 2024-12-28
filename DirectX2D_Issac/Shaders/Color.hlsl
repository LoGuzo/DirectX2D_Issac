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
cbuffer ColorBuffer : register(b11)
{
	float4 Color;
};
/////////////////////////////////////////
// ��������
/////////////////////////////////////////
struct VertexInput
{
	float4 pos : POSITION; // Semantic : ��ȯ���̳� �Ű������� ��� ������ ��Ÿ���°�
};
struct PixelInput
{
	float4 pos : SV_Position; // RS�ܰ� ��ģ ���� �������� SystemValue
};


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
	return output;
	
};
float4 PS(PixelInput input) : SV_TARGET // RTV�� ������ System Value
{
	float4 color = Color;
	return color;
};
