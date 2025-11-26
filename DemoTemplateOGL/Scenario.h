#ifndef GRAPHICSRR_H
#define GRAPHICSRR_H

#ifdef _WIN32 
#include <windows.h>
#include <windowsx.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include "Base/camera.h"
#include "Base/Billboard.h"
#include "Base/BillboardAnimation.h"
#include <iostream>
#include "Base/Scene.h"
#include "Texto.h"
#include "Billboard2D.h"
#include "CollitionBox.h"
#include "DOGENEMY.h"
#include "KidFox.h"

class Scenario : public Scene {
private:
	SkyDome* sky;
	SkyDome* ball;
	Terreno* terreno;
	std::vector<Billboard*> billBoard;
	std::vector<BillboardAnimation*> billBoardAnim;
	std::vector<Billboard2D*> billBoard2D;
	std::vector<Model*> ourModel;
	Model* camara;
	Water* water;
	float angulo;
	float animacion = 0;
	std::vector<Texto*> ourText;

	std::vector<DogEnemy*> dogsvector;
	std::vector<KidFox*> kitsvector;
public:
	// Example: At file scope or as Scenario class members
	float carBPosX = -180.0f; // Start position
	float carRPosX = carBPosX + carROffset;
	float carTPosX = carBPosX + carROffset + carTOffset;

	float carBSpeed = 0.5f;   // Units per frame
	float carBFixedZ = -140.0f; // The z position of the road

	float carROffset = 35.0f; // Offset between carB and carR
	float carTOffset = 70.0f; // Offset between carB and carT

	Model* carB = nullptr;    // Pointer to your carB model
	Model* carR = nullptr;    // Pointer to your carR model
	Model* carT = nullptr;    // Pointer to your carT model

	float dogEnemyPosY;

	float duckOrbitAngle = 0.0f;
	float duckOrbitSpeed = 2.5f; // radians per second
	float duckOrbitRadius = 4.0f; // distance from center
	glm::vec3 duckOrbitCenter = glm::vec3(-123.0f, 7.5f, 118.0f); // set as desired
	float orbitY = duckOrbitCenter.y;

	Scenario(Camera *cam);
	Scenario(Model *camIni);

	//~Scenario();
	void InitGraph(Model *main);

	void inicializaBillboards();


	//el metodo render toma el dispositivo sobre el cual va a dibujar
	//y hace su tarea ya conocida
	Scene* Render();

	
	std::vector<Model*> *getLoadedModels();
	std::vector<Billboard*> *getLoadedBillboards();
	std::vector<BillboardAnimation*> *getLoadedBillboardsAnimation();
	std::vector<Billboard2D*> *getLoadedBillboards2D();
	std::vector<Texto*> *getLoadedText();

	Model* getMainModel();
	void setMainModel(Model* mainModel);
	float getAngulo();
	void setAngulo(float angulo);
	SkyDome* getSky();
	Terreno* getTerreno();

	

//    void update() override;

	~Scenario();
};

#endif