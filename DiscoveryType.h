#pragma once

enum class discovery_type {
	no = -1,
	red,
	blue,
	green,
	epic_red,
	epic_blue,
	epic_green,
	discoveries_count
};


const char* ToString(discovery_type evt);