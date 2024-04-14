#include "Config.hpp"
#include "UI/MiscViewController.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

#include "UnityEngine/Resources.hpp"

#include "bsml/shared/BSML-Lite/Creation/Image.hpp"
#include "bsml/shared/BSML-Lite/Creation/Settings.hpp"
#include "bsml/shared/BSML-Lite/Creation/Misc.hpp"
#include "bsml/shared/BSML-Lite/Creation/Layout.hpp"
#include "bsml/shared/BSML-Lite/Creation/Buttons.hpp"
#include "bsml/shared/BSML-Lite/Creation/Text.hpp"

#include "GlobalNamespace/SimpleLevelStarter.hpp"
#include "GlobalNamespace/BeatmapLevelSO.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"

DEFINE_TYPE(InGameText, MiscViewController);

void StartTestLevel(InGameText::MiscViewController* self) {
    auto simpleLevelStarters = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::SimpleLevelStarter*>();
    for (auto& starter : simpleLevelStarters)
    {
        if (starter->get_gameObject()->get_name()->Contains("PerformanceTestLevelButton"))
        {
            starter->__cordl_internal_get__gameplayModifiers()->__cordl_internal_set__zenMode(true);
            starter->StartLevel();
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
    using namespace BSML;
    using namespace BSML::Lite;
    using namespace UnityEngine::UI;

    if (firstActivation) {
        GameObject* container = CreateScrollableSettingsContainer(get_transform());

        BSML::Lite::CreateToggle(container->get_transform(), "Enable In-Game Text", getModConfig().InGameTextEnabled.GetValue(), 
            [=](bool value) {
                getModConfig().InGameTextEnabled.SetValue(value);
            }
        );

        BSML::Lite::CreateStringSetting(container->get_transform(), "In-Game Text", getModConfig().InGameText.GetValue(),
            [=](std::string value) {
                getModConfig().InGameText.SetValue(value);
            }
        );

        BSML::Lite::CreateColorPicker(container->get_transform(), "Text Color", getModConfig().TextQolor.GetValue(),
            [=](UnityEngine::Color value) {
                getModConfig().TextQolor.SetValue(value);
            }
        );

        BSML::Lite::CreateIncrementSetting(container->get_transform(), "Text Size", 1, 0.5, getModConfig().TextSize.GetValue(),
            [=](float value) {
                getModConfig().TextSize.SetValue(value);
            }
        );

        BSML::Lite::CreateText(container->get_transform(), "");

        auto testButton = BSML::Lite::CreateUIButton(container->get_transform(), "Test Configuration", "PlayButton",
            [&]() {
                StartTestLevel(this);
            }
        );
        testButton->set_interactable(false);
        AddHoverHint(testButton->get_gameObject(), "Feature disabled until further notice");
    }
}