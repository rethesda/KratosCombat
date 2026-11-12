#include "Charger.h"
#include "Settings.h"
#include "Actors/BaseActor.h"
#include "Weapons/RelicWeapon.h"

Charger::Charger()
{
}

void Charger::StartWeaponCharging() {
    if (auto rHandRelic = parent->GetRightHandRelic(); rHandRelic) {
        if (rHandRelic->Charge(Config::ChargeHitCount, Config::ChargeMagnitude, 1u, -1u)) {
            parent->GetActor()->SetGraphVariableBool("IsWeaponCharged", true);
        } else {
            parent->GetActor()->SetGraphVariableBool("IsWeaponCharged", false);
        }
    } else {
        spdlog::info("the weapon is not chargeable");
    }
}
void Charger::StopWeaponCharging() {
    if (auto rHandRelic = parent->GetRightHandRelic(); rHandRelic) {
        if (rHandRelic->Charge(Config::ChargeHitCount, Config::ChargeMagnitude, 0u, -1u)) {
            parent->GetActor()->SetGraphVariableBool("IsWeaponCharged", true);
        } else {
            parent->GetActor()->SetGraphVariableBool("IsWeaponCharged", false);
        }
    } else {
        spdlog::info("the weapon is not chargeable");
    }
}
void Charger::ChargeWeapon(const uint8_t a_stage) {
    if (auto rHandRelic = parent->GetRightHandRelic(); rHandRelic) {
        if (rHandRelic->Charge(Config::ChargeHitCount, Config::ChargeMagnitude, a_stage, -1u)) {
            parent->GetActor()->SetGraphVariableBool("IsWeaponCharged", true);
        } else {
            parent->GetActor()->SetGraphVariableBool("IsWeaponCharged", false);
        }
    } else {
        spdlog::info("the weapon is not chargeable");
    }
}

bool Charger::IsCanCharge(const RelicType a_relic) const
{
    const auto index = static_cast<std::size_t>(a_relic);

    if (index >= canCharge.size()) {
        return false;
    }

    return canCharge[index];
}

void Charger::OnAttach(BaseActor* a_actor)
{
    ActorCapability::OnAttach(a_actor);
    if (parent && parent->IsValid()) {
        if (auto callerAVO = parent->GetActor() ? parent->GetActor()->AsActorValueOwner() : nullptr) {
            enchantingLevel = callerAVO->GetActorValue(RE::ActorValue::kEnchanting);
        }
    }
}

void Charger::HandleAction(const ActionType a_action)
{
    switch (a_action)
    {
    case ActionType::kRage:
        break;
    case ActionType::kWeaponCharge:
        if (!parent->IsInRage() && parent->GetRightHandRelic() && !parent->GetRightHandRelic()->IsCharged()) {
            parent->GetActor()->SetGraphVariableInt("iKratosActionType", (uint8_t)ActionType::kWeaponCharge);
            parent->GetActor()->NotifyAnimationGraph("DoKratosAction");
        }
        break;
    case ActionType::kSpecialIdle:
        break;
    case ActionType::kWeaponCall:
        break;

    default:
        break;
    }
}
