#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

#include "questui/shared/CustomTypes/Components/Settings/ColorSetting.hpp"
#include "questui/shared/CustomTypes/Components/Settings/IncrementSetting.hpp"

#include "HMUI/InputFieldView.hpp"

using namespace UnityEngine;

DECLARE_CLASS_CODEGEN(InGameText, gameplaySetupView, UnityEngine::MonoBehaviour,
    //Misc
    DECLARE_INSTANCE_FIELD(QuestUI::ColorSetting*, QolorPicker);
    DECLARE_INSTANCE_FIELD(HMUI::InputFieldView*, TextSetting);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, SizeSetting);

    //Pos
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, PosX);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, PosY);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, PosZ);

    //Rot
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, RotX);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, RotY);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, RotZ);

    DECLARE_INSTANCE_METHOD(void, DidActivate, bool firstActivation);


);