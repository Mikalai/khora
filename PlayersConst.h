
struct ConstPlayers {
    ConstPlayers(const WorldLogic& world);

    bool All(std::function<bool(const PlayerLogic& player)> action);

public:
    const WorldLogic& _world;
};
