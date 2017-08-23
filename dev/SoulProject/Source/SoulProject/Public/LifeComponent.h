// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LifeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLifeValueChanged, ULifeComponent*, LifeComponent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOULPROJECT_API ULifeComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = Life)
	FOnLifeValueChanged	OnLifeValueChanged;

public:	

	ULifeComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = Life)
	bool	IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = Life)
	bool	IsDead() const;

	UFUNCTION(BlueprintCallable, Category = Life)
	void	SetLife(int32 NewLife);

	UFUNCTION(BlueprintCallable, Category = Life)
	void	ApplyDamages(int32 DamagesAmount);

	UFUNCTION(BlueprintCallable, Category = Life)
	void	Heal(int32 HealAmount);

	UFUNCTION()
	void	OnRep_CurrentLife();

	UFUNCTION(BlueprintCallable, Category = Life)
	float	GetLifeRatio() const;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_CurrentLife, Category = Life)
	int32 CurrentLife;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Life)
	int32 MaxLife;
	
};
