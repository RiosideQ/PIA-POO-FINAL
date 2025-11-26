#pragma once
#include "Base/model.h"
#include "Billboard2D.h"

/*class Dust : public Model {
public:
    std::vector<std::wstring> dustTextures = {
    L"billboards/Dust.png",
    L"billboards/Dust2.png",
    L"billboards/Dust3.png"
    };
    int currentDustFrame = 0;
    float dustFrameTimer = 0.0f;
    float dustFrameDuration = 1.0f; // seconds per frame
};*/
#pragma once
#include "Base/model.h"
#include "Billboard2D.h"

class Dust : public Model {
public:
	vector<Billboard2D*> dustys;
	Dust(string const& path, Camera* camera, bool rotationX = false, bool rotationY = true, bool gamma = false)
		: Model(path, camera, rotationX, rotationY, gamma) {
		setDust(); //setDust = asignardustys
	}
	Dust(vector<Vertex>& vertices, unsigned int numVertices, vector<unsigned int>& indices, unsigned int numIndices, Camera* camera)
		: Model(vertices, numVertices, indices, numIndices, camera) {
		setDust();
	}
	Dust(string const& path, glm::vec3& actualPosition, Camera* cam, bool rotationX = false, bool rotationY = true, bool gamma = false) : Model(path, actualPosition, cam, rotationX, rotationY, gamma) {
		setDust();
	}
	Dust() : Model() {
		setDust();
	}
	void setDust() {
		dustys.push_back(new Billboard2D((WCHAR*)L"billboards/Dust3.png", 600, 600, 50, 50, 50, this->cameraDetails));
		glm::vec3 scale = glm::vec3(100.0f, 100.0f, 0.0f);
		dustys.back()->setScale(&scale);
	}
	void updateDustEffect(bool isInCave) {
        /*if (isInCave) {
            if (dustys.empty()) {
                dustys.push_back(new Billboard2D((WCHAR*)L"billboards/Dust3.png", 600, 600, 50, 50, 50, this->cameraDetails));
                glm::vec3 scale = glm::vec3(100.0f, 100.0f, 0.0f);
                dustys.back()->setScale(&scale);
            }
        } else {
            // Remove and delete all dustys
            for (auto* d : dustys) {
                delete d;
            }
            //dustys.clear();
        }*/
        if (isInCave) {
			//INFO("Adding dust effect", "Dust effect activated");
        }
		else {
			INFO("Removing dust effect", "Dust effect deactivated");
		}
    }

	void Draw() {
		for (Billboard2D* dusty : dustys)
			dusty->Draw();
		Model::Draw();
	}
};
