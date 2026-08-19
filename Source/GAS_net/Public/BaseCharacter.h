// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayEffectTypes.h"
#include "BaseCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeDelegate, float, NewVal);

UCLASS()
class GAS_NET_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnHealthChangeDelegate HealthChangedEvent;	
	
	
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnHealthChangeDelegate MPChangedEvent;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnHealthChangeDelegate StrengthChangedEvent;

	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
	FGameplayAbilityInfo GameplayAbilityInfo(TSubclassOf<UBaseGameplayAbility>AbilityClass, int level);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);
	void OnMPAttributeChanged(const FOnAttributeChangeData& Data);
	void OnStrengthAttributeChanged(const FOnAttributeChangeData& Data);

};
