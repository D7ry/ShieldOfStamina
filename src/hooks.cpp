#include "hooks.h"
#include "dataHandler.h"
namespace Utils {
	inline void damageav(RE::Actor* a, RE::ActorValue av, float val)
	{
		a->As<RE::ActorValueOwner>()->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, av, -val);
	}
}
void hitEventHook::InstallHook() {
	REL::Relocation<uintptr_t> hook{ REL::ID(37673) };
	SKSE::AllocTrampoline(1 << 4);
	auto& trampoline = SKSE::GetTrampoline();
	_ProcessHit = trampoline.write_call<5>(hook.address() + 0x3C0, processHit);
	DEBUG("hit event hook installed!");
};

/*stamina blocking*/
void hitEventHook::processHit(RE::Actor* target, RE::HitData& hitData) {

	if (!target) {
		return;
	}
	int hitFlag = (int)hitData.flags;
	using HITFLAG = RE::HitData::Flag;

	if (hitFlag & (int)HITFLAG::kBlocked) {
		bool isPlayerTarget = target->IsPlayerRef() || target->IsPlayerTeammate();
		float staminaDamageBase = hitData.totalDamage;
		float staminaDamageMult;
		float staminaDamage;
		DEBUG("base stamina damage is {}", staminaDamageBase);
		if (hitFlag & (int)HITFLAG::kBlockWithWeapon) {
			DEBUG("hit blocked with weapon");
			if (isPlayerTarget) {
				staminaDamageMult = settings::bckWpnStaminaPenaltyMultPlayer;
			}
			else {
				staminaDamageMult = settings::bckWpnStaminaPenaltyMultNPC;
			}
		}
		else {
			DEBUG("hit blocked with shield");
			if (isPlayerTarget) {
				staminaDamageMult = settings::bckShdStaminaPenaltyMultPlayer;
			}
			else {
				staminaDamageMult = settings::bckShdStaminaPenaltyMultNPC;
			}
		}
		staminaDamage = staminaDamageBase * staminaDamageMult;
		DEBUG("stamina damage is {}", staminaDamage);
		float currStamina = target->GetActorValue(RE::ActorValue::kStamina);
		if (currStamina < staminaDamage) {
			DEBUG("not enough stamina to block, blocking part of damage!");
			if (settings::guardBreak) {
				DEBUG("guard break!");
				target->NotifyAnimationGraph("staggerStart");
			}
			hitData.totalDamage = hitData.totalDamage - (currStamina / staminaDamageMult);
			DEBUG("failed to block {} damage", hitData.totalDamage);
		}
		else {
			hitData.totalDamage = 0;
		}
		Utils::damageav(target, RE::ActorValue::kStamina,
			staminaDamage);
	}
	_ProcessHit(target, hitData);
}