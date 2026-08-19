// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "Net/UnrealNetwork.h"

UBaseAttributeSet::UBaseAttributeSet()
{
}

void UBaseAttributeSet::GetLifetimeReplicatedProps(TArray <FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, HP, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, MaxHP, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, MP, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, MaxMP, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Strength, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, MaxStrength, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Attack, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Aromo, COND_None, REPNOTIFY_Always);
}

void UBaseAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetHPAttribute())
    {
        SetHP(FMath::Clamp(GetHP(), 0.0f, GetMaxHP()));
    }

    if (Data.EvaluatedData.Attribute == GetMPAttribute())
    {
        SetMP(FMath::Clamp(GetMP(), 0.0f, GetMaxMP()));
    }

    if (Data.EvaluatedData.Attribute == GetStrengthAttribute())
    {
        SetStrength(FMath::Clamp(GetStrength(), 0.0f, GetMaxStrength()));
    }
}

void UBaseAttributeSet::OnRep_HP(const FGameplayAttributeData& OldHP)
{

    OnHPChanged.Broadcast(HP.GetCurrentValue(), MaxHP.GetCurrentValue());
}

void UBaseAttributeSet::OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP)
{
}

void UBaseAttributeSet::OnRep_MP(const FGameplayAttributeData& OldMP)
{

}

void UBaseAttributeSet::OnRep_MaxMP(const FGameplayAttributeData& OldMaxMP)
{

}

void UBaseAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength)
{

}

void UBaseAttributeSet::OnRep_MaxStrength(const FGameplayAttributeData& OldMaxStrength)
{

}

void UBaseAttributeSet::OnRep_Attack(const FGameplayAttributeData& OldAttack)
{

}

void UBaseAttributeSet::OnRep_Aromo(const FGameplayAttributeData& OldAromo)
{

}