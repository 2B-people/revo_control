#pragma once

#include <serial/serial.h>

#include <cstring>
#include <iostream>
#include <map>
#include <vector>

#define REVO_JASON_BEGIN 0xaa
#define REVO_JASON_END 0xf4

#define REVO_PROTOCOL_VERSION 1

namespace revo
{

    class RevoJason
    {

    public:
        RevoJason(/* args */);
        ~RevoJason();

        int init();
        // 按照文档的，四种模式，通过write的重载实现，read应该只有一种模式，但这里保留了重载
        template <typename T>
        int read(short &motor_id, T &value);
        template <typename T>
        // 写的时候做个const保护
        int write(short &motor_id, const T &value);
        // 计划用于调用电机的状态切换，输入应该包括电机id和状态请求
        int call(short &motor_id, const short &status);

    private:
        /* data */
        std::map<int32_t, short> revo_motor_map_;
        // 类型还不确定,用于打包和解包一帧数据
        int encodePacket();
        int decodePacket();
    };

} // namespace revo
