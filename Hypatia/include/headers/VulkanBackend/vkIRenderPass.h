#pragma once


namespace hyp_backend {

	class IRenderPass {
	public:
		IRenderPass() {}
		void virtual InitRenderPass() = 0;
		void virtual Draw(uint32_t nextImageIndex) = 0;
	};
}