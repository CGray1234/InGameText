#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"

#include "UnityEngine/Sprite.hpp"
#include "HMUI/ImageView.hpp"
#include "HMUI/InputFieldView.hpp"
#include "questui/shared/CustomTypes/Components/Settings/ColorSetting.hpp"
#include "questui/shared/CustomTypes/Components/Settings/IncrementSetting.hpp"
#include "UnityEngine/UI/Button.hpp"

#include "HMUI/FlowCoordinator.hpp"
#include "HMUI/ViewController.hpp"

using namespace UnityEngine;

DECLARE_CLASS_CODEGEN(InGameText, gameplaySetupView, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_FIELD(HMUI::ViewController*, viewController);
    DECLARE_INSTANCE_FIELD(HMUI::FlowCoordinator*, flowCoordinator);

    //Misc
    DECLARE_INSTANCE_FIELD(UI::Button*, MiscButton);
    //Misc Layout
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::VerticalLayoutGroup*, MiscLayout);
    DECLARE_INSTANCE_FIELD(HMUI::InputFieldView*, TextString);
    DECLARE_INSTANCE_FIELD(QuestUI::ColorSetting*, TextColor);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, TextSize);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, miscBackButton);

    //Pos
    DECLARE_INSTANCE_FIELD(UI::Button*, PositionButton);
    // Position Layout
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::VerticalLayoutGroup*, PositionLayout);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, PosX);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, PosY);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, PosZ);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, posBackButton);

    //Rot
    DECLARE_INSTANCE_FIELD(UI::Button*, RotationButton);
    // Rotation Layout
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::VerticalLayoutGroup*, RotationLayout);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, RotX);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, RotY);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, RotZ);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, rotBackButton);


    DECLARE_INSTANCE_METHOD(void, DidActivate, bool firstActivation);
);