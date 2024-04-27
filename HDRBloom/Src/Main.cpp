#include <cstdint>
#include <Windows.h>

#include <imgui.h>

#include "CrashModule.h"
#include "PlatformModule.h"
#include "RenderModule.h"
#include "GeometryRenderer2D.h"
#include "TextRenderer2D.h"
#include "TTFont.h"

int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
	PlatformModule::WindowConstructParams windowParam{ L"HDRBloom", 100, 100, 1000, 800, false, false };

	CrashModule::Init();
	PlatformModule::Init(windowParam);
	RenderModule::Init(PlatformModule::GetWindowHandle());

	PlatformModule::SetEndLoopCallback([&]() { RenderModule::Uninit(); });
	RenderModule::SetPointSizeMode(true);
	RenderModule::SetAlphaBlendMode(true);

	GeometryRenderer2D* renderer = RenderModule::CreateResource<GeometryRenderer2D>();
	renderer->SetOrtho(Mat4x4::Ortho(0.0f, static_cast<float>(windowParam.w), static_cast<float>(windowParam.h), 0.0f, -1.0f, 1.0f));

	TextRenderer2D* textRenderer = RenderModule::CreateResource<TextRenderer2D>();
	textRenderer->SetOrtho(Mat4x4::Ortho(0.0f, static_cast<float>(windowParam.w), static_cast<float>(windowParam.h), 0.0f, -1.0f, 1.0f));

	TTFont* font = RenderModule::CreateResource<TTFont>("Resource/Font/SeoulNamsanEB.ttf", 0x00, 0x127, 64.0f);
	
	PlatformModule::RunLoop(
		[&](float deltaSeconds)
		{
			RenderModule::BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

			textRenderer->DrawText2D(font, L"Hello, World", Vec2f(500.0f, 400.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f));

			RenderModule::EndFrame();
		}
	);

	PlatformModule::Uninit();
	CrashModule::Uninit();
	return 0;
}