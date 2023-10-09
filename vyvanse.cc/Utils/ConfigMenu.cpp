#include "ConfigMenu.hpp"
#include "../MenuConfig.hpp"
#include "ConfigSaver.hpp"
#include "../TriggerBot.h"
#include "../AimBot.hpp"
#include <filesystem>

namespace ConfigMenu {

	void RenderConfigMenu() {
		// Config
		if (ImGui::BeginTabItem("Config"))
		{
			ImGui::PushItemWidth(160.0f);

			static char configNameBuffer[128] = "New_Config";
			ImGui::InputText(" ", configNameBuffer, sizeof(configNameBuffer));
			ImGui::SameLine();
			if (ImGui::Button("Create Config", { 100.0f, 25.0f }))
			{
				std::string configFileName = std::string(configNameBuffer) + ".config";
				MyConfigSaver::SaveConfig(configFileName);
			}
			ImGui::Separator();

			static int selectedConfig = -1;

			const std::string configDir = std::filesystem::current_path().string();
			static std::vector<std::string> configFiles;

			configFiles.clear();
			for (const auto& entry : std::filesystem::directory_iterator(configDir))
			{
				if (entry.is_regular_file() && entry.path().extension() == ".config")
				{
					configFiles.push_back(entry.path().filename().string());
				}
			}

			for (int i = 0; i < configFiles.size(); ++i)
			{
				if (ImGui::Selectable(configFiles[i].c_str(), selectedConfig == i))
				{
					selectedConfig = i;
				}
			}

			if (selectedConfig != -1)
			{
				ImGui::Text("Selected: %s", configFiles[selectedConfig].c_str());
			}

			if (ImGui::Button("Load Selected", { 100.0f, 25.0f }) && selectedConfig >= 0 && selectedConfig < configFiles.size())
			{
				std::string selectedConfigFile = configFiles[selectedConfig];
				MyConfigSaver::LoadConfig(selectedConfigFile);
				// Because the style is switched when Combo is activated, the style should be manually updated here
				// Render::UpdateStyle(MenuConfig::MenuStyle);
				// Umm...Some problem occured
			}

			ImGui::SameLine();
			if (ImGui::Button("Save Selected", { 100.0f, 25.0f }) && selectedConfig >= 0 && selectedConfig < configFiles.size())
			{
				std::string selectedConfigFile = configFiles[selectedConfig];
				MyConfigSaver::SaveConfig(selectedConfigFile);
			}

			ImGui::SameLine();
			if (ImGui::Button("Delete Selected", { 100.0f, 25.0f }) && selectedConfig >= 0 && selectedConfig < configFiles.size())
				ImGui::OpenPopup("##reallyDelete");

			if (ImGui::BeginPopup("##reallyDelete"))
			{
				ImGui::TextUnformatted("Are you sure?");
				if (ImGui::Button("No", { 45.0f, 0.0f }))
					ImGui::CloseCurrentPopup();
				ImGui::SameLine();
				if (ImGui::Button("Yes", { 45.0f, 0.0f }))
				{
					// Delete
					std::string selectedConfigFile = configFiles[selectedConfig];
					std::string fullPath = configDir + "/" + selectedConfigFile;
					if (std::remove(fullPath.c_str()) == 0)
					{
						configFiles.erase(configFiles.begin() + selectedConfig);
						selectedConfig = -1;
					}
					else
					{
					}
					ImGui::CloseCurrentPopup();
				}
			ImGui::EndPopup();
			}

			ImGui::SameLine();
			if (ImGui::Button("Reset Config", { 100.0f, 25.0f }))
				ImGui::OpenPopup("##reallyReset");
			if (ImGui::BeginPopup("##reallyReset"))
			{
				ImGui::TextUnformatted("Are you sure?");
				if (ImGui::Button("No", { 45.0f, 0.0f }))
					ImGui::CloseCurrentPopup();
				ImGui::SameLine();
				if (ImGui::Button("Yes", { 45.0f, 0.0f }))
				{
					ConfigMenu::ResetToDefault();
					ImGui::CloseCurrentPopup();
				}	
				ImGui::EndPopup();
			}
			ImGui::EndTabItem();
		}
	}

	void ResetToDefault() {
		MenuConfig::ShowBoneESP = true;
		MenuConfig::ShowBoxESP = true;
		MenuConfig::ShowHealthBar = true;
		MenuConfig::ShowWeaponESP = false;
		MenuConfig::ShowEyeRay = false;
		MenuConfig::ShowPlayerName = true;
		MenuConfig::AimBot = false;
		MenuConfig::AimPosition = 0;
		MenuConfig::AimPositionIndex = BONEINDEX::head;
		MenuConfig::BoxType = 0;
		MenuConfig::HealthBarType = 0;
		MenuConfig::BoneColor = ImColor(0, 255, 255, 255);
		MenuConfig::BoxColor = ImColor(255, 80, 0, 255);
		MenuConfig::EyeRayColor = ImVec4(255, 0, 0, 255);
		MenuConfig::ShowMenu = true;
		MenuConfig::ShowRadar = false;
		MenuConfig::RadarRange = 150;
		MenuConfig::ShowRadarCrossLine = true;
		MenuConfig::RadarCrossLineColor = ImColor(220, 220, 220, 255);
		MenuConfig::RadarType = 2;
		MenuConfig::RadarPointSizeProportion = 1.f;
		MenuConfig::Proportion = 3300;
		MenuConfig::TriggerBot = false;
		MenuConfig::TeamCheck = true;
		MenuConfig::BypassOBS = false;
		MenuConfig::VisibleCheck = true;
		MenuConfig::ShowHeadShootLine = false;
		MenuConfig::HeadShootLineColor = ImColor(255, 255, 255, 200);
		MenuConfig::AimBotHotKey = 0;
		MenuConfig::ShowLineToEnemy = false;
		MenuConfig::FovLineSize = 60.0f;
		TriggerBot::TriggerDelay = 90;
		AimControl::RCSBullet = 1;
		TriggerBot::HotKey = VK_LMENU;
		AimControl::RCSScale = ImVec2(1.2f, 1.4f);
		MenuConfig::FovLineColor = ImVec4(55, 55, 55, 220);
		MenuConfig::LineToEnemyColor = ImVec4(255, 255, 255, 220);
		MenuConfig::ShowCrossHair = false;
		MenuConfig::CrossHairColor = ImColor(0, 255, 0, 255);
		MenuConfig::CrossHairSize = 75;

		MenuConfig::ESPenbled = false;

		MenuConfig::ShowPenis = false;
		MenuConfig::PenisLength = 15.f;
		MenuConfig::PenisSize = 1.3f;
		MenuConfig::PenisColor = ImColor(255, 0, 0, 200);

		MenuConfig::DrawFov = false;
		MenuConfig::FovCircleColor = ImColor(255, 255, 255, 255);
	}
}
