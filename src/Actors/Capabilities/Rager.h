#pragma once

#include "ActorCapability.h"
#include "Types.h"

class RelicWeapon;

class Rager : public ActorCapability
{
public:
    inline static constexpr auto kType = ActorType::kRager;

    Rager();
    virtual ~Rager() = default;

    void OnAttach(BaseActor* a_actor) override;

    void Update(float a_delta) override;
    void HandleAction(const ActionType a_action) override;

    [[nodiscard]] ActorType GetType() const override { return ActorType::kRager; }

    void StartRage(const bool a_justAnim = false);
    void EndRage(const bool a_fromAnnotation = false, const bool a_playAnim = true, const bool a_justAnim = false);

    void GrantValorBuff() {_gettingHittedInValor = true;}

    float CalcRageDamageOrBuffAmount(const float a_amount, const float a_mult = 1.f);
    void RestoreRage(const float a_value, const bool a_justRestore);

    [[nodiscard]] bool IsInRage() const { return _isInRage; }
    [[nodiscard]] bool IsCanRage() const { return (*rage > *rageDamageAmount * 6.f) && !_isInRage; }
    [[nodiscard]] bool IsWantFinishRage() const {return _isWantFinishRage;}

    [[nodiscard]] RageType GetRageType() const { return rageType; }
    [[nodiscard]] RageType GetLastTriggeredRageType() const { return lastTriggeredRage; }
    [[nodiscard]] float GetRageAmount() const { return *rage; }
    [[nodiscard]] float GetRageLimit() const { return *rageLimit; }
    [[nodiscard]] float GetBuffAmount() const { return *rageBuffAmount; }
    [[nodiscard]] float GetRageDamageAmount() const { return *rageDamageAmount; }

    void SetRageAmount(float a_rageAmount) noexcept { *rage = a_rageAmount; }
    void SetRageLimit(float a_rageLimit) noexcept { *rageLimit = a_rageLimit; }
    void SetRageBuffAmount(float a_rageBuffAmount) noexcept { *rageBuffAmount = a_rageBuffAmount; }
    void SetRageDamageAmount(float a_rageDamageAmount) noexcept { *rageDamageAmount = a_rageDamageAmount; }
    void SetRageType(RageType a_rageType) noexcept { rageType = a_rageType; }

    [[nodiscard]] RelicWeapon* FindKnownRelic(const RelicType a_type) const;

protected:
    RE::SpellItem*      SpellSpartanRage    = nullptr;
    RE::SpellItem*      SpellStrenghtBuff   = nullptr;
    RE::EffectSetting*  EffectSpartanRage   = nullptr;
    RE::EffectSetting*  EffectStrenghtBuff  = nullptr;

    float* rage             = &localRage;
    float* rageLimit        = &localRageLimit;
    float* rageBuffAmount   = &localRageBuffAmount;
    float* rageDamageAmount = &localRageDamageAmount;

    float localRage             = 0.f;
    float localRageLimit        = 600.f;
    float localRageBuffAmount   = 20.f;
    float localRageDamageAmount = 3.f;

    RageType rageType = RageType::kFury;
    RageType lastTriggeredRage = RageType::kFury;

private:
    RE::TESBoundObject* _LastEquippedObjectR = nullptr;
    RE::TESBoundObject* _LastEquippedObjectL = nullptr;
    bool _isInRage             = false;
    bool _isWantFinishRage     = false;
    bool _gettingHittedInValor = false;
};
