#pragma once

#include "CoreMinimal.h"

#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Views/STableViewBase.h"
#include "Widgets/Views/STableRow.h"

#include "GeorgeChatMessages.h"
#include "GeorgeChatUser.h"

class SMultiLineEditableTextBox;
class FGeorgeChatClient;

class SGeorgeChatMessageRow final : public STableRow<TSharedRef<FGeorgeChatMessage>>
{
public:
	SLATE_BEGIN_ARGS(SGeorgeChatMessageRow) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedPtr<FGeorgeChatUser>& InUser, const TSharedRef<FGeorgeChatMessage>& InMessage);

private:
	TWeakPtr<FGeorgeChatUser> ChatUser; // the owning user, used to determine color
	TWeakPtr<FGeorgeChatMessage> Message;

	TSharedRef<SWidget> MakeWidget() const;
};
