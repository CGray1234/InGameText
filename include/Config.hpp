#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig,

    CONFIG_VALUE(InGameText, std::string, "In-Game Text", "Hello World!");
    CONFIG_VALUE(InGameTextEnabled, bool, "Enable In-Game Text", false);

    CONFIG_VALUE(TextPosition, UnityEngine::Vector3, "In-Game Text Position", UnityEngine::Vector3(0.0f, 2.0f, 3.0f));
    CONFIG_VALUE(TextRotation, UnityEngine::Vector3, "In-Game Text Rotation", UnityEngine::Vector3(-45.0f, 0.0f, 0.0f));
    CONFIG_VALUE(TextSize, UnityEngine::Vector2, "In-Game Text Size", UnityEngine::Vector2(45.0f, 25.0f));

    CONFIG_INIT_FUNCTION(

        CONFIG_INIT_VALUE(InGameText);
        CONFIG_INIT_VALUE(InGameTextEnabled);

        CONFIG_INIT_VALUE(TextPosition);
        CONFIG_INIT_VALUE(TextRotation);
        CONFIG_INIT_VALUE(TextSize);
    )
)