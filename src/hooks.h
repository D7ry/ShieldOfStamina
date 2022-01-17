#pragma once
class hitEventHook
{
public:
    static void InstallHook();
private:
    static void processHit(RE::Actor* target, RE::HitData& hitData);
    static inline REL::Relocation<decltype(processHit)> _ProcessHit;
};