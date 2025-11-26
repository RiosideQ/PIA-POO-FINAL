#pragma once
#include "Base/model.h"
#include "SkyDome.h"
#include "Terreno.h"
#include "Billboard.h"
#include "BillboardAnimation.h"
#include "Billboard2D.h"
#include "Texto.h"
#include "Water.h"
#include "Animator.h"
#include "Animation.h"
#include "Principal.h"
#include "DOGENEMY.h"
#include "KidFox.h"
#include "InputDevices/KeyboardInput.h"
#include <chrono>
#include <cmath>
extern int kitCollectCounter;

class Scene {
	protected:
	std::chrono::steady_clock::time_point lastCollisionTime = std::chrono::steady_clock::now();
	std::unique_ptr<Billboard2D> loseBillboard;

	public:
		virtual float getAngulo() = 0;
		virtual void setAngulo(float angulo) = 0;
		virtual Model* getMainModel() = 0;
		virtual void setMainModel(Model* mainModel) = 0;
		virtual Scene* Render() = 0;
		virtual SkyDome* getSky() = 0;
		virtual Terreno* getTerreno() = 0;
		virtual std::vector<Model*> *getLoadedModels() = 0;
		virtual std::vector<Billboard*> *getLoadedBillboards() = 0;
		virtual std::vector<BillboardAnimation*> *getLoadedBillboardsAnimation() = 0;
		virtual std::vector<Billboard2D*> *getLoadedBillboards2D() = 0;
		virtual std::vector<Texto*> *getLoadedText() = 0;

		

		virtual ~Scene(){
		};


		/*bool isPlayerNearDogEnemyMod(float thresholdDistance) {
			Model* player = getMainModel();
			glm::vec3 playerPos = *player->getTranslate();

			for (Model* model : *getLoadedModels()) {
				if (model->getModelType() == "dogEnemyMod") {
					glm::vec3 dogPos = *model->getTranslate();
					float dx = playerPos.x - dogPos.x;
					float dy = playerPos.y - dogPos.y;
					float dz = playerPos.z - dogPos.z;
					float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
					if (distance < thresholdDistance) {
						return true; // Player is close to a dogEnemyMod
					}
				}
			}
			return false; // No dogEnemyMod is close
		}*/
		virtual int update() {
			float startEnemy = 0.0f;
			float angulo = getAngulo() + 1.5 * gameTime.deltaTime / 100;
			angulo = angulo >= 360 ? angulo - 360.0 : angulo;
			setAngulo(angulo);
			getSky()->setRotY(angulo);
			Model* camara = getMainModel();

			int remaining = remainingKits();

			int tp;
			//
			for (int i = 0; i < getLoadedModels()->size(); i++){
				auto it = getLoadedModels()->begin() + i;
				Model *collider = NULL, *model = *it;
				DogEnemy* Dcollider = NULL;
				int idxCollider = -1;
                bool objInMovement = (*model->getNextTranslate()) != (*model->getTranslate());
				glm::vec3 &posM = objInMovement ? *model->getNextTranslate() : *model->getTranslate();
                glm::vec3 ejeColision = glm::vec3(0);
				bool isPrincipal = model == camara; // Si es personaje principal, activa gravedad
				ModelCollider mcollider = model->update(getTerreno()->Superficie(posM.x, posM.z), *getLoadedModels(), ejeColision, isPrincipal);
				
				KidFox* kit = dynamic_cast<KidFox*>(collider);

				//Collision delay//
				const int collisionCooldownMs = 1000; // 10 seconds
				auto now = std::chrono::steady_clock::now();
				auto msSinceLastCollision = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastCollisionTime).count();

				//OLD BUT FUNCTIONAL

				

				if (mcollider.model != NULL){
					collider = (Model*)mcollider.model;
					idxCollider = mcollider.attrIdx;
				}
				//KidFox* kit = dynamic_cast<KidFox*>(collider);

				if (collider != NULL && model == camara){
					
					if (collider->name.compare("cube") == 0) {
						//tp = 1;
						auto now = std::chrono::steady_clock::now();
						auto msSinceLastCollision = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastCollisionTime).count();

						if (msSinceLastCollision >= collisionCooldownMs) {
							INFO("OW", "collision");
							Principal* principal = (Principal*)camara;
							if (principal->vidas.size() > 0) {
								delete principal->vidas.back();
								principal->vidas.pop_back();
							}
						}
					}

					if (collider->name.compare("Dug") == 0) {
						tp = 1;
						
					}
					if (collider->name.compare("Dug2") == 0) {
						tp = 2;

					}

					if (collider->getModelType() == "carB" || collider->getModelType() == "carR" || collider->getModelType() == "carT") {
						//tp = 1;
						auto now = std::chrono::steady_clock::now();
						auto msSinceLastCollision = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastCollisionTime).count();

						if (msSinceLastCollision > collisionCooldownMs) {
							INFO("OUCH!", "TE ATROPEYARON");
							Principal* principal = (Principal*)camara;
							if (principal->vidas.size() > 0) {
								delete principal->vidas.back();
								principal->vidas.pop_back();
							}
							lastCollisionTime = now;
						}
						
					}

					if (collider->getModelType() == "KIT1" || collider->getModelType() == "KIT2" || collider->getModelType() == "KIT3" || collider->getModelType() == "KIT4" || collider->getModelType() == "KIT5") {
						INFO("CACHORRO ENCONTRADO", "Ahi estas!");
						if (kitCollectCounter < 5)
							++kitCollectCounter;

						if (removeCollideModel(collider, idxCollider))
							i--;

					}

					if (ejeColision.y == 1){
						//INFO("APLASTADO!!!!", "JUMP HITBOX");
						/*if (removeCollideModel(collider, idxCollider))
							i--;
						*/ //Add a delay to the collision detection
					}
					else {
						
						
					}
					lastCollisionTime = std::chrono::steady_clock::now();
					
					
				}

				/*if (collider && collider->name == "KITS") {
					//if (KEYS[input.E]) {
					auto modelos = getLoadedModels();
					auto it = std::find(modelos->begin(), modelos->end(), kit);

					if (it != modelos->end()) {
						modelos->erase(it);
					}

					delete kit;

					int restantes = remainingKits();
					INFO("YUPO", "YAYY");

					//KEYS[input.E] = false;
				//}
				}*/
				//
				if (i < 0) i = 0;
			}


			/*remaining = remainingKits();

			if (remaining == 0) {
				static bool HasWon = false;

				if (!HasWon) {
					HasWon = true;

					INFO("YOU'VE WON", "CONGRATS");

				}
			}*/

			// Actualizamos la camara
            camara->cameraDetails->CamaraUpdate(camara->getRotY(), camara->getTranslate());

			

			/*if (isPlayerNearDogEnemyMod(5.0f)) { // 5.0f is the distance threshold
				auto now = std::chrono::steady_clock::now();
				auto msSinceLastCollision = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastCollisionTime).count();

				if (msSinceLastCollision > collisionCooldownMs) {
					INFO("OW", "ATROPEYADO");
					Principal* principal = (Principal*)camara;
					if (principal->vidas.size() > 0) {
						delete principal->vidas.back();
						principal->vidas.pop_back();
					}
					lastCollisionTime = now;
				}
			}*/

            return tp;
        }
		
		virtual bool removeCollideModel(Model* collider, int idxCollider){
			auto it = std::find(getLoadedModels()->begin(), getLoadedModels()->end(), collider);
			if (idxCollider == 0){
				collider->setActive(false);
				Model* AABB = (Model*)collider->getModelAttributes()->at(0).hitbox;
				delete AABB;
				collider->getModelAttributes()->at(0).hitbox = NULL;
			} else {
				ModelAttributes &attr = collider->getModelAttributes()->at(idxCollider);
				Model *AABB = (Model*)attr.hitbox;
				delete AABB;
				collider->getModelAttributes()->erase(collider->getModelAttributes()->begin() + idxCollider);
			}
			if (collider->getModelAttributes()->size() == 1 && !collider->getActive()){
				it = std::find(getLoadedModels()->begin(), getLoadedModels()->end(), collider);
				it = getLoadedModels()->erase(it);
				delete collider;
				return true;
			}
			return false;
		}

		int remainingKits() {
			int count = 0;
			for (auto m : *getLoadedModels()) {
				KidFox* kf = dynamic_cast<KidFox*>(m);
				if (kf && !kf->isInventory() && kf->getModelType() == "KITS") {
					count++;
				}
			}
			return count;
		}

		virtual Model* lookForCollition(glm::vec3 &yPos, bool collitionMovement = false) {
			std::vector<Model*> *ourModel = getLoadedModels();
			Model *camara = getMainModel();
			for (int i = 0; i < ourModel->size(); i++) {
				Model *model = (*ourModel)[i];
				if (model != camara) {
					if (camara->colisionaCon(model->getModelAttributes()->at(0), yPos, collitionMovement)) {
						return model;
					}
				}
			}
			return NULL;
		}


};