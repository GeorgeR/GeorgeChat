#include "SGeorgeChatView.h"

#include "Widgets/Layout/SScrollBox.h"

#include "GeorgeChatClient.h"
#include "Widgets/SGeorgeChatMessageRow.h"

#define LOCTEXT_NAMESPACE "GeorgeChat"

void SGeorgeChatView::Construct(const FArguments& InArgs, const TSharedRef<FGeorgeChatClient>& InClient)
{
	Client = InClient;

	ChildSlot[SNullWidget::NullWidget];

	const TSharedRef<SScrollBar> ScrollBar = SNew(SScrollBar);

	ChildSlot
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Fill)
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.Padding(2.0f)
		.FillHeight(1.0f)
		[
			SNew(SBorder)
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.VAlign(VAlign_Bottom)
				.FillWidth(1)
				[
					SAssignNew(MessageListView, SListView<TSharedRef<FGeorgeChatMessage>>)
					.ListItemsSource(&Client->GetMessageHistory())
					.OnGenerateRow_Lambda([this](const TSharedRef<FGeorgeChatMessage>& InMessage, const TSharedRef<STableViewBase>& InOwnerTable)
					{
						return SNew(SGeorgeChatMessageRow, InOwnerTable, Client->User, InMessage);
					})
					.ItemHeight(24.0f)
				]
			]
		]
		+SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.FillWidth(1.0f)
			[
				SAssignNew(MessageTextBox, SEditableTextBox)
				.HintText(LOCTEXT("MessageHint", "Type your message..."))
				.ClearKeyboardFocusOnCommit(false)
				.OnTextCommitted(this, &SGeorgeChatView::OnMessageTextCommitted)
			]
			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SButton)
				.Text(LOCTEXT("SendButton", "Send"))
				.OnClicked_Lambda([this]()
				{
					OnMessageTextCommitted(MessageTextBox->GetText(), ETextCommit::OnEnter);
					return FReply::Handled();
				})
				.IsEnabled_Lambda([this]() // disable if no text to send
				{
					return !MessageTextBox->GetText().IsEmpty();
				})
			]
		]
	];
}

void SGeorgeChatView::OnMessageTextCommitted(const FText& InText, ETextCommit::Type CommitInfo) const
{
	if(CommitInfo == ETextCommit::OnEnter)
	{
		// don't allow empty messages
		if(InText.IsEmpty())
			return;
		
		Client->SendMessage(InText.ToString());
		MessageTextBox->SetText(FText::GetEmpty());
		MessageListView->RequestListRefresh(); // @fixme: for some reason in chat2 (only), the first message doesn't trigger a refresh
		MessageListView->ScrollToBottom();
	}
}

#undef LOCTEXT_NAMESPACE
