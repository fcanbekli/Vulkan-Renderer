#pragma once

namespace hyp_vlk
{
	namespace hyp_backend {
		class PresentationManager {
		private:
			VkSurfaceKHR m_surface;
		public:
			PresentationManager();

			void CreateWin32Surface(VkInstance& instance, HWND& hWindow, HINSTANCE& hInstance);
		};
	}
} 