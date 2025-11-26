#include "DOGENEMY.h"
#include <glm/gtc/random.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/matrix_transform.hpp>

void DogEnemy::setup() {
    // tiempo base
    nextAttackTime = 3.0f + rand() % 5;

    // NO movemos la posición porque Scene la define

    glm::vec3 vel(0.0f, 0.0f, 0.05f);
    setVelocity(&vel);

    // rotación inicial basada en velocidad
    float rotY = atan2(vel.x, vel.z);
    setRotY(glm::degrees(rotY));
    setNextRotY(glm::degrees(rotY));
}

void DogEnemy::update(float deltaTime, const glm::vec3& playerPos, bool playerQuieto) {
    localTime += deltaTime;

    glm::vec3* pos = getTranslate();
    glm::vec3* vel = getVelocity();
    if (!pos || !vel) return;

    // Movimiento normal
    *pos += (*vel)*deltaTime;
    pos->y = baseAltitude.y;

    // Rotación según velocidad
    if (glm::length(*vel) > 0.001f) {
        float rotY = atan2(-vel->x, -vel->z);
        setRotY(glm::degrees(rotY)-180);
        setNextRotY(glm::degrees(rotY)-180);
    }

    // Decidir ataque
    if (!attacking && localTime > nextAttackTime) {
        attacking = true;
        targetPosition = playerPos;
        attackTimer = 3.0f; // dura 3 segundos el intento
        localTime = 0.0f;
        nextAttackTime = 5.0f + static_cast<float>(rand() % 5);
    }

    if (attacking) {
        attackTimer -= deltaTime;

        glm::vec3 dir = targetPosition - *pos;
        if (glm::length(dir) > 0.01f) {
            dir = glm::normalize(dir);
            *vel = dir * 6.0f; // velocidad hacia jugador
        }

        // Colisión si jugador quieto y cerca
        if (playerQuieto && glm::distance(*pos, playerPos) < 1.0f) {
            INFO("¡Te mordio el canino!", "WOOF");
            attacking = false;
        }

        if (attackTimer <= 0.0f) {
            attacking = false;
        }
    }

    setTranslate(pos);
    setNextTranslate(pos);
}