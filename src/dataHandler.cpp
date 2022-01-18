#include "dataHandler.h"
#include "SimpleIni.h"
void dataHandler::readSettings() {
	INFO("reading settings");
	using namespace settings;
	CSimpleIniA ini;
#define SETTINGFILE_PATH "Data\\SKSE\\Plugins\\ShieldOfStamina.ini"
	ini.LoadFile(SETTINGFILE_PATH);
	bckShdStaminaMult_PC_Block_NPC = static_cast<float>(ini.GetLongValue("General", "bckShdStaminaMult_PC_Block_NPC", 1));
	bckWpnStaminaMult_PC_Block_NPC = static_cast<float>(ini.GetLongValue("General", "bckWpnStaminaMult_PC_Block_NPC", 1));
	bckShdStaminaMult_NPC_Block_PC = static_cast<float>(ini.GetLongValue("General", "bckShdStaminaMult_NPC_Block_PC", 1));
	bckWpnStaminaMult_NPC_Block_PC = static_cast<float>(ini.GetLongValue("General", "bckWpnStaminaMult_NPC_Block_PC", 1));
	bckShdStaminaMult_NPC_Block_NPC = static_cast<float>(ini.GetLongValue("General", "bckShdStaminaMult_NPC_Block_NPC", 1));
	bckWpnStaminaMult_NPC_Block_NPC = static_cast<float>(ini.GetLongValue("General", "bckWpnStaminaMult_NPC_Block_NPC", 1));

	guardBreak = ini.GetBoolValue("General", "GuardBreak", true);
	noRegenOnBlock = ini.GetBoolValue("General", "noRegenOnBlock", true);
}

namespace settings
{
	float bckShdStaminaMult_PC_Block_NPC = 1;
	float bckWpnStaminaMult_PC_Block_NPC = 1;

	float bckShdStaminaMult_NPC_Block_PC = 1; //stamina penalty mult for NPCs blockign a player hit with a shield
	float bckWpnStaminaMult_NPC_Block_PC = 1;

	float bckShdStaminaMult_NPC_Block_NPC = 1;
	float bckWpnStaminaMult_NPC_Block_NPC = 1;

	bool guardBreak = true;
	bool noRegenOnBlock = true;
}