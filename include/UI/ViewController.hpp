#pragma once

#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/register.hpp"

#include "HMUI/ViewController.hpp"
#include "HMUI/FlowCoordinator.hpp"
#include "UnityEngine/UI/Button.hpp"

DECLARE_CLASS_CODEGEN(InGameText, InGameTextViewController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(HMUI::FlowCoordinator*, flowCoordinator);

    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, positionButton);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, miscButton);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, rotationButton);
    
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
)