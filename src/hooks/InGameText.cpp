#include "GlobalNamespace/GameplayCoreInstaller.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"
#include "GlobalNamespace/LevelBar.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

#include "Config.hpp"

#include "hooks.hpp"

UnityEngine::GameObject *screen;

using namespace QuestUI::BeatSaberUI;

MAKE_AUTO_HOOK_MATCH(InGameText, &GlobalNamespace::GameplayCoreInstaller::InstallBindings, void, GlobalNamespace::GameplayCoreInstaller *self) {

    InGameText(self);

    screen = CreateFloatingScreen(UnityEngine::Vector2(1.0f, 1.0f), UnityEngine::Vector3(getModConfig().TextPosition.GetValue()), UnityEngine::Vector3(getModConfig().TextRotation.GetValue()), 0.0f, false, false);

    if (getModConfig().InGameTextEnabled.GetValue() == true) {

        auto TextModel = CreateText(screen->get_transform(), getModConfig().InGameText.GetValue());

        screen->SetActive(true);
        
        TextModel->set_fontSize(getModConfig().TextSize.GetValue());
        
    } else {
        screen->SetActive(false);
    }
}

MAKE_AUTO_HOOK_MATCH(OpenPause, &GlobalNamespace::PauseMenuManager::Start, void, GlobalNamespace::PauseMenuManager *self) {
    OpenPause(self);

    screen->SetActive(false);

    auto toggleScreen = self->levelBar->get_transform()->get_parent()->get_parent()->GetComponent<UnityEngine::Canvas *>();

    //AddConfigValueStringSetting(toggleScreen->get_transform(), getModConfig().InGameText)->get_gameObject();

    AddConfigValueToggle(toggleScreen->get_transform(), getModConfig().InGameTextEnabled)->get_gameObject();
}

MAKE_AUTO_HOOK_MATCH(ContinueButtonPressed, &GlobalNamespace::PauseMenuManager::ContinueButtonPressed, void, GlobalNamespace::PauseMenuManager *self) {
    ContinueButtonPressed(self);

    screen->SetActive(getModConfig().InGameTextEnabled.GetValue());    
}

MAKE_AUTO_HOOK_MATCH(RestartButtonPressed, &GlobalNamespace::PauseMenuManager::RestartButtonPressed, void, GlobalNamespace::PauseMenuManager *self) {
    RestartButtonPressed(self);
    
    screen->SetActive(getModConfig().InGameTextEnabled.GetValue());
}

MAKE_AUTO_HOOK_MATCH(MenuButtonPressed, &GlobalNamespace::PauseMenuManager::MenuButtonPressed, void, GlobalNamespace::PauseMenuManager *self) {
    MenuButtonPressed(self);

    UnityEngine::Object::DestroyImmediate(screen->get_gameObject());
}