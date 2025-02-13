#include "Entity_Manager.h"



void EntityManager::Update()
{
	for (std::shared_ptr<Entity>& ent : add_next_frame) {
		all.push_back(ent);
		per_type[ent->GetType()].push_back(ent);
	}

	add_next_frame.clear();
	RemoveInactive();
	//printf("ent size: %d\n", (int)all.size());
}
void EntityManager::RemoveInactive()
{
	all.erase(std::remove_if(all.begin(), all.end(), [&](std::shared_ptr<Entity>& ent) {
		return !ent->IsActive() || ent == nullptr;
		}), all.end());


	for (auto& [key, val] : per_type) {
		val.erase(std::remove_if(val.begin(), val.end(), [&](std::shared_ptr<Entity>& ent) {
			return !ent->IsActive() || ent == nullptr;
			}), val.end());
	}
}
void EntityManager::ResteatType(int entity_id, const EntityType current_type, const EntityType change_to) {

	for (auto& [key, val] : per_type) {
		if (key != current_type) {
			continue;
		}

		auto it = std::remove_if(val.begin(), val.end(), [&](std::shared_ptr<Entity>& each) {
			if (each->GetID() == entity_id) {
				each->type = change_to;
				per_type[change_to].push_back(std::move(each));
				return true;
			}
			return false;
			});

		val.erase(it, val.end());
	}

}

const std::vector<std::shared_ptr<Entity>>& EntityManager::GetEntities()const {
	return all;
}
const std::vector<std::shared_ptr<Entity>>& EntityManager::GetEntities(const EntityType t) {
	return per_type[t];
}
const std::map<EntityType, std::vector<std::shared_ptr<Entity>>>& EntityManager::GetEntitiesMap()const {
	return per_type;
}
