#include "Scenario1.h"
#ifdef __linux__ 
#define ZeroMemory(x,y) memset(x,0,y)
#define wcscpy_s(x,y,z) wcscpy(x,z)
#define wcscat_s(x,y,z) wcscat(x,z)
#endif

Scenario1::Scenario1(Camera* cam) { // Initialize directory here
	glm::vec3 translate;
	glm::vec3 scale;
	Model* model = new Model("models/Cube/Cube.obj", cam);
	translate = glm::vec3(0.0f, 0.0f, 3.0f);
	scale = glm::vec3(0.25f, 0.25f, 0.25f);	// it's a bit too big for our scene, so scale it down
	model->setScale(&scale);
	model->setTranslate(&translate);
	model->setNextTranslate(&translate);
	InitGraph(model);

}
Scenario1::Scenario1(Model* camIni) {
	InitGraph(camIni);
}
void Scenario1::InitGraph(Model* main) {
	
	float matAmbient[] = { 1,1,1,1 };
	float matDiff[] = { 1,1,1,1 };
	angulo = 0;
	camara = main;
	//creamos el objeto skydome
	sky = new SkyDome(32, 32, 20, (WCHAR*)L"skydome/SkyboxDirt.png", main->cameraDetails);
	//ball = new SkyDome(5, 5, 10, (WCHAR*)L"skydome/ELLIOT.png", main->cameraDetails);
	//creamos el terreno
	terreno = new Terreno((WCHAR*)L"skydome/terrenoCave.jpg", (WCHAR*)L"skydome/DirtTile.jpg", 400, 400, main->cameraDetails);
	water = new Water((WCHAR*)L"textures/terreno.bmp", (WCHAR*)L"textures/water.bmp", 20, 20, camara->cameraDetails);
	glm::vec3 translate;
	glm::vec3 scale;
	glm::vec3 rotation;
	translate = glm::vec3(0.0f, 20.0f, 30.0f);
	water->setTranslate(&translate);
	// load models
	// -----------
	ourModel.emplace_back(main);


	Model* Dug = new Model("models/Nature/DugDirt.fbx", main->cameraDetails);
	//Model* Dug = new Model("models/backpack/backpack.obj", main->cameraDetails, false, false);
	translate = glm::vec3(156.0f, terreno->Superficie(156.0f, 107.0f) + 2, 107.0f);
	Dug->setNextTranslate(&translate);
	Dug->setTranslate(&translate);
	Dug->setNextRotX(-90); // 45� rotation
	Dug->setNextRotZ(45); // 45� rotation
	scale = glm::vec3(2.7f, 2.7f, 2.7f);	// it's a bit too big for our scene, so scale it down
	Dug->setScale(&scale);
	Dug->setModelType("Dug2");
	Dug->name = "Dug2";
	ourModel.emplace_back(Dug);

	Model* Kit2 = new Model("models/animals/SleepingFox.fbx", main->cameraDetails);
	translate = glm::vec3(-55.0f, 12.0f, 35.0f);//(x,y,z) (←,↑,↑)
	Kit2->setTranslate(&translate);
	Kit2->setNextTranslate(&translate);
	//rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation X
	Kit2->setNextRotY(180); // 45� rotation
	scale = glm::vec3(0.03f, 0.03f, 0.03f);	// it's a bit too big for our scene, so scale it down
	Kit2->setScale(&scale);
	Kit2->setModelType("KIT2");
	Kit2->name = "KIT2";
	ourModel.emplace_back(Kit2);
	
	
	// Randomly place rocks
	int numrock1s = 30; // Number of rock1s to spawn
	float minX = -180.0f, maxX = 180.0f;
	float minZ = -180.0f, maxZ = 180.0f;
	float yOffset = -0.1f; // Adjust as needed for your terrain

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distX(minX, maxX);
	std::uniform_real_distribution<float> distZ(minZ, maxZ);

	for (int i = 0; i < numrock1s; ++i) {
		float x = distX(gen);
		float z = distZ(gen);
		float y = terreno->Superficie(x, z) + yOffset; // Use terrain height if available

		Model* rock1Clone = new Model("models/Cave/ROCK_SET_MESH.fbx", main->cameraDetails);
		glm::vec3 rock1Pos(x, y, z);
		rock1Clone->setTranslate(&rock1Pos);
		rock1Clone->setNextTranslate(&rock1Pos);
		//rock1Clone->setNextRotX(-90);

		// Remove hitbox if needed
		rock1Clone->getModelAttributes()->at(0).hitbox = NULL;
		ourModel.emplace_back(rock1Clone);
	}

	int numrock2s = 30; // Number of rock2s to spawn

	for (int i = 0; i < numrock2s; ++i) {
		float x = distX(gen);
		float z = distZ(gen);
		float y = terreno->Superficie(x, z) + yOffset; // Use terrain height if available

		Model* rock2Clone = new Model("models/Cave/ROCK_MESH_01.fbx", main->cameraDetails);
		glm::vec3 rock2Pos(x, y, z);
		rock2Clone->setTranslate(&rock2Pos);
		rock2Clone->setNextTranslate(&rock2Pos);
		//rock2Clone->setNextRotX(-90);

		// Remove hitbox if needed
		rock2Clone->getModelAttributes()->at(0).hitbox = NULL;
		ourModel.emplace_back(rock2Clone);
	}

	int numrock3s = 30; // Number of rock3s to spawn


	for (int i = 0; i < numrock3s; ++i) {
		float x = distX(gen);
		float z = distZ(gen);
		float y = terreno->Superficie(x, z) + yOffset; // Use terrain height if available

		Model* rock3Clone = new Model("models/Cave/ROCK_MESH_06.fbx", main->cameraDetails);
		glm::vec3 rock3Pos(x, y, z);
		rock3Clone->setTranslate(&rock3Pos);
		rock3Clone->setNextTranslate(&rock3Pos);
		//rock3Clone->setNextRotX(-90);

		// Remove hitbox if needed
		rock3Clone->getModelAttributes()->at(0).hitbox = NULL;
		ourModel.emplace_back(rock3Clone);
	}

	/*
	Model* model;
	model = new Model("models/fogata/fogata.obj", main->cameraDetails);
	translate = glm::vec3(0.0f, 10.0f, 25.0f);
	model->setTranslate(&translate);
	model->setNextTranslate(&translate);
	rotation = glm::vec3(1.0f, 0.0f, 0.0f); //rotation X
	model->setNextRotX(45); // 45� rotation
	ourModel.emplace_back(model);

	Model* pez = new Model("models/pez/pez.obj", main->cameraDetails);
	translate = glm::vec3(0.0f, terreno->Superficie(0.0f, 50.0f), 50.0f);
	pez->setNextTranslate(&translate);
	pez->setTranslate(&translate);
	ourModel.emplace_back(pez);
	ModelAttributes m;
	m.setTranslate(&translate);
	m.setNextTranslate(&translate);
	m.translate.x = 5;
	model = CollitionBox::GenerateAABB(m.translate, pez->AABBsize, main->cameraDetails);
	model->setTranslate(&m.translate);
	model->setNextTranslate(&m.translate);
	m.hitbox = model;
	pez->getModelAttributes()->push_back(m);
	m.setTranslate(&translate);
	m.setNextTranslate(&translate);
	m.translate.x = 10;
	model = CollitionBox::GenerateAABB(m.translate, pez->AABBsize, main->cameraDetails);
	model->setTranslate(&m.translate);
	model->setNextTranslate(&m.translate);
	m.hitbox = model; // Le decimos al ultimo ModelAttribute que tiene un hitbox asignado
	pez->getModelAttributes()->push_back(m);

	model = new Model("models/dancing_vampire/dancing_vampire.dae", main->cameraDetails);
	translate = glm::vec3(0.0f, terreno->Superficie(0.0f, 60.0f), 60.0f);
	scale = glm::vec3(0.02f, 0.02f, 0.02f);	// it's a bit too big for our scene, so scale it down
	model->setTranslate(&translate);
	model->setNextTranslate(&translate);
	model->setScale(&scale);
	model->setNextRotY(90);
	ourModel.emplace_back(model);
	try {
		std::vector<Animation> animations = Animation::loadAllAnimations("models/dancing_vampire/dancing_vampire.dae", model->GetBoneInfoMap(), model->getBonesInfo(), model->GetBoneCount());
		std::vector<Animation> animation = Animation::loadAllAnimations("models/dancing_vampire/dancing_vampire.dae", model->GetBoneInfoMap(), model->getBonesInfo(), model->GetBoneCount());
		std::move(animation.begin(), animation.end(), std::back_inserter(animations));
		for (Animation animation : animations)
			model->setAnimator(Animator(animation));
		model->setAnimation(1);
	}
	catch (...) {
		ERRORL("Could not load animation!", "ANIMACION");
	}

	Model* silly = new Model("models/Silly_Dancing/Silly_Dancing.fbx", main->cameraDetails);
	translate = glm::vec3(10.0f, terreno->Superficie(10.0f, 60.0f), 60.0f);
	scale = glm::vec3(0.02f, 0.02f, 0.02f);	// it's a bit too big for our scene, so scale it down
	silly->setTranslate(&translate);
	silly->setNextTranslate(&translate);
	silly->setScale(&scale);
	silly->setNextRotY(180);
	ourModel.emplace_back(silly);
	try {
		std::vector<Animation> animations = Animation::loadAllAnimations("models/Silly_Dancing/Silly_Dancing.fbx", silly->GetBoneInfoMap(), silly->getBonesInfo(), silly->GetBoneCount());
		for (Animation animation : animations)
			silly->setAnimator(Animator(animation));
		silly->setAnimation(0);
	}
	catch (...) {
		ERRORL("Could not load animation!", "ANIMACION");
	}
	m.setTranslate(&translate);
	m.setNextTranslate(&translate);
	m.translate.x += 10;
	m.setScale(&scale);
	m.setNextRotY(180);
	m.setRotY(180);
	model = CollitionBox::GenerateAABB(m.translate, silly->AABBsize, main->cameraDetails);
	model->setTranslate(&m.translate);
	model->setNextTranslate(&m.translate);
	model->setScale(&scale);
	model->setNextRotY(180);
	model->setRotY(180);
	m.hitbox = model; // Le decimos al ultimo ModelAttribute que tiene un hitbox asignado
	silly->getModelAttributes()->push_back(m);
	// Import model and clone with bones and animations
	model = new Model("models/Silly_Dancing/Silly_Dancing.fbx", main->cameraDetails);
	translate = glm::vec3(30.0f, terreno->Superficie(30.0f, 60.0f), 60.0f);
	scale = glm::vec3(0.02f, 0.02f, 0.02f);	// it's a bit too big for our scene, so scale it down
	model->name = "Silly_Dancing1";
	model->setTranslate(&translate);
	model->setNextTranslate(&translate);
	model->setScale(&scale);
	model->setNextRotY(180);
	ourModel.emplace_back(model);
	// Para clonar la animacion se eliminan los huesos del modelo actual y se copian los modelos y animators
	model->GetBoneInfoMap()->clear();
	model->getBonesInfo()->clear();
	*model->GetBoneInfoMap() = *silly->GetBoneInfoMap();
	*model->getBonesInfo() = *silly->getBonesInfo();
	model->setAnimator(silly->getAnimator());

	//	model = new Model("models/IronMan.obj", main->cameraDetails);
//	translate = glm::vec3(0.0f, 20.0f, 30.0f);
//	scale = glm::vec3(0.025f, 0.025f, 0.025f);	// it's a bit too big for our scene, so scale it down
//	model->setScale(&scale);
//	model->setTranslate(&translate);
//	ourModel.emplace_back(model);
	model = new Model("models/backpack/backpack.obj", main->cameraDetails, false, false);
	translate = glm::vec3(20.0f, terreno->Superficie(20.0f, 0.0f) + 2, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);	// it's a bit too big for our scene, so scale it down
	model->setTranslate(&translate);
	model->setNextTranslate(&translate);
	model->setScale(&scale);
	ourModel.emplace_back(model);
	model->lightColor = glm::vec3(10, 0, 0);
	model = new CollitionBox(60.0f, 15.0f, 10.0f, 10, 10, 10, main->cameraDetails);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);	// it's a bit too big for our scene, so scale it down
	model->setNextTranslate(model->getTranslate());
	model->setScale(&scale);
	ourModel.emplace_back(model);
	*/

	inicializaBillboards();
	std::wstring prueba(L"Esta es una prueba");
	ourText.emplace_back(new Texto(prueba, 20, 0, 0, SCR_HEIGHT, 0, camara));

	/*/for (int i = 0; i < 350; i++) {

		float x = (rand() % 800) - 400;
		float z = (rand() % 800) - 400;
		float y = (rand() % 200) + 50;
		//Billboard* gota = new Billboard((WCHAR*)L"textures/Gota.png", 0.7f, 1.3f, x, y, z, camara->cameraDetails);
		//lluviaBillboards.push_back(gota);
		lluviaBillboards.push_back(new Billboard((WCHAR*)L"textures/Gota.png", 0.7f, 1.3f, x, y, z, camara->cameraDetails));
	}*/

	
	// Add more frames as needed

	billBoard2D.emplace_back(new Billboard2D((WCHAR*)L"textures/Clues.png", 6, 6, 570, 0, 0, camara->cameraDetails));
	scale = glm::vec3(225.0f, 225.0f, 0.0f);	// it's a bit too big for our scene, so scale it down
	billBoard2D.back()->setScale(&scale);


	/*billBoard2D.emplace_back(new Billboard2D((WCHAR*)L"billboards/Dust3.png", 600, 600, 0, 0, 0, camara->cameraDetails));
	scale = glm::vec3(1000.0f, 1000.0f, 0.0f);	// it's a bit too big for our scene, so scale it down
	billBoard2D.back()->setScale(&scale);*/
}

void Scenario1::updateDustAnimation(float deltaTime) {
	dustFrameTimer += deltaTime;
	if (dustFrameTimer >= dustFrameDuration) {
		dustFrameTimer = 0.0f;
		dustFrame = (dustFrame + 1) % dustFrames.size();

		// Remove the old billboard
		if (!billBoard2D.empty()) {
			delete billBoard2D.back();
			billBoard2D.pop_back();
		}

		// Add the new frame
		billBoard2D.emplace_back(new Billboard2D(
			(WCHAR*)dustFrames[dustFrame].c_str(),
			600, 600, 0, 0, 0, camara->cameraDetails));
		glm::vec3 scale = glm::vec3(1000.0f, 1000.0f, 0.0f);
		billBoard2D.back()->setScale(&scale);
	}
}


void Scenario1::inicializaBillboards() {
	/*float ye = terreno->Superficie(0, 0);
	billBoard.emplace_back(new Billboard((WCHAR*)L"billboards/Arbol.png", 6, 6, 0, ye - 1, 0, camara->cameraDetails));

	ye = terreno->Superficie(-9, -15);
	billBoard.emplace_back(new Billboard((WCHAR*)L"billboards/Arbol3.png", 8, 8, -9, ye - 1, -15, camara->cameraDetails));

	BillboardAnimation* billBoardAnimated = new BillboardAnimation();
	ye = terreno->Superficie(5, -5);
	for (int frameArbol = 1; frameArbol < 5; frameArbol++) {
		wchar_t textura[50] = { L"billboards/baile" }; //CHANGE THE ANIMATION FILE NAME
		if (frameArbol != 1) {
			wchar_t convert[25];
			swprintf(convert, 25, L"%d", frameArbol);
			wcscat_s(textura, 50, convert);
		}
		wcscat_s(textura, 50, L".png");
		billBoardAnimated->pushFrame(new Billboard((WCHAR*)textura, 6, 6, 5, ye - 1, -5, camara->cameraDetails));
	}
	billBoardAnim.emplace_back(billBoardAnimated);
	*/

}

Scene* Scenario1::Render() {
	//borramos el biffer de color y el z para el control de profundidad a la 
	//hora del render a nivel pixel.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	//	glClearColor(255.0f, 255.0f, 255.0f, 255.0f);

	if (this->animacion > 10) { // Timer se ejecuta cada 1000/30 = 33.333 ms
		for (BillboardAnimation* b : billBoardAnim) {
			b->nextAnimation();
		}
		this->animacion = 0;
	}
	else {
		animacion = animacion + (1 * gameTime.deltaTime / 100);
	}

	updateDustAnimation(gameTime.deltaTime / 1000.0f); // Convert ms to seconds if needed


	// Decimos que dibuje la media esfera
	sky->Draw();
	// Ahora el terreno
	terreno->Draw();

	//water->Draw();
	// Dibujamos cada billboard que este cargado en el arreglo de billboards.
	for (int i = 0; i < billBoard.size(); i++)
		billBoard[i]->Draw();
	for (int i = 0; i < billBoardAnim.size(); i++)
		billBoardAnim[i]->Draw();
	for (int i = 0; i < billBoard2D.size(); i++)
		billBoard2D[i]->Draw();
	// Dibujamos cada modelo que este cargado en nuestro arreglo de modelos
	for (int i = 0; i < ourModel.size(); i++) {
		ourModel[i]->Draw();
	}
	for (int i = 0; i < ourText.size(); i++) {
		ourText[i]->Draw();
	}

	/*for (auto* gota : lluviaBillboards) {
		gota->Draw();
	}*/



	// Le decimos a winapi que haga el update en la ventana
	return this;
}



std::vector<Model*>* Scenario1::getLoadedModels() {
	return &ourModel;
}
std::vector<Billboard*>* Scenario1::getLoadedBillboards() {
	return &billBoard;
}
std::vector<Billboard2D*>* Scenario1::getLoadedBillboards2D() {
	return &billBoard2D;
}
std::vector<Texto*>* Scenario1::getLoadedText() {
	return &ourText;
}
std::vector<BillboardAnimation*>* Scenario1::getLoadedBillboardsAnimation() {
	return &billBoardAnim;
}

Model* Scenario1::getMainModel() {
	return this->camara;
}
void Scenario1::setMainModel(Model* mainModel) {
	this->camara = mainModel;
}
float Scenario1::getAngulo() {
	return this->angulo;
}
void Scenario1::setAngulo(float angulo) {
	this->angulo = angulo;
}
SkyDome* Scenario1::getSky() {
	return sky;
}
Terreno* Scenario1::getTerreno() {
	return terreno;
}

Scenario1::~Scenario1() {
	/*if (dustAnim) {
		delete dustAnim;
		dustAnim = nullptr;
	}*/

	if (this->sky != NULL) {
		delete this->sky;
		this->sky = NULL;
	}
	if (this->terreno != NULL) {
		delete this->terreno;
		this->terreno = NULL;
	}
	if (billBoard.size() > 0)
		for (int i = 0; i < billBoard.size(); i++)
			delete billBoard[i];
	if (billBoardAnim.size() > 0)
		for (int i = 0; i < billBoardAnim.size(); i++)
			delete billBoardAnim[i];
	if (billBoard2D.size() > 0)
		for (int i = 0; i < billBoard2D.size(); i++)
			delete billBoard2D[i];
	this->billBoard.clear();
	if (ourText.size() > 0)
		for (int i = 0; i < ourText.size(); i++)
			if (!(ourText[i]->name.compare("FPSCounter") || ourText[i]->name.compare("Coordenadas")))
				delete ourText[i];
	this->ourText.clear();
	if (ourModel.size() > 0)
		for (int i = 0; i < ourModel.size(); i++)
			if (ourModel[i] != camara)
				delete ourModel[i];
	this->ourModel.clear();
}
