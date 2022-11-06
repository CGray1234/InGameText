#pragma once

#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/register.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

DECLARE_CLASS_CODEGEN(InGameText, InGameTextViewController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(HMUI::FlowCoordinator*, flowCoordinator);

    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, positionButton);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, miscButton);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, rotationButton);
    
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

public:

    UnityEngine::UI::Button* CreateViewControllerButton(UnityEngine::Transform* parent, std::string title, std::string description, HMUI::ViewController* viewController);
)