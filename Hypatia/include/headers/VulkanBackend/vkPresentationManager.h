#pragma once

namespace hyp_vlk
{
	namespace hyp_backend {
		class PresentationSystem {

		public:
			PresentationSystem();

			static void CreateWin32Surface(VkInstance& instance, HWND& hWindow, HINSTANCE& hInstance, VkSurfaceKHR& surface);
		};
	}
} 