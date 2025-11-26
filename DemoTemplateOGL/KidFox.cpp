#include "KidFox.h"

KidFox::KidFox(const std::string& path, Camera* cam) : Model(path, cam) {
	inventory = false;
	picked = false;
}

KidFox::KidFox(const std::string& path, Camera* cam, glm::vec3* posInicial) : Model(path, cam) {
	inventory = false;
	picked = false;

	setTranslate(posInicial);
	setNextTranslate(posInicial);
}