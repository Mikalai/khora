#pragma once

enum class ActionType {
	NotAvailable = -2,
	Unknown = -1,
	Philosophy,
	Law,
	Culture,
	Trade,
	Military,
	Policy,
	Development,
	Count
};

const char* ToString(ActionType evt);