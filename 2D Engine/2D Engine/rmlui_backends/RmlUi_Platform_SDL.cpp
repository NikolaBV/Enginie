/*
 * This source file is part of RmlUi, the HTML/CSS Interface Middleware
 */

#include "RmlUi_Platform_SDL.h"
#include <RmlUi/Core/Context.h>
#include <RmlUi/Core/Input.h>
#include <RmlUi/Core/StringUtilities.h>
#include <RmlUi/Core/SystemInterface.h>
#include <SDL.h>

SystemInterface_SDL::SystemInterface_SDL()
{
	cursor_default = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	cursor_move = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
	cursor_pointer = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	cursor_resize = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
	cursor_cross = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
	cursor_text = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
	cursor_unavailable = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO);
}

SystemInterface_SDL::~SystemInterface_SDL()
{
	SDL_FreeCursor(cursor_default);
	SDL_FreeCursor(cursor_move);
	SDL_FreeCursor(cursor_pointer);
	SDL_FreeCursor(cursor_resize);
	SDL_FreeCursor(cursor_cross);
	SDL_FreeCursor(cursor_text);
	SDL_FreeCursor(cursor_unavailable);
}

void SystemInterface_SDL::SetWindow(SDL_Window* in_window)
{
	window = in_window;
}

double SystemInterface_SDL::GetElapsedTime()
{
	static const Uint64 start = SDL_GetPerformanceCounter();
	static const double frequency = double(SDL_GetPerformanceFrequency());
	return double(SDL_GetPerformanceCounter() - start) / frequency;
}

void SystemInterface_SDL::SetMouseCursor(const Rml::String& cursor_name)
{
	SDL_Cursor* cursor = nullptr;

	if (cursor_name.empty() || cursor_name == "arrow")
		cursor = cursor_default;
	else if (cursor_name == "move")
		cursor = cursor_move;
	else if (cursor_name == "pointer")
		cursor = cursor_pointer;
	else if (cursor_name == "resize")
		cursor = cursor_resize;
	else if (cursor_name == "cross")
		cursor = cursor_cross;
	else if (cursor_name == "text")
		cursor = cursor_text;
	else if (cursor_name == "unavailable")
		cursor = cursor_unavailable;

	if (cursor)
		SDL_SetCursor(cursor);
}

void SystemInterface_SDL::SetClipboardText(const Rml::String& text_utf8)
{
	SDL_SetClipboardText(text_utf8.c_str());
}

void SystemInterface_SDL::GetClipboardText(Rml::String& text)
{
	char* raw_text = SDL_GetClipboardText();
	text = Rml::String(raw_text);
	SDL_free(raw_text);
}

bool RmlSDL::InputEventHandler(Rml::Context* context, SDL_Event& ev)
{
	bool result = true;

	switch (ev.type)
	{
	case SDL_MOUSEMOTION: result = context->ProcessMouseMove(ev.motion.x, ev.motion.y, GetKeyModifierState()); break;
	case SDL_MOUSEBUTTONDOWN:
		result = context->ProcessMouseButtonDown(ConvertMouseButton(ev.button.button), GetKeyModifierState());
		SDL_CaptureMouse(SDL_TRUE);
		break;
	case SDL_MOUSEBUTTONUP:
		SDL_CaptureMouse(SDL_FALSE);
		result = context->ProcessMouseButtonUp(ConvertMouseButton(ev.button.button), GetKeyModifierState());
		break;
	case SDL_MOUSEWHEEL: result = context->ProcessMouseWheel(float(-ev.wheel.y), GetKeyModifierState()); break;
	case SDL_KEYDOWN:
		result = context->ProcessKeyDown(ConvertKey(ev.key.keysym.sym), GetKeyModifierState());
		if (ev.key.keysym.sym == SDLK_RETURN || ev.key.keysym.sym == SDLK_KP_ENTER)
			result &= context->ProcessTextInput('\n');
		break;
	case SDL_KEYUP: result = context->ProcessKeyUp(ConvertKey(ev.key.keysym.sym), GetKeyModifierState()); break;
	case SDL_TEXTINPUT: result = context->ProcessTextInput(Rml::String(&ev.text.text[0])); break;
	case SDL_WINDOWEVENT:
	{
		switch (ev.window.event)
		{
		case SDL_WINDOWEVENT_SIZE_CHANGED:
		{
			Rml::Vector2i dimensions(ev.window.data1, ev.window.data2);
			context->SetDimensions(dimensions);
		}
		break;
		case SDL_WINDOWEVENT_LEAVE: context->ProcessMouseLeave(); break;
		}
	}
	break;
	default: break;
	}

	return result;
}

Rml::Input::KeyIdentifier RmlSDL::ConvertKey(int sdlkey)
{
	switch (sdlkey)
	{
	case SDLK_UNKNOWN:      return Rml::Input::KI_UNKNOWN;
	case SDLK_ESCAPE:       return Rml::Input::KI_ESCAPE;
	case SDLK_SPACE:        return Rml::Input::KI_SPACE;
	case SDLK_0:            return Rml::Input::KI_0;
	case SDLK_1:            return Rml::Input::KI_1;
	case SDLK_2:            return Rml::Input::KI_2;
	case SDLK_3:            return Rml::Input::KI_3;
	case SDLK_4:            return Rml::Input::KI_4;
	case SDLK_5:            return Rml::Input::KI_5;
	case SDLK_6:            return Rml::Input::KI_6;
	case SDLK_7:            return Rml::Input::KI_7;
	case SDLK_8:            return Rml::Input::KI_8;
	case SDLK_9:            return Rml::Input::KI_9;
	case SDLK_a:            return Rml::Input::KI_A;
	case SDLK_b:            return Rml::Input::KI_B;
	case SDLK_c:            return Rml::Input::KI_C;
	case SDLK_d:            return Rml::Input::KI_D;
	case SDLK_e:            return Rml::Input::KI_E;
	case SDLK_f:            return Rml::Input::KI_F;
	case SDLK_g:            return Rml::Input::KI_G;
	case SDLK_h:            return Rml::Input::KI_H;
	case SDLK_i:            return Rml::Input::KI_I;
	default: break;
	}
	return Rml::Input::KI_UNKNOWN;
}

int RmlSDL::ConvertMouseButton(int button)
{
	switch (button)
	{
	case SDL_BUTTON_LEFT: return 0;
	case SDL_BUTTON_RIGHT: return 1;
	case SDL_BUTTON_MIDDLE: return 2;
	default: return 3;
	}
}

int RmlSDL::GetKeyModifierState()
{
	SDL_Keymod sdl_mods = SDL_GetModState();

	int retval = 0;

	if (sdl_mods & KMOD_CTRL)
		retval |= Rml::Input::KM_CTRL;

	if (sdl_mods & KMOD_SHIFT)
		retval |= Rml::Input::KM_SHIFT;

	if (sdl_mods & KMOD_ALT)
		retval |= Rml::Input::KM_ALT;

	if (sdl_mods & KMOD_NUM)
		retval |= Rml::Input::KM_NUMLOCK;

	if (sdl_mods & KMOD_CAPS)
		retval |= Rml::Input::KM_CAPSLOCK;

	return retval;
}


