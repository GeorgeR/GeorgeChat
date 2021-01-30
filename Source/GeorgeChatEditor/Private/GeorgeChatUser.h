#pragma once

#include "CoreMinimal.h"

// stores info about a user's identity, in this case just a number
struct FGeorgeChatUser
{
public:
	typedef int32 FId;
	FId UserId; // 1 or 2

	FGeorgeChatUser(const int32 InUserId) : UserId(InUserId) {  }
};