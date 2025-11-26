#pragma once
#ifndef DOGENEMY_H
#define DOGENEMY_H

#include "base/model.h"
#include "Base/camera.h"
#include "Principal.h"
#include <glm/glm.hpp>
#include <cstdlib>
#include <ctime>
#include <string>

class DogEnemy : public Model {
private:
    float localTime = 0.0f;
    float attackTimer = 0.0f;
    float nextAttackTime = 0.0f;
    bool attacking = false;

    //std::string modelTypeD;

    glm::vec3 targetPosition;
    glm::vec3 baseAltitude = glm::vec3(0, 0, 0); // altura típica
    float alturaInicial = 3.0f;

    void setup();

public:
    // Constructores LIMPIOS que solo llaman setup()
    DogEnemy(string const& path, Camera* camera, bool rotationX = false, bool rotationY = true, bool gamma = false) 
        : Model(path, camera, rotationX, rotationY, gamma)
    {
		setup();
    }
    DogEnemy(vector<Vertex>& vertices, unsigned int numVertices, vector<unsigned int>& indices, unsigned int numIndices, Camera* camera) 
        : Model(vertices, numVertices, indices, numIndices, camera)
    {
        setup();
    }
    DogEnemy(string const& path, glm::vec3& actualPosition, Camera* cam, bool rotationX = false, bool rotationY = true, bool gamma = false)
        : Model(path, actualPosition, cam, rotationX, rotationY, gamma)
    {
        setup();
    }
	DogEnemy() : Model()
	{
		setup();
	}
    // UPDATE FINAL
    //const std::string& getModelTypeD() const { return modelTypeD; }

    void update(float deltaTime, const glm::vec3& playerPos, bool playerQuieto);
};
#endif