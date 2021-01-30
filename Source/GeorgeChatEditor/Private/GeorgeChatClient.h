#pragma once

#include "CoreMinimal.h"

#include "GeorgeChatUser.h"

struct FGeorgeChatMessage;
class FMessageEndpoint;
class FGeorgeChatClient;

class FGeorgeChatClient
	: public TSharedFromThis<FGeorgeChatClient>
{
public:
	TSharedPtr<FGeorgeChatUser> User;
	TArray<TSharedRef<FGeorgeChatMessage>> MessageHistory;

	explicit FGeorgeChatClient(const TSharedPtr<FGeorgeChatUser>& InUser);
	~FGeorgeChatClient();

	const TArray<TSharedRef<FGeorgeChatMessage>>& GetMessageHistory() const;

	void SendMessage(const FString& Content) const;

private:
	TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;

	void AddMessageToHistory(const FGeorgeChatMessage& InMessage);
	void HandleChatMessage(const FGeorgeChatMessage& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);
};
