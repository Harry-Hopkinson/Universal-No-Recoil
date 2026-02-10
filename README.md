<div align="center">
    <h1>🎯 Universal No Recoil</h1>
    <a href="https://github.com/Harry-Hopkinson/Universal-No-Recoil/releases/latest">
        <img src="https://raw.githubusercontent.com/Harry-Hopkinson/Universal-No-Recoil/master/assets/app.png" alt="App Preview" width="750px">
    </a>
    <hr>
    <p>Support me developing this project by donating to me on Ko-Fi.</p>
    <a href="https://ko-fi.com/harryhopkinson">
        <img src="https://img.shields.io/badge/Ko--fi-F16061?style=for-the-badge&logo=ko-fi&logoColor=white" alt="Support the Project">
    </a>

| Release Build                                                                                                                                                                                                   | Early Access Build                                                                                                                                                                                                   |
| --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [![Release](https://img.shields.io/badge/Release%20Build-Download-blue?style=for-the-badge&logo=github)](https://github.com/Harry-Hopkinson/Universal-No-Recoil/releases/latest/download/UniversalNoRecoil.zip) | [![Development](https://img.shields.io/badge/Development%20Build-Download-yellow?style=for-the-badge&logo=github)](https://nightly.link/Harry-Hopkinson/Universal-No-Recoil/workflows/CI/main/UniversalNoRecoil.zip) |

A lightweight, efficient **no-recoil tool** for FPS Games. Designed for smooth performance and ease of use, whilst having deep customisability without all the bloat.

</div>

## Why I Made This

Most recoil control tools are packed with features you'll never use, slowing down your system. Tools like Logitech G Hub (now detectable) were too large and bloated just to handle simple recoil control. I built this tool to be **clean**, **compact**, and **laser-focused** on one thing: **removing recoil with minimal system impact**. No drivers, no background bloat—just raw utility.

## Why Use This Tool?

- **Lightning Fast** – Optimised for minimal CPU usage and instant response.
- **Powerful Configs** – Extensive configuration options. Fine-tune your recoil control to perfection (with a slider) on top of custom keybinds and theme customisation.
- **Open Source** – Fully transparent and customisable. Fork the code and develop it for your favourite game or add new features.
- **No Installation** – Just download, extract the zip folder and run the .exe file.
- **Controller Support** – Full support for controller recoil compensation, with adjustable sensitivity while firing. (Requires DS4Windows for Playstation controllers).

## How to Use

1. **Download** `UniversalNoRecoil.zip` from the [Github Releases](https://github.com/Harry-Hopkinson/Universal-No-Recoil/releases/latest) and extract the zip folder.
2. **Run the Program** (double-click `UniversalNoRecoil.exe`). No installation needed.
3. **Select your recoil compensation strength** by using the sliders.
4. **Use the Toggle Recoil Button** to enable/disable the recoil control.
5. **Use CapsLock** (default) to toggle on/off during gameplay. Enable by clicking on the Toggle Key button.
6. **Modify toggle keys, themes, controller support and more** in the Config.toml file.
7. **Enjoy improved accuracy and reduced recoil** in your FPS game!

## Support Development

Any form of donation is greatly appreciated and will help keep me motivated to keep working on this project and developing it further with new features and improvements.

[![Ko-Fi](https://img.shields.io/badge/Ko--fi-F16061?style=for-the-badge&logo=ko-fi&logoColor=white)](https://ko-fi.com/harryhopkinson)

## Config Explained

The app automatically creates a `Config.toml` file on first run. You can manually edit it to customise the experience.

### Example:

```ini
[General]
Enabled = true
VerticalRecoil = 3.00
HorizontalRecoil = 0.00

[Controller]
Enabled = false
Multiplier = 10

[Keys]
# Use https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
# And then convert the key code to decimal
# Toggle Key (e.g. 20 = CAPS LOCK)
ToggleKey = 20
ToggleKeyEnabled = false


[Theme]
BackgroundColour = RGB(30, 30, 30)
TextColour = RGB(230, 230, 230)
ButtonColour = RGB(70, 70, 70)
LineColour = RGB(180, 180, 180)
```

### Fields Explained

#### [General]

- **Enabled:** Enable or disable recoil adjustment.
- **VerticalRecoil:** The vertical recoil compensation value.
- **HorizontalRecoil:** The horizontal recoil compensation value (Positive goes right, negative goes left).

#### [Controller]

- **Enabled:** Enable or disable recoil adjustment with a controller.
- **Multiplier:** The multiplier for controller adjustment when firing.

#### [Keys]

- **ToggleKey:** The key code for toggling recoil adjustment.
- **ToggleKeyEnabled:** Enable or disable recoil adjustment with a toggle key.


#### [Theme]

- **BackgroundColour:** RGB values for the background colour of the app.
- **TextColour:** RGB values for the text colour of the app.
- **ButtonColour:** RGB values for the button colour of the app.
- **LineColour:** RGB values for the line colour of the app.

## Disclaimer

**This tool is for educational purposes only.** Use it at your own risk. I do not advocate cheating.

Windows Defender may flag it as a false positive due to the nature of input simulation. You can verify the safety by checking the file on VirusTotal. Always download from the official GitHub repository or the website to ensure you have the real version.

---
