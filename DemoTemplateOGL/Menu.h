#pragma once
#include "Billboard2D.h"
#include "Base/camera.h"

class Menu {
private:
	vector<Billboard2D*> billBoard2D;
	Camera* camDetails = NULL;
	Billboard2D* arrow;
	glm::vec3 menuOrigin = glm::vec3(0.0f, 0.0f, 0.0f); // Add this line

	void initMenu() {
		glm::vec3 scale2 = glm::vec3(75.0f, 75.0f, 0.0f);	// it's a bit too big for our scene, so scale it down
		billBoard2D.emplace_back(new Billboard2D((WCHAR*)L"textures/WoodDia.png",
			6, 6, 175, 175, 0, camDetails));//play = 175,175 - exit = 175, 320
		billBoard2D.back()->setScale(&scale2);
		arrow = billBoard2D.back();
		glm::vec3 scale = glm::vec3(300.0f, 300.0f, 0.0f);	// it's a bit too big for our scene, so scale it down
		billBoard2D.emplace_back(new Billboard2D((WCHAR*)L"textures/WoodMenu.png",
			6, 6, 250, 150, 0, camDetails));
		billBoard2D.back()->setScale(&scale);
		
	}
public:
	Menu(Camera* cam, glm::vec3 origin = glm::vec3(0.0f, 0.0f, 0.0f)) { // Add origin parameter
		camDetails = cam;

		menuOrigin = origin;// add
		initMenu();
	}
	void setMenuOrigin(const glm::vec3& origin) { // Optional: to move menu later
		menuOrigin = origin;
	}
	void Update(int opc) {
		glm::vec3 trans;
		switch (opc) {
		case 1:trans = glm::vec3(175, 175, 0);
			break;
		case 2:trans = glm::vec3(175, 320, 0);
			break;
		}
		arrow->setTranslate(&trans);
	}
	void Draw() {
		for (auto *b : billBoard2D)
			b->Draw();
	}
};