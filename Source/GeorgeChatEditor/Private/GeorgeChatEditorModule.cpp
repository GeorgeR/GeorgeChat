#include "GeorgeChatEditorModule.h"

#include "ToolMenus.h"

#include "GeorgeChatClient.h"
#include "GeorgeChatEditorCommands.h"
#include "GeorgeChatEditorStyle.h"
#include "GeorgeChatMessages.h"
#include "GeorgeChatUser.h"
#include "Widgets/SGeorgeChatView.h"

#define LOCTEXT_NAMESPACE "GeorgeChat"

FName ChatTabName1 = "Chat1";
FText ChatTabLabel1 = LOCTEXT("GeorgeChat.Label1", "Chat 1");
FName ChatTabName2 = "Chat2";
FText ChatTabLabel2 = LOCTEXT("GeorgeChat.Label2", "Chat 2");

namespace
{
	static TSharedRef<SDockTab> SpawnChatTab(const FSpawnTabArgs& SpawnTabArgs, const TSharedRef<FGeorgeChatClient> Client)
	{
		TSharedRef<SDockTab> NewTab = 
			SNew(SDockTab)
			.TabRole(ETabRole::NomadTab)
			[
				SNew(SBorder)
				.Padding(4)
				.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
				[
					SNew(SGeorgeChatView, Client)
				]
			];
		return NewTab;
	}

	static TSharedRef<SWidget> HandleShowToolbarMenu(TSharedPtr<class FUICommandList> CommandList)
	{
		auto& Commands = FGeorgeChatEditorCommands::Get();
		FMenuBuilder MenuBuilder(true, CommandList);

		MenuBuilder.AddMenuEntry(FGeorgeChatEditorCommands::Get().OpenChatWindow1);
		MenuBuilder.AddMenuEntry(FGeorgeChatEditorCommands::Get().OpenChatWindow2);

		return MenuBuilder.MakeWidget();
	}
}

void FGeorgeChatEditorModule::StartupModule()
{
	FGeorgeChatEditorStyle::Initialize();
	FGeorgeChatEditorStyle::ReloadTextures();

	FGeorgeChatEditorCommands::Register();

	ChatClients.Empty();
	
	auto ChatUser1 = MakeShared<FGeorgeChatUser>(1);
	auto ChatClient1 = MakeShared<FGeorgeChatClient>(ChatUser1);
	ChatClients.Add(ChatClient1);

	auto ChatUser2 = MakeShared<FGeorgeChatUser>(2);
	auto ChatClient2 = MakeShared<FGeorgeChatClient>(ChatUser2);
	ChatClients.Add(ChatClient2);

	FTabSpawnerEntry& TabSpawner1 = FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ChatTabName1, FOnSpawnTab::CreateStatic(SpawnChatTab, ChatClient1));
	TabSpawner1.SetDisplayName(ChatTabLabel1);
	TabSpawner1.SetMenuType(ETabSpawnerMenuType::Hidden);

	FTabSpawnerEntry& TabSpawner2 = FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ChatTabName2, FOnSpawnTab::CreateStatic(SpawnChatTab, ChatClient2));
	TabSpawner2.SetDisplayName(ChatTabLabel2);
	TabSpawner2.SetMenuType(ETabSpawnerMenuType::Hidden);

	CommandList = MakeShareable(new FUICommandList);
	CommandList->MapAction(
		FGeorgeChatEditorCommands::Get().OpenChatWindow1,
		FExecuteAction::CreateRaw(this, &FGeorgeChatEditorModule::TryOpenChatWindow, 1)
	);
	CommandList->MapAction(
		FGeorgeChatEditorCommands::Get().OpenChatWindow2,
		FExecuteAction::CreateRaw(this, &FGeorgeChatEditorModule::TryOpenChatWindow, 2)
	);

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FGeorgeChatEditorModule::RegisterMenus));
}

void FGeorgeChatEditorModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);

	FGeorgeChatEditorStyle::Shutdown();
    FGeorgeChatEditorCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ChatTabName1);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ChatTabName2);

	ChatClients.Empty();
}

void FGeorgeChatEditorModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);
	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu(TEXT("LevelEditor.LevelEditorToolBar"));
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitComboButton(
					"Chat",
					FUIAction(),
					FOnGetContent::CreateStatic(&HandleShowToolbarMenu, CommandList),
					LOCTEXT("GeorgeChat.Toolbar.ButtonText", "Chat"),
					LOCTEXT("GeorgeChat.Toolbar.ButtonTooltip", "Show chat actions"),
					FSlateIcon(FGeorgeChatEditorStyle::GetStyleSetName(), TEXT("GeorgeChat.ToolbarIcon"))));
			}
		}
	}
}

void FGeorgeChatEditorModule::TryOpenChatWindow(int32 UserId)
{
	FGlobalTabmanager::Get()->TryInvokeTab(UserId == 1 ? ChatTabName1 : ChatTabName2);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGeorgeChatEditorModule, GeorgeChatEditor)