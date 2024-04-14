#include "GlobalNamespace/GameplayCoreInstaller.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"
#include "GlobalNamespace/LevelBar.hpp"

#include "bsml/shared/BSML-Lite/Creation/Settings.hpp"
#include "bsml/shared/BSML-Lite/Creation/Layout.hpp"
#include "bsml/shared/BSML-Lite/Creation/Text.hpp"
#include "bsml/shared/BSML-Lite/Creation/Misc.hpp"

#include "HMUI/Screen.hpp"

#include "Config.hpp"
#include "hooks.hpp"

using namespace BSML;

HMUI::Screen *screen;

MAKE_AUTO_HOOK_MATCH(GameplayCoreInstaller_InstallBindings, &GlobalNamespace::GameplayCoreInstaller::InstallBindings, void, GlobalNamespace::GameplayCoreInstaller *self) {

    GameplayCoreInstaller_InstallBindings(self);

    screen = BSML::Lite::CreateFloatingScreen(UnityEngine::Vector2(0.0f, 0.0f), UnityEngine::Vector3(getModConfig().PositionX.GetValue(), getModConfig().PositionY.GetValue(), getModConfig().PositionZ.GetValue()), UnityEngine::Vector3(getModConfig().RotationX.GetValue(), getModConfig().RotationY.GetValue(), getModConfig().RotationZ.GetValue()), 0.0f, false, );

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

MAKE_AUTO_HOOK_MATCH(PauseMenuManager_Start, &GlobalNamespace::PauseMenuManager::Start, void, GlobalNamespace::PauseMenuManager *self) {
    PauseMenuManager_Start(self);

    screen->get_gameObject()->set_active(false);

    auto toggleScreen = self->__cordl_internal_get__levelBar()->get_transform()->get_parent()->get_parent()->GetComponent<UnityEngine::Canvas *>();

    AddConfigValueToggle(toggleScreen->get_transform(), getModConfig().InGameTextEnabled)->get_gameObject();
}

MAKE_AUTO_HOOK_MATCH(ContinueButtonPressed, &GlobalNamespace::PauseMenuManager::ContinueButtonPressed, void, GlobalNamespace::PauseMenuManager *self) {
    ContinueButtonPressed(self);

    screen->get_gameObject()->set_active(getModConfig().InGameTextEnabled.GetValue());    
}

MAKE_AUTO_HOOK_MATCH(RestartButtonPressed, &GlobalNamespace::PauseMenuManager::RestartButtonPressed, void, GlobalNamespace::PauseMenuManager *self) {
    RestartButtonPressed(self);
    
    screen->get_gameObject()->set_active(getModConfig().InGameTextEnabled.GetValue());
}

MAKE_AUTO_HOOK_MATCH(MenuButtonPressed, &GlobalNamespace::PauseMenuManager::MenuButtonPressed, void, GlobalNamespace::PauseMenuManager *self) {
    MenuButtonPressed(self);

    UnityEngine::Object::DestroyImmediate(screen->get_gameObject());
}