#include "InvincibilityHandle.h"

int32 FInvincibilityHandle::HandleGenerator(0);

FInvincibilityHandle::FInvincibilityHandle()
	: Handle(HandleGenerator++)
{}

FInvincibilityHandle::FInvincibilityHandle(const FInvincibilityHandle& InHandle)
{
	Handle = InHandle.Handle;
}

bool FInvincibilityHandle::operator==(const FInvincibilityHandle& InHandle) const
{
	return (Handle == InHandle.Handle);
}

bool FInvincibilityHandle::IsValid() const
{
	return (Handle > 0);
}

void FInvincibilityHandle::MakeInvalid()
{
	Handle = INDEX_NONE;
}
