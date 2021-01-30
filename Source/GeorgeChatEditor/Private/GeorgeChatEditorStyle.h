#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

class GEORGECHATEDITOR_API FGeorgeChatEditorStyle
{
public:
	static void Initialize();
	static void Shutdown();

	static void ReloadTextures();

	static const ISlateStyle& Get();

	static FName GetStyleSetName();

private:
	static TSharedPtr<class FSlateStyleSet> StyleInstance;
	
	static TSharedRef<class FSlateStyleSet> Create();
};