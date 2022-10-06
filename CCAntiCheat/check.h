#include "handler.h"

class EventData {
public:
	EventData() {};
	volatile EVENT_ID GetId() {
		return EVENT_ID::DEFAULT_EVENT;
	}

	template<class T>
	auto as() -> T* {
		return (T*)this;
	}
};