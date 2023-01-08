#include <UI/GeneralUserInput.h>
#include <UI/ICityStrategy.h>
#include <Resources.h>

class WorldLogic;
class PlayerLogic;

class AIUserInput final : public GeneralUserInput {
public:
    AIUserInput(int playerId, WorldLogic& world);
    void SelectPlayersCountAsync(std::function<void(int count)> cb) override;
    void SelectCityColorAsync(std::function<void(player_color color)> cb) override;
    void SelectCityAsync(std::function<void(Cities city)> cb) override;
    void SelectPolicyFromDraftAsync(std::function<void(Policies policy)> cb) override;
    void ThrowDiceAsync(int diceIndex, std::function<void(int diceIndex, int diceValue)> cb) override;
    void SelectActionAsync(int diceValue, bool allowMilitary, SelectActionsCallback cb) override;
    void SelectLawPolicyAsync(Policies a, Policies b, std::function<void(Policies selected, Policies dropped)> cb) override;
    void SelectExpeditionAsync(std::function<void(int expedition)> cb) override;
    void MakeProgressAsync(std::function<void(ProgressTrackType)> cb) override;
    void SelectPolicyFromHandsAsync(PolicySelectionReasonType reason, SelectPolicyCallback cb) override;
    void SelectDiscoveryFromHandsAsync(SelectDiscoveryCallback cb) override;
	void SelectDiscoveryFromPoolAsync(SelectDiscoveryCallback cb) override;
	void SelectPolicyFromActiveDeckAsync(SelectPolicyCallback cb) override;

private:
    std::unique_ptr<ICityStrategy> CreateCityStrategy(Cities city);

private:
    std::unique_ptr<ICityStrategy> _strategy;
};
