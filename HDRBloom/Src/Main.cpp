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
	renderer->SetOrtho(RenderModule::GetScreenOrtho());

	TextRenderer2D* textRenderer = RenderModule::CreateResource<TextRenderer2D>();
	textRenderer->SetOrtho(RenderModule::GetScreenOrtho());

	TTFont* font = RenderModule::CreateResource<TTFont>("Resource/Font/SeoulNamsanEB.ttf", 0x00, 0x127, 64.0f);
	
	PlatformModule::RunLoop(
		[&](float deltaSeconds)
		{
			RenderModule::BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
			renderer->DrawWireframeRectangle2D(Vec2f(500.0f, 400.0f), 300.0f, 100.0f, 0.0f, Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
			textRenderer->DrawText2D(font, L"Bloom!", Vec2f(500.0f, 400.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f));

			RenderModule::EndFrame();
		}
	);

	PlatformModule::Uninit();
	CrashModule::Uninit();
	return 0;
}