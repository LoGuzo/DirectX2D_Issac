// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS  // scanf관련하여 보안모드 무시
// Console윈도우를 붙일려면 iostream,stdio가 include되어 있어야 한다
// 아래명령어가 iostream,stdio위에 정의 되어야 한다
// console을 debug mode에서만 동작
#ifdef _DEBUG
#pragma comment(linker,"/entry:wWinMainCRTStartup /subsystem:console")
#endif
#pragma warning (disable: 4477) 
#pragma warning (disable: 4467) 
#pragma warning (disable: 4244) 
#pragma warning (disable: 4267) 
#pragma warning (disable: 4018)

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
// C++관련 라이브러리 
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <mutex>
#include <algorithm>
#include <assert.h>
using namespace std;

// 다이렉트X 라이브러리
#include  <d3d11.h>
#include  <d3dcompiler.h>  // High Level Shader Language : 바이너리

#include  <DirectXMath.h>  // DirectX에서 사용될 수학 Libaray
#include  <DirectXTex.h>   // Image를 읽어들이는 Libray : 
using namespace DirectX;

#include  <imgui.h>
#include  <imgui_impl_dx11.h>
#include  <imgui_impl_win32.h>

// 다이렉트X 2D 라이브러리 : Text
#include <d2d1_2.h>
#include <dwrite.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
// 추가로 라이브러리
#pragma comment(lib, "DirectXTex.lib")
#pragma comment(lib, "ImGui.lib")

// DirectX의 Type 정의
typedef XMFLOAT4    Float4;
typedef XMFLOAT3    Float3;
typedef XMFLOAT2    Float2;
typedef XMVECTOR    Vector4;
typedef XMMATRIX    Matrix;
typedef XMFLOAT4X4  Float4x4;
typedef XMFLOAT4X4  MatrixF;

// MACRO
#define  SAFE_DELETE(p)           {if(p) { delete(p); (p)=NULL;}}
#define  SAFE_RELEASE(p)          {if(p) {(p)->Release(); (p)=NULL;}}
#define  SAFE_DELETE_ARRAY(p)     {if(p) { delete [] (p); (p)=NULL;}}


#include "Framework/Base/SingleTon.h"
#include "Framework/Base/DScene.h"
#include "Framework/Base/Vector2.h"
#include "Framework/Base/Vector3.h"
#include "Framework/Base/MatrixUtil.h"
#include "Framework/Base/DObject.h"
#include "Framework/Base/DGameObject.h"

extern   Vector2 GobalScale;

#include "Framework/Buffer/DConstantBuffer.h"
#include "Framework/Buffer/DVertexBuffer.h"
#include "Framework/Buffer/DIndexBuffer.h"
#include "Framework/Buffer/DMatrixBuffer.h"
#include "Framework/Buffer/GlobalBuffer.h"

#include "Framework/Shader/DShader.h"
#include "Framework/Shader/DVertexShader.h"
#include "Framework/Shader/DPixelShader.h"

#include "Framework/Render/DDirectWrite.h"
#include "Framework/Render/DQuad.h"
#include "Framework/Render/DSprite.h"

#include "Framework/Collider/DCollider.h"
#include "Framework/Collider/DLineCollider.h"

#include "Framework/System/DDevice.h"
#include "Framework/System/GameTime.h"
#include "Framework/System/DKeyboard.h"

#include "Framework/Manager/DCamera.h"
#include "Framework/Manager/DMainWindow.h"
#include "Framework/Manager/DSceneManager.h"
#include "Framework/Manager/DShaderManager.h"
#include "Framework/Manager/DImageManager.h"
#include "Framework/Manager/DObjectManager.h"
#include "Framework/Manager/DObserverCollision.h"

#define   MAIN   MainWindow::GetInstance()
#define   DEVICE DDevice::GetInstance()->GetDevice()
#define   DC     DDevice::GetInstance()->GetDeviceContext()