#include "object.h"

#include <fstream>
#include <iostream>

/* Helper function from https://gist.github.com/JISyed/7837265 */
const char* ReadShaderFileToMemory(const char* filePath)
{
	const char * shaderFileBuffer = NULL;

	std::ifstream inSdrFileStream(filePath);
	if(inSdrFileStream)
	{
		// Get length of shader file by seeking and telling (offset of 0)
		inSdrFileStream.seekg(0, inSdrFileStream.end);
		unsigned long fileLength = (unsigned long) inSdrFileStream.tellg() + 1;
		inSdrFileStream.seekg(0, inSdrFileStream.beg);

		// Read shader file into a memory buffer (array)
		char * inputFileBuffer = new char[fileLength];
		memset(inputFileBuffer, 0, fileLength);
		inSdrFileStream.read(inputFileBuffer, fileLength);
		inputFileBuffer[fileLength-1] = 0;

		// Hand over file contents to a const pointer
		shaderFileBuffer = inputFileBuffer;
		inputFileBuffer = NULL;
	}
	else
	{
		std::cout << "Shader File: Error. Not found!" << std::endl;
		return NULL;
	}

	return shaderFileBuffer;
}

namespace __game__ {
    cBush::cBush(double x, double z) {
        this->translation = vec3(x, 0, z);

        /* Front */
        addPoint(vec3(0, 0, 0), vec3(0, 0, 1));
        addPoint(vec3(0.3, 0, 0), vec3(0, 0, 1));
        addPoint(vec3(0.3, 0.3, 0), vec3(0, 0, 1));
        addPoint(vec3(0, 0.3, 0), vec3(0, 0, 1));
    	   
        /* Back */
        addPoint(vec3(0, 0, -0.3), vec3(0, 0, -1));
        addPoint(vec3(0, 0.3, -0.3), vec3(0, 0, -1));
        addPoint(vec3(0.3, 0.3, -0.3), vec3(0, 0, -1));
        addPoint(vec3(0.3, 0, -0.3), vec3(0, 0, -1));
    	   
        /* Top */
        addPoint(vec3(0, 0.3, 0), vec3(0, 1, 0));
        addPoint(vec3(0.3, 0.3, 0), vec3(0, 1, 0));
        addPoint(vec3(0.3, 0.3, -0.3), vec3(0, 1, 0));
        addPoint(vec3(0, 0.3, -0.3), vec3(0, 1, 0));

        /* Bottom */
        addPoint(vec3(0, 0, 0), vec3(0, -1, 0));
        addPoint(vec3(0, 0, -0.3), vec3(0, -1, 0));
        addPoint(vec3(0.3, 0, -0.3), vec3(0, -1, 0));
        addPoint(vec3(0.3, 0, 0), vec3(0, -1, 0));

        /* Left */
        addPoint(vec3(0, 0.3, -0.3), vec3(0, -1, 0));
        addPoint(vec3(0, 0, -0.3), vec3(0, -1, 0));
        addPoint(vec3(0, 0, 0), vec3(0, -1, 0));
        addPoint(vec3(0, 0.3, 0), vec3(0, -1, 0));

        /* Right */
        addPoint(vec3(0.3, 0, -0.3), vec3(-1, 0, 0));
        addPoint(vec3(0.3, 0.3, -0.3), vec3(-1, 0, 0));
        addPoint(vec3(0.3, 0.3, 0), vec3(-1, 0, 0));
        addPoint(vec3(0.3, 0, 0), vec3(-1, 0, 0));

        this->vertShader = glCreateShader(GL_VERTEX_SHADER);
        this->fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        
        const char* tempChar = ReadShaderFileToMemory("system/data/bushVert.glsl");
        int compiled;

        glShaderSource(
            this->vertShader,
            1, 
            &tempChar, NULL
            );
        glCompileShader(this->vertShader);
        glGetShaderiv(this->vertShader, GL_COMPILE_STATUS, &compiled);
        if (compiled == 0) {
            printf("Compilation error for vert shader \n");
            char buffer[1000];
            glGetShaderInfoLog(this->vertShader, 1000, NULL, buffer);
            printf("%s \n", buffer);
            abort();
        }

        tempChar = ReadShaderFileToMemory("system/data/bushFrag.glsl");
        glShaderSource(this->fragShader,
                       1,
                       &tempChar, NULL);
        glCompileShader(this->fragShader);
        glGetShaderiv(this->fragShader, GL_COMPILE_STATUS, &compiled);
        if (compiled == 0) {
            printf("Compilation error for fragment shader \n");
            char buffer[1000];
            glGetShaderInfoLog(this->vertShader, 1000, NULL, buffer);
            printf("%s \n", buffer);
            abort();
        }
        this->shaderProgram = glCreateProgram();
        glAttachShader(this->shaderProgram, this->vertShader);
        glAttachShader(this->shaderProgram, this->fragShader);
        glLinkProgram(this->shaderProgram);
        glValidateProgram(this->shaderProgram);
    }

    void cBush::setHeight(double h) {
        this->translation.y = h;
    }

    void cBush::render() {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        double mMat[16];
        glTranslated(this->translation.x, this->translation.y, this->translation.z);
        glRotated(this->rotation.z, 0, 0, 1);
        glRotated(this->rotation.y, 0, 1, 0);
        glRotated(this->rotation.x, 1, 0, 0);
        glScaled(this->scale, this->scale, this->scale);
        if (!hidden) {
            if(this->texID != 0) glBindTexture(GL_TEXTURE_2D, this->texID);
            glUseProgram(this->shaderProgram);
            glBegin(GL_QUADS);
            {
                for (auto p : this->points) {
                    glVertex3d(p.x, p.y, p.z);
                }
            }
            glEnd();
            glUseProgram(0);
            if(this->texID != 0) glBindTexture(GL_TEXTURE_2D, 0);
        }
        for (auto ch : this->children) {
            if (ch->getName() == "Camera") continue;
            ch->render();
        }
        glPopMatrix();
    }
}