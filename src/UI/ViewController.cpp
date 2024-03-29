#include "UI/ViewController.hpp"
#include "UI/FlowCoordinator.hpp"
#include "UI/MiscViewController.hpp"
#include "UI/PositionViewController.hpp"
#include "UI/RotationViewController.hpp"
#include "UnityEngine/Resources.hpp"
#include "bsml/shared/BSML/Components/Backgroundable.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
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

DEFINE_TYPE(InGameText, InGameTextViewController);

void StartTestLevel(InGameText::InGameTextViewController* self) {
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

        GameObject* scrollView = CreateScrollView(verticalLayoutGroup->get_transform());
        LayoutElement* scrollViewLayoutElement = scrollView->GetComponentInParent<LayoutElement*>();
        scrollViewLayoutElement->set_preferredWidth(120);
        scrollViewLayoutElement->set_preferredHeight(65);

        auto enableButton = CreateToggle(scrollView->get_transform(), "Enable InGameText", getModConfig().InGameTextEnabled.GetValue(),
            [](bool value) {
                getModConfig().InGameTextEnabled.SetValue(value);
            }
        );

        positionButton = CreateViewControllerButton(scrollView->get_transform(), "Position Settings", "Change the position of your text!", CreateViewController<InGameText::PositionViewController*>());
        rotationButton = CreateViewControllerButton(scrollView->get_transform(), "Rotation Settings", "Change the angle/rotation of your text!", CreateViewController<InGameText::RotationViewController*>());
        miscButton = CreateViewControllerButton(scrollView->get_transform(), "Miscellaneous Settings", "Change other text settings like color, size, and what you want it to say!", CreateViewController<InGameText::MiscViewController*>());

        auto testButton = CreateUIButton(scrollView->get_transform(), "Test Configuration", "PlayButton",
            [&]() {
                StartTestLevel(this);
            }
        );

        HorizontalLayoutGroup* horizontalLayoutGroup = CreateHorizontalLayoutGroup(verticalLayoutGroup->get_transform());
        horizontalLayoutGroup->set_padding(RectOffset::New_ctor(8, 0, -5, 5));

        CreateText(horizontalLayoutGroup->get_transform(), "Welcome to the new InGameText UI!", Vector2::get_zero(), Vector2(4, 4));
        Button* githubButton = CreateUIButton(horizontalLayoutGroup->get_transform(), "Open GitHub Page",
            []() {
                Application::OpenURL("https://github.com/CGray1234/InGameText");
            }
        );
        SetButtonTextSize(githubButton, 3);
    }
}

UnityEngine::UI::Button* InGameText::InGameTextViewController::CreateViewControllerButton(
    UnityEngine::Transform* parent,
    std::string title,
    std::string description,
    HMUI::ViewController* viewController
) {
    using namespace HMUI;
    using namespace UnityEngine;
    using namespace UnityEngine::UI;

    HorizontalLayoutGroup* horizontalLayoutGroup = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(parent);
    BSML::Backgroundable* horizontalLayoutGroupBackgroundable = horizontalLayoutGroup->GetComponent<QuestUI::Backgroundable*>();
    horizontalLayoutGroupBackgroundable->ApplyBackground("panel-top");
    horizontalLayoutGroupBackgroundable->GetComponentInChildren<ImageView*>()->skew = .18f;
    LayoutElement* horizontalLayoutGroupLayoutElement = horizontalLayoutGroup->GetComponent<LayoutElement*>();
    horizontalLayoutGroupLayoutElement->set_preferredWidth(100);
    horizontalLayoutGroupLayoutElement->set_preferredHeight(15);

    VerticalLayoutGroup* verticalLayoutGroup = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(horizontalLayoutGroup->get_transform());
    verticalLayoutGroup->set_spacing(-5);
    verticalLayoutGroup->set_padding(RectOffset::New_ctor(0, 0, -1, 0));
    LayoutElement* verticalLayoutGroupLayoutElement = verticalLayoutGroup->GetComponent<LayoutElement*>();
    verticalLayoutGroupLayoutElement->set_preferredWidth(65);

    BSML::Lite::CreateText(verticalLayoutGroup->get_transform(), description, true, Vector2::get_zero(), Vector2(3, 3))->set_alignment(TMPro::TextAlignmentOptions::Center);

    Button* openButton = BSML::Lite::CreateUIButton(verticalLayoutGroup->get_transform(), title, "PlayButton",
        [this, title, viewController]() {
            flowCoordinator->SetTitle(title, ViewController::AnimationType::In);
            flowCoordinator->ReplaceTopViewController(viewController, flowCoordinator, flowCoordinator, nullptr, ViewController::AnimationType::In, ViewController::AnimationDirection::Horizontal);

            reinterpret_cast<InGameText::InGameTextFlowCoordinator*>(flowCoordinator)->currentViewController = viewController;
        }
    );
    BSML::Lite::SetButtonTextSize(openButton, 5);

    Object::Destroy(openButton->get_transform()->Find("Content")->GetComponent<LayoutElement*>());

    ContentSizeFitter* contentSizeFitter = openButton->get_gameObject()->AddComponent<ContentSizeFitter*>();
    contentSizeFitter->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);

    return openButton;
}