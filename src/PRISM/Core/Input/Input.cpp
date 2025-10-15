#include <PRISM/Core/Input/Input.h>


Input *Input::Instance = nullptr;
Input::Input()
{
    Instance = this;
}