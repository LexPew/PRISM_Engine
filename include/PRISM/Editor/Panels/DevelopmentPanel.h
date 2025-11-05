#pragma once

namespace PRISM::Editor
{
    /**
     * @class DevelopmentPanel
     * @brief Class for managing development panels that provide information about the engine's status and capabilities.
     * 
     * The Development Panel class provides a set of methods to manage UI elements related to engine development, including 
     * displaying and toggling different development themes such as light or dark themes.
     */
    class DevelopmentPanel
    {

    public:
        /**
         * @brief Displays the development panel in its current state.
         *
         * This function renders the UI elements related to engine development, providing information about 
         * the status and capabilities of the PRISM engine.
         */
        static void Display();

        /**
         * @brief Switches to a light theme for the development panel.
         *
         * This function changes the appearance of the UI elements in the development panel to provide a more 
         * comfortable and readable interface, even under a light color scheme.
         */
        static void LightTheme();

        /**
         * @brief Switches to a dark theme for the development panel.
         *
         * This function changes the appearance of the UI elements in the development panel to provide 
         * an interface with reduced strain under a dark color scheme, often used in combination with other elements of the user interface.
         */
        static void DarkTheme();

        /**
         * @brief Toggles the display state of the development panel.
         *
         * This function changes the visibility of the UI elements related to engine development by either 
         * showing or hiding them, depending on their current state.
         */
        static void ToggleDisplay() { toggleDisplay = !toggleDisplay; }
    
    private:
        /**
         * @brief The current display state of the development panel.
         *
         * This variable keeps track of whether or not the UI elements related to engine development are currently displayed.
         */
        static bool toggleDisplay;

    };
}
