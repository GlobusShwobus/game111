#pragma once

#include "File_Manager.h"

class JSONConfig {
    std::unique_ptr<nlohmann::json> entity_config;

public:
    JSONConfig() = default;

    void Init(std::unique_ptr<nlohmann::json> config);
    const nlohmann::json& Get()const;
    const nlohmann::json& Get(const char* specific)const {
        static nlohmann::json empty;

        if (entity_config && entity_config->contains(specific)) {
            return (*entity_config)[specific];
        }
        else
            return empty;
    }

    bool Good()const;
};