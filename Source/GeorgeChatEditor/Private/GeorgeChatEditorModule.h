#pragma once

#include "IGeorgeChatEditorModuleInterface.h"

#include "CoreMinimal.h"

class FGeorgeChatClient;
class FGeorgeChatEditorToolbarExtender;

class FGeorgeChatEditorModule final
    : public IGeorgeChatEditorModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual bool SupportsDynamicReloading() override { return true; }

private:
	TSharedPtr<class FUICommandList> CommandList;
	TArray<TSharedPtr<FGeorgeChatClient>> ChatClients;

	void RegisterMenus();
	void TryOpenChatWindow(int32 UserId);
};
