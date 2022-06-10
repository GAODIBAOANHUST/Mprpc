#include "mprpcconfig.h"

#include <iostream>
#include <string>

// 负责解析加载配置文件
void MprpcConfig::LoadConfigFile(const char *config_file)
{
    FILE *pf = fopen(config_file, "r");
    if (pf == nullptr)
    {
        std::cout << config_file << " is not exist" << std::endl;
        exit(EXIT_FAILURE);
    }

    // 1.注释   2.正确的配置项  3.去掉开头的多余的空格
    while (!feof(pf))
    {
        char buf[512] = {0};
        fgets(buf, 512, pf);

        // 解析配置项
        std::string read_buf(buf);
        Trim(read_buf);

        // 判断#的注释
        if (read_buf[0] == '#' || read_buf.empty())
        {
            continue;
        }
        int index = read_buf.find('=');
        if (index == -1)
        {
            // 配置项不合法
            continue;
        }

        std::string key;
        std::string value;
        key = read_buf.substr(0, index);
        Trim(key);
        // 127.0.0.1    \n      
        int endindex = read_buf.find('\n', index);
        value = read_buf.substr(index + 1, endindex - index - 1);
        Trim(value);
        m_configMap.emplace(key, value);
    }
}

// 查询配置项信息
std::string MprpcConfig::Load(const std::string &key)
{
    auto iter = m_configMap.find(key);
    if (iter == m_configMap.end())
    {
        return "";
    }
    return m_configMap[key];
}

// 去掉字符串前后的空格
void MprpcConfig::Trim(std::string &src_buf)
{
    // 去掉字符串前面多余的空格
    int index = src_buf.find_first_not_of(' ');
    if (index != -1)
    {
        // 说明字符串前面有空格
        src_buf = src_buf.substr(index, src_buf.length() - index);
    }
    // 去掉字符串后面多余的空格
    index = src_buf.find_last_not_of(' ');
    if (index != -1)
    {
        // 说明字符串后面有空格
        src_buf = src_buf.substr(0, index + 1);
    }
}