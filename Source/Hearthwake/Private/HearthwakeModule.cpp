#include "Modules/ModuleManager.h"
#include "HearthwakeCore.h"

class FHearthwakeModule : public FDefaultGameModuleImpl {
public:
    virtual void StartupModule() override {
        FDefaultGameModuleImpl::StartupModule();
        hearthwake::Inventory Inventory(10);
        const bool Ready = Inventory.apply({1, "wood", 1}) == hearthwake::Outcome::Applied;
        UE_LOG(LogTemp, Display, TEXT("Hearthwake core startup: %s"), Ready ? TEXT("ready") : TEXT("failed"));
    }
};
IMPLEMENT_PRIMARY_GAME_MODULE(FHearthwakeModule, Hearthwake, "Hearthwake");
