#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

#include "GlobalNamespace/SimpleLevelStarter.hpp"
#include "GlobalNamespace/BeatmapLevelSO.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"
#include "GlobalNamespace/MenuTransitionsHelper.hpp"

#include "UnityEngine/Resources.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"

#include "UI/ViewController.hpp"
#include "UI/RotationViewController.hpp"
#include "UI/PositionViewController.hpp"
#include "UI/MiscViewController.hpp"

#include "Config.hpp"

#include "main.hpp"

DEFINE_TYPE(InGameText, MainViewController);
DEFINE_TYPE(InGameText, RotationViewController);
DEFINE_TYPE(InGameText, PositionViewController);
DEFINE_TYPE(InGameText, MiscViewController);

using namespace QuestUI::BeatSaberUI;
using namespace UnityEngine;
using namespace InGameText;

UnityEngine::UI::Button *PositionViewButton;
UnityEngine::UI::Button *RotationViewButton;
UnityEngine::UI::Button *MiscViewButton;

void TextViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    using namespace UnityEngine::UI;
    if (firstActivation) {
        UnityEngine::GameObject *VerticalLayoutGroup = CreateVerticalLayoutGroup(get_transform());

        UnityEngine::GameObject *scrollView = CreateScrollView(get_transform());
        LayoutElement* scrollViewElement = scrollView->GetComponentInParent<LayoutElement*>();
        scrollViewElement->set_preferredWidth(120);
        scrollViewElement->set_preferredHeight(65);

        CreateToggle(scrollView->get_transform(), "Enabled", getModConfig().InGameTextEnabled.GetValue(),
            [=](bool value) {
                getModConfig().InGameTextEnabled.SetValue(value);

                PositionViewButton->set_interactable(value);
                RotationViewButton->set_interactable(value);
                MiscViewButton->set_interactable(value);
            }
        )

        CreateViewControllerButton(scrollView->get_transform(), "Text Positioning", "Customize where you want your text to be!", CreateViewController<InGameText::PositionViewController>());
        CreateViewControllerButton(scrollView->get_transform(), "Text Rotation", "Customize the angle/rotation of your text!", CreateViewController<InGameText::RotationViewController>());
        CreateViewControllerButton(scrollView->get_transform(), "Miscellaneous Text Properties", "Customize miscellaneous text properties such as size, color, and what you want it to say!", CreateViewController<InGameText::MiscViewController>());
    }
}

UnityEngine::UI::Button* InGameText::UI::CreateViewControllerButton(
    UnityEngine::Transform* parent, 
    std::string title, 
    std::string description, 
    HMUI::ViewController* viewController
) {
    using namespace HMUI;
    using namespace UnityEngine;
    using namespace UnityEngine::UI;

    HorizontalLayoutGroup* horizontalLayoutGroup = CreateHorizontalLayoutGroup(parent);
}