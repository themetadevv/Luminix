#pragma once

enum WindowFlags
{
	WindowFlags_None = 0,
	NoTitleBar = 1 << 0,   // Disable title-bar
	NoResize = 1 << 1,   // Disable user resizing with the lower-right grip
	NoMove = 1 << 2,   // Disable user moving the window
	NoScrollbar = 1 << 3,   // Disable scrollbars (window can still scroll with mouse or programmatically)
	NoScrollWithMouse = 1 << 4,   // Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
	NoCollapse = 1 << 5,   // Disable user collapsing window by double-clicking on it. Also referred to as Window Menu Button (e.g. within a docking node).
	AlwaysAutoResize = 1 << 6,   // Resize every window to its content every frame
	NoBackground = 1 << 7,   // Disable drawing background color (WindowBg, etc.) and outside border. Similar as using SetNextWindowBgAlpha(0.0f).
	NoSavedSettings = 1 << 8,   // Never load/save settings in .ini file
	NoMouseInputs = 1 << 9,   // Disable catching mouse, hovering test with pass through.
	MenuBar = 1 << 10,  // Has a menu-bar
	HorizontalScrollbar = 1 << 11,  // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
	NoFocusOnAppearing = 1 << 12,  // Disable taking focus when transitioning from hidden to visible state
	NoBringToFrontOnFocus = 1 << 13,  // Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)
	AlwaysVerticalScrollbar = 1 << 14,  // Always show vertical scrollbar (even if ContentSize.y < Size.y)
	AlwaysHorizontalScrollbar = 1 << 15,  // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
	NoNavInputs = 1 << 16,  // No keyboard/gamepad navigation within the window
	NoNavFocus = 1 << 17,  // No focusing toward this window with keyboard/gamepad navigation (e.g. skipped by Ctrl+Tab)
	UnsavedDocument = 1 << 18,  // Display a dot next to the title. When used in a tab/docking context, tab is selected when clicking the X + closure is not assumed (will wait for user to stop submitting the tab). Otherwise closure is assumed when pressing the X, so if you keep submitting the tab may reappear at end of tab bar.
	NoNav = NoNavInputs | NoNavFocus,
	NoDecoration = NoTitleBar | NoResize | NoScrollbar | NoCollapse,
	NoInputs = NoMouseInputs | NoNavInputs | NoNavFocus,
};

enum InputTextFlags
{
	// Basic filters (also see ImGuiInputTextFlags_CallbackCharFilter)
	InputTextFlags_None = 0,
	CharsDecimal = 1 << 0,   // Allow 0123456789.+-*/
	CharsHexadecimal = 1 << 1,   // Allow 0123456789ABCDEFabcdef
	CharsScientific = 1 << 2,   // Allow 0123456789.+-*/eE (Scientific notation input)
	CharsUppercase = 1 << 3,   // Turn a..z into A..Z
	CharsNoBlank = 1 << 4,   // Filter out spaces, tabs

	// Inputs
	AllowTabInput = 1 << 5,   // Pressing TAB input a '\t' character into the text field
	EnterReturnsTrue = 1 << 6,   // Return 'true' when Enter is pressed (as opposed to every time the value was modified). Consider using IsItemDeactivatedAfterEdit() instead!
	EscapeClearsAll = 1 << 7,   // Escape key clears content if not empty, and deactivate otherwise (contrast to default behavior of Escape to revert)
	CtrlEnterForNewLine = 1 << 8,   // In multi-line mode, validate with Enter, add new line with Ctrl+Enter (default is opposite: validate with Ctrl+Enter, add line with Enter).

	// Other options
	ReadOnly = 1 << 9,   // Read-only mode
	Password = 1 << 10,  // Password mode, display all characters as '*', disable copy
	AlwaysOverwrite = 1 << 11,  // Overwrite mode
	AutoSelectAll = 1 << 12,  // Select entire text when first taking mouse focus
	ParseEmptyRefVal = 1 << 13,  // InputFloat(), InputInt(), InputScalar() etc. only: parse empty string as zero value.
	DisplayEmptyRefVal = 1 << 14,  // InputFloat(), InputInt(), InputScalar() etc. only: when value is zero, do not display it. Generally used with ImGuiInputTextFlags_ParseEmptyRefVal.
	NoHorizontalScroll = 1 << 15,  // Disable following the cursor horizontally
	NoUndoRedo = 1 << 16,  // Disable undo/redo. Note that input text owns the text data while active, if you want to provide your own undo/redo stack you need e.g. to call ClearActiveID().

	// Elide display / Alignment
	ElideLeft = 1 << 17,  // When text doesn't fit, elide left side to ensure right side stays visible. Useful for path/filenames. Single-line only!

	// Callback features
	CallbackCompletion = 1 << 18,  // Callback on pressing TAB (for completion handling)
	CallbackHistory = 1 << 19,  // Callback on pressing Up/Down arrows (for history handling)
	CallbackAlways = 1 << 20,  // Callback on each iteration. User code may query cursor position, modify text buffer.
	CallbackCharFilter = 1 << 21,  // Callback on character inputs to replace or discard them. Modify 'EventChar' to replace or discard, or return 1 in callback to discard.
	CallbackResize = 1 << 22,  // Callback on buffer capacity changes request (beyond 'buf_size' parameter value), allowing the string to grow. Notify when the string wants to be resized (for string types which hold a cache of their Size). You will be provided a new BufSize in the callback and NEED to honor it. (see misc/cpp/imgui_stdlib.h for an example of using this)
	CallbackEdit = 1 << 23,  // Callback on any edit. Note that InputText() already returns true on edit + you can always use IsItemEdited(). The callback is useful to manipulate the underlying buffer while focus is active.

	// Multi-line Word-Wrapping [BETA]
	// - Not well tested yet. Please report any incorrect cursor movement, selection behavior etc. bug to https://github.com/ocornut/imgui/issues/3237.
	// - Wrapping style is not ideal. Wrapping of long words/sections (e.g. words larger than total available width) may be particularly unpleasing.
	// - Wrapping width needs to always account for the possibility of a vertical scrollbar.
	// - It is much slower than regular text fields.
	//   Ballpark estimate of cost on my 2019 desktop PC: for a 100 KB text buffer: +~0.3 ms (Optimized) / +~1.0 ms (Debug build).
	//   The CPU cost is very roughly proportional to text length, so a 10 KB buffer should cost about ten times less.
	WordWrap = 1 << 24,  // InputTextMultiline(): word-wrap lines that are too long.
};

enum SliderFlags
{
	SliderFlags_None = 0,
	Logarithmic = 1 << 5,       // Make the widget logarithmic (linear otherwise). Consider using ImGuiSliderFlags_NoRoundToFormat with this if using a format-string with small amount of digits.
	NoRoundToFormat = 1 << 6,       // Disable rounding underlying value to match precision of the display format string (e.g. %.3f values are rounded to those 3 digits).
	NoInput = 1 << 7,       // Disable Ctrl+Click or Enter key allowing to input text directly into the widget.
	WrapAround = 1 << 8,       // Enable wrapping around from max to min and from min to max. Only supported by DragXXX() functions for now.
	ClampOnInput = 1 << 9,       // Clamp value to min/max bounds when input manually with Ctrl+Click. By default Ctrl+Click allows going out of bounds.
	ClampZeroRange = 1 << 10,      // Clamp even if min==max==0.0f. Otherwise due to legacy reason DragXXX functions don't clamp with those values. When your clamping limits are dynamic you almost always want to use it.
	NoSpeedTweaks = 1 << 11,      // Disable keyboard modifiers altering tweak speed. Useful if you want to alter tweak speed yourself based on your own logic.
	ColorMarkers = 1 << 12,      // DragScalarN(), SliderScalarN(): Draw R/G/B/A color markers on each component.
	AlwaysClamp = ClampOnInput | ClampZeroRange,
	InvalidMask_ = 0x7000000F,   // [Internal] We treat using those bits as being potentially a 'float power' argument from legacy API (obsoleted 2020-08) that has got miscast to this enum, and will trigger an assert if needed.
};