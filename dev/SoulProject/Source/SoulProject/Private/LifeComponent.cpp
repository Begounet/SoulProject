// Fill out your copyright notice in the Description page of Project Settings.

#include "LifeComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "UnrealNetwork.h"

// Sets default values for this component's properties
ULifeComponent::ULifeComponent()
	: CurrentLife(100)
	, MaxLife(100)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bReplicates = true;
}

void ULifeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ULifeComponent, CurrentLife);
	DOREPLIFETIME(ULifeComponent, MaxLife);
	DOREPLIFETIME(ULifeComponent, NumInvincibilityHandled);
}

bool ULifeComponent::IsAlive() const
{
	return (CurrentLife > 0);
}

bool ULifeComponent::IsDead() const
{
	return (!IsAlive());
}

void ULifeComponent::SetLife(int32 NewLife)
{
 	CurrentLife = FMath::Clamp(NewLife, 0, MaxLife);
	OnRep_CurrentLife();
}

void ULifeComponent::ApplyDamages(int32 DamagesAmount)
{
	if (!IsInvincible())
	{
		SetLife(CurrentLife - DamagesAmount);
	}
}

void ULifeComponent::Heal(int32 HealAmount)
{
	SetLife(CurrentLife + HealAmount);
}

void ULifeComponent::OnRep_CurrentLife()
{
	OnLifeValueChanged.Broadcast(this);
}

void ULifeComponent::OnRep_NumInvincibilityHandled()
{
	if (NumInvincibilityHandled <= 1)
	{
		OnInvincibilityModeChanged.Broadcast(this, NumInvincibilityHandled > 0);
	}
}

float ULifeComponent::GetLifeRatio() const
{
	return ((float) CurrentLife / (float) MaxLife);
}

FInvincibilityHandle ULifeComponent::EnableInvincibility()
{
	FInvincibilityHandle newInvinciblityHandle;
	SetNumInvincibilityHandled(NumInvincibilityHandled + 1);
	return (newInvinciblityHandle);
}

void ULifeComponent::EnableTimedInvincibility(float Duration)
{
	SetNumInvincibilityHandled(NumInvincibilityHandled + 1);
	
	if (UWorld* world = GetWorld())
	{
		FTimerManager& timerManager = world->GetTimerManager();
		FTimerHandle timerHandle;
		timerManager.SetTimer(timerHandle, this, &ULifeComponent::HandleLifetimeElapsed, Duration);
	}
}

void ULifeComponent::DisableInvincibility(FInvincibilityHandle& Handle)
{
	if (Handle.IsValid())
	{
		Handle.MakeInvalid();
		SetNumInvincibilityHandled(NumInvincibilityHandled - 1);
	}
}

bool ULifeComponent::IsInvincible() const
{
	return (NumInvincibilityHandled > 0);
}

void ULifeComponent::SetNumInvincibilityHandled(int32 InNumInvincibilityHandled)
{
	NumInvincibilityHandled = FMath::Clamp(InNumInvincibilityHandled, 0, 1);
	OnRep_NumInvincibilityHandled();
}

void ULifeComponent::HandleLifetimeElapsed()
{
	SetNumInvincibilityHandled(NumInvincibilityHandled - 1);
}

