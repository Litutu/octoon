#include <octoon/animation_component.h>

namespace octoon
{
	OctoonImplementSubClass(AnimationComponent, GameComponent, "Animation")

	AnimationComponent::AnimationComponent() noexcept
	{
	}

	AnimationComponent::AnimationComponent(animation::AnimationClip<float>&& clip) noexcept
	{
		clips_.emplace_back(clip);
	}

	AnimationComponent::AnimationComponent(animation::AnimationClips<float>&& clips) noexcept
		: clips_(std::move(clips))
	{
	}

	AnimationComponent::AnimationComponent(const animation::AnimationClip<float>& clip) noexcept
	{
		clips_.emplace_back(clip);
	}

	AnimationComponent::AnimationComponent(const animation::AnimationClips<float>& clips) noexcept
		: clips_(clips)
	{
	}

	AnimationComponent::~AnimationComponent() noexcept
	{
	}

	void
	AnimationComponent::play() noexcept
	{
		this->addComponentDispatch(GameDispatchType::FrameBegin);
	}

	void
	AnimationComponent::pause() noexcept
	{
		this->removeComponentDispatch(GameDispatchType::FrameBegin);
	}

	void
	AnimationComponent::stop() noexcept
	{
		this->removeComponentDispatch(GameDispatchType::FrameBegin);
	}

	GameComponentPtr
	AnimationComponent::clone() const noexcept
	{
		return std::make_shared<AnimationComponent>();
	}

	void 
	AnimationComponent::onActivate() except
	{
	}

	void
	AnimationComponent::onDeactivate() noexcept
	{
		this->removeComponentDispatch(GameDispatchType::FrameBegin);
	}

	void
	AnimationComponent::onFrameBegin() except
	{
	}

	void
	AnimationComponent::onFrame() except
	{
	}

	void
	AnimationComponent::onFrameEnd() except
	{
	}
}