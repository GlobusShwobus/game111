#pragma once

#include "Entity.h"

struct Config {
	EntityType type;
	int size_x;
	int size_y;
	int speed;
};

class EntityManager {

	std::vector<Config> entity_data_shortcuts;

	std::vector<std::shared_ptr<Entity>> add_next_frame;
	std::vector<std::shared_ptr<Entity>> all;
	std::map<EntityType, std::vector<std::shared_ptr<Entity>>> per_type;


	size_t total_entities = 0;

	vec2i window_size = { 0,0 };

	void InitLocalConfig(const nlohmann::json& config);

	bool PosIsFree(vec2i& pos)const;

	void RemoveInactive();

public:

	EntityManager(const nlohmann::json& CONFIG) {
		InitLocalConfig(CONFIG);
	}

	void Update();

	//void AddEnemy(vec2& POS, const vec2& VEL);
	//void AddBullet(const vec2& origin, const vec2& target);
	//void AddStickyBomb(const vec2& origin, const vec2& target);
	//void AddObstacle(vec2& POS);

	const std::vector<std::shared_ptr<Entity>>& GetEntities()const {
		return all;
	}
	const std::vector<std::shared_ptr<Entity>>& GetEntities(const EntityType t) {
		return per_type[t];
	}
	const std::map<EntityType, std::vector<std::shared_ptr<Entity>>>& GetEntitiesMap()const {
		return per_type;
	}
	/*
	//think it works, did not test beyond taking a look and it looking like cancer
	const std::map<EntityType, std::vector<const Entity* const>> GetCustomMap(const std::set<EntityType>& listoftypes)const {

		std::map<EntityType, std::vector<const Entity* const>> custom;

		for (EntityType type : listoftypes) {

			for (auto& [key, val] : per_type) {

				if (key == type) {

					for (const std::shared_ptr<Entity>& each : val) {

						custom[key].push_back(each.get());

					}

				}

			}

		}

		return custom;
	}
	*/
	/*
	void ResteatType(int entity_id, const EntityType current_type, const EntityType change_to) {

		for (auto& [key, val] : per_type) {
			if (key != current_type) {
				continue;
			}

			auto it = std::remove_if(val.begin(), val.end(), [&](std::shared_ptr<Entity>& each) {
				if (each->ID() == entity_id) {
					each->type = change_to;
					per_type[change_to].push_back(std::move(each));
					return true;
				}
				return false;
				});

			val.erase(it, val.end());
		}

	}
	*/
};