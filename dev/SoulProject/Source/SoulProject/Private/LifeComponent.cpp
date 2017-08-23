// Fill out your copyright notice in the Description page of Project Settings.

#include "LifeComponent.h"
#include "UnrealNetwork.h"
#include "Kismet/KismetSystemLibrary.h"

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
	SetLife(CurrentLife - DamagesAmount);
}

void ULifeComponent::Heal(int32 HealAmount)
{
	SetLife(CurrentLife + HealAmount);
}

void ULifeComponent::OnRep_CurrentLife()
{
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("OnRep_CurrentLife : %d"), CurrentLife));
	OnLifeValueChanged.Broadcast(this);
}

float ULifeComponent::GetLifeRatio() const
{
	return ((float)CurrentLife / (float)MaxLife);
}

