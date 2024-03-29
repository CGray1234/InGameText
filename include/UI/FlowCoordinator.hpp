#pragma once

#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/register.hpp"
#include "ViewController.hpp"
#include "UI/GameplaySetupView.hpp"
#include "main.hpp"

DECLARE_CLASS_CODEGEN(InGameText, InGameTextFlowCoordinator, HMUI::FlowCoordinator,
    DECLARE_INSTANCE_FIELD(InGameText::InGameTextViewController*, inGameTextViewController);
    DECLARE_INSTANCE_FIELD(HMUI::ViewController*, currentViewController);

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD(void, BackButtonWasPressed, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "BackButtonWasPressed", 1), HMUI::ViewController* topViewController);
)