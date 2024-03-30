// From PinkCore: https://github.com/BSMGPink/PinkCore/blob/master/src/Utils/UIUtils.cpp
#include "Utils/UIUtils.hpp"

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

        spriteSwap->__cordl_internal_set__highlightStateSprite(highlighted);
        spriteSwap->__cordl_internal_set__pressedStateSprite(highlighted);

        spriteSwap->__cordl_internal_set__disabledStateSprite(normal);
        spriteSwap->__cordl_internal_set__normalStateSprite(normal);
	}
}