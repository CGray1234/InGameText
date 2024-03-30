#include "UI/FlowCoordinator.hpp"
#include "UI/ViewController.hpp"
#include "GlobalNamespace/MenuTransitionsHelper.hpp"

#include "bsml/shared/Helpers/creation.hpp"

DEFINE_TYPE(InGameText, InGameTextFlowCoordinator);

void InGameText::InGameTextFlowCoordinator::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    using namespace HMUI;

    if (firstActivation) {
        SetTitle(MOD_ID, ViewController::AnimationType::Out);

        set_showBackButton(true);

        inGameTextViewController = BSML::Helpers::CreateViewController<InGameText::InGameTextViewController*>();
        inGameTextViewController->flowCoordinator = this;

        currentViewController = nullptr;

        ProvideInitialViewControllers(inGameTextViewController, nullptr, nullptr, nullptr, nullptr);
    }
}

void InGameText::InGameTextFlowCoordinator::BackButtonWasPressed(
    HMUI::ViewController* topViewController
) {
    using namespace HMUI;
    using namespace UnityEngine;

    if (currentViewController) {
        SetTitle(MOD_ID, ViewController::AnimationType::In);
        ReplaceTopViewController(inGameTextViewController, this, this, nullptr, ViewController::AnimationType::Out, ViewController::AnimationDirection::Horizontal);

        currentViewController = nullptr;
    } else {
        ____parentFlowCoordinator->DismissFlowCoordinator(this, ViewController::AnimationDirection::Horizontal, nullptr, false);
    }
}