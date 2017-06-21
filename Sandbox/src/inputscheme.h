#pragma once

#include <map>

#include "gameaction.h"
#include "inputaction.h"

class InputScheme
{
public:	
	InputScheme();
	InputScheme(const std::map<InputAction, GameAction>& mapping);

	void bind(InputAction inputAction, GameAction gameAction);
	void operator+=(const std::pair<InputAction, GameAction>& pair);
	GameAction operator[](InputAction inputAction);

private:
	static std::map<InputAction, GameAction> defaultMapping();

	std::map<InputAction, GameAction> _mapping;
};

