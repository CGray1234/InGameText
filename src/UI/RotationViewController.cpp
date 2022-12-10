#include "Config.hpp"
#include "UI/RotationViewController.hpp"

#include "UnityEngine/Sprite.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

#include "GlobalNamespace/SimpleLevelStarter.hpp"
#include "GlobalNamespace/BeatmapLevelSO.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"

DEFINE_TYPE(InGameText, RotationViewController);

void StartTestLevel(InGameText::RotationViewController* self) {
    ArrayW<GlobalNamespace::SimpleLevelStarter*> levelStartArray = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::SimpleLevelStarter*>();
    for (int i = 0; i < sizeof(levelStartArray); i++)
    {
        GlobalNamespace::SimpleLevelStarter* start = (GlobalNamespace::SimpleLevelStarter*)levelStartArray->values[i];
        if (start->get_gameObject()->get_name()->Contains("PerformanceTestLevelButton"))
        {
            start->gameplayModifiers->zenMode = true;
            start->level->songName = ("In-Game Text Config Test");
            start->StartLevel();
            return;
        } 
    }
}

void InGameText::RotationViewController::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace UnityEngine;
    using namespace QuestUI::BeatSaberUI;
    using namespace UnityEngine::UI;

    if (firstActivation) {
        GameObject* container = CreateScrollableSettingsContainer(get_transform());

        QuestUI::BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Text Rotation X", 1, 1, getModConfig().RotationX.GetValue(), 
            [=](float value) {
                getModConfig().RotationX.SetValue(value);
            }
        );

        QuestUI::BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Text Rotation Y", 1, 1, getModConfig().RotationY.GetValue(), 
            [=](float value) {
                getModConfig().RotationY.SetValue(value);
            }
        );

        QuestUI::BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Text Rotation Z", 1, 1, getModConfig().RotationZ.GetValue(), 
            [=](float value) {
                getModConfig().RotationZ.SetValue(value);
            }
        );

        QuestUI::BeatSaberUI::CreateText(container->get_transform(), "");

        auto testButton = QuestUI::BeatSaberUI::CreateUIButton(container->get_transform(), "Test Configuration", "PlayButton",
            [&]() {
                StartTestLevel(this);
            }
        );
    }
}