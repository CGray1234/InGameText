#include "bsml/shared/Helpers/creation.hpp"
#include "Config.hpp"
#include "UI/GameplaySetupView.hpp"
#include "UI/ViewController.hpp"
#include "UI/FlowCoordinator.hpp"
#include "UI/MiscViewController.hpp"
#include "UI/PositionViewController.hpp"
#include "UI/RotationViewController.hpp"

#include "Utils/UIUtils.hpp"
#include "assets.hpp"

#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "HMUI/ViewController.hpp"
#include "HMUI/FlowCoordinator.hpp"

#include "GlobalNamespace/SimpleLevelStarter.hpp"
#include "UnityEngine/Resources.hpp"
#include "GlobalNamespace/BeatmapLevelSO.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"

#include "bsml/shared/BSML-Lite/Creation/Image.hpp"
#include "bsml/shared/BSML-Lite/Creation/Settings.hpp"
#include "bsml/shared/BSML-Lite/Creation/Misc.hpp"
#include "bsml/shared/BSML-Lite/Creation/Layout.hpp"
#include "bsml/shared/BSML-Lite/Creation/Buttons.hpp"
#include "bsml/shared/BSML-Lite/Creation/Text.hpp"

#include "UnityEngine/UI/ContentSizeFitter.hpp"

DEFINE_TYPE(InGameText, gameplaySetupView);

using namespace UnityEngine::UI;
using namespace UnityEngine;
using namespace BSML;
using namespace BSML::Lite;

void StartTestLevel(InGameText::gameplaySetupView* self) {
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

void InGameText::gameplaySetupView::DidActivate(bool firstActivation) {
    if (!firstActivation) return;
    auto verticalLayoutGroup = CreateVerticalLayoutGroup(get_transform());

    auto enableMod = CreateToggle(verticalLayoutGroup->get_transform(), "Enable In-Game Text", 
        [=](bool value) {
            getModConfig().InGameTextEnabled.SetValue(value);
        }
    );

    auto horizontalLayoutGroup = CreateHorizontalLayoutGroup(verticalLayoutGroup->get_transform());
    horizontalLayoutGroup->get_rectTransform()->set_anchoredPosition({0.0f, 0.0f});
    horizontalLayoutGroup->set_padding(RectOffset::New_ctor(2, 2, 2, 2));
    auto horizontalLayoutGroupElement = horizontalLayoutGroup->GetComponent<LayoutElement*>();
    horizontalLayoutGroupElement->set_preferredHeight(65.0f);
    horizontalLayoutGroupElement->set_preferredWidth(97.5f);
    auto horizontalLayoutGroupFitter = horizontalLayoutGroup->GetComponent<ContentSizeFitter*>();
    horizontalLayoutGroupFitter->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
    horizontalLayoutGroupFitter->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize);

    MiscLayout = CreateVerticalLayoutGroup(get_transform());
    MiscLayout->get_rectTransform()->set_anchoredPosition({0.0f, 0.0f});
    MiscLayout->set_padding(RectOffset::New_ctor(2, 2, 2, 2));
    auto MiscLayoutGroupElement = MiscLayout->GetComponent<LayoutElement*>();
    MiscLayoutGroupElement->set_preferredHeight(65.0f);
    MiscLayoutGroupElement->set_preferredWidth(70.0f);
    auto MiscLayoutGroupFitter = MiscLayout->GetComponent<ContentSizeFitter*>();
    MiscLayoutGroupFitter->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
    MiscLayoutGroupFitter->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize);
    TextString = CreateStringSetting(MiscLayout->get_transform(), "In-Game Text", getModConfig().InGameText.GetValue(), 
        [=](std::string value) {
            getModConfig().InGameText.SetValue(value);
        }
    );
    TextColor = CreateColorPicker(MiscLayout->get_transform(), "Text Color", getModConfig().TextQolor.GetValue(),
        [=](Color value) {
            getModConfig().TextQolor.SetValue(value);
        }
    );
    TextSize = CreateIncrementSetting(MiscLayout->get_transform(), "Text Size", 1, 1, getModConfig().TextSize.GetValue(), 
        [=](float value) {
            getModConfig().TextSize.SetValue(value);
        }
    );
    auto miscTest = BSML::Lite::CreateUIButton(MiscLayout->get_transform(), "Test Configuration", "PlayButton", [&]() {
        StartTestLevel(this);
    });
    miscTest->set_interactable(false);
    AddHoverHint(miscTest->get_gameObject(), "Feature disabled until further notice");
    miscBackButton = BSML::Lite::CreateUIButton(MiscLayout->get_transform(), "BACK", [=](){
        MiscLayout->get_gameObject()->SetActive(false);
        horizontalLayoutGroup->get_gameObject()->SetActive(true);
    });
    MiscLayout->get_gameObject()->SetActive(false);

    PositionLayout = CreateVerticalLayoutGroup(get_transform());
    PositionLayout->get_rectTransform()->set_anchoredPosition({0.0f, 0.0f});
    PositionLayout->set_padding(RectOffset::New_ctor(2, 2, 2, 2));
    auto posLayoutGroupElement = PositionLayout->GetComponent<LayoutElement*>();
    posLayoutGroupElement->set_preferredHeight(65.0f);
    posLayoutGroupElement->set_preferredWidth(70.0f);
    auto posLayoutGroupFitter = PositionLayout->GetComponent<ContentSizeFitter*>();
    posLayoutGroupFitter->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
    posLayoutGroupFitter->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize);
    PosX = CreateIncrementSetting(PositionLayout->get_transform(), "Text Position X", 1, 1, getModConfig().PositionX.GetValue(), 
        [=](float value) {
            getModConfig().PositionX.SetValue(value);
        }
    );
    PosY = CreateIncrementSetting(PositionLayout->get_transform(), "Text Position Y", 1, 1, getModConfig().PositionY.GetValue(), 
        [=](float value) {
            getModConfig().PositionY.SetValue(value);
        }
    );
    PosZ = CreateIncrementSetting(PositionLayout->get_transform(), "Text Position Z", 1, 1, getModConfig().PositionZ.GetValue(), 
        [=](float value) {
            getModConfig().PositionZ.SetValue(value);
        }
    );
    auto posTest = CreateUIButton(PositionLayout->get_transform(), "Test Configuration", "PlayButton", [&]() {
        StartTestLevel(this);
    });
    posTest->set_interactable(false);
    AddHoverHint(posTest->get_gameObject(), "Feature disabled until further notice");
    posBackButton = CreateUIButton(PositionLayout->get_transform(), "BACK", [=](){
        PositionLayout->get_gameObject()->SetActive(false);
        horizontalLayoutGroup->get_gameObject()->SetActive(true);
    });
    PositionLayout->get_gameObject()->SetActive(false);

    RotationLayout = CreateVerticalLayoutGroup(get_transform());
    RotationLayout->get_rectTransform()->set_anchoredPosition({0.0f, 0.0f});
    RotationLayout->set_padding(RectOffset::New_ctor(2, 2, 2, 2));
    auto rotLayoutGroupElement = RotationLayout->GetComponent<LayoutElement*>();
    rotLayoutGroupElement->set_preferredHeight(65.0f);
    rotLayoutGroupElement->set_preferredWidth(70.0f);
    auto rotLayoutGroupFitter = RotationLayout->GetComponent<ContentSizeFitter*>();
    rotLayoutGroupFitter->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
    rotLayoutGroupFitter->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize);
    RotX = CreateIncrementSetting(RotationLayout->get_transform(), "Text Rotation X", 1, 1, getModConfig().RotationX.GetValue(), 
        [=](float value) {
            getModConfig().RotationX.SetValue(value);
        }
    );
    RotY = CreateIncrementSetting(RotationLayout->get_transform(), "Text Rotation Y", 1, 1, getModConfig().RotationY.GetValue(), 
        [=](float value) {
            getModConfig().RotationY.SetValue(value);
        }
    );
    RotZ = CreateIncrementSetting(RotationLayout->get_transform(), "Text Rotation Z", 1, 1, getModConfig().RotationZ.GetValue(), 
        [=](float value) {
            getModConfig().RotationZ.SetValue(value);
        }
    );
    auto rotTest = CreateUIButton(RotationLayout->get_transform(), "Test Configuration", "PlayButton", [&]() {
        StartTestLevel(this);
    });
    rotTest->set_interactable(false);
    AddHoverHint(rotTest->get_gameObject(), "Feature disabled until further notice");
    rotBackButton = CreateUIButton(RotationLayout->get_transform(), "BACK", [=](){
        RotationLayout->get_gameObject()->SetActive(false);
        horizontalLayoutGroup->get_gameObject()->SetActive(true);
    });
    RotationLayout->get_gameObject()->SetActive(false);

    MiscButton = CreateUIButton(horizontalLayoutGroup->get_transform(), "", "SettingsButton", [=]() {
        MiscLayout->get_gameObject()->SetActive(true);
        horizontalLayoutGroup->get_gameObject()->SetActive(false);
    });
    UIUtils::SwapButtonSprites(MiscButton, BSML::Lite::Base64ToSprite(miscIcon), BSML::Lite::Base64ToSprite(miscSelected));

    PositionButton = CreateUIButton(horizontalLayoutGroup->get_transform(), "", "SettingsButton", [=]() {
        PositionLayout->get_gameObject()->SetActive(true);
        horizontalLayoutGroup->get_gameObject()->SetActive(false);
    });
    UIUtils::SwapButtonSprites(PositionButton, BSML::Lite::Base64ToSprite(posIcon), BSML::Lite::Base64ToSprite(posSelected));
    
    RotationButton = CreateUIButton(horizontalLayoutGroup->get_transform(), "", "SettingsButton", [=]() {
        RotationLayout->get_gameObject()->SetActive(true);
        horizontalLayoutGroup->get_gameObject()->SetActive(false);
    });
    UIUtils::SwapButtonSprites(RotationButton, BSML::Lite::Base64ToSprite(rotIcon), BSML::Lite::Base64ToSprite(rotSelected));
}