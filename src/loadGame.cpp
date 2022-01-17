#include "loadGame.h"
#include "hooks.h"
#include "dataHandler.h"
namespace loadGame {
	void EventCallBACK(SKSE::MessagingInterface::Message* msg)
	{
		if (msg->type == SKSE::MessagingInterface::kDataLoaded) {
			INFO("data loaded, initializing...");
			dataHandler::readSettings();
			INFO("initialization complete!");
		}
	}


};