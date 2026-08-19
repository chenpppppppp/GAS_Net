// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHPChangedDelegate, float, NewHP, float, MaxHP);

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class GAS_NET_API UBaseAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    UBaseAttributeSet();

    // === 生命值 ===
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseAttributeSet", ReplicatedUsing = OnRep_HP)
    FGameplayAttributeData HP;
    ATTRIBUTE_ACCESSORS(UBaseAttributeSet, HP);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseAttributeSet", ReplicatedUsing = OnRep_MaxHP)
    FGameplayAttributeData MaxHP;
    ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxHP);

    // === 法力值 ===
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseAttributeSet", ReplicatedUsing = OnRep_MP)
    FGameplayAttributeData MP;
    ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MP);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseAttributeSet", ReplicatedUsing = OnRep_MaxMP)
    FGameplayAttributeData MaxMP;
    ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxMP);

    // === 体力 ===
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseAttributeSet", ReplicatedUsing = OnRep_Strength)
    FGameplayAttributeData Strength;
    ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Strength);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseAttributeSet", ReplicatedUsing = OnRep_MaxStrength)
    FGameplayAttributeData MaxStrength;
    ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxStrength);

    // === 攻击力 ===
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseAttributeSet", ReplicatedUsing = OnRep_Attack)
    FGameplayAttributeData Attack;
    ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Attack);

    // === 护甲 ===
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseAttributeSet", ReplicatedUsing = OnRep_Aromo)
    FGameplayAttributeData Aromo;
    ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Aromo);

    UPROPERTY(BlueprintAssignable, Category = "Attributes")
    FOnHPChangedDelegate OnHPChanged;



    // 夹值处理（服务器权威）
    virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

    // 复制注册
    virtual void GetLifetimeReplicatedProps(TArray <FLifetimeProperty> &OutLifetimeProps) const override;

    // === OnRep 声明 ===
    UFUNCTION()
    void OnRep_HP(const FGameplayAttributeData& OldHP);

    UFUNCTION()
    void OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP);

    UFUNCTION()
    void OnRep_MP(const FGameplayAttributeData& OldMP);

    UFUNCTION()
    void OnRep_MaxMP(const FGameplayAttributeData& OldMaxMP);

    UFUNCTION()
    void OnRep_Strength(const FGameplayAttributeData& OldStrength);

    UFUNCTION()
    void OnRep_MaxStrength(const FGameplayAttributeData& OldMaxStrength);

    UFUNCTION()
    void OnRep_Attack(const FGameplayAttributeData& OldAttack);

    UFUNCTION()
    void OnRep_Aromo(const FGameplayAttributeData& OldAromo);
};