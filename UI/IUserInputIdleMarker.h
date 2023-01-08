#pragma once

class IUserInputIdleMarker {
public:
	virtual ~IUserInputIdleMarker();
	virtual bool IsIdle() const = 0;
};
