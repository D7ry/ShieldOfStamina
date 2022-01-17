#include "dataHandler.h"
#include "SimpleIni.h"
void dataHandler::readSettings() {
	INFO("reading settings");
	using namespace settings;
	CSimpleIniA ini;
#define SETTINGFILE_PATH "Data\\SKSE\\Plugins\\ShieldOfStamina.ini"
	ini.LoadFile(SETTINGFILE_PATH);
	bckWpnStaminaPenaltyMultPlayer = static_cast<float>(ini.GetLongValue("General", "bckWpnStaminaPenaltyMultPlayer", 1));
	bckWpnStaminaPenaltyMultNPC = static_cast<float>(ini.GetLongValue("General", "bckWpnStaminaPenaltyMultNPC", 1));
	bckShdStaminaPenaltyMultPlayer = static_cast<float>(ini.GetLongValue("General", "bckShdStaminaPenaltyMultPlayer", 1));
	bckShdStaminaPenaltyMultNPC = static_cast<float>(ini.GetLongValue("General", "bckShdStaminaPenaltyMultNPC", 1));
	guardBreak = ini.GetBoolValue("General", "GuardBreak", true);
}

namespace settings
{
	float bckWpnStaminaPenaltyMultPlayer = 1;
	float bckWpnStaminaPenaltyMultNPC = 1;
	float bckShdStaminaPenaltyMultPlayer = 1;
	float bckShdStaminaPenaltyMultNPC = 1;
	bool guardBreak = true;
}