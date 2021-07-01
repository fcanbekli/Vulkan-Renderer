#pragma once

namespace hypatia
{
	namespace hyp_backend {

		class IRenderPass {
		public:
			IRenderPass(){}
			void virtual InitRenderPass();
			void virtual Draw(uint32_t nextImageIndex);

		};
	}
}

