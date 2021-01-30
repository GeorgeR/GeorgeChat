#include "GeorgeChatClient.h"

#include "MessageEndpoint.h"
#include "MessageEndpointBuilder.h"

#include "GeorgeChatMessages.h"

#define LOCTEXT_NAMESPACE "GeorgeChat"

FGeorgeChatClient::FGeorgeChatClient(const TSharedPtr<FGeorgeChatUser>& InUser)
	: User(InUser)
{
	const FString MessageEndpointName = TEXT("GeorgeChat");
	MessageEndpoint = FMessageEndpoint::Builder(*MessageEndpointName)
		.ReceivingOnThread(ENamedThreads::GameThread)
		.Handling<FGeorgeChatMessage>(this, &FGeorgeChatClient::HandleChatMessage);

	if(MessageEndpoint.IsValid())
	{
		MessageEndpoint->Subscribe<FGeorgeChatMessage>();
	}
}

FGeorgeChatClient::~FGeorgeChatClient()
{
	if(MessageEndpoint.IsValid())
	{
		MessageEndpoint->Disable();
		MessageEndpoint.Reset();
	}
}

const TArray<TSharedRef<FGeorgeChatMessage>>& FGeorgeChatClient::GetMessageHistory() const
{
	return MessageHistory;
}

void FGeorgeChatClient::SendMessage(const FString& Content) const
{
	check(User.IsValid());
	check(MessageEndpoint.IsValid()); // not connected yet

	void* Memory = FMemory::Malloc(sizeof(FGeorgeChatMessage));
	MessageEndpoint->Publish(new(Memory) FGeorgeChatMessage{User->UserId, FDateTime::UtcNow(), Content}, EMessageScope::Process);
}

void FGeorgeChatClient::AddMessageToHistory(const FGeorgeChatMessage& InMessage)
{
	MessageHistory.Emplace(MakeShared<FGeorgeChatMessage>(InMessage));
}

void FGeorgeChatClient::HandleChatMessage(
	const FGeorgeChatMessage& InMessage,
	const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context)
{
	AddMessageToHistory(InMessage);
}

#undef LOCTEXT_NAMESPACE