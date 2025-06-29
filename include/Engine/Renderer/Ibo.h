#pragma once

#include <glad/glad.h>
#include <vector>

class Ibo{

public:
    Ibo();
    ~Ibo();
    void Create(std::vector<unsigned int> indices);
    void Bind()const;
    void Unbind()const;
    void Delete();
    unsigned int getID() const {return ID;}

private:
    unsigned int ID;


};