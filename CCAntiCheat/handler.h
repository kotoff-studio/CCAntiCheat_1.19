#pragma once

class EventData;

typedef void(*EventCallback)(EventData*);

#define EVENT_COUNT 7
enum class EVENT_ID {
	DEFAULT_EVENT, //Responsible caller: NONE, this event should never be used.
	LOCALPLAYER_UPDATE_HEAD_Y, //Responsible caller: "Patches/LocalPlayer/SetYHeadRotHook.cpp"
	ACTOR_SET_ROT, //Responsible caller: "Patches/Actor/SetRotHook.cpp"
	RENDER_EVENT,
	KEYPRESS_EVENT,
	MOUSE_INPUT_EVENT,
	INTERACTION_TICK_EVENT

	//ATTENTION: REMEMBER TO UPDATE THE MACRO!
};
