#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

#include "UnityEngine/Sprite.hpp"
#include "HMUI/ImageView.hpp"

#include "HMUI/FlowCoordinator.hpp"
#include "HMUI/ViewController.hpp"

using namespace UnityEngine;

DECLARE_CLASS_CODEGEN(InGameText, gameplaySetupView, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_FIELD(HMUI::ViewController*, viewController);
    DECLARE_INSTANCE_FIELD(HMUI::FlowCoordinator*, flowCoordinator);

    //Misc
    DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, MiscImage);
    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, MiscButton);

    //Pos
    DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, PositionImage);
    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, PositionButton);

    //Rot
    DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, RotationImage);
    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, RotationButton);



    DECLARE_INSTANCE_METHOD(void, DidActivate, bool firstActivation);

public:
    
    HMUI::ImageView* CreateViewControllerImage(UnityEngine::Transform* parent, std::string title, UnityEngine::Sprite* image, UnityEngine::Vector2 anchoredPosition, UnityEngine::Vector2 sizeDelta, HMUI::ViewController* viewController);
);