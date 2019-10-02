#include <MiscTab.h>
#include <UpdateCheck.h>
#include <ImGuiExtensions.h>
#include <imgui/imgui.h>
#include <Utility.h>
#include <Input.h>

namespace GW2Radial
{
DEFINE_SINGLETON(MiscTab);

MiscTab::MiscTab():
shubiaoPOSX_(u8"方块大小", "shubiaoPOSX", "shubiao", 50.0f),
shubiaoPOSY_(u8"方块大小", "shubiaoPOSY", "shubiao", 50.0f),
shubiaoRED_(u8"方块颜色", "shubiaoRED", "shubiao", 1.0f),
shubiaoGRE_(u8"方块颜色", "shubiaoGRE", "shubiao", 0.0f),
shubiaoBLU_(u8"方块颜色", "shubiaoBLU", "shubiao", 0.0f),
shubiaoALH_(u8"方块颜色", "shubiaoALH", "shubiao", 1.0f),
showboostime_(u8"总是显示BOSS计时器", "showboostime", "shubiao", true),
//getmingtian_(u8"获取明天的游戏日常", "getmingtian", "shubiao", true)
getweb_(u8"获取网页日常", "getweb", "shubiao", true),
showfankuai_(u8"总是显示鼠标跟随方块", "showfankuai_", "shubiao", true),
jiemiandaxiao_(u8"界面大小", "jiemiandaxiao_", "shubiao", 1.0f),
shubiaofankuaiyangshi_(u8"方块样式", "shubiaofankuaiyangshi_", "shubiao", 0),
zhengtitoumingdu_(u8"透明度", "toumingdu_", "shubiao", 0.44f),
jianyimoshi_(u8"简易模式(只显示前两行BOSS)", "showfankuai_", "shubiao", true)
{
	SettingsMenu::i()->AddImplementer(this);
}

MiscTab::~MiscTab()
{
	if(auto i = SettingsMenu::iNoInit(); i)
		i->RemoveImplementer(this);
}
void MiscTab::DrawMenu()
{
	//if(auto uc = UpdateCheck::iNoInit(); uc)
	//	ImGuiConfigurationWrapper(ImGui::Checkbox, uc->checkEnabled_);
	if(auto i = Input::iNoInit(); i)
		ImGuiConfigurationWrapper(ImGui::Checkbox, i->distinguishLeftRight_);
	ImGui::Text(u8"鼠标跟随模块设置");
	std::vector<const char*> shubiaoyanhgsh(3);

	shubiaoyanhgsh[0] = u8"方块";
	shubiaoyanhgsh[1] = u8"十字";
	shubiaoyanhgsh[2] = u8"圆形";


	bool (*cmsb)(const char*, int*, const char* const*, int, int) = &ImGui::Combo;
	ImGuiConfigurationWrapper(cmsb, shubiaofankuaiyangshi_, shubiaoyanhgsh.data(), 3, -1);

	if (shubiaofankuaiyangshi_.value() == 2)
	{
		bool(*POS)(const char*, float*, float, float, const char*, float) = &ImGui::SliderFloat;
		ImGuiConfigurationWrapper(POS, u8"方块大小", shubiaoPOSX_, 20.0f, 100.0f, "%.F", 1.0f);
}
	else
	{
		bool(*POS)(const char*, float*, float, float, const char*, float) = &ImGui::SliderFloat2;
		ImGuiConfigurationWrapper(POS, u8"方块大小", shubiaoPOSX_, shubiaoPOSY_, 5.0f, 200.0f, "%.F", 1.0f);
	}

	bool(*cl)(const char*, float*, ImGuiInputTextFlags) = &ImGui::ColorEdit4;
	ImGuiConfigurationWrapper(cl, u8"方块颜色", shubiaoRED_, shubiaoGRE_, shubiaoBLU_, shubiaoALH_, ImGuiColorEditFlags_AlphaBar);
	ImGuiConfigurationWrapper(&ImGui::Checkbox, showfankuai_);//总是现实鼠标方块
	ImGui::Text(u8"BOSS计时器设置");
	ImGuiConfigurationWrapper(&ImGui::SliderFloat, jiemiandaxiao_, 0.52f, 3.0f, "%.2f", 1.0f);
	ImGuiConfigurationWrapper(&ImGui::SliderFloat, zhengtitoumingdu_, 0.01f, 1.0f,"%.2f",1.0f);
	ImGuiConfigurationWrapper(&ImGui::Checkbox, jianyimoshi_);//getmingtian_
	ImGuiConfigurationWrapper(&ImGui::Checkbox, showboostime_);//getmingtian_
	//ImGuiConfigurationWrapper(&ImGui::Checkbox, getmingtian_);
	ImGuiConfigurationWrapper(&ImGui::Checkbox, getweb_);
	ImGui::PopItemWidth();

#if 0
	ImGui::Separator();

	ImGui::Text("Use these buttons to bind the respective key in your game's settings menu:");

	ImGui::InputInt("Virtual Key", reinterpret_cast<int*>(&vk_), 1, 100, ImGuiInputTextFlags_CharsHexadecimal);

	ImGui::Text(utf8_encode(GetKeyName(vk_)).c_str());

	if(ImGui::Button("Send"))
	{
		Input::i()->SendKeybind({ vk_ });
	}
#elif 0
	const auto btnWidth = ImGui::GetWindowWidth() * 0.25f - ImGui::GetStyle().FramePadding.x * 2;

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			const uint vk = VK_F13 + i * 4 + j;
			if(ImGui::Button(utf8_encode(GetKeyName(vk)).c_str(), ImVec2(btnWidth, 0)))
			{
				Input::i()->SendKeybind({ vk });
			}

			if(j < 3)
				ImGui::SameLine();
		}
	}
#endif
}

}
