// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "BaseAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseGameplayAbility.h"          // ¡û Ìí¼ÓÕâÐÐ


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	UAbilitySystemComponent* MyAbilitySystemComponent = this->FindComponentByClass<UAbilitySystemComponent>();
	if (MyAbilitySystemComponent) {
		MyAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetHPAttribute()).AddUObject(this, &ABaseCharacter::OnHealthAttributeChanged);
		MyAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetMPAttribute()).AddUObject(this, &ABaseCharacter::OnMPAttributeChanged);
		MyAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetStrengthAttribute()).AddUObject(this, &ABaseCharacter::OnStrengthAttributeChanged);
	}
	
}

FGameplayAbilityInfo ABaseCharacter::GameplayAbilityInfo(TSubclassOf<UBaseGameplayAbility>AbilityClass, int level)
{
	UAbilitySystemComponent* MyAbilitySystemComponent = this->FindComponentByClass<UAbilitySystemComponent>();
	UBaseGameplayAbility* AbilityInctance = AbilityClass->GetDefaultObject<UBaseGameplayAbility>();
	if (MyAbilitySystemComponent && AbilityInctance)
	{
		return	AbilityInctance->GetAbilityInfo(level);
	}

	return FGameplayAbilityInfo();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	HealthChangedEvent.Broadcast(Data.NewValue);
}

void ABaseCharacter::OnMPAttributeChanged(const FOnAttributeChangeData& Data)
{
	MPChangedEvent.Broadcast(Data.NewValue);
}

void ABaseCharacter::OnStrengthAttributeChanged(const FOnAttributeChangeData& Data)
{
	StrengthChangedEvent.Broadcast(Data.NewValue);
}


