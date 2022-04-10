#ifndef TEXTURESERVICE_H
#define TEXTURESERVICE_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "stb_image.h"

using namespace std;

class TextureService
{
public:

	TextureService();

	unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false, bool invert = false);

};

#endif