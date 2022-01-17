#pragma once
class dataHandler
{

public:

	static void readSettings();
};

namespace settings 
{
	extern float bckWpnStaminaPenaltyMultPlayer;
	extern float bckWpnStaminaPenaltyMultNPC;
	extern float bckShdStaminaPenaltyMultPlayer;
	extern float bckShdStaminaPenaltyMultNPC;
	extern bool guardBreak;
}