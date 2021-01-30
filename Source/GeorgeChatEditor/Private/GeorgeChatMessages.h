#pragma once

#include "CoreMinimal.h"

#include "GeorgeChatMessages.generated.h"

USTRUCT()
struct FGeorgeChatMessage
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	int32 AuthorId;

	UPROPERTY()
	FDateTime TimeStamp;

	UPROPERTY()
	FString Content;

	FGeorgeChatMessage() = default;

	FGeorgeChatMessage(int32 InAuthorId, const FDateTime& InTimeStamp, const FString& InContent)
		: AuthorId(InAuthorId),
		  TimeStamp(InTimeStamp),
		  Content(InContent)
	{
	}
};
