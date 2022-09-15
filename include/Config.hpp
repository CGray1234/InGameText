#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig,

    CONFIG_VALUE(InGameText, std::string, "In-Game Text", "Hello World!");
    CONFIG_VALUE(InGameTextEnabled, bool, "Enable In-Game Text", false);

    CONFIG_VALUE(TextQolor, UnityEngine::Color, "Text Color", UnityEngine::Color(1, 1, 1, 1));

    //CONFIG_VALUE(TextPosition, UnityEngine::Vector3, "In-Game Text Position", UnityEngine::Vector3(0.0f, 0.0f, 0.0f));

    CONFIG_VALUE(PositionX, float, "Text Position X", 0);
    CONFIG_VALUE(PositionY, float, "Text Position Y", 0);
    CONFIG_VALUE(PositionZ, float, "Text Position Z", 0);

    //CONFIG_VALUE(TextRotation, UnityEngine::Vector3, "In-Game Text Rotation", UnityEngine::Vector3(0.0f, 0.0f, 0.0f));

    CONFIG_VALUE(RotationX, float, "Text Rotation X", 0);
    CONFIG_VALUE(RotationY, float, "Text Rotation Y", 0);
    CONFIG_VALUE(RotationZ, float, "Text Rotation Z", 0);

    CONFIG_VALUE(TextSize, float, "In-Game Text Size", 5);

    CONFIG_INIT_FUNCTION(

        CONFIG_INIT_VALUE(InGameText);
        CONFIG_INIT_VALUE(InGameTextEnabled);

        CONFIG_INIT_VALUE(TextQolor);

        //CONFIG_INIT_VALUE(TextPosition);
        CONFIG_INIT_VALUE(PositionX);
        CONFIG_INIT_VALUE(PositionY);
        CONFIG_INIT_VALUE(PositionZ);
        //CONFIG_INIT_VALUE(TextRotation);
        CONFIG_INIT_VALUE(RotationX);
        CONFIG_INIT_VALUE(RotationY);
        CONFIG_INIT_VALUE(RotationZ);
        
        CONFIG_INIT_VALUE(TextSize);
    )
)