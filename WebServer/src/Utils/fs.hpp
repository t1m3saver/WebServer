#include <fstream>
#include <filesystem>
#include <string>
#include <yaml-cpp/yaml.h>
#include <map>

namespace utils::fs {
    // 检查文件是否存在
    bool isFileExist(const std::string& filePath);

    // 检查目录是否存在
    bool isDirectoryExist(const std::string& dirPath);

    // 创建文件
    bool createFile(const std::string& filePath);

    // 重命名文件
    bool renameFile(const std::string& oldFilePath, const std::string& newFilePath);

    // 创建目录
    bool createPath(const std::string& dirPath);

    // 删除文件
    bool deleteFile(const std::string& filePath);

    // 删除目录
    bool deletePath(const std::string& dirPath);

    // 获取文件扩展名
    std::string getFileExtension(const std::string& filePath);

    // 获取父目录路径
    std::string getParentPath(const std::string& filePath);

    // 复制文件
    bool copyFile(const std::string& sourcePath, const std::string& destinationPath);

    //获取配置文件的信息
    static std::map<std::string, std::map<std::string, std::string>> readConfig(const std::string& filename = "../../config.yaml");
}
