#pragma once
#include "Base/model.h"
#include "Billboard2D.h"

class Principal : public Model {
public:
	vector<Billboard2D*> vidas;
	Principal(string const& path, Camera* camera, bool rotationX = false, bool rotationY = true, bool gamma = false)
		: Model(path, camera, rotationX, rotationY, gamma) {
		asignarVidas();
	}
	Principal(vector<Vertex>& vertices, unsigned int numVertices, vector<unsigned int>& indices, unsigned int numIndices, Camera* camera)
		: Model(vertices, numVertices, indices, numIndices, camera) {
		asignarVidas();
	}
	Principal(string const& path, glm::vec3& actualPosition, Camera* cam, bool rotationX = false, bool rotationY = true, bool gamma = false) : Model(path, actualPosition, cam, rotationX, rotationY, gamma) {
		asignarVidas();
	}
	Principal() : Model() {
		asignarVidas();
	}
	void asignarVidas() {
		vidas.push_back(new Billboard2D((WCHAR*)L"textures/foxLife.png", 6, 6, 0, 0, 0, this->cameraDetails));
		glm::vec3 scale = glm::vec3(100.0f, 100.0f, 0.0f);
		vidas.back()->setScale(&scale);

		vidas.push_back(new Billboard2D((WCHAR*)L"textures/foxLife.png", 6, 6, 50, 0, 0, this->cameraDetails));
		scale = glm::vec3(100.0f, 100.0f, 0.0f);
		vidas.back()->setScale(&scale);


		vidas.push_back(new Billboard2D((WCHAR*)L"textures/foxLife.png", 6, 6, 100, 0, 0, this->cameraDetails));
		scale = glm::vec3(100.0f, 100.0f, 0.0f);
		vidas.back()->setScale(&scale);

		vidas.push_back(new Billboard2D((WCHAR*)L"textures/foxLife.png", 6, 6, 150, 0, 0, this->cameraDetails));
		scale = glm::vec3(100.0f, 100.0f, 0.0f);
		vidas.back()->setScale(&scale);
	}

	void Draw() {
		for (Billboard2D* vida : vidas)
			vida->Draw();
		Model::Draw();
	}
};
