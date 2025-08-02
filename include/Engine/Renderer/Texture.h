#pragma once

#include <string>

class Texture
{

public:
    Texture(){}
    Texture(const std::string& filepath);
    ~Texture();

    void Create(const std::string& filepath);
    void Bind(unsigned int slot = 0);
    void Unbind();

private:
    unsigned int ID;
    unsigned int width, height, BPP;
    std::string filepath;
    unsigned char* localBuffer;

};