#pragma once

class WorldLogic;

class WorldLogicPrepare {
public:
    WorldLogicPrepare(WorldLogic& logic);
    void UpgradeCitiesToFirstLevel();
    void ShufflePolicies();
    void ShuffleEvents();
    void GivePolicies();
	void BeginDraft();
	void EndDraft();
	void ChangeDraft();
	void SelectCities();
	void SelectPlayersCount();
	void SelectCityColor();
    void CreateExpeditions();

private:
    WorldLogic& _world;
};
