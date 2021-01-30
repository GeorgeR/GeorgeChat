#include "SGeorgeChatMessageRow.h"

#define LOCTEXT_NAMESPACE "GeorgeChat"

FSlateColor OwnerMessageColor{FLinearColor{0.0, 0.4072, 0.9734}};
FSlateColor OtherMessageColor{FLinearColor::White};

void SGeorgeChatMessageRow::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedPtr<FGeorgeChatUser>& InUser, const TSharedRef<FGeorgeChatMessage>& InMessage)
{
	ChatUser = InUser;
	Message = InMessage;

	STableRow<TSharedRef<FGeorgeChatMessage>>::Construct(
		STableRow<TSharedRef<FGeorgeChatMessage>>::FArguments()
		.ShowSelection(false) // don't need selection
		.Content()
		[
			MakeWidget()
		],
		InOwnerTableView
	);
}

TSharedRef<SWidget> SGeorgeChatMessageRow::MakeWidget() const
{
	const TSharedPtr<FGeorgeChatMessage> PinnedMessage = Message.Pin();
	const bool bIsOwnerMessage = PinnedMessage->AuthorId == ChatUser.Pin()->UserId;
	
	const FText AuthorText = FText::Format(
		LOCTEXT("ChatMessageAuthor", "Chat {0}{1}:"),
		PinnedMessage->AuthorId,
		FText::FromString(bIsOwnerMessage ? TEXT(" (Me)") : TEXT("")));

	const FText ContentText = FText::FromString(PinnedMessage->Content);
	const FSlateColor& Color = bIsOwnerMessage ? OwnerMessageColor : OtherMessageColor;
	
	return SNew(SHorizontalBox)
		// author
		+SHorizontalBox::Slot()
		.AutoWidth() // fit to content
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Center)
		[
			SNew(SBox)
			.Padding(2.0f)
			[
				SNew(STextBlock)
				.ColorAndOpacity(Color)
				.Text(AuthorText)
			]
		]
		// content
		+SHorizontalBox::Slot()
		.FillWidth(1.0f) // fill the remainder of the space
		.VAlign(VAlign_Center)
		[
			SNew(SBox)
			.Padding(2.0f)
			[
				SNew(STextBlock)
				.ColorAndOpacity(Color)
				.Text(ContentText)
			]
		];
}

#undef LOCTEXT_NAMESPACE
