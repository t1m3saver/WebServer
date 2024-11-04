#include "fs.hpp"
#include "../LogSystem/LoggerItf.hpp"

namespace utils::fs {
bool isFileExist(const std::string& filePath){
    try{
        return std::filesystem::exists(filePath) && std::filesystem::is_regular_file(filePath);
    }catch(const std::filesystem::filesystem_error& e){
        LOG_ERROR("utils::fs::isFileExist error, "<<e);
    }
}

static std::map<std::string, std::map<std::string, std::string>> readConfig(const std::string& filename = "../../config.yaml"){
    static std::map<std::string, std::map<std::string, std::string>> res;
    static std::set<string> checker;
    if(checker.find(filename) != checker.end()){
        return res;
    }else if(filename != "../../config.yaml"){
        
    }else{
      YAML::Node config = YAML::LoadFile(filename);
      for(const auto& sectionName : config){
        if(sectionName.first.IsScalar()){
            const std::string key = sectionName.first.as<std::string>();
            const YAML::Node& sectionNode = sectionName.second;
            for (const auto& item : sectionNode) {
                res[key][item.first.as<std::string>()] = item.second.as<std::string>();
            }
        }
      }
      checker.insert(filename);
    }
}
}