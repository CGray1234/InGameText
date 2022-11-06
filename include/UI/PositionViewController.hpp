#pragma once

#include "main.hpp"

#include "custom-types/shared/register.hpp"
#include "custom-types/shared/macros.hpp"
#include "HMUI/ViewController.hpp"

#define GET_FIND_METHOD(mPtr) il2cpp_utils::il2cpp_type_check::MetadataGetter<mPtr>::get()

DECLARE_CLASS_CODEGEN(InGameText, PositionViewController, HMUI::ViewController,
    DECLARE_OVERRIDE_METHOD(void, DidActivate, GET_FIND_METHOD(&ViewController::DidActivate), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
)