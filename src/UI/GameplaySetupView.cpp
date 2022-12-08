#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"
#include "Config.hpp"
#include "UI/GameplaySetupView.hpp"
#include "Images/MiscSettingsIcon.hpp"
#include "Images/RotationSettingsIcon.hpp"
#include "Images/PositionSettingsIcon.hpp"
#include "UI/ViewController.hpp"
#include "UI/FlowCoordinator.hpp"
#include "UI/MiscViewController.hpp"
#include "UI/PositionViewController.hpp"
#include "UI/RotationViewController.hpp"

#include "UnityEngine/RectOffset.hpp"
#include "HMUI/ViewController.hpp"
#include "HMUI/FlowCoordinator.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"

DEFINE_TYPE(InGameText, gameplaySetupView);

using namespace UnityEngine::UI;
using namespace UnityEngine;
using namespace QuestUI::BeatSaberUI;

void InGameText::gameplaySetupView::DidActivate(bool firstActivation) {
    if (!firstActivation) return;

    auto verticalLayoutGroup = CreateVerticalLayoutGroup(get_transform());
    verticalLayoutGroup->get_rectTransform()->set_anchoredPosition({0.0f, 0.0f});
    verticalLayoutGroup->set_padding(RectOffset::New_ctor(2, 2, 2, 2));
    // auto verticalLayoutGroupElement = verticalLayoutGroup->GetComponent<LayoutElement*>();
    // verticalLayoutGroupElement->set_preferredHeight(65.0f);
    // verticalLayoutGroupElement->set_preferredWidth(70.0f);
    auto verticalLayoutGroupFitter = verticalLayoutGroup->GetComponent<ContentSizeFitter*>();
    verticalLayoutGroupFitter->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
    verticalLayoutGroupFitter->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize);

    MiscImage = Base64ToSprite(MiscSettingsIcon);
    RotationImage = Base64ToSprite(RotationIcon);
    PositionImage = Base64ToSprite(PositionIcon);

    MiscButton = InGameText::gameplaySetupView::CreateViewControllerImage(verticalLayoutGroup->get_transform(), "Miscellaneous Settings", MiscImage, UnityEngine::Vector2(0.0f, 0.0f), UnityEngine::Vector2(10.0f, 10.0f), CreateViewController<InGameText::MiscViewController*>());
    PositionButton = InGameText::gameplaySetupView::CreateViewControllerImage(verticalLayoutGroup->get_transform(), "Position Settings", PositionImage, UnityEngine::Vector2(0.0f, 0.0f), UnityEngine::Vector2(10.0f, 10.0f), CreateViewController<InGameText::PositionViewController*>());
    RotationButton = InGameText::gameplaySetupView::CreateViewControllerImage(verticalLayoutGroup->get_transform(), "Rotation Settings", RotationImage, UnityEngine::Vector2(0.0f, 0.0f), UnityEngine::Vector2(10.0f, 10.0f), CreateViewController<InGameText::RotationViewController*>());
}

HMUI::ImageView* InGameText::gameplaySetupView::CreateViewControllerImage(
    UnityEngine::Transform* parent,
    std::string title,
    UnityEngine::Sprite* image,
    UnityEngine::Vector2 anchoredPosition,
    UnityEngine::Vector2 sizeDelta,
    HMUI::ViewController* viewController
) {
    using namespace HMUI;

    auto clickableImage = QuestUI::BeatSaberUI::CreateClickableImage(parent, image, anchoredPosition, sizeDelta,
        [this, title, viewController]() {
            flowCoordinator->SetTitle(title, ViewController::AnimationType::Out);
            flowCoordinator->ReplaceTopViewController(viewController, flowCoordinator, flowCoordinator, nullptr, ViewController::AnimationType::Out, ViewController::AnimationDirection::Horizontal);

            reinterpret_cast<InGameText::InGameTextFlowCoordinator*>(flowCoordinator)->currentViewController = viewController;
        }
    );

    return clickableImage;
}