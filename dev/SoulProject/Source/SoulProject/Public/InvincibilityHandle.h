#pragma once

#include "InvincibilityHandle.generated.h"

USTRUCT(BlueprintType)
struct FInvincibilityHandle
{
	GENERATED_BODY()

public:


	FInvincibilityHandle();
	FInvincibilityHandle(const FInvincibilityHandle& InHandle);

	virtual bool	operator==(const FInvincibilityHandle& InHandle) const;
	bool			IsValid() const;
	void			MakeInvalid();


private:

	static int32	HandleGenerator;

	int32	Handle;

};