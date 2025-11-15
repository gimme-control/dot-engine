#pragma once 

#include "glad/glad.h"
#include <string> 
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 

class Shader 
{
public: 
    unsigned int ID; 
    Shader(std::string vertexPath, std::string fragmentPath)
    {
         
        std::ifstream vertFile(vertexPath);
        std::ifstream fragFile(fragmentPath);
        if(!vertFile.is_open() || !fragFile.is_open())
        {
            std::cout << "ERROR::SHADER_FILE_PATH_INCORRECT" << "\n";
        }

        std::string vShader; 
        std::string fShader; 
        std::string line; 

        while(std::getline(vertFile, line))
        {
            vShader += line;         
            vShader += '\n';
        }

        while(std::getline(fragFile, line))
        {
            fShader += line;         
            fShader += '\n';
        }
        
        const char* vShaderCode = vShader.c_str(); 
        const char* fShaderCode = fShader.c_str(); 

        vertFile.close(); 
        fragFile.close(); 

        unsigned int vertex, fragment; 

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL); 
        glCompileShader(vertex); 

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);

        // shader program 
        ID = glCreateProgram(); 

        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);

        glDeleteShader(vertex);
        glDeleteShader(fragment);

    }

    void use()
    {
        glUseProgram(ID);
    }
    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
    }
    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);

    }
    void setFloat(const std::string &name, float value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setMat4(unsigned int loc, glm::mat4 value) const
    {
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
    }
}; 

