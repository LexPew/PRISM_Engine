#pragma once

namespace PRISM::Editor
{
    class DevelopmentPanel
    {


    public:

        static void Display();
        static void LightTheme();
        static void DarkTheme();

        static void ToggleDisplay() { toggleDisplay = !toggleDisplay; }
    private:
        static bool toggleDisplay;

    };
}
