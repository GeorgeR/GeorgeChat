#include "GeorgeChatEditorCommands.h"

#include "Framework/Commands/Commands.h"

#include "GeorgeChatEditorStyle.h"

#define LOCTEXT_NAMESPACE "GeorgeChat"

FGeorgeChatEditorCommands::FGeorgeChatEditorCommands()
    : TCommands<FGeorgeChatEditorCommands>(TEXT("GeorgeChat"),
    NSLOCTEXT("Contexts", "GeorgeChat", "GeorgeChat"),
    NAME_None,
    FGeorgeChatEditorStyle::GetStyleSetName()) { }

void FGeorgeChatEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenChatWindow1, "Open Chat 1", "Opens the chat window for User1.", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(OpenChatWindow2, "Open Chat 2", "Opens the chat window for User2.", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
