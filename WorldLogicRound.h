#pragma once

class WorldLogic;

class WorldLogicRound {
public:
	WorldLogicRound(WorldLogic& world);
	void DeclareEvent();
	void CollectTax();
	void ThrowDices();
	void IdentifyOrder();
	void ApplyThrowDicesStagePerks();
	void SelectActions();
	void OpenActions();
	bool AllActionsDone() const;
	void BeginExecuteActions();
	void ExecuteNextAction();

	void BeginProgressStage();
	void ExecuteProgressAction();
	void EndProgressStage();

	void ApplyGlobalEvent();

private:
	WorldLogic& _world;
};

class ConstWorldLogicRound {
public:
	ConstWorldLogicRound(const WorldLogic& world);
	bool AllActionsDone() const;
	bool AllProgressDone() const;
	bool AllEventEffectsApplied() const;

private:
	const WorldLogic& _world;
};