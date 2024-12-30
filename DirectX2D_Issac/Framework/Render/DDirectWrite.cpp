#include "framework.h"
#include "DDirectWrite.h"

DirectWrite::DirectWrite()
{
	HRESULT hr;

	// 1. DirectWrite 팩토리 생성
	hr = DWriteCreateFactory
	(
		DWRITE_FACTORY_TYPE_SHARED,  // 여러 프로세서가 같이 이용
		__uuidof(IDWriteFactory),
		(IUnknown**)&writeFactory
	);
	assert(SUCCEEDED(hr));

	// 2. D3D와 같이 사용하기 위해
	D2D1_FACTORY_OPTIONS option;
	option.debugLevel = D2D1_DEBUG_LEVEL_WARNING;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory);
	assert(SUCCEEDED(hr));

	IDXGIDevice* dxgiDevice;
	hr = DEVICE->QueryInterface(&dxgiDevice);
	assert(SUCCEEDED(hr));

	hr = factory->CreateDevice(dxgiDevice, &device);
	assert(SUCCEEDED(hr));

	hr = device->CreateDeviceContext
	(
		D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS,
		&deviceContext
	);
	assert(SUCCEEDED(hr));

	CreateBackBuffer();
}

DirectWrite::~DirectWrite()
{
	DeleteBackBuffer();


	wstring szFontFile = L"Image/Font/SkiCargo.ttf";

	BOOL b = RemoveFontResourceEx(
		szFontFile.c_str(), 		// name of font file
		FR_PRIVATE,   		// font characteristics
		NULL         		// Reserved.
	);
}

void DirectWrite::CreateBackBuffer()
{
	HRESULT hr;

	if (!DDevice::GetInstance()->GetSwapChain())
		return;
	if (deviceContext == NULL)
		return;

	hr = DDevice::GetInstance()->GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (void**)&surface);
	assert(SUCCEEDED(hr));

	D2D1_BITMAP_PROPERTIES1 bp;
	bp.pixelFormat.format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
	bp.dpiX = 96;
	bp.dpiY = 96;
	bp.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
	bp.colorContext = NULL;

	hr = deviceContext->CreateBitmapFromDxgiSurface(surface, &bp, &bitmap);
	assert(SUCCEEDED(hr));

	deviceContext->SetTarget(bitmap);

	hr = deviceContext->CreateSolidColorBrush(D2D1::ColorF(1, 1, 1), &brush);
	assert(SUCCEEDED(hr));

	if (0)
	{
		writeFactory->CreateTextFormat
		(
			L"돋움체",
			NULL,
			DWRITE_FONT_WEIGHT_SEMI_BOLD,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			15,
			L"ko",
			&format
		);

		AddBrush();
		AddStyle("Default", L"배달의민족 주아", 30.0f);
		SetStyle("Default");
	}

	if (1)
	{
		wstring fontFile = L"Image/Font/SkiCargo.ttf";
		AddFontResourceEx(fontFile.c_str(), FR_PRIVATE, NULL);

		HRESULT hr = writeFactory->CreateTextFormat
		(
			L"SkiCargo",
			NULL,
			DWRITE_FONT_WEIGHT_SEMI_BOLD,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			15,
			L"ko",
			&format
		);

		AddBrush();
		AddStyle("Default", L"SkiCargo", 30.0f);
		SetStyle("Default");
	}
	}

void DirectWrite::DeleteBackBuffer()
{
	if (!deviceContext)
		return;

	deviceContext->SetTarget(NULL);

	SAFE_RELEASE(brush);
	SAFE_RELEASE(format);

	SAFE_RELEASE(bitmap);
	SAFE_RELEASE(surface);
}

void DirectWrite::RenderText(wstring& text, RECT& rect)
{
	D2D1_RECT_F rt;
	rt.left = (float)rect.left;
	rt.top = (float)rect.top;
	rt.right = (float)rect.right;
	rt.bottom = (float)rect.bottom;

	deviceContext->DrawTextW(text.c_str(), text.length(), format, &rt, brush);
}

void DirectWrite::RenderText(wstring text, Vector2 pos, int R, int G, int B, float size)
{
	Vector2 Size = Vector2(0, 0);

	SetColor(RGB(R, G, B), 1.0f);

	Size.x = text.size() * m_pCurFormat->GetFontSize();
	Size.y = m_pCurFormat->GetFontSize();
	int sizeX = GetStringWidth(text, size) * 0.5f;

	Vector2 halfSize = { Size.x * 0.5f, Size.y * 0.5f };

	D2D1_RECT_F rectF;
	rectF.left = pos.x - sizeX;
	rectF.right = pos.x + sizeX;
	rectF.top = pos.y - halfSize.y;
	rectF.bottom = pos.y + halfSize.y;

	deviceContext->DrawTextW(text.c_str(), (UINT)text.size(),
		m_pCurFormat, &rectF, m_pCurBrush);

	return;
}

void DirectWrite::DrawLine(Vector2 start, Vector2 end, float strokeWidth)
{
	ID2D1SolidColorBrush* brush;
	deviceContext->CreateSolidColorBrush(D2D1::ColorF(0, 1, 0), &brush);

	deviceContext->SetTransform(D2D1::Matrix3x2F::Identity());

	Vector2 startPos = start;
	Vector2 endPos = end;


	deviceContext->DrawLine(D2D1::Point2F(startPos.x, startPos.y), D2D1::Point2F(endPos.x, endPos.y), brush, strokeWidth);
	SAFE_RELEASE(brush);
}

void DirectWrite::SkewRectangle(RECT rect, D2D1::ColorF color, float angle, float angle2)
{
	D2D1_RECT_F rt;
	rt.left = (float)rect.left;
	rt.top = (float)rect.top;
	rt.right = (float)rect.right;
	rt.bottom = (float)rect.bottom;

	D2D1_POINT_2F offset;
	offset.x = rect.left + (rect.right - rect.left) * 0.5f;
	offset.y = rect.top + (rect.bottom - rect.top) * 0.5f;

	ID2D1SolidColorBrush* brush;
	deviceContext->CreateSolidColorBrush(color, &brush);
	deviceContext->SetTransform(D2D1::Matrix3x2F::Rotation(angle, offset));
	deviceContext->SetTransform(D2D1::Matrix3x2F::Skew(angle2, 0, offset));
	deviceContext->FillRectangle(D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom), brush);

	SAFE_RELEASE(brush);
}

void DirectWrite::AddBrush()
{
	ID2D1SolidColorBrush* brush = nullptr;

	D2D1::ColorF colorF(1, 1, 1);
	deviceContext->CreateSolidColorBrush(colorF, &brush);

	cm_Brushes["default"] = brush;
	m_pCurBrush = brush;
}

void DirectWrite::AddStyle(string key, wstring font, float size, DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STYLE style, DWRITE_FONT_STRETCH stretch)
{
	if (cm_Formats.count(key) > 0) return;

	IDWriteTextFormat* format;

	HRESULT hr = writeFactory->CreateTextFormat(font.c_str(), nullptr,
		weight, style, stretch, size, L"ko", &format);

	assert(SUCCEEDED(hr));

	cm_Formats[key] = format;
}

void DirectWrite::SetColor(COLORREF color, float alpha)
{
	m_pCurBrush->SetColor(D2D1::ColorF(
		(FLOAT)GetRValue(color) / 255.f,
		(FLOAT)GetGValue(color) / 255.f,
		(FLOAT)GetBValue(color) / 255.f,
		alpha));
}

void DirectWrite::SetColor(float r, float g, float b, float alpha)
{
	m_pCurBrush->SetColor(D2D1::ColorF(r, g, b, alpha));
}

void DirectWrite::SetStyle(string key)
{
	if (cm_Formats.count(key) == 0) return;
	m_pCurFormat = cm_Formats[key];
}

int DirectWrite::GetStringWidth(wstring text, float size)
{
	HFONT hFont, hOldFont;

	hFont = CreateFont((int)size, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_MODERN, TEXT("돋움체"));

	HDC hdc = ::GetDC(MAIN->GetHandle());
	hOldFont = (HFONT)SelectObject(hdc, hFont);
	SIZE sz;
	GetTextExtentPoint32(hdc, text.c_str(), text.length(), &sz);
	DeleteObject(SelectObject(hdc, hOldFont));
	ReleaseDC(MAIN->MAIN->GetHandle(), hdc);
	return sz.cx;
}
