#pragma once

#include <filesystem>
#include <vsg/io/Options.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <vsg/all.h>
#include <Locale/Translate.h>
#include <Resources.h>
#include <PolicyTemplate.h>
#include "KhoraScene.h"
#include "KhoraSceneBuilder.h"
#include <ExpeditionTemplate.h>

const vsg::dvec4 darkColor{ 0.2,0.2,0.2,1.0 };
double tableCaptionScale = 0.003;

std::unique_ptr<Scene> KhoraSceneBuilder::OnCreateScene() {
	return std::make_unique<KhoraScene>();
}

void KhoraSceneBuilder::OnBuildScene(Scene& scene, const Assets& assets) {
	OnBuildScene(static_cast<KhoraScene&>(scene), static_cast<const KhoraAssets&>(assets));
}

void KhoraSceneBuilder::OnBuildScene(KhoraScene& scene, const KhoraAssets& assets) {
	
	_box = CreateBox();

	{
		auto table_material = Clone(assets.table_material);

		NewTransform().
			AddChild(table_material)
			.MoveToWorld();

		table_material->addChild(assets.table_geometry);
		scene.AddToWorld(table_material);
	}

	// root->matrix = vsg::rotate(-vsg::PI / 2.0, 1.0, 0.0, 0.0);
	{
		auto board_material = Clone(assets.board_material);
		scene.AddToWorld(board_material);
		board_material->addChild(assets.board_geometry);
	}

	{
		auto node = scene.policies_deck_location = Clone(assets.policies_deck_location);
		if (DEBUG_POLICIES_DECK) {
			node->addChild(_box);
		}
		scene.AddToWorld(node);
	}

	{
		auto node = scene.events_deck_close_location = Clone(assets.events_deck_close_location);
		if (DEBUG_CLOSE_EVENTS_DECK) {
			node->addChild(_box);
		}
		scene.AddToWorld(node);
	}

	{
		auto node = scene.events_deck_open_location = Clone(assets.events_deck_open_location);
		if (DEBUG_OPEN_EVENTS_DECK) {
			node->addChild(_box);
		}
		scene.AddToWorld(node);
	}

	if (DEBUG_POINTS_LOCATION) {
		for (int i = 0; i < max_points_locations; ++i) {
			auto point = scene.points_location[i] = Clone(assets.points_location[i]);
			point->addChild(_box);
			scene.AddToWorld(point);
		}
	}

	if (DEBUG_TAX_LOCATION) {
		for (int i = 0; i < max_tax_locations; ++i) {
			auto point = scene.tax_location[i] = Clone(assets.tax_location[i]);
			point->addChild(_box);
			scene.AddToWorld(point);
		}
	}

	if (DEBUG_POPULATION_LOCATION) {
		for (int i = 0; i < max_population_locations; ++i) {
			auto point = scene.population_location[i] = Clone(assets.population_location[i]);
			point->addChild(_box);
			scene.AddToWorld(point);
		}
	}

	if (DEBUG_GLORY_LOCATION) {
		for (int i = 0; i < max_glory_locations; ++i) {
			auto point = scene.glory_location[i] = Clone(assets.glory_location[i]);
			point->addChild(_box);
			scene.AddToWorld(point);
		}
	}

	if (DEBUG_ARMY_LOCATION) {
		for (int i = 0; i < max_army_locations; ++i) {
			auto point = scene.army_location[i] = Clone(assets.army_location[i]);
			point->addChild(_box);
			scene.AddToWorld(point);
		}
	}

	for (int i = 0; i < As<int>(discovery_type::discoveries_count); ++i) {
		scene.discovery_materials[i] = Clone(assets.discovery_materials[i]);
		scene.discovery_materials[i]->addChild(assets.discovery_geometry);
	}

	for (int i = 0; i < GetExpeditionsCount(); ++i) {

		auto& e = GetExpeditionTemplate(i);
		for (int j = 0; j < e.discoveries.size(); ++j) {
			if (e.discoveries[j] == discovery_type::no)
				continue;

			// all expeditions has 1 except of the last			
			auto location = scene.expedition_discoveries[i + j] = vsg::MatrixTransform::create();
			location->matrix = vsg::translate(0, 1, 0);

			location->addChild(scene.discovery_materials[As<int>(e.discoveries[j])]);
			scene._discoveryTokenToExpedition[location] = i;
			scene._expeditionToDiscoveryTokens[i].push_back(location);			

			scene.AddToWorld(location);
		}
	}

	for (int i = 0; i < achieves_count; ++i) {
		auto point = scene.achieve_location[i] = Clone(assets.achieve_location[i]);
		point->addChild(_box);
		scene.AddToWorld(point);
	}

	for (int i = 0; i < As<int>(PolicyType::Count); ++i) {
		scene.policy_front_materials[i] = Clone(assets.policy_front_materials[i]);
		scene.policy_front_materials[i]->addChild(assets.policy_front_geometry);
	}

	scene.policy_back_material = Clone(assets.policy_back_material);
	scene.policy_back_material->addChild(assets.policy_back_geometry);

	for (int i = 0; i < As<int>(Policies::policies_count); ++i) {		
		auto& type = GetPolicyTemplate(As<Policies>(i));

		auto frontLocation = vsg::MatrixTransform::create();
		frontLocation->matrix = assets.policy_front_offset->matrix;
		frontLocation->addChild(scene.policy_front_materials[As<int>(type.GetRepeateType())]);

		auto backLocation = vsg::MatrixTransform::create();
		backLocation->matrix = assets.policy_back_offset->matrix;
		backLocation->addChild(scene.policy_back_material);

		
		auto imageLocation = vsg::MatrixTransform::create();
		imageLocation->matrix = assets.policy_image_offset->matrix;
		imageLocation->addChild(assets.policy_image_geometry);

		auto image = Clone(assets.policy_materials[i]);
		image->addChild(assets.policy_image_geometry);

		imageLocation->addChild(image);
		

		auto location = scene.policies[i] = vsg::MatrixTransform::create();
		location->addChild(frontLocation);
		location->addChild(backLocation);
		location->addChild(imageLocation);

		scene.policies[i] = location;
		scene.AddToWorld(location);
	}

	scene.event_back_material = Clone(assets.event_back_material);
	scene.event_back_material->addChild(assets.event_back_geometry);

	for (int i = 0; i < (int)GlobalEventType::Count; ++i) {
		auto backLocation = vsg::MatrixTransform::create();
		backLocation->matrix = assets.events_back_offset->matrix;
		backLocation->addChild(scene.event_back_material);

		auto frontLocation = vsg::MatrixTransform::create();
		frontLocation->matrix = assets.events_front_offset->matrix;

		auto material = scene.event_materials[i] = Clone(assets.events_materials[i]);
		material->addChild(assets.event_front_geometry);
		frontLocation->addChild(material);

		auto root = vsg::MatrixTransform::create();
		root->matrix = vsg::translate(0.0, 2.0, 0.0);
		root->addChild(frontLocation);
		root->addChild(backLocation);

		scene.events[i] = root;
		scene.AddToWorld(root);
	}

	double darkScale = 0.005;
	
	{
		auto t = scene.persepolis_text_location = Clone(assets.persepolis_text_location);
		t->addChild(CreateText(assets.font, tr("PERSEPOLIS"), { 0.0, 0.0, 0.0 }, { 0.6, 0.6, 0.6, 1.0 }, 0.008));
		scene.AddToWorld(t);
	}
	{
		auto t = scene.troops_text_location = Clone(assets.troops_text_location);
		t->addChild(CreateText(assets.font, tr("TROOPS"), { 0.0, 0.0, 0.0 }, darkColor, darkScale));
		scene.AddToWorld(t);
	}
	
	{
		auto t = scene.glory_text_location = Clone(assets.glory_text_location);
		t->addChild(CreateText(assets.font, tr("GLORY"), { 0.0, 0.0, 0.0 }, darkColor, darkScale));
		scene.AddToWorld(t);
	}
	
	{
		auto t = scene.tax_text_location = Clone(assets.tax_text_location);
		t->addChild(CreateText(assets.font, tr("TAX"), { 0.0, 0.0, 0.0 }, darkColor, darkScale));
		scene.AddToWorld(t);
	}

	{
		auto t = scene.population_text_location = Clone(assets.population_text_location);
		t->addChild(CreateText(assets.font, tr("POPULATION"), { 0.0, 0.0, 0.0 }, darkColor, darkScale));
		scene.AddToWorld(t);
	}
	
	CreateSelectPlayersCountMessageBox();
	CreateSelectColorMessageBox();
	CreateSelectCityMessageBox();
	_root->addChild(_cameraAligned);


	return s;
}


void KhoraSceneBuilder::::CreateSelectPlayersCountMessageBox() {
	_selectPlayersCountMessageBox = vsg::Switch::create();
	_selectPlayersCountMessageBox->setAllChildren(false);

	vsg::dvec4 v;
	v.set(0.0, 0.0, 0.0, 1.0);
	auto p = _camera->projectionMatrix->transform() * v;
	// p = p / p.w;	

	auto offset = vsg::translate(0.0, 0.0, -2.0 * p.z);
	auto abs = vsg::AbsoluteTransform::create(); // vsg::MatrixTransform::create();
	abs->matrix = offset;

	v.set(1.0, 1.0, 0.0, 1.0);
	p = _camera->projectionMatrix->transform() * v;

	vsg::GeometryInfo gi;
	float w = 0.01f * 2.0f;
	float h = 0.005f * 2.0f;
	gi.position.set(0, 0, 0);
	gi.dx.set(w, 0.0f, 0.0f);
	gi.dy.set(0.0f, h, 0.0f);
	gi.dz.set(0.0f, 0.0f, 0.2f);
	gi.color.set(0.8f, 0.8f, 0.8f, 0.8f);

	state.blending = true;


	auto quad = builder->createQuad(gi, state);
	float size = 0.001 * 2;
	for (int i = 1; i < 4; ++i) {
		gi.position.set(0, 0, 0);
		gi.dx.set(size, 0.0f, 0.0f);
		gi.dy.set(0.0f, size, 0.0f);
		gi.dz.set(0.0f, 0.0f, 0.05f);
		gi.color.set(1.0f, 0.0f, 0.0f, 1.0f);
		state.blending = false;

		auto q = builder->createQuad(gi, state);
		auto t = vsg::MatrixTransform::create();
		t->matrix = vsg::translate(-w / 2.0f + (float)(i)*w / 4.0f, 0.0f, 0.00001f);
		t->addChild(q);

		OnActivate(t, [i, this](auto v) {
			std::cout << "SET PLAYERS COUNT " << i + 1 << std::endl;
		_world.SetPlayersCount(i + 1);
		_selectPlayersCountMessageBox->setAllChildren(false);
			});

		abs->addChild(t);
	}

	abs->addChild(quad);

	auto layout = vsg::StandardLayout::create();
	layout->horizontalAlignment = vsg::StandardLayout::CENTER_ALIGNMENT;
	layout->verticalAlignment = vsg::StandardLayout::BOTTOM_ALIGNMENT;
	layout->position = vsg::vec3(0, 1.5, 0);
	layout->horizontal = vsg::vec3(1.0, 0.0, 0.0);
	layout->vertical = vsg::vec3(0.0, 1.0, 0.0);
	layout->color = vsg::vec4(1.0, 1.0, 1.0, 1.0);
	layout->outlineWidth = 0.0;
	layout->billboard = true;

	auto data = vsg::stringValue::create(tr("Select players count"));

	auto text = vsg::Text::create();
	text->text = data;
	text->font = _font;
	text->layout = layout;
	text->setup(0, _options);

	auto s = vsg::AbsoluteTransform::create();
	s->matrix = vsg::translate(0.0f, 0.0f, -15.0f);// *vsg::scale(0.1f, 0.1f, 1.0f);
	s->addChild(text);

	abs->addChild(s);
	_selectPlayersCountMessageBox->addChild(false, abs);
	// _cameraAligned->addChild(_selectPlayersCountMessageBox);
	
	_worldRoot->addChild(_selectPlayersCountMessageBox);
}



void KhoraSceneBuilder::::CreateSelectColorMessageBox() {

	_selectColorMessageBox = vsg::Switch::create();
	_selectColorMessageBox->setAllChildren(false);

	vsg::dvec4 v;
	v.set(0.0, 0.0, 0.0, 1.0);
	auto p = _camera->projectionMatrix->transform() * v;
	// p = p / p.w;	

	auto offset = vsg::translate(0.0, 0.0, -2.0 * p.z);
	auto abs = vsg::AbsoluteTransform::create();
	abs->matrix = offset;

	v.set(1.0, 1.0, 0.0, 1.0);
	p = _camera->projectionMatrix->transform() * v;

	vsg::GeometryInfo gi;
	float w = 0.01f * 2.0f;
	float h = 0.005f * 2.0f;
	gi.position.set(0, 0, 0);
	gi.dx.set(w, 0.0f, 0.0f);
	gi.dy.set(0.0f, h, 0.0f);
	gi.dz.set(0.0f, 0.0f, 0.2f);
	gi.color.set(0.8f, 0.8f, 0.8f, 0.8f);

	state.blending = true;


	auto quad = builder->createQuad(gi, state);
	float size = 0.001 * 2;
	for (int i = 0; i < 4; ++i) {
		gi.position.set(0, 0, 0);
		gi.dx.set(size, 0.0f, 0.0f);
		gi.dy.set(0.0f, size, 0.0f);
		gi.dz.set(0.0f, 0.0f, 0.05f);
		gi.color.set(1.0f, 0.0f, 0.0f, 1.0f);
		state.blending = false;

		auto q = builder->createQuad(gi, state);
		auto t = vsg::MatrixTransform::create();
		t->matrix = vsg::translate(-w / 2.0f + (float)(i + 1) * w / 5.0f, 0.0f, 0.00001f);
		t->addChild(q);

		OnActivate(t, [i, this](auto v) {
			std::cout << "SET PLAYERS COLOR " << i << std::endl;
		_selectColorMessageBoxCallback((player_color)i);
		_selectColorMessageBox->setAllChildren(false);
			});

		abs->addChild(t);
	}

	abs->addChild(quad);

	auto layout = vsg::StandardLayout::create();
	layout->horizontalAlignment = vsg::StandardLayout::CENTER_ALIGNMENT;
	layout->verticalAlignment = vsg::StandardLayout::BOTTOM_ALIGNMENT;
	layout->position = vsg::vec3(0, 1.5, 0);
	layout->horizontal = vsg::vec3(1.0, 0.0, 0.0);
	layout->vertical = vsg::vec3(0.0, 1.0, 0.0);
	layout->color = vsg::vec4(1.0, 1.0, 1.0, 1.0);
	layout->outlineWidth = 0.0;
	layout->billboard = true;

	auto data = vsg::stringValue::create(tr("Select color"));

	auto text = vsg::Text::create();
	text->text = data;
	text->font = _font;
	text->layout = layout;
	text->setup(0, _options);

	auto s = vsg::AbsoluteTransform::create();
	s->matrix = vsg::translate(0.0f, 0.0f, -15.0f);// *vsg::scale(0.1f, 0.1f, 1.0f);
	s->addChild(text);

	abs->addChild(s);
	_selectColorMessageBox->addChild(false, abs);
	//_cameraAligned->addChild(_selectColorMessageBox);
	_worldRoot->addChild(_selectColorMessageBox);
}

void KhoraSceneBuilder::::CreateSelectCityMessageBox() {
	_selectCityMessageBox = vsg::Switch::create();
	_selectCityMessageBox->setAllChildren(false);

	vsg::dvec4 v;
	v.set(0.0, 0.0, 0.0, 1.0);
	auto p = _camera->projectionMatrix->transform() * v;
	// p = p / p.w;	

	auto offset = vsg::translate(0.0, 0.0, -2.0 * p.z);
	auto abs = vsg::AbsoluteTransform::create(); // vsg::MatrixTransform::create();
	abs->matrix = offset;

	v.set(1.0, 1.0, 0.0, 1.0);
	p = _camera->projectionMatrix->transform() * v;

	vsg::GeometryInfo gi;
	float w = 0.01f * 2.0f;
	float h = 0.005f * 2.0f;
	gi.position.set(0, 0, 0);
	gi.dx.set(w, 0.0f, 0.0f);
	gi.dy.set(0.0f, h, 0.0f);
	gi.dz.set(0.0f, 0.0f, 0.2f);
	gi.color.set(0.8f, 0.8f, 0.8f, 0.8f);

	state.blending = true;


	auto quad = builder->createQuad(gi, state);
	float size = 0.0005 * 2;
	int count = cities_count;
	for (int i = 0; i < count; ++i) {
		gi.position.set(0, 0, 0);
		gi.dx.set(size, 0.0f, 0.0f);
		gi.dy.set(0.0f, size, 0.0f);
		gi.dz.set(0.0f, 0.0f, 0.05f);
		gi.color.set(1.0f, 0.0f, 0.0f, 1.0f);
		state.blending = false;

		auto q = builder->createQuad(gi, state);
		auto t = vsg::MatrixTransform::create();
		t->matrix = vsg::translate(-w / 2.0f + (float)(i + 1) * w / 5.0f, 0.0f, 0.00001f);
		t->addChild(q);

		OnActivate(t, [i, this](auto v) {
			std::cout << "SET CITY" << i << std::endl;
		_selectCityMessageBoxCallback((Cities)i);
		_selectCityMessageBox->setAllChildren(false);
			});

		abs->addChild(t);
	}

	abs->addChild(quad);

	auto layout = vsg::StandardLayout::create();
	layout->horizontalAlignment = vsg::StandardLayout::CENTER_ALIGNMENT;
	layout->verticalAlignment = vsg::StandardLayout::BOTTOM_ALIGNMENT;
	layout->position = vsg::vec3(0, 1.5, 0);
	layout->horizontal = vsg::vec3(1.0, 0.0, 0.0);
	layout->vertical = vsg::vec3(0.0, 1.0, 0.0);
	layout->color = vsg::vec4(1.0, 1.0, 1.0, 1.0);
	layout->outlineWidth = 0.0;
	layout->billboard = true;

	auto data = vsg::stringValue::create(tr("Select city"));

	auto text = vsg::Text::create();
	text->text = data;
	text->font = _font;
	text->layout = layout;
	text->setup(0, _options);

	auto s = vsg::AbsoluteTransform::create();
	s->matrix = vsg::translate(0.0f, 0.0f, -15.0f);// *vsg::scale(0.1f, 0.1f, 1.0f);
	s->addChild(text);

	abs->addChild(s);
	_selectCityMessageBox->addChild(false, abs);
	//_cameraAligned->addChild(_selectCityMessageBox);
	_worldRoot->addChild(_selectCityMessageBox);
}