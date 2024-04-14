#include "Config.hpp"
#include "UI/RotationViewController.hpp"

#include "UnityEngine/Sprite.hpp"
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

DEFINE_TYPE(InGameText, RotationViewController);

void StartTestLevel(InGameText::RotationViewController* self) {
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

void InGameText::RotationViewController::DidActivate(
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

        BSML::Lite::CreateIncrementSetting(container->get_transform(), "Text Rotation X", 1, 1, getModConfig().RotationX.GetValue(), 
            [=](float value) {
                getModConfig().RotationX.SetValue(value);
            }
        );

        BSML::Lite::CreateIncrementSetting(container->get_transform(), "Text Rotation Y", 1, 1, getModConfig().RotationY.GetValue(), 
            [=](float value) {
                getModConfig().RotationY.SetValue(value);
            }
        );

        BSML::Lite::CreateIncrementSetting(container->get_transform(), "Text Rotation Z", 1, 1, getModConfig().RotationZ.GetValue(), 
            [=](float value) {
                getModConfig().RotationZ.SetValue(value);
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