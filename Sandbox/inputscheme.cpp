#include "inputscheme.h"

std::map<InputAction, GameAction> InputScheme::DefaultMapping()
{
	return
	{
		{
			{ InputAction::WPress,   GameAction::MoveAxialForward  },
			{ InputAction::WRelease, GameAction::MoveAxialNone     },
			{ InputAction::SPress,   GameAction::MoveAxialBackward },
			{ InputAction::SRelease, GameAction::MoveAxialNone     },
			{ InputAction::DPress,   GameAction::MoveLateralRight  },
			{ InputAction::DRelease, GameAction::MoveLateralNone   },
			{ InputAction::APress,   GameAction::MoveLateralLeft   },
			{ InputAction::ARelease, GameAction::MoveLateralNone   },
			{ InputAction::EscPress, GameAction::CloseWindow       },
		}
	};
}

InputScheme::InputScheme()
	: m_mapping { DefaultMapping() }
{}

InputScheme::InputScheme(const std::map<InputAction, GameAction>& mapping)
	: m_mapping { mapping }
{}

void InputScheme::bind(const InputAction inputAction, const GameAction gameAction)
{
	m_mapping[inputAction] = gameAction;
}

void InputScheme::operator+=(const std::pair<InputAction, GameAction>& pair)
{
	bind(pair.first, pair.second);
}

GameAction InputScheme::operator[](InputAction inputAction)
{
	const auto it = m_mapping.find(inputAction);
	if (it == m_mapping.end())
	{
		return GameAction::None;
	}
	return it->second;
}
