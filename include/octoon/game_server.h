#ifndef OCTOON_GAME_SERVER_H_
#define OCTOON_GAME_SERVER_H_

#include <octoon/game_types.h>
#include <octoon/runtime/any.h>
#include <octoon/runtime/sigslot.h>
#include <map>

namespace octoon
{
	class OCTOON_EXPORT GameServer final : public runtime::RttiInterface
	{
		OctoonDeclareSubClass(GameServer, runtime::RttiInterface)
	public:
		GameServer() noexcept;
		~GameServer() noexcept;

		void setActive(bool active) except;
		bool getActive() const noexcept;

		void setGameListener(GameListenerPtr&& listener) noexcept;
		void setGameListener(const GameListenerPtr& listener) noexcept;
		const GameListenerPtr& getGameListener() const noexcept;

		bool isQuitRequest() const noexcept;

		bool openScene(const std::string& scene_name) noexcept;
		void closeScene(const std::string& scene_name) noexcept;

		bool addScene(const GameScenePtr& scene) noexcept;
		void closeScene(const GameScenePtr& scene) noexcept;

		GameScenePtr findScene(const std::string& scene_name) noexcept;
		const GameScenes& getScenes() const noexcept;

		template<typename T, typename ...Args, typename = std::enable_if_t<std::is_base_of<GameFeature, T>::value>>
		void addFeature(Args&&... args) except { this->addFeature(std::make_unique<T>(std::forward<Args>(args)...)); }
		void addFeature(GameFeaturePtr&& component) except;

		template<typename T, typename = std::enable_if_t<std::is_base_of<GameFeature, T>::value>>
		T* getFeature() const noexcept { return dynamic_cast<T*>(this->getFeature(T::RTTI)); }
		GameFeature* getFeature(const runtime::Rtti* rtti) const noexcept;
		GameFeature* getFeature(const runtime::Rtti& rtti) const noexcept;

		const GameFeatures& getFeatures() const noexcept;

		template<typename T, typename = std::enable_if_t<std::is_base_of<GameFeature, T>::value>>
		void removeFeature() noexcept { this->removeFeature(T::RTTI); }
		void removeFeature(const runtime::Rtti* rtti) noexcept;
		void removeFeature(const runtime::Rtti& rtti) noexcept;
		void removeFeature(const GameFeaturePtr& feature) noexcept;

		void cleanupAll() noexcept;
		void cleanupScenes() noexcept;
		void cleanupFeatures() noexcept;

		void sendMessage(const std::string& event, const runtime::any& data = nullptr) noexcept;
		void addMessageListener(const std::string& event, std::function<void(const runtime::any&)> listener) noexcept;
		void removeMessageListener(const std::string& event, std::function<void(const runtime::any&)> listener) noexcept;

		GameApp* getGameApp() noexcept;

		void update() noexcept(false);

	private:
		void onActivate() except;
		void onDeactivate() noexcept;

	private:
		friend GameApp;
		void setGameApp(GameApp* app) noexcept;

	private:
		GameServer(const GameServer&) noexcept = delete;
		GameServer& operator=(const GameServer&) noexcept = delete;

	private:
		bool isActived_;
		bool isQuitRequest_;

		GameScenes scenes_;
		GameFeatures features_;

		GameApp* gameApp_;
		GameListenerPtr listener_;
		std::map<std::string, runtime::signal<void(const runtime::any&)>> dispatchEvents_;
	};
}

#endif