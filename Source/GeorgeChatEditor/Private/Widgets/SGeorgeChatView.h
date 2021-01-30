#pragma once

#include "CoreMinimal.h"

#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

class SMultiLineEditableTextBox;
class FGeorgeChatClient;
struct FGeorgeChatMessage;

class SGeorgeChatView final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGeorgeChatView) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<FGeorgeChatClient>& InClient);

private:
	TSharedPtr<FGeorgeChatClient> Client;
	TSharedPtr<SListView<TSharedRef<FGeorgeChatMessage>>> MessageListView;
	TSharedPtr<SEditableTextBox> MessageTextBox;

	void OnMessageTextCommitted(const FText& InText, ETextCommit::Type CommitInfo) const;
};
