#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"
#include "Config.hpp"
#include "UI/GameplaySetupView.hpp"

#include "UnityEngine/RectOffset.hpp"

DEFINE_TYPE(InGameText, gameplaySetupView);

using namespace UnityEngine::UI;
using namespace UnityEngine;
using namespace QuestUI::BeatSaberUI;

void InGameText::gameplaySetupView::DidActivate(bool firstActivation) {
    if (!firstActivation) return;

    auto verticalLayoutGroup = CreateVerticalLayoutGroup(get_transform());
    verticalLayoutGroup->get_rectTransform()->set_anchoredPosition({0.0f, 0.0f});
    verticalLayoutGroup->set_padding(RectOffset::New_ctor(2, 2, 2, 2));
    auto verticalLayoutGroupElement = verticalLayoutGroup->GetComponent<LayoutElement*>();
    verticalLayoutGroupElement->set_preferredHeight(65.0f);
    verticalLayoutGroupElement->set_preferredWidth(70.0f);
    auto verticalLayoutGroupFitter = verticalLayoutGroup->GetComponent<ContentSizeFitter*>();
    verticalLayoutGroupFitter->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
    verticalLayoutGroupFitter->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize);

    CreateText(verticalLayoutGroup->get_transform(), "----Miscellaneous Settings----")->set_alignment(TMPro::TextAlignmentOptions::Center);

    InGameText::gameplaySetupView::TextSetting = CreateStringSetting(verticalLayoutGroup->get_transform(), "In-Game Text", getModConfig().InGameText.GetValue(),
        [](std::string value) {
            getModConfig().InGameText.SetValue(value);
        }
    );

    InGameText::gameplaySetupView::QolorPicker = CreateColorPicker(verticalLayoutGroup->get_transform(), "Text Color", getModConfig().TextQolor.GetValue(),
        [=](UnityEngine::Color value) {
            getModConfig().TextQolor.SetValue(value);
        }
    );

    InGameText::gameplaySetupView::SizeSetting = CreateIncrementSetting(verticalLayoutGroup->get_transform(), "Text Size", 1, 0.5, getModConfig().TextSize.GetValue(),
        [=](float value) {
            getModConfig().TextSize.SetValue(value);
        }
    );

    CreateText(verticalLayoutGroup->get_transform(), "----Position Settings----")->set_alignment(TMPro::TextAlignmentOptions::Center);

    InGameText::gameplaySetupView::PosX = CreateIncrementSetting(verticalLayoutGroup->get_transform(), "Text Position X", 1, 0.1, getModConfig().PositionX.GetValue(), 
        [=](float value) {
            getModConfig().PositionX.SetValue(value);
        }
    );

    InGameText::gameplaySetupView::PosY = CreateIncrementSetting(verticalLayoutGroup->get_transform(), "Text Position Y", 1, 0.1, getModConfig().PositionY.GetValue(), 
        [=](float value) {
            getModConfig().PositionY.SetValue(value);
        }
    );

    InGameText::gameplaySetupView::PosZ = CreateIncrementSetting(verticalLayoutGroup->get_transform(), "Text Position Z", 1, 0.1, getModConfig().PositionZ.GetValue(), 
        [=](float value) {
            getModConfig().PositionZ.SetValue(value);
        }
    );

    CreateText(verticalLayoutGroup->get_transform(), "----Rotation Settings----")->set_alignment(TMPro::TextAlignmentOptions::Center);

    InGameText::gameplaySetupView::RotX = CreateIncrementSetting(verticalLayoutGroup->get_transform(), "Text Rotation X", 1, 1, getModConfig().RotationX.GetValue(), 
        [=](float value) {
            getModConfig().RotationX.SetValue(value);
        }
    );

    InGameText::gameplaySetupView::RotX = CreateIncrementSetting(verticalLayoutGroup->get_transform(), "Text Rotation Y", 1, 1, getModConfig().RotationY.GetValue(), 
        [=](float value) {
            getModConfig().RotationY.SetValue(value);
        }
    );

    InGameText::gameplaySetupView::RotX = CreateIncrementSetting(verticalLayoutGroup->get_transform(), "Text Rotation Z", 1, 1, getModConfig().RotationZ.GetValue(), 
        [=](float value) {
            getModConfig().RotationZ.SetValue(value);
        }
    );
}