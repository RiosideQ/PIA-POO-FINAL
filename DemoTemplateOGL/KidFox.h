#pragma once
#include "base/model.h"
#include "Base/camera.h"
#include "Principal.h"
#include <glm/glm.hpp>
#include <cstdlib>
#include <ctime>
#include <string>

class KidFox : public Model {
private:
	bool inventory = false;//contenedor
	bool picked = false;//recogido
public:
	KidFox(const std::string& path, Camera* cam);
	KidFox(const std::string& path, Camera* cam, glm::vec3* posInicial);

	void setInventory(bool flag) { inventory = flag; }
	bool isInventory() const { return inventory;  }

	void setPicked(bool flag) { picked = flag; }
	bool isPicked() const { return picked; }

};
