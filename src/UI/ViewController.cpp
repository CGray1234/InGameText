#include "UI/ViewController.hpp"
#include "UI/FlowCoordinator.hpp"
#include "UI/MiscViewController.hpp"
#include "UI/PositionViewController.hpp"
#include "UI/RotationViewController.hpp"
#include "UnityEngine/Resources.hpp"
#include "bsml/shared/BSML/Components/Backgroundable.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/Application.hpp"
#include "Config.hpp"
#include "GlobalNamespace/SimpleLevelStarter.hpp"
#include "GlobalNamespace/BeatmapLevelSO.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"

#include "bsml/shared/BSML-Lite/Creation/Image.hpp"
#include "bsml/shared/BSML-Lite/Creation/Settings.hpp"
#include "bsml/shared/BSML-Lite/Creation/Misc.hpp"
#include "bsml/shared/BSML-Lite/Creation/Layout.hpp"
#include "bsml/shared/BSML-Lite/Creation/Buttons.hpp"
#include "bsml/shared/BSML-Lite/Creation/Text.hpp"

#include "UnityEngine/UI/ContentSizeFitter.hpp"

#include "bsml/shared/Helpers/creation.hpp"

#include "Utils/UIUtils.hpp"
#include "assets.hpp"

DEFINE_TYPE(InGameText, InGameTextViewController);

void InGameText::InGameTextViewController::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace UnityEngine;
    using namespace BSML;
    using namespace BSML::Lite;
    using namespace UnityEngine::UI;

    if (firstActivation) {
        VerticalLayoutGroup* verticalLayoutGroup = CreateVerticalLayoutGroup(get_transform());
        verticalLayoutGroup->set_padding(RectOffset::New_ctor(8, 0, -5, 5));

        auto enableMod = CreateToggle(verticalLayoutGroup->get_transform(), "Enable In-Game Text", 
            [=](bool value) {
                getModConfig().InGameTextEnabled.SetValue(value);
            }
        );
        
        HorizontalLayoutGroup* horizontalLayoutGroup = CreateHorizontalLayoutGroup(verticalLayoutGroup->get_transform());
        horizontalLayoutGroup->get_rectTransform()->set_anchoredPosition({0.0f, 0.0f});
        horizontalLayoutGroup->set_padding(RectOffset::New_ctor(2, 2, 2, 2));
        auto horizontalLayoutGroupElement = horizontalLayoutGroup->GetComponent<LayoutElement*>();
        auto horizontalLayoutGroupFitter = horizontalLayoutGroup->GetComponent<ContentSizeFitter*>();
        horizontalLayoutGroupFitter->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
        horizontalLayoutGroupFitter->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize);

        auto posButton = CreateUIButton(horizontalLayoutGroupFitter->get_transform(), "", "SettingsButton", 
            [=]() {
                flowCoordinator->SetTitle("Position Settings", ViewController::AnimationType::In);
                flowCoordinator->ReplaceTopViewController(BSML::Helpers::CreateViewController<InGameText::PositionViewController*>(), flowCoordinator, flowCoordinator, nullptr, ViewController::AnimationType::In, ViewController::AnimationDirection::Horizontal);

                reinterpret_cast<InGameText::InGameTextFlowCoordinator*>(flowCoordinator)->currentViewController = BSML::Helpers::CreateViewController<InGameText::PositionViewController*>();
        });
        UIUtils::SwapButtonSprites(posButton, Base64ToSprite(posIcon), Base64ToSprite(posSelected));

        auto rotButton = CreateUIButton(horizontalLayoutGroupFitter->get_transform(), "", "SettingsButton", 
            [=]() {
                flowCoordinator->SetTitle("Rotation Settings", ViewController::AnimationType::In);
                flowCoordinator->ReplaceTopViewController(BSML::Helpers::CreateViewController<InGameText::RotationViewController*>(), flowCoordinator, flowCoordinator, nullptr, ViewController::AnimationType::In, ViewController::AnimationDirection::Horizontal);

                reinterpret_cast<InGameText::InGameTextFlowCoordinator*>(flowCoordinator)->currentViewController = BSML::Helpers::CreateViewController<InGameText::RotationViewController*>();
        });
        UIUtils::SwapButtonSprites(rotButton, Base64ToSprite(rotIcon), Base64ToSprite(rotSelected));

        auto miscButton = CreateUIButton(horizontalLayoutGroupFitter->get_transform(), "", "SettingsButton", 
            [=]() {
                flowCoordinator->SetTitle("Rotation Settings", ViewController::AnimationType::In);
                flowCoordinator->ReplaceTopViewController(BSML::Helpers::CreateViewController<InGameText::MiscViewController*>(), flowCoordinator, flowCoordinator, nullptr, ViewController::AnimationType::In, ViewController::AnimationDirection::Horizontal);

                reinterpret_cast<InGameText::InGameTextFlowCoordinator*>(flowCoordinator)->currentViewController = BSML::Helpers::CreateViewController<InGameText::MiscViewController*>();
        });
        UIUtils::SwapButtonSprites(miscButton, Base64ToSprite(miscIcon), Base64ToSprite(miscSelected));

        
    }
}