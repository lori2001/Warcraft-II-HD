#pragma once

// --- SFML ---------------------
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

// --- System Files -------------
#include "NGin/System/Console.h"
#include "NGin/System/Resources.h"
#include "NGin/System/Timer.h"

// --- Utilities ----------------
#include "NGin/Utilities/Align.h"
#include "NGin/Utilities/Bind.h"
#include "NGin/Utilities/Vectors.h"

// --- Animation ----------------
#include "NGin/Animation/AnimationFile.h" // includes Timer.h

// --- Audio --------------------
#include "NGin/Audio/Audio.h"

// -- File Reading/Writing ------
#include "NGin/Files/Json.h" // nlohmann vendor -> class ngin::Json
#include "NGin/Files/FileReader.h"

// --- User Interface -----------
#include "NGin/UserInterface/Cursor.h"
#include "NGin/UserInterface/Button.h"
#include "NGin/UserInterface/Dropdown.h"
#include "NGin/UserInterface/InputText.h"
#include "NGin/UserInterface/ScrollBox.h"
#include "NGin/UserInterface/Slider.h" // includes Button.h
#include "NGin/UserInterface/Switcher.h" // includes Button.h

// --- RealTimeStrategy -------------
#include "NGin/RTS/Pathfinding.h"
// ----------------------------------

// --- Level Types --------------------
#include "NGin/Levels/Level.h"
#include "NGin/Levels/MainLevel.h" 

// --- Entry Point(int main()) --------
#include "NGin/EntryPoint.h"
// ------------------------------------
