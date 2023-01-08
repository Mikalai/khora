#pragma once

#include "ActionType.h"

const char* ToString(ActionType evt) {
	switch (evt)
	{
	case ActionType::NotAvailable:		
		return "NotAvailable";
	case ActionType::Philosophy:
		return "Philosophy";
	case ActionType::Law:
		return "Law";
	case ActionType::Culture:
		return "Culture";
	case ActionType::Trade:
		return "Trade";
	case ActionType::Military:
		return "Military";
	case ActionType::Policy:
		return "Policy";
	case ActionType::Development:
		return "Development";
	default:
		return "unknown";
	}
}
