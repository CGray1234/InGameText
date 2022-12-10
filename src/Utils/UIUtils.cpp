// From PinkCore: https://github.com/BSMGPink/PinkCore/blob/master/src/Utils/UIUtils.cpp
#include "Utils/UIUtils.hpp"

#include "questui/shared/BeatSaberUI.hpp"

#include "UnityEngine/Texture.hpp"
#include "UnityEngine/Texture2D.hpp"
#include "UnityEngine/TextureWrapMode.hpp"
#include "UnityEngine/Sprite.hpp"
#include "HMUI/ButtonSpriteSwap.hpp"
#include "HMUI/ImageView.hpp"
#include "UnityEngine/UI/Button.hpp"
#include <string>

using namespace HMUI;
using namespace UnityEngine;

namespace UIUtils
{

    void SwapButtonSprites(UnityEngine::UI::Button* button, UnityEngine::Sprite* normal, UnityEngine::Sprite* highlighted)
	{
		normal->get_texture()->set_wrapMode(TextureWrapMode::Clamp);
        highlighted->get_texture()->set_wrapMode(TextureWrapMode::Clamp);

        ButtonSpriteSwap* spriteSwap = button->GetComponent<ButtonSpriteSwap*>();

        spriteSwap->highlightStateSprite = highlighted;
        spriteSwap->pressedStateSprite = highlighted;

        spriteSwap->disabledStateSprite = normal;
        spriteSwap->normalStateSprite = normal;
	}
}