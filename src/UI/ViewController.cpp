#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

#include "GlobalNamespace/SimpleLevelStarter.hpp"
#include "GlobalNamespace/BeatmapLevelSO.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"
#include "GlobalNamespace/MenuTransitionsHelper.hpp"

#include "UnityEngine/Resources.hpp"

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

        floatingScreen = CreateFloatingScreen(UnityEngine::Vector2(getModConfig().TextSize.GetValue()), UnityEngine::Vector3(getModConfig().TextPosition.GetValue()), UnityEngine::Vector3(getModConfig().TextRotation.GetValue()), 0.0f, false, false);

        CreateText(floatingScreen->get_transform(), getModConfig().InGameText.GetValue(), UnityEngine::Vector2(0.0f, 0.0f), UnityEngine::Vector2(getModConfig().TextSize.GetValue()));

        AddConfigValueToggle(container->get_transform(), getModConfig().InGameTextEnabled)->get_gameObject();

        CreateText(container->get_transform(), "");

        AddConfigValueStringSetting(container->get_transform(), getModConfig().InGameText)->get_gameObject();

        CreateText(container->get_transform(), "");

        auto testConfigButton = CreateUIButton(container->get_transform(), "Test Configuration", "PlayButton", [&]() { StartTestLevel(this); });
        auto summonReplicaText = CreateUIButton(container->get_transform(), "Toggle Main Menu Text Replica", [&]() {
            if (floatingScreen->get_active() == true) {
                floatingScreen->SetActive(false);
            } else {
                floatingScreen->SetActive(true);
            }
        });
        auto applyChangesButton = CreateUIButton(container->get_transform(), "Apply Changes To Main Menu", [&]() {
            Resources::FindObjectsOfTypeAll<GlobalNamespace::MenuTransitionsHelper*>()[0]->RestartGame(nullptr);
        });

        CreateText(container->get_transform(), "");

        AddConfigValueIncrementVector2(container->get_transform(), getModConfig().TextSize, 1, 0.5);
        CreateText(container->get_transform(), "");
        AddConfigValueIncrementVector3(container->get_transform(), getModConfig().TextPosition, 1, 0.5);
        CreateText(container->get_transform(), "");
        AddConfigValueIncrementVector3(container->get_transform(), getModConfig().TextRotation,  1, 0.5);
    }
}

void TextViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling) {
    floatingScreen->SetActive(false);
}