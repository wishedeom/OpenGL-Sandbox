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
	using Mapping = std::map<InputAction, GameAction>;
	
	static Mapping DefaultMapping();

	Mapping m_mapping;
};

