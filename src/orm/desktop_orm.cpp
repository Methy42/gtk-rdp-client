#include <fstream>
#include <iostream>
#include "desktop_orm.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

DesktopORM::DesktopORM()
    : file_path_("desktops.json") {
    // 如果指定路径的文件不存在，则创建一个新文件
    std::ifstream input(file_path_);
    if (!input.good()) {
        std::ofstream output(file_path_);
        if (!output.is_open()) {
            throw std::runtime_error("Failed to create new file: " + file_path_);
        }
        // 创建一个空的JSON对象，并保存到文件中（方便后续读取）
        json j;
        output << j.dump(4);
        output.close();
    }
    // 尝试从文件中加载桌面配置信息
    if (!loadFromFile()) {
        std::cerr << "Failed to load desktops from file: " << file_path_ << "\n";
    }
}

const std::vector<Desktop>& DesktopORM::getDesktops() const {
    return desktops_;
}

const Desktop& DesktopORM::getDesktopById(int id) const {
    for (const auto& desktop : desktops_) {
        if (desktop.getId() == id) {
            return desktop;
        }
    }
    throw std::runtime_error("Desktop with given ID not found");
}

void DesktopORM::addDesktop(const Desktop& desktop) {
    desktops_.push_back(desktop);
    saveToFile();
}

bool DesktopORM::updateDesktopById(int id, const Desktop& desktop) {
    for (auto& d : desktops_) {
        if (d.getId() == id) {
            d = desktop;
            saveToFile();
            return true;
        }
    }
    return false;
}

bool DesktopORM::removeDesktopById(int id) {
    for (auto it = desktops_.begin(); it != desktops_.end(); ++it) {
        if (it->getId() == id) {
            desktops_.erase(it);
            saveToFile();
            return true;
        }
    }
    return false;
}

bool DesktopORM::loadFromFile() {
    std::ifstream input(file_path_);
    if (!input.is_open()) {
        return false;
    }

    json j;
    input >> j;

    try {
        auto desktops_json = j.at("desktops");
        for (const auto& desktop_json : desktops_json) {
            auto name = desktop_json.at("name").get<std::string>();
            auto ip = desktop_json.at("ip").get<std::string>();
            auto port = desktop_json.at("port").get<int>();
            auto account = desktop_json.at("account").get<std::string>();
            auto password = desktop_json.at("password").get<std::string>();
            auto domain = desktop_json.at("domain").get<std::string>();
            auto auto_login = desktop_json.at("auto_login").get<bool>();
            desktops_.emplace_back(name, ip, port, account, password, domain, auto_login);
        }
        return true;
    } catch (...) {
        return false;
    }
}

bool DesktopORM::saveToFile() const {
    std::ofstream output(file_path_);
    if (!output.is_open()) {
        return false;
    }

    json j;
    for (const auto& desktop : desktops_) {
        json desktop_json = {
            {"name", desktop.getName()},
            {"ip", desktop.getIP()},
            {"port", desktop.getPort()},
            {"account", desktop.getAccount()},
            {"password", desktop.getPassword()},
            {"domain", desktop.getDomain()},
            {"auto_login", desktop.getAutoLogin()}
        };
        j["desktops"].push_back(desktop_json);
    }

    output << j.dump(4); // pretty print with 4 spaces
    return true;
}

DesktopORM& DesktopORM::getInstance() {
    return instance;
}

DesktopORM DesktopORM::instance;