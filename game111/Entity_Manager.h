#pragma once

#include "Entity.h"
#include "Texture_Manager.h"

class EntityManager {

	std::vector<std::shared_ptr<Entity>> add_next_frame;
	std::vector<std::shared_ptr<Entity>> all;
	std::map<EntityType, std::vector<std::shared_ptr<Entity>>> per_type;

	size_t total_entities = 0;
	void RemoveInactive();

	std::string ConvertTypeToQuery(EntityType type) {
		switch (type) {
		//case EntityType::testmap001: return	"Testmap001";
		case EntityType::player:	 return	"Player";
		case EntityType::enemy:		 return	"Enemy";
		}
		return {};//hopefully causes crash idk
	}

public:

	EntityManager() {}

	void Update();
	void ResteatType(int entity_id, const EntityType current_type, const EntityType change_to);


	void AddEntity(const nlohmann::json& entity_config, EntityType type, const TextureManager& txtm) {
		const auto& conf = entity_config[ConvertTypeToQuery(type)];

		SDL_FRect bb;
		bb.x = conf["posx"];
		bb.y = conf["posy"];
		bb.w = conf["width"];
		bb.h = conf["height"];

		SDL_Texture* txt = txtm.GetTexture(conf["name"].get<std::string>());
		auto make = std::make_shared<Entity>(total_entities++, type, bb, txt);

		add_next_frame.push_back(make);
	}

	const std::vector<std::shared_ptr<Entity>>& GetEntities()const;
	const std::vector<std::shared_ptr<Entity>>& GetEntities(const EntityType t);
	const std::map<EntityType, std::vector<std::shared_ptr<Entity>>>& GetEntitiesMap()const;

	/*
	bool PosIsFree(vec2& pos)const {

		while (true) {
			bool isFree = true;

			for (const auto& each : all) {
				const sf::FloatRect& bounds = each->shape.getGlobalBounds();

				if (bounds.contains(pos.x, pos.y)) {

					isFree = false;

					pos.x = bounds.left + bounds.width;


					if (pos.x >= window_size.x) {
						pos.x = 0;
						pos.y += bounds.height;
					}

					if (pos.y >= window_size.y) {
						return false;
					}
					break;
				}
			}

			if (isFree) {
				return true;
			}
		}
	}
	*/
};