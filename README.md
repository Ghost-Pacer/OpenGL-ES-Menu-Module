# UI Module v1.5
## Ghost Pacer August 2021

### UIKit

*Version 1.5* of the Ghost Pacer UIKit. The UIKit is a framework for creating dynamic and self-updating image+text based UIs. It's designed to be used alongside a [UILayer](https://github.com/Ghost-Pacer/PowerVR-SDK/tree/master/Projects/UILayer) framework that provides interfacing functionality between the UIKit modules and a `PVRShell` framework. The UIModule depends on functionality provided by the [PowerVR SDK 3.5](https://github.com/Ghost-Pacer/PowerVR-SDK), and it must be included and built inside an SDK application. All UIKit classes use OpenGL ES 2.0 to display graphics.

### Implementation

The UIKit is implemented across a series of c++ UI classes. Version 1.5 includes `UIImage`, `UICompositeView`, `UITextBlock`, `UIButton`, `UIProgressBar`, `UIBrightnessMenu`, `UISpeedMenu`, and `UIBasicHUD`. All of these classes extend the `UIElement` interfacing structure to provide uniform implementation structure.
The `UIMessage` and `UIPrinter` classes enable render-time updating and text-drawing respectively.

#### UIElement

The UIElement abstract/header class provides defines the functionality that every rendering UIKit element must implement. By defining this set of common functionality, we unlock a desirable level of implementation simplicity. Many of the UIElement implementations in the UIKit feature nested arrays of other UIElements. By using such a structure, texture loading, vertex construction, and rendering take place in a single loop pass. The functions themselves are below:

```c++
virtual bool LoadTextures(CPVRTString* const pErrorStr) = 0;
virtual void BuildVertices() = 0;
virtual bool Render(GLuint uiMVPMatrixLoc, UIPrinter* printer) = 0;
virtual void Update(UIMessage updateMessage) = 0;
virtual void Hide() = 0;
virtual void Show() = 0;
virtual void Delete() = 0;
```
* In **LoadTextures**, UIElement implementing classes load their .pvr textures into memory.
* In **BuildVertices**, UIElement implementing classes construct their vertex buffers and load them into memory.
* In **Render**, UIElement implementing classes draw themselves.
* In **Update**, UIElement implementing classes update themselves based on the information contained in a `UIMessage`.
* In **Hide**, UIElement implementing classes hide themselves.
* In **Show**, UIElement implementing classes show themselves.
* In **Delete**, UIElement implementing classes free all allocated memory within them.

#### UIPrinter

The `UIPrinter` is the UIKit class used to display text. It serves as a wrapper for multiple PVR `CPVRTPrint3D` classes that allows for font and sizing customization in text displayed with OpenGL ES 2.0. To store and enumerate fonts and text, the UIPrinter class defines the `UIFont` enum, and the `UITextSpec` data structure:

```c++
enum UIFont {
	UIFBold,
	UIFMedium
	UIFRegular,
	UIFThin,
	UIFLight
};

struct UITextSpec {
	char* text;
	GLuint color;
	float xRel, yRel, scale;
	UITextType updateKey;
	UIFont font;
};
```
* **UIFont** enumerates the fonts contained within the UIModules `Fonts` folder
* A **UITextSpec** stores all the information needed to display text using UIPrinter

Additionally, UIPrinter defines and implements the following functions:

```c++
UIPrinter();
bool LoadFonts(int pvrShellWidth, int pvrShellHeight, bool isRotated);
void Print(float x, float y, float scale, GLuint color, UIFont font, char* text);
void Measure(float* width, float* height, float scale, UIFont font, char* text);
bool Rotated();
void Delete();
```
* **UIPrinter** is a generic constructor for a UIPrinter
* **LoadFonts** loads the fonts from the `Fonts` folder into accessibly memory
* **Print** prints text to the screen
* **Measure** measures the width and height of text object
* **Rotated** returns whether or not the text is rotated
* **Delete** Frees all memory allocated within the printer

#### UIMessage

The UIMessage class defines a data structure for storing frame data from the App Layer. Since the UIModule may not have access to the [Protocols](https://github.com/Ghost-Pacer/protocols) library, UIKit elements need a way to access protobuf-encoded data without having access to the protobufs themselves. The UIMessage provides functionality for loading protobuf information into memory and accessing it. It defines a series of enumerated data keys and stores maps from those keys to the data they correspond to. The maps are organized by type. The UIMessages is intended to be initialized and moved through the [UILayer](https://github.com/Ghost-Pacer/PowerVR-SDK/tree/master/Projects/UILayer) framework before it's passed to each `UIElement` through their `Update` functions. It defines and implements the following functions:

```c++
void Write(UIFloat key, float value);
void Write(UITextType key, char* value);
void Write(UIBool key, bool value);
void Write(UIState state);
void Write(UIAction action);
void Write(UIWorkoutStage stage);
void SetTotalRacers(int total);
float Read(UIFloat key);
char* Read(UITextType key);
bool Read(UIBool key);
UIState ReadState();
UIAction ReadAction();
UIWorkoutStage ReadWorkoutStage();
int GetTotalRacers();
UIMessage Delegate(UIFloat key);
UIMessage Delegate(UITextType key);
UIMessage Delegate(UIBool key);
```
* The **Write** functions write data from the provided key to the corresponding map
* The **Read** functions read data from the requested map/key
* The **Delegate** functions duplicate the current UIMessage but remove all data except for what corresponds to one key in the data maps.
* **SetTotalRacers** sets the total number of runners in a run
* **GetTotalRacers** returns the total number of runners in a run.

#### UIImage

`UIImage` is the most fundamental UIElement class. It displays a rectangular textured gl quad with dynamic positioning and sizing. To draw a UIImage, construct one with the appropriate parameters and treat it as a generic UIElement, calling its `LoadTextures`, `BuildVertices` and `Render` functions in order. Constructing a UIImage requires a .pvr texture filepath, (x, y) position, and the image's dimensions:

```c++
UIImage(const char* textureName, float x, float y, float width, float height);
```

#### UICompositeView

`UICompositeView` is a framework for containing multiple UIElements and displaying text alongside them. UICompositeView is a UIElement class, meaning that it implements the UIElement interface for asset loading and rendering. It stores and modifies text using the `UITextSpec` struct defined in `UIPrinter`. In addition to implementing the UIElement superstructure it has the following custom functionality:

```c++
UICompositeView(float x, float y);
UICompositeView(char* bgTex, float x, float y, float width, float height);
void AddElement(UIElement* newElement);
void AddImage(char* textureName, float xRel, float yRel, float width, float height);
void AddText(char* text, GLuint color, float xRel, float yRel, float scale, UITextType updateKey, UIFont font);
```

* The first constructor defines a default composite view with a default background texture at a specified position
* The seconds constructor defines a custom composite view with a custom background and size at a specified position
* **AddElement** adds a `UIElement` to the view
* **AddImage** creates and adds a custom image to the view
* **AddText** creates and adds custom text to the view

#### UITextBlock

`UITextBlock` defines and implements a piece of custom text with a background UIImage. In addition to implementing the standard UIElement functionality, it has the following custom functions:

```c++
UITextBlock(char* text, float x, float y, GLuint color, UITextType m_updateKey);
UITextBlock(char* text, char* textSecondary, UIFont fontMain, UIFont fontSec,
        float x, float y, GLuint color, UITextType m_updateKey);
UITextBlock(char* bg, char* text, char* textSecondary, UIFont fontMain, UIFont fontSec,
        float x, float y, float width, float height, GLuint color, UITextType updateKey);
void AddSecondaryText(char* textSecondary, UIFont fontSecondary);
```

* The first creates the default updating text block with fixed sizing and background
* The second creates a text block with a custom piece of secondary text with a custom font. The rest of the text block is still custom
* The third creates a fully custom text block
* **AddSecondaryText** Adds the secondary text to the text block

#### UIButton

`UIButton` defines a piece of text with a UIImage background that can toggle between "on" and "off" states depending on whether the button is selected. It implements the UIElement functionality and defines the following custom functions:

```c++
UIButton(char* text, float x, float y, GLuint activeColor, GLuint inactiveColor, UIBool updateKey);
UIButton(char* activeBG, char* inactiveBG, char* text, float x, float y, float width, float height, 
    float insetX, float insetY, float textScale, GLuint activeColor, GLuint inactiveColor, UIFont font);
void ToggleActive();
```

* The first defines the default UIButton with custom text coloration for active and inactive states
* The second defines a custom UIButton with customized "on" and "off" states
* The **ToggleActive** function toggles whether the button displays its active or inactive state

#### UIProgressBar

A UIProgress bar is made of 2 scaling UIImages that emulate the functionality of a conventional progress bar. It uses the enum `PBType` to regulate appearance. It implements the UIElement functionality and defines the following custom functions:

```c++
UIProgressBar(float x, float y, float initialCompletion);
UIProgressBar(PBType type, float x, float y, float initialCompletion);
UIProgressBar(float x, float y, float width, float height, float insetX, float insetY, float initialCompletion);
void SetCompletion(float newCompletion);
float GetCompletion();
```

* The first constructor defines a default progress bar with some initial completion
* The second allows for custom PBTypes
* The third creates a custom sized progress bar
* **SetCompletion** sets the progress bar's completion (take a float between 0 and 1)
* **GetCompletion** returns the progres bar's completion

#### UIBrightnessMenu

The UIBrightnessMenu is a full-screened UIElement view that displays a Brightness icon, a progress bar detailing the current brightness, and a menu interface for changing the brightness via UIMessage updates. UIBrightnessMenu does not implement any custom functions other than a default constructor and the required UIElement interface functions.

#### UISpeedMenu

The UISpeedMenu is a full-screened UIElement view that displays an interface for modulating avatar speed. UISpeedMenu does not implement any custom functions other than a default constructor and the required UIElement interface functions.

#### UIBasicHUD

The UIBasicHUD is a UIElement that displays two UITextBlock hud elements at the top of the display. UIBasicHUD does not implement any custom functions other than a default constructor and the required UIElement interface functions.

### Assumptions

Assumes that assets are in "assets" folder in same root directory as the ui-module:

    [root]
        [assets]
        [UI Module]

### Files

* `UIBasicHUD.cpp` - Implements UIBasicHUD
* `UIBasicHUD.h` - Header for UIBasicHUD
* `UIBrightnessMenu.cpp` - Implements UIBrightnessMenu
* `UIBrightnessMenu.h` - Header for UIBrightnessMenu
* `UIButton.cpp` - Implements UIButton
* `UIButton.h` - Header for UIButton
* `UICompositeView.cpp` - Implements UICompositeView
* `UICompositeView.h` - Header for UICompositeView
* `UIElement.h` - Defines UIElement
* `UIImage.cpp` - Implements UIImage
* `UIImage.h` - Header for UIImage
* `UIMessage.cpp` - Implements UIMessage
* `UIMessage.h` - Header for UIMessage
* `UIPrinter.cpp` - Implements UIPrinter
* `UIPrinter.h` - Header for UIPrinter
* `UIProgressBar.cpp` - Implements UIProgressBar
* `UIProgressBar.h` - Header for UIProgressBar
* `UISpeedMenu.cpp` - Implements UISpeedMenu
* `UISpeedMenu.h` - Header for UISpeedMenu
* `UITextBlock.cpp` - Implements UITextBlock
* `UITextBlock.h` - Header for UITextBlock

### Compilation

To compile, add each required UIKit .o file to PVR Makefile's dependency list and run `make`

### Testing

Use [UILayer](https://github.com/Ghost-Pacer/PowerVR-SDK/tree/master/Projects/UILayer) to test.

## Legacy Modules

Version 1.0 of the Ghost Pacer used a text-only UI created by Ronith K. These legacy modules are still used in parts of the 1.5, and they are included in the final product.

### Overview
Print2D and MenuController are dependent on OGLESTools2.h, which is provided by the PowerVR SDK.

These files were designed to work specifically with OpenGL ES 2.

### Print2D
This class adds extra functionality to the CPVRTPrint3D class provided by PowerVR. CPVRTPrint3D can render text where the top left coordinate of its bounding box is given by the user. Print2D allows the rendering text at a given center coordinate of its bounding box. This makes it trivial to center text on a screen.

Additionally, Print2D can render a list of text, each with their own scale and color. The text will appear spaced evenly and will be centered horizontally within its bounding box.

### MenuView
MenuView interface allows easily displaying a menu and visually navigating up and down to select different options.

### BannerView
Used to display single/multi-line text centered or pinned-to-top of screen. You can customize the text size, but if the provided size is too large the banner will automatically scale to fit the screen width.

### ButtonLegendView
Displays Ghost Pacer Glasses button glyphs in the bottom right corner of the screen. Loads glyphs from a custom version of Montserrat Bold font.

### CustomMontserratBold
A modified version of Montserrat Bold font that replaces certain characters with Ghost Pacer icons.
Modified chracters:
* ~ → Up Button Glyph
* ` → Down Button Glyph
* \ → Ok Button Glyph
