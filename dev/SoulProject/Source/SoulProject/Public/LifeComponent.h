// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InvincibilityHandle.h"
#include "LifeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLifeValueChanged, ULifeComponent*, LifeComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInvincibilityModeChanged, ULifeComponent*, LifeComponent, bool, bIsInvincible);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOULPROJECT_API ULifeComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = Life)
	FOnLifeValueChanged	OnLifeValueChanged;

	UPROPERTY(BlueprintAssignable, Category = Life)
	FOnInvincibilityModeChanged OnInvincibilityModeChanged;

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

	UFUNCTION()
	void	OnRep_NumInvincibilityHandled();

	UFUNCTION(BlueprintCallable, Category = Life)
	float	GetLifeRatio() const;

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = Life)
	FInvincibilityHandle	EnableInvincibility();

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = Life)
	void					EnableTimedInvincibility(float Duration);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = Life)
	void					DisableInvincibility(UPARAM(ref) FInvincibilityHandle& Handle);

	UFUNCTION(BlueprintCallable, Category = Life)
	bool					IsInvincible() const;


protected:

	void		SetNumInvincibilityHandled(int32 InNumInvincibilityHandled);


private:

	void		HandleLifetimeElapsed();


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_CurrentLife, Category = Life)
	int32 CurrentLife;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Life)
	int32 MaxLife;

	
protected:

	UPROPERTY(ReplicatedUsing=OnRep_NumInvincibilityHandled)
	int32 NumInvincibilityHandled;
	
};
