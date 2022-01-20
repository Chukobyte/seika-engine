#pragma once

#include <iostream>
#include <cassert>

#include <json/json.hpp>

namespace JsonHelper {
static bool HasKey(const nlohmann::json &json, const std::string &key) {
    try {
        json.at(key);
        return true;
    } catch (nlohmann::json::type_error &te) {
    } catch (nlohmann::json::out_of_range &oor) {
    }
    return false;
}

template<typename T>
static T Get(const nlohmann::json &json, const std::string &key) {
    if (HasKey(json, key)) {
        return json.at(key);
    }
    std::cerr << "Key '" << key << "' doesn't exist!" << std::endl;
    assert(false && "Key doesn't exist in json!");
    return T();
}

template<typename T>
static T GetDefault(const nlohmann::json &json, const std::string &key, T defaultValue) {
    if (HasKey(json, key)) {
        return json.at(key);
    }
    return defaultValue;
}
}
