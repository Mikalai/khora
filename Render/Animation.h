#pragma once

#include <functional>

using OnCompleteCallback = std::function<void()>;

class Animation {
public:
	virtual ~Animation();
	virtual void Update(float dt) = 0;
	bool IsComplete() const { return _isComplete; }

	void OnComplete(OnCompleteCallback cb);

protected:

	void SetComplete();

private:
	bool _isComplete{ false };
	std::vector<OnCompleteCallback> _cb;
};
