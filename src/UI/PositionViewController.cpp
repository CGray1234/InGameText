#include "Config.hpp"
#include "UI/PositionViewController.hpp"

#include "bsml/shared/BSML-Lite/Creation/Image.hpp"
#include "bsml/shared/BSML-Lite/Creation/Settings.hpp"
#include "bsml/shared/BSML-Lite/Creation/Misc.hpp"
#include "bsml/shared/BSML-Lite/Creation/Layout.hpp"
#include "bsml/shared/BSML-Lite/Creation/Buttons.hpp"
#include "bsml/shared/BSML-Lite/Creation/Text.hpp"

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
    using namespace BSML;
    using namespace BSML::Lite;
    using namespace UnityEngine::UI;

    if (firstActivation) {
        GameObject* container = CreateScrollableSettingsContainer(get_transform());

        BSML::CreateIncrementSetting(container->get_transform(), "Text Position X", 1, 0.1, getModConfig().PositionX.GetValue(), 
            [=](float value) {
                getModConfig().PositionX.SetValue(value);
            }
        );

        BSML::CreateIncrementSetting(container->get_transform(), "Text Position Y", 1, 0.1, getModConfig().PositionY.GetValue(), 
            [=](float value) {
                getModConfig().PositionY.SetValue(value);
            }
        );

        BSML::CreateIncrementSetting(container->get_transform(), "Text Position Z", 1, 0.1, getModConfig().PositionZ.GetValue(), 
            [=](float value) {
                getModConfig().PositionZ.SetValue(value);
            }
        );

        BSML::Lite::CreateText(container->get_transform(), "");

        auto testButton = BSML::Lite::CreateUIButton(container->get_transform(), "Test Configuration", "PlayButton",
            [&]() {
                StartTestLevel(this);
            }
        );
    }
}