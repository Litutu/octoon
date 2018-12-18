#ifndef OCTOON_RENDER_SYSTEM_H_
#define OCTOON_RENDER_SYSTEM_H_

#include <octoon/runtime/singleton.h>
#include <octoon/video/render_types.h>
#include <octoon/hal/graphics.h>

namespace octoon
{
	namespace video
	{
		class OCTOON_EXPORT RenderSystem final
		{
			OctoonDeclareSingleton(RenderSystem)
		public:
			RenderSystem() noexcept;
			~RenderSystem() noexcept;

			void setup(const graphics::GraphicsDevicePtr& device, std::uint32_t w, std::uint32_t h) except;
			void close() noexcept;

			void setFramebufferSize(std::uint32_t w, std::uint32_t h) noexcept;
			void getFramebufferSize(std::uint32_t& w, std::uint32_t& h) const noexcept;

			graphics::GraphicsInputLayoutPtr createInputLayout(const graphics::GraphicsInputLayoutDesc& desc) noexcept;
			graphics::GraphicsDataPtr createGraphicsData(const graphics::GraphicsDataDesc& desc) noexcept;
			graphics::GraphicsTexturePtr createTexture(const graphics::GraphicsTextureDesc& desc) noexcept;
			graphics::GraphicsSamplerPtr createSampler(const graphics::GraphicsSamplerDesc& desc) noexcept;
			graphics::GraphicsFramebufferPtr createFramebuffer(const graphics::GraphicsFramebufferDesc& desc) noexcept;
			graphics::GraphicsFramebufferLayoutPtr createFramebufferLayout(const graphics::GraphicsFramebufferLayoutDesc& desc) noexcept;
			graphics::GraphicsShaderPtr createShader(const graphics::GraphicsShaderDesc& desc) noexcept;
			graphics::GraphicsProgramPtr createProgram(const graphics::GraphicsProgramDesc& desc) noexcept;
			graphics::GraphicsStatePtr createRenderState(const graphics::GraphicsStateDesc& desc) noexcept;
			graphics::GraphicsPipelinePtr createRenderPipeline(const graphics::GraphicsPipelineDesc& desc) noexcept;
			graphics::GraphicsDescriptorSetPtr createDescriptorSet(const graphics::GraphicsDescriptorSetDesc& desc) noexcept;
			graphics::GraphicsDescriptorSetLayoutPtr createDescriptorSetLayout(const graphics::GraphicsDescriptorSetLayoutDesc& desc) noexcept;
			graphics::GraphicsDescriptorPoolPtr createDescriptorPool(const graphics::GraphicsDescriptorPoolDesc& desc) noexcept;

			void render(graphics::GraphicsContext& context) noexcept;

		private:
			void setupFramebuffers(std::uint32_t w, std::uint32_t h) except;

		private:
			RenderSystem(const RenderSystem&) = delete;
			RenderSystem& operator=(const RenderSystem&) = delete;

		private:
			std::uint32_t width_, height_;

			graphics::GraphicsFramebufferPtr fbo_;
			graphics::GraphicsTexturePtr colorTexture_;
			graphics::GraphicsTexturePtr depthTexture_;

			graphics::GraphicsDevicePtr device_;
		};
	}
}

#endif