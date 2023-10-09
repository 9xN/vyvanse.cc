#include <string>
#include "Cheats.h"
#include "Render.hpp"
#include "MenuConfig.hpp"
#include "Utils/ConfigMenu.hpp"
#include "Utils/ConfigSaver.hpp"

void Cheats::Menu()
{
	ImGui::Begin("vyvanse.cc",nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	
	{
		ImGui::BeginTabBar("vyvanse.cc", ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_NoTooltip);
		// esp menu
		if (ImGui::BeginTabItem("ESP"))
		{
//			ImGui::Columns(2, nullptr, false);
//			ImGui::SetColumnOffset(1, 250.0f);

			Gui.MyCheckBox("Enabled", &MenuConfig::ESPenbled);
			ImGui::Checkbox("Box", &MenuConfig::ShowBoxESP);
			ImGui::SameLine();
			ImGui::ColorEdit4("##BoxColor", reinterpret_cast<float*>(&MenuConfig::BoxColor), ImGuiColorEditFlags_NoInputs);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(MenuConfig::ComboWidth);
			ImGui::Combo("BoxStyle", &MenuConfig::BoxType, "Normal\0Dynamic");

			ImGui::Checkbox("Skeleton", &MenuConfig::ShowBoneESP);
			ImGui::SameLine();
			ImGui::ColorEdit4("##BoneColor", reinterpret_cast<float*>(&MenuConfig::BoneColor), ImGuiColorEditFlags_NoInputs);

			ImGui::Checkbox("EyeRay", &MenuConfig::ShowEyeRay);
			ImGui::SameLine();
			ImGui::ColorEdit4("##EyeRay", reinterpret_cast<float*>(&MenuConfig::EyeRayColor), ImGuiColorEditFlags_NoInputs);

			ImGui::Checkbox("HealthBar", &MenuConfig::ShowHealthBar);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(MenuConfig::ComboWidth); 
			ImGui::Combo("BarStyle", &MenuConfig::HealthBarType, "Vetical\0Horizontal");
			
			ImGui::Checkbox("Weapon", &MenuConfig::ShowWeaponESP);
			ImGui::Checkbox("Name", &MenuConfig::ShowPlayerName);
		
			ImGui::Checkbox("SnapLine", &MenuConfig::ShowLineToEnemy);
			ImGui::SameLine();
			ImGui::ColorEdit4("##LineToEnemyColor", reinterpret_cast<float*>(&MenuConfig::LineToEnemyColor), ImGuiColorEditFlags_NoInputs);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(MenuConfig::ComboWidth);
			ImGui::Combo("Line Pos", &MenuConfig::LinePos, "Top\0Center\0Bottom");

//			ImGui::NextColumn();
			ImGui::NewLine();
			ImGui::Checkbox("Penis", &MenuConfig::ShowPenis);
			ImGui::SameLine();
			ImGui::ColorEdit4("##PenisColor", reinterpret_cast<float*>(&MenuConfig::PenisColor), ImGuiColorEditFlags_NoInputs);
			ImGui::SliderFloat("Length", &MenuConfig::PenisLength, 1.0f, 50.0f, "%.1f");
			ImGui::SliderFloat("Size", &MenuConfig::PenisSize, 1.3f, 5.0f, "%.3f");

//			ImGui::Columns(1);
			ImGui::EndTabItem();
		}

		// aimbot menu
		if (ImGui::BeginTabItem("AimBot"))
		{
			Gui.MyCheckBox("Enabled", &MenuConfig::AimBot);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(75.f);
			if (ImGui::Combo("Key", &MenuConfig::AimBotHotKey, "LALT\0RBUTTON\0XBUTTON1\0XBUTTON2\0CAPITAL\0SHIFT\0CONTROL"))
			{
				AimControl::SetHotKey(MenuConfig::AimBotHotKey);
			}

			ImGui::Checkbox("Draw Fov", &MenuConfig::DrawFov);
			ImGui::SameLine();
			ImGui::ColorEdit4("##FovCircleColor", reinterpret_cast<float*>(&MenuConfig::FovCircleColor), ImGuiColorEditFlags_NoInputs);
			ImGui::Checkbox("Visible Only", &MenuConfig::VisibleCheck);

			float FovMin = 0.1f, FovMax = 89.f;
			float SmoothMin = 0.1f, SmoothMax = 1.f;
			ImGui::SliderFloat("Fov", &AimControl::AimFov, 0.0f, 25.0f, "%.1f", ImGuiSliderFlags_Logarithmic);
			ImGui::SliderFloat("Speed", &AimControl::Smooth, 0.0f, 1.0f, "%.1f");
			if (ImGui::Combo("Bone", &MenuConfig::AimPosition, "Head\0Neck\0Chest\0Penis"))
			{
				switch (MenuConfig::AimPosition)
				{
				case 0:
					MenuConfig::AimPositionIndex = BONEINDEX::head;
					break;
				case 1:
					MenuConfig::AimPositionIndex = BONEINDEX::neck_0;
					break;
				case 2:
					MenuConfig::AimPositionIndex = BONEINDEX::spine_1;
					break;
				case 3:
					MenuConfig::AimPositionIndex = BONEINDEX::pelvis;
					break;
				default:
					break;
				}
			}
			ImGui::EndTabItem();
		}

		// RCS menu
		if (ImGui::BeginTabItem("RCS"))
		{
			Gui.MyCheckBox("Enabled", &MenuConfig::RCS);
			ImGui::SliderInt("Start Bullet", &AimControl::RCSBullet, 1, 6, "%d");
			ImGui::SliderFloat("Yaw", &AimControl::RCSScale.x, 0.f, 2.f, "%.1f");
			ImGui::SliderFloat("Pitch", &AimControl::RCSScale.y, 0.f, 2.f, "%.1f");

			ImGui::EndTabItem();
		}

		// Radar menu
		if (ImGui::BeginTabItem("Radar"))
		{
			Gui.MyCheckBox("Enabled", &MenuConfig::ShowRadar);
			ImGui::SetNextItemWidth(MenuConfig::ComboWidth + 20);
			ImGui::Combo("Style", &MenuConfig::RadarType, "Circle\0Arrow\0Circle & Arrow");
			ImGui::Checkbox("Custom", &MenuConfig::customRadar);
			
			if (MenuConfig::customRadar)
			{
				ImGui::NewLine();
				ImGui::Checkbox("Cross Line", &MenuConfig::ShowRadarCrossLine);
				ImGui::SameLine();
				ImGui::ColorEdit4("##CrossLineColor", reinterpret_cast<float*>(&MenuConfig::RadarCrossLineColor), ImGuiColorEditFlags_NoInputs);
				float RadarPointSizeProportionMin = 0.8f, RadarPointSizeProportionMax = 2.f;
				float ProportionMin = 500.f, ProportionMax = 3300.f;
				float RadarRangeMin = 100.f, RadarRangeMax = 300.f;
				ImGui::SliderFloat("PointSize", &MenuConfig::RadarPointSizeProportion, RadarPointSizeProportionMin, RadarPointSizeProportionMax, "%.1f");
				ImGui::SliderFloat("Proportion", &MenuConfig::Proportion, ProportionMin, ProportionMax, "%.1f");
				ImGui::SliderFloat("Range", &MenuConfig::RadarRange, RadarRangeMin, RadarRangeMax, "%.1f");
			}
			


//			ImGui::Checkbox("Fov Line", &MenuConfig::ShowFovLine);
//			ImGui::SameLine();
//			ImGui::ColorEdit4("##FovLineColor", reinterpret_cast<float*>(&MenuConfig::FovLineColor), ImGuiColorEditFlags_NoInputs);
//			float FovLineSizeMin = 20.f, FovLineSizeMax = 120.f;
//			Gui.SliderScalarEx1("Length", ImGuiDataType_Float, &MenuConfig::FovLineSize, &FovLineSizeMin, &FovLineSizeMax, "%.1f", ImGuiSliderFlags_None);

			ImGui::EndTabItem();
		}

		// TriggerBot
		if (ImGui::BeginTabItem("TriggerBot"))
		{
			Gui.MyCheckBox("Enabled", &MenuConfig::TriggerBot);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(MenuConfig::ComboWidth);
			if (ImGui::Combo("Key", &MenuConfig::TriggerHotKey, "LALT\0RBUTTON\0XBUTTON1\0XBUTTON2\0CAPITAL\0SHIFT\0CONTROL"))
			{
				TriggerBot::SetHotKey(MenuConfig::TriggerHotKey);
			}

			DWORD TriggerDelayMin = 10, TriggerDelayMax = 300;
			ImGui::SliderInt("Delay", &TriggerBot::TriggerDelay, TriggerDelayMin, TriggerDelayMax, "%d ms", ImGuiSliderFlags_None);

			ImGui::EndTabItem();
		}

		// Misc
		if (ImGui::BeginTabItem("Misc"))
		{
			ImGui::Columns(2, nullptr, false);
			ImGui::SetColumnOffset(1, 250.0f);

			if (ImGui::Combo("Style", &MenuConfig::MenuStyle, "Default\0Enemy\0Classic"))
				Render::UpdateStyle(MenuConfig::MenuStyle);

			ImGui::Checkbox("Headshot Line", &MenuConfig::ShowHeadShootLine);
			ImGui::SameLine();
			ImGui::ColorEdit4("##HeadShootLineColor", reinterpret_cast<float*>(&MenuConfig::HeadShootLineColor), ImGuiColorEditFlags_NoInputs);
			ImGui::Checkbox("Crosshair", &MenuConfig::ShowCrossHair);
			ImGui::SameLine();
			ImGui::ColorEdit4("##CrossHairColor", reinterpret_cast<float*>(&MenuConfig::CrossHairColor), ImGuiColorEditFlags_NoInputs);
//			ImGui::SetNextItemWidth(MenuConfig::SliderWidth);
//			ImGui::SliderFloat("Crosshair Size", &MenuConfig::CrossHairSize, 15.f, 100.f, "%.1f");
//			ImGui::Checkbox("Bunny Hop", &MenuConfig::Bhop);

			ImGui::NextColumn();
			ImGui::Checkbox("Team Check", &MenuConfig::TeamCheck);
			ImGui::Checkbox("Bypass OBS", &MenuConfig::BypassOBS);

			ImGui::Columns(1);
			ImGui::EndTabItem();
		}

		// Config
		ConfigMenu::RenderConfigMenu();

		// About
		if (ImGui::BeginTabItem("README"))
		{
			// Since it's already the MIT license, there's no need to do that.
			// ImGui::TextColored(ImColor(255, 0, 0, 255), "Reselling prohibited");

			ImGui::Text("Author: github.com/9xN");
			ImGui::NewLine();
			ImGui::TextColored(ImColor(0, 200, 255, 255), "Last update: 2023-10-6");
			ImGui::NewLine();

			ImGui::Text("Offsets:");
			ImGui::Text("EntityList:");
			ImGui::SameLine();
			ImGui::Text(std::to_string(Offset::EntityList).c_str());
			ImGui::Text("Matrix:");
			ImGui::SameLine();
			ImGui::Text(std::to_string(Offset::Matrix).c_str());
			ImGui::Text("LocalPlayerController:");
			ImGui::SameLine();
			ImGui::Text(std::to_string(Offset::LocalPlayerController).c_str());
			ImGui::Text("ViewAngle:");
			ImGui::SameLine();
			ImGui::Text(std::to_string(Offset::ViewAngle).c_str());
			ImGui::Text("LocalPlayerPawn:");
			ImGui::SameLine();
			ImGui::Text(std::to_string(Offset::LocalPlayerPawn).c_str());

			ImGui::EndTabItem();
		}

	}ImGui::End();
}

void Cheats::RadarSetting(Base_Radar& Radar)
{
	// Radar window
	ImGui::SetNextWindowBgAlpha(0.1f);
	ImGui::Begin("Radar", 0, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize({ MenuConfig::RadarRange * 2,MenuConfig::RadarRange * 2 });
	
	if (!MenuConfig::customRadar)
	{
		ImGui::SetWindowPos(ImVec2(0, 0));
		MenuConfig::ShowRadarCrossLine = false;
		MenuConfig::Proportion = 3300.f;
		MenuConfig::RadarPointSizeProportion = 1.f;
		MenuConfig::RadarRange = 150.f;
	}
		

	// Radar.SetPos({ Gui.Window.Size.x / 2,Gui.Window.Size.y / 2 });
	Radar.SetDrawList(ImGui::GetWindowDrawList());
	Radar.SetPos({ ImGui::GetWindowPos().x + MenuConfig::RadarRange, ImGui::GetWindowPos().y + MenuConfig::RadarRange });
	Radar.SetProportion(MenuConfig::Proportion);
	Radar.SetRange(MenuConfig::RadarRange);
	Radar.SetSize(MenuConfig::RadarRange * 2);
	Radar.SetCrossColor(MenuConfig::RadarCrossLineColor);

	Radar.ArcArrowSize *= MenuConfig::RadarPointSizeProportion;
	Radar.ArrowSize *= MenuConfig::RadarPointSizeProportion;
	Radar.CircleSize *= MenuConfig::RadarPointSizeProportion;

	Radar.ShowCrossLine = MenuConfig::ShowRadarCrossLine;
	Radar.Opened = true;
}

void Cheats::RenderCrossHair(ImDrawList* drawList) noexcept
{
	if (!MenuConfig::ShowCrossHair)
		return;

	Render::DrawCrossHair(drawList, ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), ImGui::ColorConvertFloat4ToU32(MenuConfig::CrossHairColor));
}

void Cheats::FakeBhop()
{
	static DWORD lastTick = 0;
	DWORD currentTick = GetTickCount();

	if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && currentTick - lastTick >= 20)
	{
		keybd_event(VK_SPACE, 0, 0, 0);
		keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
		lastTick = currentTick;
	}
}

void Cheats::Run()
{	
	// Show menu
	static DWORD lastTick = 0; 
	DWORD currentTick = GetTickCount(); 
	if ((GetAsyncKeyState(VK_INSERT) & 0x8000) && currentTick - lastTick >= 150){
		// Check key state per 150ms once to avoid loop
		MenuConfig::ShowMenu = !MenuConfig::ShowMenu;
		lastTick = currentTick; 
	}
	if(MenuConfig::ShowMenu)
		Menu();

	// Update matrix
	if(!ProcessMgr.ReadMemory(gGame.GetMatrixAddress(), gGame.View.Matrix,64))
		return;

	// Update EntityList Entry
	gGame.UpdateEntityListEntry();

	DWORD64 LocalControllerAddress = 0;
	DWORD64 LocalPawnAddress = 0;

	if (!ProcessMgr.ReadMemory(gGame.GetLocalControllerAddress(), LocalControllerAddress))
		return;
	if (!ProcessMgr.ReadMemory(gGame.GetLocalPawnAddress(), LocalPawnAddress))
		return;

	// LocalEntity
	CEntity LocalEntity;
	if (!LocalEntity.UpdateController(LocalControllerAddress))
		return;
	if (!LocalEntity.UpdatePawn(LocalPawnAddress))
		return;

	// HealthBar Map
	static std::map<DWORD64, Render::HealthBar> HealthBarMap;

	// AimBot data
	float DistanceToSight = 0;
	float MaxAimDistance = 100000;
	Vec3  HeadPos{ 0,0,0 };
	Vec3  AimPos{ 0,0,0 };

	// Radar Data
	Base_Radar Radar;
	if (MenuConfig::ShowRadar)
		RadarSetting(Radar);

	for (int i = 0; i < 64; i++)
	{
		CEntity Entity;
		DWORD64 EntityAddress = 0;
		if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListEntry() + (i + 1) * 0x78, EntityAddress))
			continue;
		if (EntityAddress == LocalEntity.Controller.Address)
			continue;
		if (!Entity.UpdateController(EntityAddress))
			continue;
		if (!Entity.UpdatePawn(Entity.Pawn.Address))
			continue;

		if (MenuConfig::TeamCheck && Entity.Controller.TeamID == LocalEntity.Controller.TeamID)
			continue;
		if (!Entity.IsAlive())
			continue;
//		if (MenuConfig::VisibleCheck && (!Entity.Pawn.bSpottedByMask > 0))
//			continue;


		// Add entity to radar
		if (MenuConfig::ShowRadar)
			Radar.AddPoint(LocalEntity.Pawn.Pos, LocalEntity.Pawn.ViewAngle.y, Entity.Pawn.Pos, ImColor(237, 85, 106, 200), MenuConfig::RadarType, Entity.Pawn.ViewAngle.y);

		if (!Entity.IsInScreen())
			continue;

		// Bone Debug
	/*	for (int BoneIndex = 0; BoneIndex < Entity.BoneData.BonePosList.size(); BoneIndex++)
		{
			Vec2 ScreenPos{};
			if (gGame.View.WorldToScreen(Entity.BoneData.BonePosList[BoneIndex].Pos, ScreenPos))
			{
				Gui.Text(std::to_string(BoneIndex), ScreenPos, ImColor(255, 255, 255, 255));
			}
		}*/

		DistanceToSight = Entity.GetBone().BonePosList[BONEINDEX::head].ScreenPos.DistanceTo({ Gui.Window.Size.x / 2,Gui.Window.Size.y / 2 });


		if (DistanceToSight < MaxAimDistance)
		{
			MaxAimDistance = DistanceToSight;
			if ((MenuConfig::VisibleCheck && Entity.Pawn.bSpottedByMask > 0) || !MenuConfig::VisibleCheck)
			{
				AimPos = Entity.GetBone().BonePosList[MenuConfig::AimPositionIndex].Pos;
				if (MenuConfig::AimPositionIndex == BONEINDEX::head)
					AimPos.z -= 1.f;
			}
		}
		

		if (MenuConfig::ESPenbled)
		{
			// Draw Bone
			Render::DrawBone(Entity, MenuConfig::BoneColor, 1.3f);

			// Draw Penis
			Render::ShowPenis(Entity, MenuConfig::PenisLength, MenuConfig::PenisColor, MenuConfig::PenisSize);

			// Draw eyeRay
			Render::ShowLosLine(Entity, 50.0f, MenuConfig::EyeRayColor, 1.3f);

			// Box
			ImVec4 Rect;
			switch (MenuConfig::BoxType)
			{
			case 0:
				Rect = Render::Get2DBox(Entity);
				break;
			case 1:
				Rect = Render::Get2DBoneRect(Entity);
				break;
			default:
				break;
			}

			// Snap Line
			if (MenuConfig::ShowLineToEnemy)
			{
				Render::LineToEnemy(Rect, MenuConfig::LineToEnemyColor, 1.2);
			}
				
			// Draw Box
			if (MenuConfig::ShowBoxESP)
				Gui.Rectangle({ Rect.x,Rect.y }, { Rect.z,Rect.w }, MenuConfig::BoxColor, 1.3);

			// Draw HealthBar
			if (MenuConfig::ShowHealthBar)
			{
				ImVec2 HealthBarPos, HealthBarSize;
				if (MenuConfig::HealthBarType == 0)
				{
					// Vertical
					HealthBarPos = { Rect.x - 10.f,Rect.y };
					HealthBarSize = { 7 ,Rect.w };
				}
				else
				{
					// Horizontal
					HealthBarPos = { Rect.x + Rect.z / 2 - 70 / 2,Rect.y - 13 };
					HealthBarSize = { 70,8 };
				}
				Render::DrawHealthBar(EntityAddress, 100, Entity.Controller.Health, HealthBarPos, HealthBarSize, MenuConfig::HealthBarType);
			}

			// Draw weaponName
			if (MenuConfig::ShowWeaponESP)
				Gui.StrokeText(Entity.Pawn.WeaponName, { Rect.x + Rect.z / 2,Rect.y + Rect.w }, ImColor(255, 255, 255, 255), 14, true);

			if (MenuConfig::ShowPlayerName)
			{
				if (MenuConfig::HealthBarType == 0)
					Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2,Rect.y - 14 }, ImColor(255, 255, 255, 255), 14, true);
				else
					Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2,Rect.y - 13 - 14 }, ImColor(255, 255, 255, 255), 14, true);
			}
		}
	}
	// Radar render
	if(MenuConfig::ShowRadar)
	{
		Radar.Render();
		ImGui::End();
	}

	// TriggerBot
	if (MenuConfig::TriggerBot && GetAsyncKeyState(TriggerBot::HotKey))
		TriggerBot::Run(LocalEntity);	

	// Fov line
	Render::DrawFov(LocalEntity, MenuConfig::FovLineSize, MenuConfig::FovLineColor, 1);

	// HeadShoot Line
	Render::HeadShootLine(LocalEntity, MenuConfig::HeadShootLineColor);
	
	// CrossHair
	RenderCrossHair(ImGui::GetBackgroundDrawList());

	// Aimbot
	if (MenuConfig::AimBot)
	{
		Render::DrawFovCircle(LocalEntity);

		if (GetAsyncKeyState(AimControl::HotKey))
		{
			
			if (AimPos != Vec3(0, 0, 0))
			{
				AimControl::AimBot(LocalEntity, LocalEntity.Pawn.CameraPos, AimPos);
			}
		}	
	}
	
	/*
	if (MenuConfig::Bhop)
	{
		FakeBhop();
	}
	*/
	
	
}
