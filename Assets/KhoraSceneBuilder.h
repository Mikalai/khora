#pragma once

#include <filesystem>
#include <vsg/io/Options.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <vsg/all.h>
#include <Resources.h>
#include <Assets/SceneBuilder.h>

class AssetsCompiler;
class KhoraScene;
class KhoraAssets;

class KhoraSceneBuilder : public SceneBuilder {
public:

protected:
    std::unique_ptr<Scene> OnCreateScene() override;
    void OnBuildScene(Scene& scene, const Assets& assets) override;

private:
    void OnBuildScene(KhoraScene& scene, const KhoraAssets& assets);

    void CreateSelectPlayersCountMessageBox(KhoraScene& scene, const KhoraAssets& assets);
    void CreateSelectColorMessageBox(KhoraScene& scene, const KhoraAssets& assets);
    void CreateSelectCityMessageBox(KhoraScene& scene, const KhoraAssets& assets);

    vsg::ref_ptr<vsg::Switch> _selectPlayersCountMessageBox;
    vsg::ref_ptr<vsg::Switch> _selectColorMessageBox;
};
