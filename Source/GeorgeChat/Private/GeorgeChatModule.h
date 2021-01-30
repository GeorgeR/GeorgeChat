#pragma once

#include "IGeorgeChatModuleInterface.h"

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FGeorgeChatModule final
    : public IGeorgeChatModuleInterface
{
public:
    void StartupModule() override;
    void ShutdownModule() override;
};