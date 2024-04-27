#include <cstdint>
#include <Windows.h>

#include "CrashModule.h"
#include "PlatformModule.h"
#include "RenderModule.h"

int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
	PlatformModule::WindowConstructParams windowParam{ L"HDRBloom", 100, 100, 1000, 800, false, false };

	CrashModule::Init();
	PlatformModule::Init(windowParam);
	RenderModule::Init(PlatformModule::GetWindowHandle());

	PlatformModule::SetEndLoopCallback([&]() { RenderModule::Uninit(); });

	PlatformModule::RunLoop(
		[&](float deltaSeconds)
		{
			RenderModule::BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

			RenderModule::EndFrame();
		}
	);

	PlatformModule::Uninit();
	CrashModule::Uninit();
	return 0;
}