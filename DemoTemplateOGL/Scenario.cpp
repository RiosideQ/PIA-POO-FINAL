#include "Scenario.h"
#include <random> 
#include <GLFW/glfw3.h>


#ifdef __linux__ 
#define ZeroMemory(x,y) memset(x,0,y)
#define wcscpy_s(x,y,z) wcscpy(x,z)
#define wcscat_s(x,y,z) wcscat(x,z)
#endif

Scenario::Scenario(Camera *cam) {
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
Scenario::Scenario(Model *camIni) {
	InitGraph(camIni);
}
void Scenario::InitGraph(Model *main) {
	 // Use clockwise as front face

	float matAmbient[] = { 1,1,1,1 };
	float matDiff[] = { 1,1,1,1 };
	angulo = 0;
	camara = main;
	//creamos el objeto skydome
	sky = new SkyDome(32, 32, 10, (WCHAR*)L"skydome/skybox.png", main->cameraDetails);
	//ball = new SkyDome(32,32, 10, (WCHAR*)L"skydome/ELLIOT.png", main->cameraDetails);
	//creamos el terreno
	terreno = new Terreno((WCHAR*)L"skydome/terrenoOverworld.png", (WCHAR*)L"skydome/texterr4.png", 400, 400, main->cameraDetails);
	water = new Water((WCHAR*)L"textures/terreno.bmp", (WCHAR*)L"textures/WaterT.bmp", 100, 100, camara->cameraDetails);
	glm::vec3 translate;
	glm::vec3 scale;
	glm::vec3 rotation;
	scale = glm::vec3(10.0f, 10.0f, 10.0f);	// it's a bit too big for our scene, so scale it down
	water->setScale(&scale);
	translate = glm::vec3(-140.0f, 7.9f, 130.0f);
	water->setTranslate(&translate);
	
	
	// load models
	// -----------
	ourModel.emplace_back(main);

	/*Model* cube = new Model("models/Cube/cube.obj", main->cameraDetails);
	translate = glm::vec3(0.0f, terreno->Superficie(10.0f, 100.0f), -10.0f);
	cube->setNextTranslate(&translate);
	cube->setTranslate(&translate);
	ourModel.emplace_back(cube);*/

	Model* Dug = new Model("models/Nature/DugDirt.fbx", main->cameraDetails);
	//Model* Dug = new Model("models/backpack/backpack.obj", main->cameraDetails, false, false);
	translate = glm::vec3(156.0f, terreno->Superficie(156.0f, 107.0f)+2, 107.0f);
	Dug->setNextTranslate(&translate);
	Dug->setTranslate(&translate);
	Dug->setNextRotX(-90); // 45� rotation
	Dug->setNextRotZ(45); // 45� rotation
	scale = glm::vec3(2.7f, 2.7f, 2.7f);	// it's a bit too big for our scene, so scale it down
	Dug->setScale(&scale);
	Dug->setModelType("Dug");
	Dug->name = "Dug";
	ourModel.emplace_back(Dug);

	Model* DuckMal;
	DuckMal = new Model("models/animals/DuckMallard.fbx", main->cameraDetails);
	translate = glm::vec3(18.0f, 13.0f, 25.0f);
	DuckMal->setTranslate(&translate);
	DuckMal->setNextTranslate(&translate);
	DuckMal->setNextRotX(-90); // 45� rotation
	scale = glm::vec3(0.7f, 0.7f, 0.7f);	// it's a bit too big for our scene, so scale it down
	DuckMal->setScale(&scale);
	DuckMal->name = "DuckMal";
	ourModel.emplace_back(DuckMal);

	Model* DuckYell;
	DuckYell = new Model("models/animals/DuckYellow.fbx", main->cameraDetails);
	translate = glm::vec3(20.0f, 12.5f, 25.0f);
	DuckYell->setTranslate(&translate);
	DuckYell->setNextTranslate(&translate);
	DuckYell->setNextRotX(-90); // 45� rotation
	scale = glm::vec3(0.7f, 0.7f, 0.7f);	// it's a bit too big for our scene, so scale it down
	DuckYell->setScale(&scale);
	DuckYell->name = "DuckYell";
	ourModel.emplace_back(DuckYell);

	/*Model* DuckWhite1;
	DuckWhite1 = new Model("models/animals/DuckWhite.fbx", main->cameraDetails);
	translate = glm::vec3(15.0f, 13.0f, 25.0f);
	DuckWhite1->setTranslate(&translate);
	DuckWhite1->setNextTranslate(&translate);
	DuckWhite1->setNextRotX(-90); // 45� rotation
	DuckWhite1->setNextRotZ(45); // 45� rotation
	scale = glm::vec3(0.7f, 0.7f, 0.7f);	// it's a bit too big for our scene, so scale it down
	DuckWhite1->setScale(&scale);
	ourModel.emplace_back(DuckWhite1);*/

	Model* DuckIdle = new Model("models/animals/DuckWhite_idle.fbx", main->cameraDetails);
	//translate = glm::vec3(10.0f, terreno->Superficie(0.0f, 80.0f), 25.0f);
	translate = glm::vec3(-83.0f, 9.5f, 107.0f);
	scale = glm::vec3(0.00032f, 0.00032f, 0.00032f);	// it's a bit too big for our scene, so scale it down
	DuckIdle->setTranslate(&translate);
	DuckIdle->setNextTranslate(&translate);
	DuckIdle->setScale(&scale);
	DuckIdle->setNextRotY(-135);
	ourModel.emplace_back(DuckIdle);
	try {
		std::vector<Animation> animations = Animation::loadAllAnimations("models/animals/DuckWhite_idle.fbx", DuckIdle->GetBoneInfoMap(), DuckIdle->getBonesInfo(), DuckIdle->GetBoneCount());
		std::vector<Animation> animation = Animation::loadAllAnimations("models/animals/DuckWhite_idle.fbx", DuckIdle->GetBoneInfoMap(), DuckIdle->getBonesInfo(), DuckIdle->GetBoneCount());
		std::move(animation.begin(), animation.end(), std::back_inserter(animations));
		for (Animation animation : animations)
			DuckIdle->setAnimator(Animator(animation));
		DuckIdle->setAnimation(1);
	}
	catch (...) {
		ERRORL("Could not load animation!", "ANIMACION");
	}




	/*Model* dog = new Model("models/animals/DogBase.fbx", main->cameraDetails);
	//translate = glm::vec3(28.0f, 12.5f, 25.0f);//(x,y,z)
	float dy = terreno->Superficie(28.0f, 25.0f);
	translate = glm::vec3(28.0f, dy, 25.0f);//(x,y,z)
	dog->setTranslate(&translate);
	dog->setNextTranslate(&translate);
	//rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation X
	//dog->setNextRotX(45); // 45� rotation
	scale = glm::vec3(0.2f, 0.2f, 0.20f);	// it's a bit too big for our scene, so scale it down
	dog->setScale(&scale);
	ourModel.emplace_back(dog);*/

	DogEnemy* dogE = new DogEnemy("models/animals/DogRun2.fbx", main->cameraDetails);
	glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.5f);
	dogE->setVelocity(&velocity);
	float dy = terreno->Superficie(118.0f, -75.0f);
	translate = glm::vec3(118.0f, dy, -75.0f);//(x,y,z)
	dogE->setTranslate(&translate);
	dogE->setNextTranslate(&translate);
	//rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation X
	//dogE->setNextRotY(-90); // 45� rotation
	//scale = glm::vec3(0.2f, 0.2f, 0.20f);	// it's a bit too big for our scene, so scale it down
	scale = glm::vec3(0.025f, 0.025f, 0.025f);	// it's a bit too big for our scene, so scale it down
	dogE->setScale(&scale);
	//dogE->setNextRotZ(45); // 45� rotation
	dogE->setModelType("dogEnemyMod");
	dogsvector.emplace_back(dogE); 
	ourModel.emplace_back(dogE);

	try {
		std::vector<Animation> animations = Animation::loadAllAnimations("models/animals/DogRun2.fbx", dogE->GetBoneInfoMap(), dogE->getBonesInfo(), dogE->GetBoneCount());
		std::vector<Animation> animation = Animation::loadAllAnimations("models/animals/DogRun2.fbx", dogE->GetBoneInfoMap(), dogE->getBonesInfo(), dogE->GetBoneCount());
		std::move(animation.begin(), animation.end(), std::back_inserter(animations));
		for (Animation animation : animations)
			dogE->setAnimator(Animator(animation));
		dogE->setAnimation(1);
	}
	catch (...) {
		ERRORL("Could not load animation!", "ANIMACION");
	}



	/*Model* cat = new Model("models/animals/Cat.fbx", main->cameraDetails);
	translate = glm::vec3(28.0f, 13.0f, 20.0f);//(x,y,z) (←,↑,↑)
	cat->setTranslate(&translate);
	cat->setNextTranslate(&translate);
	//rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation X
	cat->setNextRotY(180); // 45� rotation
	scale = glm::vec3(0.7f, 0.7f, 0.7f);	// it's a bit too big for our scene, so scale it down
	cat->setScale(&scale);
	ourModel.emplace_back(cat);*/

	Model* CatIdle = new Model("models/animals/Cat_idle.fbx", main->cameraDetails);
	//translate = glm::vec3(10.0f, terreno->Superficie(0.0f, 80.0f), 25.0f);
	translate = glm::vec3(92.0f, 29.0f, 185.0f);//(x,y,z) (←,↑,↑)
	scale = glm::vec3(0.00032f, 0.00032f, 0.00032f);	// it's a bit too big for our scene, so scale it down
	CatIdle->setTranslate(&translate);
	CatIdle->setNextTranslate(&translate);
	CatIdle->setScale(&scale);
	CatIdle->setNextRotY(90);
	CatIdle->getModelAttributes()->at(0).hitbox = NULL;
	ourModel.emplace_back(CatIdle);
	try {
		std::vector<Animation> animations = Animation::loadAllAnimations("models/animals/Cat_idle.fbx", CatIdle->GetBoneInfoMap(), CatIdle->getBonesInfo(), CatIdle->GetBoneCount());
		std::vector<Animation> animation = Animation::loadAllAnimations("models/animals/Cat_idle.fbx", CatIdle->GetBoneInfoMap(), CatIdle->getBonesInfo(), CatIdle->GetBoneCount());
		std::move(animation.begin(), animation.end(), std::back_inserter(animations));
		for (Animation animation : animations)
			CatIdle->setAnimator(Animator(animation));
		CatIdle->setAnimation(1);
	}
	catch (...) {
		ERRORL("Could not load animation!", "ANIMACION");
	}

	/*Model* Spider = new Model("models/animals/spiderWidow.fbx", main->cameraDetails);
	//translate = glm::vec3(10.0f, terreno->Superficie(0.0f, 80.0f), 25.0f);
	translate = glm::vec3(20.0f, 14.0f, 10.0f);//(x,y,z) (←,↑,↑)
	scale = glm::vec3(0.03f, 0.03f, 0.03f);	// it's a bit too big for our scene, so scale it down
	Spider->setTranslate(&translate);
	Spider->setNextTranslate(&translate);
	Spider->setScale(&scale);
	//Spider->setNextRotY(-45);
	ourModel.emplace_back(Spider);
	try {
		std::vector<Animation> animations = Animation::loadAllAnimations("models/animals/spiderWidow.fbx", Spider->GetBoneInfoMap(), Spider->getBonesInfo(), Spider->GetBoneCount());
		std::vector<Animation> animation = Animation::loadAllAnimations("models/animals/spiderWidow.fbx", Spider->GetBoneInfoMap(), Spider->getBonesInfo(), Spider->GetBoneCount());
		std::move(animation.begin(), animation.end(), std::back_inserter(animations));
		for (Animation animation : animations)
			Spider->setAnimator(Animator(animation));
		Spider->setAnimation(1);
	}
	catch (...) {
		ERRORL("Could not load animation!", "ANIMACION");
	}*/

	//KITS---------------------------------------------

	//Placements
	//KIT 1 - Lake
	//KIT 2 - Cave
	//KIT 3 - By the house
	//KIT 4 - Across the road
	//KIT 5 - Parkour


	Model* Kit1 = new Model("models/animals/SleepingFox.fbx", main->cameraDetails);
	translate = glm::vec3(-123.0f, 9.0f, 118.0f);//(x,y,z) (←,↑,↑)
	Kit1->setTranslate(&translate);
	Kit1->setNextTranslate(&translate);
	//rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation X
	Kit1->setNextRotY(45); // 45� rotation
	scale = glm::vec3(0.03f, 0.03f, 0.03f);	// it's a bit too big for our scene, so scale it down
	Kit1->setScale(&scale);
	Kit1->setModelType("KIT1");
	Kit1->name = "KIT1";
	ourModel.emplace_back(Kit1);

	Model* Kit3 = new Model("models/animals/SleepingFox.fbx", main->cameraDetails);
	translate = glm::vec3(182.0f, terreno->Superficie(182.0f, -35.0f)+1, -35.0f);//(x,y,z) (←,↑,↑)
	Kit3->setTranslate(&translate);
	Kit3->setNextTranslate(&translate);
	//rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation X
	//Kit3->setNextRotY(180); // 45� rotation
	scale = glm::vec3(0.03f, 0.03f, 0.03f);	// it's a bit too big for our scene, so scale it down
	Kit3->setScale(&scale);
	Kit3->setModelType("KIT3");
	Kit3->name = "KIT3";
	ourModel.emplace_back(Kit3);

	Model* Kit4 = new Model("models/animals/SleepingFox.fbx", main->cameraDetails);
	translate = glm::vec3(-127.0f, terreno->Superficie(-127.0f, -166.0f)+1, -166.0f);//(x,y,z) (←,↑,↑)
	Kit4->setTranslate(&translate);
	Kit4->setNextTranslate(&translate);
	//rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation X
	Kit4->setNextRotY(90); // 45� rotation
	scale = glm::vec3(0.03f, 0.03f, 0.03f);	// it's a bit too big for our scene, so scale it down
	Kit4->setScale(&scale);
	Kit4->setModelType("KIT4");
	Kit4->name = "KIT4";
	ourModel.emplace_back(Kit4);

	Model* Kit5 = new Model("models/animals/SleepingFox.fbx", main->cameraDetails);
	translate = glm::vec3(95.0f, 28.8F, 182.0f);//(x,y,z) (←,↑,↑)
	Kit5->setTranslate(&translate);
	Kit5->setNextTranslate(&translate);
	//rotation = glm::vec3(0.0f, 0.0f, 0.0f); //rotation X
	Kit5->setNextRotY(90); // 45� rotation
	scale = glm::vec3(0.03f, 0.03f, 0.03f);	// it's a bit too big for our scene, so scale it down
	Kit5->setScale(&scale);
	Kit5->setModelType("KIT5");
	Kit5->name = "KIT5";
	ourModel.emplace_back(Kit5);

	//NATRURE//-----------------------------------------------------

	Model* Tree = new Model("models/Nature/Tree.fbx", main->cameraDetails);
	translate = glm::vec3(-10.0f, 10.0f, 20.0f);//(x,y,z) (←,↑,↑)
	Tree->setNextTranslate(&translate);
	Tree->setTranslate(&translate);
	Tree->setNextRotX(-90);
	Tree->getModelAttributes()->at(0).hitbox = NULL; // Le decimos al ultimo ModelAttribute que tiene un hitbox asignado
	ourModel.emplace_back(Tree);

	Model* Pine = new Model("models/Nature/Pine.fbx", main->cameraDetails);
	translate = glm::vec3(-10.0f, 10.0f, 8.0f);//(x,y,z) (←,↑,↑)
	Pine->setNextTranslate(&translate);
	Pine->setTranslate(&translate);
	Pine->setNextRotX(-90);
	scale = glm::vec3(2.1f, 2.1f, 2.1f);	// it's a bit too big for our scene, so scale it down
	Pine->setScale(&scale);
	Pine->getModelAttributes()->at(0).hitbox = NULL;
	ourModel.emplace_back(Pine);

	Model* Lake = new Model("models/Nature/LakeShore.fbx", main->cameraDetails);
	translate = glm::vec3(-160.0f, -1.0f, 155.0f);//(x,y,z) (←,↑ up,↑)
	Lake->setNextRotX(270);
	Lake->setNextRotZ(95); //og was 175
	Lake->setNextTranslate(&translate);
	Lake->setTranslate(&translate);
	scale = glm::vec3(3.1f, 3.1f, 3.1f);	// it's a bit too big for our scene, so scale it down
	Lake->setScale(&scale);
	Lake->getModelAttributes()->at(0).hitbox = NULL;
	ourModel.emplace_back(Lake);
	
	Model* Lake2 = new Model("models/Nature/LakeShore.fbx", main->cameraDetails);
	translate = glm::vec3(-100.0f, -1.0f, 145.0f);//(x,y,z) (←,↑ up,↑)
	Lake2->setNextRotX(270);
	Lake2->setNextRotZ(-180); //og was 175
	Lake2->setNextTranslate(&translate);
	Lake2->setTranslate(&translate);
	scale = glm::vec3(3.1f, 3.1f, 3.1f);	// it's a bit too big for our scene, so scale it down
	Lake2->setScale(&scale);
	Lake2->getModelAttributes()->at(0).hitbox = NULL;
	ourModel.emplace_back(Lake2);

	Model* Lake3 = new Model("models/Nature/LakeShore.fbx", main->cameraDetails);
	translate = glm::vec3(-100.0f, -1.0f, 95.0f);//(x,y,z) (←,↑ up,↑)
	Lake3->setNextRotX(270);
	Lake3->setNextRotZ(-90); //og was 175
	Lake3->setNextTranslate(&translate);
	Lake3->setTranslate(&translate);
	scale = glm::vec3(3.1f, 3.1f, 3.1f);	// it's a bit too big for our scene, so scale it down
	Lake3->setScale(&scale);
	Lake3->getModelAttributes()->at(0).hitbox = NULL;
	ourModel.emplace_back(Lake3);

	Model* Lake4 = new Model("models/Nature/LakeShore.fbx", main->cameraDetails);
	translate = glm::vec3(-160.0f, -1.0f, 95.0f);//(x,y,z) (←,↑ up,↑)
	Lake4->setNextRotX(270);
	//Lake4->setNextRotZ(180); //og was 175
	Lake4->setNextTranslate(&translate);
	Lake4->setTranslate(&translate);
	scale = glm::vec3(3.1f, 3.1f, 3.1f);	// it's a bit too big for our scene, so scale it down
	Lake4->setScale(&scale);
	Lake4->getModelAttributes()->at(0).hitbox = NULL;
	ourModel.emplace_back(Lake4);

	// load models

	// CLONES OF TREES-------------------------------------
	
	// Parameters for random placement
	int numTrees = 40; // Number of trees to spawn
	float minX = -184.0f, maxX = 104.0f;
	float minZ = -121.0f, maxZ = 48.0f;
	float yOffset = -0.1f; // Adjust as needed for your terrain

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distX(minX, maxX);
	std::uniform_real_distribution<float> distZ(minZ, maxZ);

	for (int i = 0; i < numTrees; ++i) {
		float x = distX(gen);
		float z = distZ(gen); 
		float y = terreno->Superficie(x, z) + yOffset; // Use terrain height if available

		Model* treeClone = new Model("models/Nature/Tree.fbx", main->cameraDetails);
		glm::vec3 treePos(x, y, z);
		treeClone->setTranslate(&treePos);
		treeClone->setNextTranslate(&treePos);
		treeClone->setNextRotX(-90);

		// Remove hitbox if needed
		treeClone->getModelAttributes()->at(0).hitbox = NULL;
		ourModel.emplace_back(treeClone);
	}

	int numpines = 30; // Number of pines to spawn

	for (int i = 0; i < numpines; ++i) {
		float x = distX(gen);
		float z = distZ(gen);
		float y = terreno->Superficie(x, z) + yOffset; // Use terrain height if available

		Model* pineClone = new Model("models/Nature/Pine.fbx", main->cameraDetails);
		glm::vec3 pinePos(x, y, z);
		pineClone->setTranslate(&pinePos);
		pineClone->setNextTranslate(&pinePos);
		pineClone->setNextRotX(-90);
		scale = glm::vec3(2.1f, 2.1f, 2.1f);	// it's a bit too big for our scene, so scale it down
		pineClone->setScale(&scale);
		// Remove hitbox if needed
		pineClone->getModelAttributes()->at(0).hitbox = NULL;
		ourModel.emplace_back(pineClone);
	}

	//Parkour Obstacles----------------------------------------
	Model* PRock1 = new Model("models/Cave/ROCK_MESH_01.fbx", main->cameraDetails);
	translate = glm::vec3(91.0f, terreno->Superficie(91.0f, 165.0f), 165.0f);//(x,y,z) (←,↑,↑)
	PRock1->setNextTranslate(&translate);
	PRock1->setTranslate(&translate);
	scale = glm::vec3(5.1f, 5.1f, 5.1f);	// it's a bit too big for our scene, so scale it down
	PRock1->setScale(&scale);
	ourModel.emplace_back(PRock1);

	Model* PRock2 = new Model("models/Cave/ROCK_MESH_06.fbx", main->cameraDetails);
	translate = glm::vec3(95.0f, terreno->Superficie(51.0f, 168.0f), 168.0f);//(x,y,z) (←,↑,↑)
	PRock2->setNextTranslate(&translate);
	PRock2->setTranslate(&translate);
	scale = glm::vec3(5.1f, 8.1f, 5.1f);	// it's a bit too big for our scene, so scale it down
	PRock2->setScale(&scale);
	ourModel.emplace_back(PRock2);

	Model* PRock3 = new Model("models/Cave/ROCK_SIDE_MESH_02.fbx", main->cameraDetails);
	translate = glm::vec3(103.0f, terreno->Superficie(103.0f, 174.0f)+10, 174.0f);//(x,y,z) (←,↑,↑)
	PRock3->setNextTranslate(&translate);
	PRock3->setTranslate(&translate);
	ourModel.emplace_back(PRock3);


	Model* PRock4 = new Model("models/Cave/COLUMN_MESH.fbx", main->cameraDetails);
	translate = glm::vec3(103.0f, terreno->Superficie(103.0f, 174.0f), 174.0f);//(x,y,z) (←,↑,↑)
	PRock4->setNextTranslate(&translate);
	PRock4->setTranslate(&translate);
	scale = glm::vec3(1.6f, 3.0f, 1.6f);	// it's a bit too big for our scene, so scale it down
	PRock4->setScale(&scale);
	//PRock4->setNextRotX(-90);
	ourModel.emplace_back(PRock4);

	Model* PRock5 = new Model("models/Cave/COLUMN_MESH.fbx", main->cameraDetails);
	translate = glm::vec3(95.0f, terreno->Superficie(95.0f, 183.0f), 183.0f);//(x,y,z) (←,↑,↑)
	PRock5->setNextTranslate(&translate);
	PRock5->setTranslate(&translate);
	scale = glm::vec3(6.0F, 3.6f, 6.6f);	// it's a bit too big for our scene, so scale it down
	PRock5->setScale(&scale);
	ourModel.emplace_back(PRock5);

	//CAVE ----------------------------------------
	Model* CaveEnt = new Model("models/Cave/ARCH_LONG_MESH.fbx", main->cameraDetails);
	float cy = terreno->Superficie(134.0f, 77.0f);
	translate = glm::vec3(134.0f, 8.5f, 77.0f);//(x,y,z) (←,↑ up,↑)
	//CaveEnt->setNextRotX(270);
	CaveEnt->setNextRotY(90); //og was 175
	CaveEnt->setNextTranslate(&translate);
	CaveEnt->setTranslate(&translate);
	scale = glm::vec3(2.1f, 2.1f, 2.1f);	// it's a bit too big for our scene, so scale it down
	CaveEnt->setScale(&scale);
	CaveEnt->getModelAttributes()->at(0).hitbox = NULL;
	ourModel.emplace_back(CaveEnt);
	
	Model* CaveEntHole = new Model("models/Cave/BEAM_ENTRANCE_MESH.fbx", main->cameraDetails);
	translate = glm::vec3(137.0f, 18.0f, 74.0f);//(x,y,z) (←,↑ up,↑)
	//CaveEntHole->setNextRotX(270);
	CaveEntHole->setNextRotY(90); //og was 175
	CaveEntHole->setNextTranslate(&translate);
	CaveEntHole->setTranslate(&translate);
	scale = glm::vec3(1.0f, 1.1f, 1.1f);	// it's a bit too big for our scene, so scale it down
	CaveEntHole->setScale(&scale);
	CaveEntHole->getModelAttributes()->at(0).hitbox = NULL;
	ourModel.emplace_back(CaveEntHole);

	Model* CaveWall1 = new Model("models/Cave/BEAM_ENTRANCE_MESH.fbx", main->cameraDetails);
	
	translate = glm::vec3(125.0f, 10.0f, 105.0f);//(x,y,z) (←,↑ up,↑)
	//CaveWall1->setNextRotX(270);
	//CaveWall1->setNextRotY(90); //og was 175
	CaveWall1->setNextTranslate(&translate);
	CaveWall1->setTranslate(&translate);
	scale = glm::vec3(2.1f, 4.1f, 2.1f);	// it's a bit too big for our scene, so scale it down
	CaveWall1->setScale(&scale);
	ourModel.emplace_back(CaveWall1);


	Model* CaveWall2 = new Model("models/Cave/BEAM_ENTRANCE_MESH.fbx", main->cameraDetails);
	translate = glm::vec3(169.5f, 10.0f, 75.0f);//(x,y,z) (←,↑ up,↑)
	CaveWall2->setNextRotY(90);
	//CaveWall2->setNextRotZ(90); //og was 175
	CaveWall2->setNextTranslate(&translate);
	CaveWall2->setTranslate(&translate);
	scale = glm::vec3(2.1f, 4.1f, 2.1f);	// it's a bit too big for our scene, so scale it down
	CaveWall2->setScale(&scale);
	ourModel.emplace_back(CaveWall2);

	Model* CaveWall3 = new Model("models/Cave/BEAM_ENTRANCE_MESH.fbx", main->cameraDetails);
	translate = glm::vec3(155.5f, 10.0f, 142.7f);//(x,y,z) (←,↑ up,↑)
	CaveWall3->setNextRotY(90);
	//CaveWall3->setNextRotZ(90); //og was 175
	CaveWall3->setNextTranslate(&translate);
	CaveWall3->setTranslate(&translate);
	scale = glm::vec3(2.1f, 4.1f, 2.1f);	// it's a bit too big for our scene, so scale it down
	CaveWall3->setScale(&scale);
	ourModel.emplace_back(CaveWall3);

	Model* CaveWall4 = new Model("models/Cave/BEAM_ENTRANCE_MESH.fbx", main->cameraDetails);

	translate = glm::vec3(190.0f, 10.0f, 112.5f);//(x,y,z) (←,↑ up,↑)
	//CaveWall4->setNextRotX(270);
	//CaveWall4->setNextRotY(90); //og was 175
	CaveWall4->setNextTranslate(&translate);
	CaveWall4->setTranslate(&translate);
	scale = glm::vec3(1.1f, 4.1f, 2.1f);	// it's a bit too big for our scene, so scale it down
	CaveWall4->setScale(&scale);
	ourModel.emplace_back(CaveWall4);



	Model* CaveCol1 = new Model("models/Cave/COLUMN_MESH.fbx", main->cameraDetails);
	translate = glm::vec3(122.5f, 10.0f, 139.7f);//(x,y,z) (←,↑ up,↑)
	CaveCol1->setNextRotY(90);
	//CaveCol1->setNextRotZ(90); //og was 175
	CaveCol1->setNextTranslate(&translate);
	CaveCol1->setTranslate(&translate);
	scale = glm::vec3(8.1f, 4.1f, 5.1f);	// it's a bit too big for our scene, so scale it down
	CaveCol1->setScale(&scale);
	CaveCol1->getModelAttributes()->at(0).hitbox = NULL;
	ourModel.emplace_back(CaveCol1);

	Model* CaveCol2 = new Model("models/Cave/COLUMN_MESH.fbx", main->cameraDetails);
	translate = glm::vec3(188.5f, 10.0f, 139.7f);//(x,y,z) (←,↑ up,↑)
	CaveCol2->setNextRotY(90);
	//CaveCol2->setNextRotZ(90); //og was 175
	CaveCol2->setNextTranslate(&translate);
	CaveCol2->setTranslate(&translate);
	scale = glm::vec3(8.1f, 4.1f, 5.1f);	// it's a bit too big for our scene, so scale it down
	CaveCol2->setScale(&scale);
	CaveCol2->getModelAttributes()->at(0).hitbox = NULL;
	ourModel.emplace_back(CaveCol2);

	Model* CaveCol3 = new Model("models/Cave/COLUMN_MESH.fbx", main->cameraDetails);
	translate = glm::vec3(191.5f, 10.0f, 76.7f);//(x,y,z) (←,↑ up,↑)
	CaveCol3->setNextRotY(90);
	//CaveCol3->setNextRotZ(90); //og was 175
	CaveCol3->setNextTranslate(&translate);
	CaveCol3->setTranslate(&translate);
	scale = glm::vec3(15.1f, 4.1f, 8.1f);	// it's a bit too big for our scene, so scale it down
	CaveCol3->setScale(&scale);
	CaveCol3->getModelAttributes()->at(0).hitbox = NULL;
	ourModel.emplace_back(CaveCol3);

	Model* CaveCeiling = new Model("models/Cave/CEILING_ENTRANCE_MESH.fbx", main->cameraDetails);
	translate = glm::vec3(155.5f, 22.0f, 110.7f);//(x,y,z) (←,↑ up,↑)
	CaveCeiling->setNextRotY(90);
	//CaveCeiling->setNextRotZ(90); //og was 175
	CaveCeiling->setNextTranslate(&translate);
	CaveCeiling->setTranslate(&translate);
	scale = glm::vec3(3.3f, 0.5f, 2.5f);	// it's a bit too big for our scene, so scale it down
	CaveCeiling->setScale(&scale);
	CaveCeiling->getModelAttributes()->at(0).hitbox = NULL;
	ourModel.emplace_back(CaveCeiling);

	//END CAVE


	//MAN MADE----------------------------------------
	float y = terreno->Superficie(134.0f, -30.0f);
	Model* House = new Model("models/ManMade/MainHouse.fbx", main->cameraDetails);
	House->setNextRotX(-90); // 45� rotation
	House->setNextRotZ(185); // 45� rotation
	translate = glm::vec3(150.0f, y, -30.0f);
	House->setNextTranslate(&translate);
	House->setTranslate(&translate);
	scale = glm::vec3(6.0f, 6.0f, 6.0f);	// it's a bit too big for our scene, so scale it down
	House->setScale(&scale);
	ourModel.emplace_back(House);

	Model* carB = new Model("models/ManMade/CarBlue.fbx", main->cameraDetails);
	carB->setRotX(270);
	carB->setNextRotX(270);
	carB->setNextRotZ(-90);
	translate = glm::vec3(25.0f, 15.0f, -17.0f);
	carB->setNextTranslate(&translate);
	carB->setTranslate(&translate);
	scale = glm::vec3(4.0f, 4.0f, 4.0f);	// it's a bit too big for our scene, so scale it down
	carB->setScale(&scale);
	carB->setModelType("carB");
	ourModel.emplace_back(carB);

	Model* carR = new Model("models/ManMade/CarRed.fbx", main->cameraDetails);
	carR->setRotX(270);
	carR->setNextRotX(270);
	translate = glm::vec3(15.0f, 13.0f, -20.0f);
	carR->setNextTranslate(&translate);
	carR->setTranslate(&translate);
	scale = glm::vec3(4.0f, 4.0f, 4.0f);	// it's a bit too big for our scene, so scale it down
	carR->setScale(&scale);

	carR->setModelType("carR");
	ourModel.emplace_back(carR);



	Model* carT = new Model("models/ManMade/TowTruck.fbx", main->cameraDetails);
	translate = glm::vec3(10.0f, 13.0f, -20.0f);
	carT->setNextTranslate(&translate);
	carT->setTranslate(&translate);
	carT->setRotX(45);
	scale = glm::vec3(4.0f, 4.0f, 4.0f);	// it's a bit too big for our scene, so scale it down
	carT->setScale(&scale);
	carT->setModelType("carT");
	ourModel.emplace_back(carT);

	Model* RoadC = new Model("models/ManMade/RoadChunk.fbx", main->cameraDetails);
	translate = glm::vec3(10.0f, 8.0f, 10.0f);
	RoadC->setNextTranslate(&translate);
	RoadC->setTranslate(&translate);
	//scale = glm::vec3(4.0f, 4.0f, 4.0f);	// it's a bit too big for our scene, so scale it down
	//RoadC->setScale(&scale);
	RoadC->setNextRotY(-90);
	ourModel.emplace_back(RoadC);

	// Repeat RoadC along the x-axis at fixed z = -80
	float fixedZ = -140.0f;
	float startX = -180.0f;
	float endX = 180.0f;
	float stepX = 10.0f; // Adjust to match the length of your road chunk model

	for (float x = startX; x <= endX; x += stepX) {
		float y = terreno->Superficie(x, fixedZ);
		Model* roadChunk = new Model("models/ManMade/RoadChunk.fbx", main->cameraDetails);
		glm::vec3 pos(x, y, fixedZ);
		roadChunk->setTranslate(&pos);
		roadChunk->setNextTranslate(&pos);
		// Set rotation if needed, e.g. roadChunk->setNextRotY(0);

		roadChunk->setNextRotY(-90);
		roadChunk->getModelAttributes()->at(0).hitbox = NULL;
		ourModel.emplace_back(roadChunk);
	}


	


	inicializaBillboards();
	std::wstring prueba(L"Esta es una prueba");
	ourText.emplace_back(new Texto(prueba, 20, 0, 0, SCR_HEIGHT, 0, camara));

	billBoard2D.emplace_back(new Billboard2D((WCHAR*)L"textures/Clues.png", 6, 6, 570, 0, 0, camara->cameraDetails));
	scale = glm::vec3(225.0f, 225.0f, 0.0f);	// it's a bit too big for our scene, so scale it down
	billBoard2D.back()->setScale(&scale);
	
	//billBoard2D.emplace_back(new Billboard2D((WCHAR*)L"billboards/awesomeface.png", 6, 6, 100, 200, 0, camara->cameraDetails));
	//scale = glm::vec3(100.0f, 100.0f, 0.0f);	// it's a bit too big for our scene, so scale it down
	//billBoard2D.back()->setScale(&scale);
}

void Scenario::inicializaBillboards() {
	
	float ye = terreno->Superficie(93, -23);
	billBoard.emplace_back(new Billboard((WCHAR*)L"textures/PELIGROPERRO.png", 8, 8, 93, ye - 2, -23, camara->cameraDetails));
	
	/*ye = terreno->Superficie(0, 0);
	billBoard.emplace_back(new Billboard((WCHAR*)L"billboards/Arbol.png", 6, 6, 0, ye - 1, 0, camara->cameraDetails));

	BillboardAnimation *billBoardAnimated = new BillboardAnimation();
	ye = terreno->Superficie(5, -5);
	for (int frameArbol = 1; frameArbol < 5; frameArbol++){
		wchar_t textura[50] = {L"billboards/baile"}; //CHANGE THE ANIMATION FILE NAME
		if (frameArbol != 1){
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

	//el metodo render toma el dispositivo sobre el cual va a dibujar
	//y hace su tarea ya conocida
Scene* Scenario::Render() {
	//borramos el biffer de color y el z para el control de profundidad a la 
	//hora del render a nivel pixel.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
//	glClearColor(255.0f, 255.0f, 255.0f, 255.0f);

	if (this->animacion > 5) { // Timer se ejecuta cada 1000/30 = 33.333 ms //CHANGE FRAME RATE OF BILLBOARD ANIMATION
		for (BillboardAnimation *b : billBoardAnim){
			b->nextAnimation();
		}
		this->animacion = 0;
	} else {
		animacion = animacion + (1 * gameTime.deltaTime/25);
	}
	

	//car MOVEMENT ANIMATION
	carBPosX += carBSpeed;
	if (carBPosX > 180.0f)
		carBPosX = -180.0f;

	carRPosX = carBPosX + carROffset;
	if (carRPosX > 180.0f)
		carRPosX = -180.0f + (carRPosX - 180.0f);

	
	carTPosX = carRPosX + carTOffset;
	if (carTPosX > 180.0f)
		carTPosX = -180.0f + (carTPosX - 180.0f);
	

	float carBY = terreno->Superficie(carBPosX, carBFixedZ) + 1.0f;
	float carRY = terreno->Superficie(carRPosX, carBFixedZ) + 1.0f;
	float carTY = terreno->Superficie(carTPosX, carBFixedZ) + 1.0f;
	glm::vec3 carBPos(carBPosX, carBY, carBFixedZ);
	glm::vec3 carRPos(carRPosX, terreno->Superficie(carRPosX, carBFixedZ) + 1.0f, carBFixedZ);
	glm::vec3 carTPos(carTPosX, terreno->Superficie(carTPosX, carBFixedZ) + 1.0f, carBFixedZ);


	// Find carB in ourModel (assuming only one carB)
	for (Model* model : ourModel) {
		// You may want to check by name or pointer if you have multiple cars
		// For example, if you set carB->setModelType("carB"); in InitGraph:
		if (model->getModelType() == "carB") {
			model->setTranslate(&carBPos);
			model->setNextTranslate(&carBPos);
			model->setNextRotZ(90); // if needed
			break;
		}
	}

	for (Model* model : ourModel) {
		if (model->getModelType() == "carR") {
			model->setTranslate(&carRPos);
			model->setNextTranslate(&carRPos);
			model->setNextRotZ(90); // if needed
			break;
		}
	}

	for (Model* model : ourModel) {
		if (model->getModelType() == "carT") {
			model->setTranslate(&carTPos);
			model->setNextTranslate(&carTPos);
			model->setNextRotY(90); // if needed
			break;
		}
	}
	glm::vec3* dogCoord;
	for (DogEnemy* dogE : dogsvector) {
		if (dogE->getModelType() == "dogEnemyMod") {
			
			dogCoord = dogE->getTranslate();
			float y = terreno->Superficie(dogCoord->x, dogCoord->z);
			glm::vec3 pos(dogCoord->x, y, dogCoord->z);
			dogE->setTranslate(&pos);
			dogE->setNextTranslate(&pos); // if needed
			//dogE->setRotY(-50); // 45� rotation
			//dogE->setNextRotY(-50); // 45� rotation
			break;
		}
	}


	//DUCK MOVEMENT
	// Update orbit angle
	duckOrbitAngle += duckOrbitSpeed * (gameTime.deltaTime / 1000.0f);
	if (duckOrbitAngle > glm::two_pi<float>()) duckOrbitAngle -= glm::two_pi<float>();

	// Calculate positions for DuckMal and DuckYell (XZ plane, fixed Y)
	glm::vec3 duckMalPos = duckOrbitCenter + glm::vec3(
		duckOrbitRadius * cos(duckOrbitAngle),
		0.0f,
		duckOrbitRadius * sin(duckOrbitAngle)
	);

	glm::vec3 duckYellPos = duckOrbitCenter + glm::vec3(
		duckOrbitRadius * cos(duckOrbitAngle + glm::pi<float>()), // opposite side
		0.0f,
		duckOrbitRadius * sin(duckOrbitAngle + glm::pi<float>())
	);

	// Set positions and Y rotation for DuckMal and DuckYell
	for (Model* duckmodel : ourModel) {
		if (duckmodel->name == "DuckMal") {
			duckmodel->setTranslate(&duckMalPos);
			duckmodel->setNextTranslate(&duckMalPos);
			// Calculate angle to center in XZ plane
			float dx = duckOrbitCenter.x - duckMalPos.x;
			float dz = duckOrbitCenter.z - duckMalPos.z;
			float angleToCenter = atan2(dx, dz); // atan2(X, Z) for OpenGL Y-up
			duckmodel->setNextRotZ(glm::degrees(angleToCenter)-90);
		}
		if (duckmodel->name == "DuckYell") {
			duckmodel->setTranslate(&duckYellPos);
			duckmodel->setNextTranslate(&duckYellPos);
			float dx = duckOrbitCenter.x - duckYellPos.x;
			float dz = duckOrbitCenter.z - duckYellPos.z;
			float angleToCenter = atan2(dx, dz);
			duckmodel->setNextRotZ(glm::degrees(angleToCenter)-90);
		}
	}




	// Decimos que dibuje la media esfera
	sky->Draw();
	// Ahora el terreno
	terreno->Draw();
	water->Draw();
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

	// Le decimos a winapi que haga el update en la ventana
	bool jugadorQuieto = glm::length(*camara->getVelocity()) < 0.01f;
	for (auto* dogdog : dogsvector) {
		dogdog->update(gameTime.deltaTime / 1000.0f, *getMainModel()->getTranslate(), jugadorQuieto);
	}

	return this;
}
	
std::vector<Model*> *Scenario::getLoadedModels() {
	return &ourModel;
}
std::vector<Billboard*> *Scenario::getLoadedBillboards() {
	return &billBoard;
}
std::vector<Billboard2D*> *Scenario::getLoadedBillboards2D(){
	return &billBoard2D;
}
std::vector<Texto*> *Scenario::getLoadedText(){
	return &ourText;
}
std::vector<BillboardAnimation*> *Scenario::getLoadedBillboardsAnimation(){
	return &billBoardAnim;
}

Model* Scenario::getMainModel() {
	return this->camara;
}
void Scenario::setMainModel(Model* mainModel){
	this->camara = mainModel;
}
float Scenario::getAngulo() {
	return this->angulo;
}
void Scenario::setAngulo(float angulo) {
	this->angulo = angulo;
}
SkyDome* Scenario::getSky() {
	return sky;
}
Terreno* Scenario::getTerreno() {
	return terreno;
}




Scenario::~Scenario() {
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
