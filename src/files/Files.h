#pragma once

#include "../recoil/Structs.h"

namespace Files
{

    /**
     * @brief Writes the editable variables to the Config.toml file
     */
    void SaveConfig();

    /**
     * @brief Loads the editable variables from the Config.toml file
     */
    void LoadConfig();

} // namespace Files
