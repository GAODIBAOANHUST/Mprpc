#pragma once

#include <google/protobuf/service.h>
#include <string>

class MprpcController : public ::google::protobuf::RpcController
{
public:
    MprpcController();

    virtual void Reset() override;
    virtual bool Failed() const override;
    virtual std::string ErrorText() const override;
    virtual void SetFailed(const std::string& reason) override;

    // 目前未实现具体的功能
    virtual void StartCancel() override;
    virtual bool IsCanceled() const override;
    virtual void NotifyOnCancel(::google::protobuf::Closure* callback) override;
private:
    bool m_failed; // Rpc方法执行过程中
    std::string m_errText; // Rpc方法执行过程中的错误信息
};