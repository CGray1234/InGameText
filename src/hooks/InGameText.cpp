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

    screen = CreateFloatingScreen(UnityEngine::Vector2(0.0f, 0.0f), UnityEngine::Vector3(getModConfig().PositionX.GetValue(), getModConfig().PositionY.GetValue(), getModConfig().PositionZ.GetValue()), UnityEngine::Vector3(getModConfig().RotationX.GetValue(), getModConfig().RotationY.GetValue(), getModConfig().RotationZ.GetValue()), 0.0f, false, false);

    if (getModConfig().InGameTextEnabled.GetValue() == true) {

        auto TextModel = CreateText(screen->get_transform(), getModConfig().InGameText.GetValue());

        screen->SetActive(true);

        TextModel->set_alignment(TMPro::TextAlignmentOptions::Center);
        
        TextModel->set_fontSize(getModConfig().TextSize.GetValue());

        TextModel->set_color(getModConfig().TextQolor.GetValue());
        
    } else {
        screen->SetActive(false);
    }
}

MAKE_AUTO_HOOK_MATCH(OpenPause, &GlobalNamespace::PauseMenuManager::Start, void, GlobalNamespace::PauseMenuManager *self) {
    OpenPause(self);

    screen->SetActive(false);

    auto toggleScreen = self->levelBar->get_transform()->get_parent()->get_parent()->GetComponent<UnityEngine::Canvas *>();

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