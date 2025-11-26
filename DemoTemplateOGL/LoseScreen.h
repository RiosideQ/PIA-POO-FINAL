#pragma once
#include "Billboard2D.h"
#include "Base/camera.h"

class LoseScreen {
private:
	vector<Billboard2D*> billBoard2D;
	Camera* camDetails = NULL;
	Billboard2D* arrow;
	void initLoseScreen() {
		glm::vec3 scale = glm::vec3(740.0f, 253.0f, 0.0f);	// it's a bit too big for our scene, so scale it down
		billBoard2D.emplace_back(new Billboard2D((WCHAR*)L"textures/YouLose.png",
			6, 6, 30, 135, 0, camDetails));;
		billBoard2D.back()->setScale(&scale);

	}
public:
	LoseScreen(Camera* cam) {
		camDetails = cam;
		initLoseScreen();
	}
	void Update(int opc) {
		glm::vec3 trans;
		switch (opc) {
		case 1:trans = glm::vec3(75, 75, 0);
			break;
		}
	}
	void Draw() {
		for (auto* b : billBoard2D)
			b->Draw();
	}
};
