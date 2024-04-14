#include "main.hpp"
#include "Config.hpp"
#include "UI/FlowCoordinator.hpp"
#include "UI/ViewController.hpp"
#include "UI/GameplaySetupView.hpp"
#include "bsml/shared/BSML.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"

auto logger = Paper::ConstLoggerContext(MOD_ID);

modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

#include "GlobalNamespace/GameplayCoreInstaller.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"
#include "GlobalNamespace/LevelBar.hpp"

#include "bsml/shared/BSML-Lite/Creation/Settings.hpp"
#include "bsml/shared/BSML-Lite/Creation/Layout.hpp"
#include "bsml/shared/BSML-Lite/Creation/Text.hpp"
#include "bsml/shared/BSML-Lite/Creation/Misc.hpp"

#include "Config.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

using namespace BSML;

HMUI::Screen *screen;

MAKE_HOOK_MATCH(GameplayCoreInstaller_InstallBindings, &GlobalNamespace::GameplayCoreInstaller::InstallBindings, void, GlobalNamespace::GameplayCoreInstaller *self) {

    GameplayCoreInstaller_InstallBindings(self);

    screen = BSML::Lite::CreateFloatingScreen(UnityEngine::Vector2(1000.0f, 1000.0f), UnityEngine::Vector3(getModConfig().PositionX.GetValue(), getModConfig().PositionY.GetValue(), getModConfig().PositionZ.GetValue()), UnityEngine::Vector3(getModConfig().RotationX.GetValue(), getModConfig().RotationY.GetValue(), getModConfig().RotationZ.GetValue()), 0.0f, false, false);

    if (getModConfig().InGameTextEnabled.GetValue() == true) {

        auto TextModel = Lite::CreateText(screen->get_transform(), getModConfig().InGameText.GetValue(), Vector2::get_zero(), Vector2::get_zero());

        screen->get_gameObject()->set_active(true);

        TextModel->set_alignment(TMPro::TextAlignmentOptions::Center);
        
        TextModel->set_fontSize(getModConfig().TextSize.GetValue());

        TextModel->set_color(getModConfig().TextQolor.GetValue());
        
    } else {
        screen->get_gameObject()->set_active(false);
    }
}

MAKE_HOOK_MATCH(PauseMenuManager_Start, &GlobalNamespace::PauseMenuManager::Start, void, GlobalNamespace::PauseMenuManager *self) {
    PauseMenuManager_Start(self);

    screen->get_gameObject()->set_active(false);

    auto toggleScreen = self->__cordl_internal_get__levelBar()->get_transform()->get_parent()->get_parent()->GetComponent<UnityEngine::Canvas *>();

    AddConfigValueToggle(toggleScreen->get_transform(), getModConfig().InGameTextEnabled)->get_gameObject();
}

MAKE_HOOK_MATCH(ContinueButtonPressed, &GlobalNamespace::PauseMenuManager::ContinueButtonPressed, void, GlobalNamespace::PauseMenuManager *self) {
    ContinueButtonPressed(self);

    screen->get_gameObject()->set_active(getModConfig().InGameTextEnabled.GetValue());    
}

MAKE_HOOK_MATCH(RestartButtonPressed, &GlobalNamespace::PauseMenuManager::RestartButtonPressed, void, GlobalNamespace::PauseMenuManager *self) {
    RestartButtonPressed(self);
    
    screen->get_gameObject()->set_active(getModConfig().InGameTextEnabled.GetValue());
}

MAKE_HOOK_MATCH(MenuButtonPressed, &GlobalNamespace::PauseMenuManager::MenuButtonPressed, void, GlobalNamespace::PauseMenuManager *self) {
    MenuButtonPressed(self);

    UnityEngine::Object::DestroyImmediate(screen->get_gameObject());
}

// Called at the early stages of game loading
extern "C" void setup(CModInfo* info) {
    info->id = MOD_ID;
    info->version = VERSION;
    modInfo.assign(*info);
	
    getConfig().Load(); // Load the config file
    logger.info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    getModConfig().Init(modInfo);
    BSML::Init();
    BSML::Register::RegisterSettingsMenu<InGameText::InGameTextFlowCoordinator*>("In-Game Text");
    BSML::Register::RegisterGameplaySetupTab<InGameText::gameplaySetupView*>("In-Game Text");

    logger.info("Installing Hooks...");
    INSTALL_HOOK(logger, GameplayCoreInstaller_InstallBindings);
    INSTALL_HOOK(logger, PauseMenuManager_Start);
    INSTALL_HOOK(logger, ContinueButtonPressed);
    INSTALL_HOOK(logger, RestartButtonPressed);
    INSTALL_HOOK(logger, MenuButtonPressed);
    logger.info("Installed all hooks!");
}