
#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BaseGameplayAbility.generated.h"
//技能消耗的类型
UENUM(BlueprintType)
enum class ECostType :uint8
{
	HP,
	MP,
	Strength
};
USTRUCT(BlueprintType)
struct FGameplayAbilityInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	float CD;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	ECostType CostType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	float CostValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	UMaterialInstance* IconMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	TSubclassOf<UBaseGameplayAbility>AbilityClass;

	FGameplayAbilityInfo();
	FGameplayAbilityInfo(float CD, ECostType CostType, float CostValue, UMaterialInstance* IconMaterial, TSubclassOf<UBaseGameplayAbility>AbilityClass);
};



UCLASS()
class GAS_NET_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	UMaterialInstance* IconMaterial;

	UFUNCTION(BlueprintCallable, Category = "AbilityInfo")
	FGameplayAbilityInfo GetAbilityInfo(int level);

};
