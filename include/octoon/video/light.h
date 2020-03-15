#ifndef OCTOON_LIGHT_H_
#define OCTOON_LIGHT_H_

#include <octoon/camera/camera.h>
#include <octoon/video/render_object.h>
#include <octoon/hal/graphics_texture.h>

namespace octoon::light
{
	enum class LightType : std::uint8_t
	{
		LightTypeSun,
		LightTypeDirectional,
		LightTypeAmbient,
		LightTypePoint,
		LightTypeSpot,
		LightTypeRectangle,
		LightTypeDisk,
		LightTypeTube,
		LightTypeEnvironment,
		LightTypeBeginRange = LightTypeSun,
		LightTypeEndRange = LightTypeEnvironment,
		LightTypeRangeSize = (LightTypeEndRange - LightTypeBeginRange + 1),
	};

	enum class ShadowMode : std::uint8_t
	{
		ShadowModeNone,
		ShadowModeHard,
		ShadowModeSoft,
		ShadowModeBeginRange = ShadowModeNone,
		ShadowModeEndRange = ShadowModeSoft,
		ShadowModeRangeSize = (ShadowModeEndRange - ShadowModeBeginRange + 1),
	};

	enum class ShadowQuality : std::uint8_t
	{
		ShadowQualityNone,
		ShadowQualityLow,
		ShadowQualityMedium,
		ShadowQualityHigh,
		ShadowQualityVeryHigh,
		ShadowQualityBeginRange = ShadowQualityNone,
		ShadowQualityEndRange = ShadowQualityVeryHigh,
		ShadowQualityRangeSize = (ShadowQualityEndRange - ShadowQualityBeginRange + 1),
	};

	class OCTOON_EXPORT Light final : public video::RenderObject, public video::RenderListener
	{
		OctoonDeclareSubClass(Light, video::RenderObject)
	public:
		Light() noexcept;
		virtual ~Light() noexcept;

		void setLightRange(float range) noexcept;
		void setLightType(LightType type) noexcept;
		void setLightIntensity(float intensity) noexcept;
		void setLightColor(const math::float3& color) noexcept;
		void setLightAttenuation(const math::float3& attenuation) noexcept;

		void setSpotInnerCone(float value) noexcept;
		void setSpotOuterCone(float value) noexcept;

		void setShadowBias(float bias) noexcept;
		void setShadowFactor(float factor) noexcept;
		void setShadowMode(ShadowMode shadowType) noexcept;

		void setGlobalIllumination(bool enable) noexcept;
		bool getGlobalIllumination() const noexcept;

		float getLightRange() const noexcept;
		float getLightIntensity() const noexcept;
		LightType getLightType() const noexcept;

		float getShadowBias() const noexcept;
		float getShadowFactor() const noexcept;
		ShadowMode getShadowMode() const noexcept;

		const math::float2& getSpotInnerCone() const noexcept;
		const math::float2& getSpotOuterCone() const noexcept;

		const math::float3& getLightColor() const noexcept;
		const math::float3& getLightAttenuation() const noexcept;

		void setSkyBox(const hal::GraphicsTexturePtr& texture) noexcept;
		const hal::GraphicsTexturePtr& getSkyBox() const noexcept;

		void setSkyLightingDiffuse(const hal::GraphicsTexturePtr& texture) noexcept;
		const hal::GraphicsTexturePtr& getSkyLightingDiffuse() const noexcept;

		void setSkyLightingSpecular(const hal::GraphicsTexturePtr& texture) noexcept;
		const hal::GraphicsTexturePtr& getSkyLightingSpecular() const noexcept;

		const std::shared_ptr<camera::Camera>& getCamera() const noexcept;

		video::RenderObjectPtr clone() const noexcept;

	private:
		bool setupShadowMap() noexcept;

		void destroyShadowMap() noexcept;
		void destroyReflectiveShadowMap() noexcept;

		void _updateTransform() noexcept;
		void _updateBoundingBox() noexcept;

	private:
		void onSceneChangeBefore() noexcept;
		void onSceneChangeAfter() noexcept;
			
		void onPreRender(const camera::Camera& camera) noexcept;
		void onPostRender(const camera::Camera& camera) noexcept;

		void onMoveAfter() noexcept;

	private:
		Light(const Light&) noexcept = delete;
		Light& operator=(const Light&) noexcept = delete;

	private:
		LightType _lightType;

		float _lightRange;
		float _lightIntensity;

		math::float3 _lightColor;
		math::float3 _lightAttenuation;

		math::float2 _spotInnerCone;
		math::float2 _spotOuterCone;

		bool _enableSoftShadow;
		bool _enableGlobalIllumination;

		float _shadowBias;
		float _shadowFactor;
		std::shared_ptr<camera::Camera> _shadowCamera;
		ShadowMode _shadowMode;

		hal::GraphicsTexturePtr _skybox;
		hal::GraphicsTexturePtr _skyDiffuseIBL;
		hal::GraphicsTexturePtr _skySpecularIBL;
	};
}

#endif