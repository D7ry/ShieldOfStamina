#pragma once
class hitEventHook //props to Loki
{
public:
    static void InstallHook() {
        REL::Relocation<uintptr_t> hook{ REL::ID(37673) };
        SKSE::AllocTrampoline(1 << 4);
        auto& trampoline = SKSE::GetTrampoline();
        _ProcessHit = trampoline.write_call<5>(hook.address() + 0x3C0, processHit);
        INFO("hit event hook installed!");
    };
private:
    static void processHit(RE::Actor* target, RE::HitData& hitData);
    static inline REL::Relocation<decltype(processHit)> _ProcessHit;
};

class staminaRegenHook //props to Ersh
{
public:
    static void InstallHook() {
        REL::Relocation<uintptr_t> hook{ REL::ID(37510) };  // 620690 - a function that regenerates stamina
        SKSE::AllocTrampoline(1 << 4);
        auto& trampoline = SKSE::GetTrampoline();
        _shouldRegenStamina = trampoline.write_call<5>(hook.address() + 0x62, shouldRegenStamina);
        INFO("stamina regen hook installed");
    };
private:
    static bool shouldRegenStamina(RE::ActorState* a_this, uint16_t a_flags);
    static inline REL::Relocation<decltype(shouldRegenStamina)> _shouldRegenStamina;
};