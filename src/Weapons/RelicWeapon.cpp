#include "RelicWeapon.h"
#include "Actors/BaseActor.h"

RelicWeapon::~RelicWeapon()
{
    spdlog::debug("relic weapon destructed");
}
RelicWeapon::RelicWeapon(RE::TESBoundObject* a_object)
    : weap(a_object->As<RE::TESObjectWEAP>())
{
    if (weap) damage = static_cast<float>(weap->attackDamage);
    spdlog::debug("relic weapon constructed: {}", weap->GetFullName());
}

BaseActor* RelicWeapon::GetCarrier() const
{
    if (wielder) return wielder;
    else if (lastWielder && lastWielder->IsValid()) {
        const auto invChanges = lastWielder->GetActor()->GetInventoryChanges();
        const auto entries = invChanges ? invChanges->entryList : nullptr;
        if (entries) {
            for (const auto entry : *entries) {
                if (entry && entry->object && entry->object == weap) {
                    return lastWielder;
                }
            }
        }
    } return nullptr;
}

void RelicWeapon::OnEquip(BaseActor* a_actor) {
    if (a_actor && a_actor->IsValid()) {
        wielder = a_actor;
        lastWielder = a_actor;
        isEquipped = true;
        currentReference = nullptr;
        ResetCharge(enchMag, defaultEnchMag, true);
    } else {
        wielder = nullptr;
        isEquipped = false;
    }
}
void RelicWeapon::SetWielder(BaseActor* a_actor) {
    if (a_actor && a_actor->IsValid()) {
        wielder = a_actor;
        lastWielder = a_actor;
        isEquipped = true;
    } else {
        wielder = nullptr;
        isEquipped = false;
    }
}
void RelicWeapon::SetOwner(BaseActor* a_actor) {
    if (a_actor && a_actor->IsValid()) {
        owner = a_actor;
    } else {
        owner = nullptr;
    }
}
