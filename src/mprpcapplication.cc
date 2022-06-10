#include "mprpcapplication.h"
#include <iostream>
#include <unistd.h>
#include <string>

void ShowArgsHelp()
{
    std::cout << "format: command -i <configfile>" << std::endl;
}

MprpcConfig MprpcApplication::m_config;

void MprpcApplication::Init(int argc, char **argv)
{
    if(argc < 2)
    {
        ShowArgsHelp();
        exit(EXIT_FAILURE);
    }

    int c = 0;
    std::string config_file;
    while ((c = getopt(argc, argv, "i:")) != -1)
    {
        switch (c)
        {
        case 'i':
            config_file = optarg;
            break;
        case '?':
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        case ':':
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        default:
            break;
        }
    }
    
    // 开始加载配置文件了 rpcserver_ip= rpcserver_port= zookepeer_ip= zookepeer_port=
    m_config.LoadConfigFile(config_file.c_str());
    // 测试
    // std::cout << "rpcserver_ip: " << m_config.Load("rpcserverip") << std::endl;
    // std::cout << "rpcserver_port: " << m_config.Load("rpcserverport") << std::endl;
    // std::cout << "zookeeper_ip: " << m_config.Load("zookeeperip") << std::endl;
    // std::cout << "zookeeper_port: " << m_config.Load("zookeeperport") << std::endl;
}

MprpcApplication& MprpcApplication::GetInstance()
{
    static MprpcApplication app;
    return app;
}

MprpcConfig& MprpcApplication::GetMprpcConfig()
{
    return m_config;
}