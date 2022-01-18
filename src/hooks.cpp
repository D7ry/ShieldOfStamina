#include "hooks.h"
#include "dataHandler.h"
namespace Utils {
	inline void damageav(RE::Actor* a, RE::ActorValue av, float val)
	{
		a->As<RE::ActorValueOwner>()->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, av, -val);
	}
}

/*stamina blocking*/
void hitEventHook::processHit(RE::Actor* target, RE::HitData& hitData) {
	//check iff hit is blocked
	int hitFlag = (int)hitData.flags;
	using HITFLAG = RE::HitData::Flag;
	if (!(hitFlag & (int)HITFLAG::kBlocked)) {
		return;
	}

	//nullPtr check in case Skyrim fucks up
	auto aggressor = hitData.aggressor.get();
	if (!target || !aggressor) {
		return;
	}

	bool isPlayerTarget = target->IsPlayerRef();
	bool isPlayerAggressor = aggressor->IsPlayerRef();
	float staminaDamageBase = hitData.totalDamage;
	float staminaDamageMult;
	DEBUG("base stamina damage is {}", staminaDamageBase);
	using namespace settings;
	if (hitFlag & (int)HITFLAG::kBlockWithWeapon) {
		DEBUG("hit blocked with weapon");
		if (isPlayerTarget) {
			staminaDamageMult = bckWpnStaminaMult_PC_Block_NPC;
		}
		else {
			if (isPlayerAggressor) {
				staminaDamageMult = bckWpnStaminaMult_NPC_Block_PC;
			}
			else {
				staminaDamageMult = bckWpnStaminaMult_NPC_Block_NPC;
			}
				
		}
	}
	else {
		DEBUG("hit blocked with shield");
		if (isPlayerTarget) {
			staminaDamageMult = bckShdStaminaMult_PC_Block_NPC;
		}
		else {
			if (isPlayerAggressor) {
				staminaDamageMult = bckShdStaminaMult_NPC_Block_PC;
			}
			else {
				staminaDamageMult = bckShdStaminaMult_NPC_Block_NPC;
			}
		}
	}
	float staminaDamage = staminaDamageBase * staminaDamageMult;
	float targetStamina = target->GetActorValue(RE::ActorValue::kStamina);
	
	//check whether there's enough stamina to block incoming attack
	if (targetStamina < staminaDamage) {
		DEBUG("not enough stamina to block, blocking part of damage!");
		if (settings::guardBreak) {
			DEBUG("guard break!");
			target->NotifyAnimationGraph("staggerStart");
		}
		hitData.totalDamage = hitData.totalDamage - (targetStamina / staminaDamageMult);
		Utils::damageav(target, RE::ActorValue::kStamina,
			targetStamina);
		DEBUG("failed to block {} damage", hitData.totalDamage);
	}
	else {
		hitData.totalDamage = 0;
		Utils::damageav(target, RE::ActorValue::kStamina,
			staminaDamage);
	}

	_ProcessHit(target, hitData);
}

bool staminaRegenHook::shouldRegenStamina(RE::ActorState* a_this, uint16_t a_flags) {
	//iff bResult is true, prevents regen.
	bool bResult = _shouldRegenStamina(a_this, a_flags); // is sprinting?

	if (!bResult) {
		RE::Actor* actor = SKSE::stl::adjust_pointer<RE::Actor>(a_this, -0xB8);
		bResult = actor->IsBlocking();
	}

	return bResult;
}