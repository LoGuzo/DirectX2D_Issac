#pragma once

#define  DIRECT DirectWrite::GetInstance()

class DirectWrite : public SingleTon<DirectWrite>
{
private:
	DirectWrite();
	friend SingleTon;

public:
	~DirectWrite();

public:
	ID2D1DeviceContext* GetDC() { return deviceContext; }

	void CreateBackBuffer();
	void DeleteBackBuffer();

	void RenderText(wstring& text, RECT& rect);
	void RenderText(wstring text, Vector2 pos, int R, int G, int B, float size);
	void DrawLine(Vector2 start, Vector2 end, float strokeWidth);
	void SkewRectangle(RECT rect, D2D1::ColorF color, float angle, float angle2);

private:
	void  AddBrush();
	void  AddStyle(string key, wstring font, float size = 20.0f,
		DWRITE_FONT_WEIGHT    weight = DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE     style = DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH   stretch = DWRITE_FONT_STRETCH_NORMAL);
	void SetColor(COLORREF color, float alpha);
	void SetColor(float r, float g, float b, float alpha);
	void SetStyle(string key);

private:
	int  GetStringWidth(wstring text, float size);  // string�� �ʺ� �����ִ� �Լ�

private:
	ID2D1Factory1* factory;               //2D�� Device�� �������ֱ� ����
	IDWriteFactory* writeFactory;         //DirectWrite����� �����ϱ� ����

	ID2D1Device* device;
	ID2D1DeviceContext* deviceContext;

	ID2D1Bitmap1* bitmap; //����ۿ�(D3D : Texture2D)
	IDXGISurface* surface; //(D3D : RTV)

	ID2D1SolidColorBrush* brush;  //�ؽ�Ʈ ����
	IDWriteTextFormat* format; //�ؽ�Ʈ ��Ʈ

private:
	map<string, ID2D1SolidColorBrush*> cm_Brushes;
	map<string, IDWriteTextFormat*>    cm_Formats;

	ID2D1SolidColorBrush* m_pCurBrush;
	IDWriteTextFormat* m_pCurFormat;
};