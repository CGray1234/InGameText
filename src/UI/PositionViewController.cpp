#include "Config.hpp"
#include "UI/PositionViewController.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

#include "Images/PositionSettingsIcon.hpp"

#include "GlobalNamespace/SimpleLevelStarter.hpp"
#include "GlobalNamespace/BeatmapLevelSO.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"

DEFINE_TYPE(InGameText, PositionViewController);

void StartTestLevel(InGameText::PositionViewController* self) {
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

void InGameText::PositionViewController::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace UnityEngine;
    using namespace QuestUI::BeatSaberUI;
    using namespace UnityEngine::UI;

    if (firstActivation) {
        GameObject* container = CreateScrollableSettingsContainer(get_transform());

        UnityEngine::Sprite* PositionImage = Base64ToSprite(PositionIcon);

        CreateImage(container->get_transform(), PositionImage, Vector2::get_zero(), Vector2(75.0f, 75.0f));

        QuestUI::BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Text Position X", 1, 0.1, getModConfig().PositionX.GetValue(), 
            [=](float value) {
                getModConfig().PositionX.SetValue(value);
            }
        );

        QuestUI::BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Text Position Y", 1, 0.1, getModConfig().PositionY.GetValue(), 
            [=](float value) {
                getModConfig().PositionY.SetValue(value);
            }
        );

        QuestUI::BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Text Position Z", 1, 0.1, getModConfig().PositionZ.GetValue(), 
            [=](float value) {
                getModConfig().PositionZ.SetValue(value);
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