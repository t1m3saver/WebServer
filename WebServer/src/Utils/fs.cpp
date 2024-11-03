#include "fs.hpp"

namespace Utils::fs {
bool isFileExist(const std::string& filePath){
    try{
        return std::filesystem::exists(filePath) && std::filesystem::is_regular_file(filePath);
    }catch(const std::filesystem::filesystem_error& e){
        
    }
}

static std::map<std::string, std::stirng> readConfig(const std::string& filename = "../../config.yaml"){
    static std::map<std::string, std::map<std::string, std::string>> res;
    if(res.find(filename) != mark.end()){
        return res[filename];
    }else{
      YAML::Node config = YAML::LoadFile(filename);
      std::map<std::string, std::string> section;
      for(const auto& sectionName : config){
        if(sectionName.first.IsScalar()){
            const std::string key = sectionName.first.as<std::string>();
            const YAML::Node& sectionNode = sectionName.second;
            for (const auto& item : sectionNode) {
                section[item.first.as<std::string>()] = item.second.as<std::string>();
            }
            res[filename] = section; // 存储到 map 中
        }
      }
    }
}
}