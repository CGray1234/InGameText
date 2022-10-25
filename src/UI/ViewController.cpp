#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

#include "GlobalNamespace/SimpleLevelStarter.hpp"
#include "GlobalNamespace/BeatmapLevelSO.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"
#include "GlobalNamespace/MenuTransitionsHelper.hpp"

#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Quaternion.hpp"

#include "UI/ViewController.hpp"

#include "Config.hpp"

#include "main.hpp"

DEFINE_TYPE(InGameText, TextViewController);

using namespace QuestUI::BeatSaberUI;
using namespace UnityEngine;
using namespace InGameText;

UnityEngine::GameObject *floatingScreen;

void StartTestLevel(InGameText::TextViewController* self) {
    ArrayW<GlobalNamespace::SimpleLevelStarter*> levelStartArray = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::SimpleLevelStarter*>();
    for (int i = 0; i < sizeof(levelStartArray); i++)
    {
        GlobalNamespace::SimpleLevelStarter* start = (GlobalNamespace::SimpleLevelStarter*)levelStartArray->values[i];
        if (start->get_gameObject()->get_name()->Contains("PerformanceTestLevelButton"))
        {
            start->level->songName = ("In-Game Text Config Test");
            start->StartLevel();
            return;
        } 
    }
}


void TextViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {

    if (firstActivation) {

        UnityEngine::GameObject *container = CreateScrollView(get_transform());

        floatingScreen = CreateFloatingScreen(UnityEngine::Vector2(0.0f, 0.0f), UnityEngine::Vector3(getModConfig().PositionX.GetValue(), getModConfig().PositionY.GetValue(), getModConfig().PositionZ.GetValue()), UnityEngine::Vector3(getModConfig().RotationX.GetValue(), getModConfig().RotationY.GetValue(), getModConfig().RotationZ.GetValue()), 0.0f, false, false);

        auto Text = CreateText(floatingScreen->get_transform(), getModConfig().InGameText.GetValue());

        Text->set_fontSize(getModConfig().TextSize.GetValue());
        Text->set_color(getModConfig().TextQolor.GetValue());

        //AddConfigValueToggle(container->get_transform(), getModConfig().InGameTextEnabled)->get_gameObject();

        CreateToggle(container->get_transform(), "Enable In-Game Text", getModConfig().InGameTextEnabled.GetValue(),
            [=](bool value) {
                getModConfig().InGameTextEnabled.SetValue(value);

                floatingScreen->SetActive(value);
            }
        );

        CreateText(container->get_transform(), "");

        //AddConfigValueStringSetting(container->get_transform(), getModConfig().InGameText)->get_gameObject();
        CreateStringSetting(container->get_transform(), "In-Game Text", getModConfig().InGameText.GetValue(), 
            [=](std::string value) {
                getModConfig().InGameText.SetValue(value);

                Text->SetText(value);
            }
        );

        CreateText(container->get_transform(), "");

        UnityEngine::UI::Button* testConfigButton = CreateUIButton(container->get_transform(), "Test Configuration", "PlayButton", [&]() { StartTestLevel(this); });

        auto summonReplicaText = CreateUIButton(container->get_transform(), "Toggle Main Menu Text Replica", [&]() {
            if (floatingScreen->get_active() == true) {
                floatingScreen->SetActive(false);
            } else {
                floatingScreen->SetActive(true);
            }
        });

        CreateText(container->get_transform(), "");
        //AddConfigValueColorPicker(container->get_transform(), getModConfig().TextQolor);
        CreateColorPicker(container->get_transform(), "Text Color", getModConfig().TextQolor.GetValue(), 
            [=](UnityEngine::Color value) {
                getModConfig().TextQolor.SetValue(value);

                Text->set_color(value);
            }
        );
        CreateText(container->get_transform(), "");
        //AddConfigValueIncrementFloat(container->get_transform(), getModConfig().TextSize, 1, 0.5, 0, 10000);
        CreateIncrementSetting(container->get_transform(), "Text Size", 1, 0.5, getModConfig().TextSize.GetValue(), 
            [=](float value) {
                getModConfig().TextSize.SetValue(value);

                Text->set_fontSize(value);
            }
        );
        CreateText(container->get_transform(), "");
        //AddConfigValueIncrementVector3(container->get_transform(), getModConfig().TextPosition, 1, 0.5);

        // X axis
        CreateIncrementSetting(container->get_transform(), "Text Position X", 1, 0.1, getModConfig().PositionX.GetValue(), 
            [=](float value) {
                getModConfig().PositionX.SetValue(value);

                floatingScreen->get_transform()->set_position(UnityEngine::Vector3(getModConfig().PositionX.GetValue(), getModConfig().PositionY.GetValue(), getModConfig().PositionZ.GetValue()));
            }
        );

        //Y
        CreateIncrementSetting(container->get_transform(), "Text Position Y", 1, 0.1, getModConfig().PositionY.GetValue(), 
            [=](float value) {
                getModConfig().PositionY.SetValue(value);

                floatingScreen->get_transform()->set_position(UnityEngine::Vector3(getModConfig().PositionX.GetValue(), getModConfig().PositionY.GetValue(), getModConfig().PositionZ.GetValue()));
            }
        );

        //Z
        CreateIncrementSetting(container->get_transform(), "Text Position Z", 1, 0.1, getModConfig().PositionZ.GetValue(), 
            [=](float value) {
                getModConfig().PositionZ.SetValue(value);

                floatingScreen->get_transform()->set_position(UnityEngine::Vector3(getModConfig().PositionX.GetValue(), getModConfig().PositionY.GetValue(), getModConfig().PositionZ.GetValue()));
            }
        );
        CreateText(container->get_transform(), "");
        //AddConfigValueIncrementVector3(container->get_transform(), getModConfig().TextRotation,  1, 1);

        //X
        CreateIncrementSetting(container->get_transform(), "Text Rotation X", 1, 1, getModConfig().RotationX.GetValue(), 
            [=](float value) {
                getModConfig().RotationX.SetValue(value);

                Text->get_transform()->set_eulerAngles(UnityEngine::Vector3(getModConfig().RotationX.GetValue(), getModConfig().RotationY.GetValue(), getModConfig().RotationZ.GetValue()));
            }
        );

        //Y
        CreateIncrementSetting(container->get_transform(), "Text Rotation Y", 1, 1, getModConfig().RotationY.GetValue(), 
            [=](float value) {
                getModConfig().RotationY.SetValue(value);

                Text->get_transform()->set_eulerAngles(UnityEngine::Vector3(getModConfig().RotationX.GetValue(), getModConfig().RotationY.GetValue(), getModConfig().RotationZ.GetValue()));
            }
        );

        //Z
        CreateIncrementSetting(container->get_transform(), "Text Rotation Z", 1, 1, getModConfig().RotationZ.GetValue(), 
            [=](float value) {
                getModConfig().RotationZ.SetValue(value);

                Text->get_transform()->set_eulerAngles(UnityEngine::Vector3(getModConfig().RotationX.GetValue(), getModConfig().RotationY.GetValue(), getModConfig().RotationZ.GetValue()));
            }
        );
    }
}

void TextViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling) {
    floatingScreen->SetActive(false);
}