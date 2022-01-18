#pragma once
class dataHandler
{

public:

	static void readSettings();
};

namespace settings 
{
	extern float bckShdStaminaMult_PC_Block_NPC;
	extern float bckWpnStaminaMult_PC_Block_NPC;

	extern float bckShdStaminaMult_NPC_Block_PC; //stamina penalty mult for NPCs blockign a player hit with a shield
	extern float bckWpnStaminaMult_NPC_Block_PC;

	extern float bckShdStaminaMult_NPC_Block_NPC;
	extern float bckWpnStaminaMult_NPC_Block_NPC;

	extern bool guardBreak;
	extern bool noRegenOnBlock;
}