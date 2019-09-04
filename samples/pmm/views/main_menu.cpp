#include "main_menu.h"

#include <octoon/octoon.h>
#include <octoon/ui/imgui.h>

using namespace octoon;

namespace MysticLit
{
	OctoonImplementSubClass(MainMenu, octoon::GameComponent, "MainMenu")

	MainMenu::MainMenu() noexcept
		: isShowedMainMenu_(true)
		, isOfflineMode_(false)
	{
	}

	MainMenu::~MainMenu() noexcept
	{
	}

	void
	MainMenu::onActivate() noexcept
	{
		this->addComponentDispatch(octoon::GameDispatchType::Gui);
	}

	void
	MainMenu::onDeactivate() noexcept
	{
		this->removeComponentDispatchs();
	}

	void
	MainMenu::onGui() noexcept
	{
		if (!isShowedMainMenu_)
			return;

		auto& style = imgui::getStyleDefault();
		imgui::pushStyleVar(imgui::GuiStyleVar::WindowPadding, math::float2(style.WindowPadding.x * 2, style.WindowPadding.y));

		if (imgui::beginMainMenuBar())
		{
			math::float2 size = imgui::getDisplaySize();
			size.y -= imgui::getWindowHeight();

			imgui::rootDock(math::float2(0, imgui::getWindowHeight()), size);
			imgui::pushStyleColor(imgui::GuiCol::Border, math::float4::Zero);

			if (imgui::beginMenu(u8"�ļ�"))
			{
				if (imgui::menuItem(u8"��", "CTRL+O")) { this->sendMessage("editor:menu:file:open"); }
				if (imgui::menuItem(u8"����", "CTRL+S")) { this->sendMessage("editor:menu:file:save"); }
				if (imgui::menuItem(u8"���Ϊ...", "CTRL+SHIFT+S")) { this->sendMessage("editor:menu:file:saveAs"); }

				imgui::separator();

				if (imgui::menuItem(u8"���ͼ��", "CTRL+B")) { this->sendMessage("editor:menu:file:picture"); }
				if (imgui::menuItem(u8"�����Ƶ", "CTRL+B")) { this->sendMessage("editor:menu:file:video"); }

				imgui::separator();

				if (imgui::menuItem(u8"����ģ��")) { this->sendMessage("editor:menu:file:import"); }
				if (imgui::menuItem(u8"����ģ��")) { this->sendMessage("editor:menu:file:export"); }

				imgui::separator();

				if (imgui::menuItem(u8"�˳�")) { this->sendMessage("editor:menu:file:exit"); }

				imgui::endMenu();
			}

			if (imgui::beginMenu(u8"����"))
			{
				if (imgui::menuItem(u8"���������", "CTRL+I")) { this->sendMessage("editor:menu:enviroment:hdri"); };
				imgui::endMenu();
			}

			if (imgui::beginMenu(u8"����"))
			{
				if (imgui::menuItem(u8"��ʼ��Ⱦ")) { this->sendMessage("editor:menu:setting:render", true); }
				if (imgui::menuItem(u8"ֹͣ��Ⱦ")) { this->sendMessage("editor:menu:setting:render", false); }

				imgui::separator();

				if (imgui::menuItem(u8"����ģʽ", "CTRL+P", isOfflineMode_))
				{
					this->sendMessage("editor:menu:setting:mode", !isOfflineMode_);
					isOfflineMode_ = !isOfflineMode_;
				}

				imgui::endMenu();
			}

			if (imgui::beginMenu(u8"����"))
			{
				if (imgui::menuItem(u8"����")) { this->sendMessage("editor:menu:help:about"); }
				imgui::endMenu();
			}

			imgui::popStyleColor();

			imgui::endMainMenuBar();
		}

		imgui::popStyleVar();
	}

	octoon::GameComponentPtr
	MainMenu::clone() const noexcept
	{
		return std::make_shared<MainMenu>();
	}
}