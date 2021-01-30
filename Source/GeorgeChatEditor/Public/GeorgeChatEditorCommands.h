#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "Framework/Commands/UICommandInfo.h"

class FUICommandList;

class GEORGECHATEDITOR_API FGeorgeChatEditorCommands 
    : public TCommands<FGeorgeChatEditorCommands>
{
public:
    FGeorgeChatEditorCommands();

	void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> OpenChatWindow1;
	TSharedPtr<FUICommandInfo> OpenChatWindow2;
};