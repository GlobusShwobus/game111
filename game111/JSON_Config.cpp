#include "JSON_Config.h"

void JSONConfig::Init(std::unique_ptr<nlohmann::json> config) {
    entity_config = std::move(config);
}

const nlohmann::json& JSONConfig::Get()const {
    return *entity_config;
}

bool JSONConfig::Good()const {
    return entity_config != nullptr;
}