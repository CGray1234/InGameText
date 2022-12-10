// From PinkCore: https://github.com/BSMGPink/PinkCore/blob/master/include/Utils/UIUtils.hpp

#pragma once

#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/Sprite.hpp"
#include <string>

namespace UIUtils
{
	void SwapButtonSprites(UnityEngine::UI::Button* button, UnityEngine::Sprite* normal, UnityEngine::Sprite* highlighted);
}