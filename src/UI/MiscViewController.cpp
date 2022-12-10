#include "Config.hpp"
#include "UI/MiscViewController.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

#include "GlobalNamespace/SimpleLevelStarter.hpp"
#include "GlobalNamespace/BeatmapLevelSO.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"

DEFINE_TYPE(InGameText, MiscViewController);

void StartTestLevel(InGameText::MiscViewController* self) {
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

void InGameText::MiscViewController::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace UnityEngine;
    using namespace QuestUI::BeatSaberUI;
    using namespace UnityEngine::UI;

    if (firstActivation) {
        GameObject* container = CreateScrollableSettingsContainer(get_transform());

        QuestUI::BeatSaberUI::CreateStringSetting(container->get_transform(), "In-Game Text", getModConfig().InGameText.GetValue(),
            [=](std::string value) {
                getModConfig().InGameText.SetValue(value);
            }
        );

        QuestUI::BeatSaberUI::CreateColorPicker(container->get_transform(), "Text Color", getModConfig().TextQolor.GetValue(),
            [=](UnityEngine::Color value) {
                getModConfig().TextQolor.SetValue(value);
            }
        );

        QuestUI::BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Text Size", 1, 0.5, getModConfig().TextSize.GetValue(),
            [=](float value) {
                getModConfig().TextSize.SetValue(value);
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