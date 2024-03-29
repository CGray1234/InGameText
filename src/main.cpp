#include "main.hpp"
#include "Config.hpp"
#include "hooks.hpp"
#include "UI/FlowCoordinator.hpp"
#include "UI/ViewController.hpp"
#include "UI/GameplaySetupView.hpp"
#include "bsml/shared/BSML.hpp"

DEFINE_CONFIG(ModConfig);

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    getModConfig().Init(modInfo);
    BSML::Init();
    BSML::Register::RegisterSettingsMenu<InGameText::InGameTextFlowCoordinator*>("In-Game Text");
    BSML::Register::RegisterGameplaySetupTab<InGameText::gameplaySetupView*>("In-Game Text");

    getLogger().info("Installing hooks...");
    
    auto& logger = getLogger();
    Hooks::InstallHooks(logger);

    getLogger().info("Installed all hooks!");
}