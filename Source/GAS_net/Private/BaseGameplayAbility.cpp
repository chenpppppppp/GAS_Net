// .cpp 文件 - 完整修改

#include "BaseGameplayAbility.h"
#include "Net/UnrealNetwork.h"

// ========== FGameplayAbilityInfo 构造函数（保持不变）==========

FGameplayAbilityInfo::FGameplayAbilityInfo() :
    CD(0),
    CostValue(0),
    CostType(ECostType::MP),
    IconMaterial(nullptr),
    AbilityClass(nullptr)
{
}

FGameplayAbilityInfo::FGameplayAbilityInfo(float CD, ECostType CostType, float CostValue, UMaterialInstance* IconMaterial, TSubclassOf<UBaseGameplayAbility> AbilityClass) :
    CD(CD),
    CostValue(CostValue),
    CostType(CostType),
    IconMaterial(IconMaterial),
    AbilityClass(AbilityClass)
{
}

// ========== UBaseGameplayAbility 实现 ===========



FGameplayAbilityInfo UBaseGameplayAbility::GetAbilityInfo(int level)
{
    UGameplayEffect* CDEffect = GetCooldownGameplayEffect();
    UGameplayEffect* CostEffect = GetCostGameplayEffect();
    float CD = 0;
    float CostValue = 0;
    ECostType CostType = ECostType::MP;

    if (CDEffect && CostEffect)
    {
        CDEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(level, CD);

        if (CostEffect->Modifiers.Num() > 0)
        {
            FGameplayModifierInfo CostEffectModifierInfo = CostEffect->Modifiers[0];
            CostEffectModifierInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(level, CostValue);

            FString CostTypeName = CostEffectModifierInfo.Attribute.AttributeName;

            if (CostTypeName == "HP")
            {
                CostType = ECostType::HP;
            }
            else if (CostTypeName == "MP")
            {
                CostType = ECostType::MP;
            }
            else if (CostTypeName == "Strength")
            {
                CostType = ECostType::Strength;
            }

            return FGameplayAbilityInfo(CD, CostType, CostValue, IconMaterial, GetClass());
        }
    }

    return FGameplayAbilityInfo();
}

