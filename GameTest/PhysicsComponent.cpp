#include "stdafx.h"
#include "PhysicsComponent.h"
#include <cmath>
#include "app\app.h"


//@desc This is where i check for collisions. One of the move important scripts. Going through all the line segments and checking their type to determine what happens to them.
//------------------------------------------------------------------------------------------------------
bool PhysicsComponent::CollisionCheck(CTable* gTable, std::map<std::string, GameObject*> gm) {

	_normal.m_x = 0.0f;
	_normal.m_y = 0.0f;
	bool bIsCollision = false;

	for (auto& line : gTable->m_lines)
	{
		//Ball Collision Detection
		if (line.m_type == eLine_Ball)
		{
			continue;
		}

		//Gaurd Collision
		if (line.m_type == eLine_Gaurd) {
			float overlapDist = radius - line.DistanceToLine(this->getGameObject()->getComponent<TransformComponent>()->_position.m_x, this->getGameObject()->getComponent<TransformComponent>()->_position.m_y);

			if (overlapDist >= 0.0f)
			{
				App::PlaySoundW("ping_pong_8bit_beeep.wav");

				//Gaurd Check One way
				if (this->getGameObject()->getComponent<RigidBodyComponent>()->_velocity.m_x > 0.0f)
				{
					_normal = line.NormalAwayFromLine(this->getGameObject()->getComponent<TransformComponent>()->_position.m_x, this->getGameObject()->getComponent<TransformComponent>()->_position.m_y);
					this->getGameObject()->getComponent<TransformComponent>()->_position = this->getGameObject()->getComponent<TransformComponent>()->_position + _normal * overlapDist * 0.1f;
					_normal = _normal.Normalize();
					CollisionResolve(this->getGameObject(), 1.1);

					//Add score
					score += 1;
				}
				break;
			}
		}

		//Target Collision
		if (line.m_type == eLine_Target) {
			float overlapDist = radius - line.DistanceToLine(this->getGameObject()->getComponent<TransformComponent>()->_position.m_x, this->getGameObject()->getComponent<TransformComponent>()->_position.m_y);

			if (overlapDist >= 0.0f)
			{
				_normal = line.NormalAwayFromLine(this->getGameObject()->getComponent<TransformComponent>()->_position.m_x, this->getGameObject()->getComponent<TransformComponent>()->_position.m_y);
				this->getGameObject()->getComponent<TransformComponent>()->_position = this->getGameObject()->getComponent<TransformComponent>()->_position + _normal * overlapDist * 0.1f;
				_normal = _normal.Normalize();
				CollisionResolve(this->getGameObject(), 1.1);

				//Add score
				score += 10000;
				break;
			}
		}

		//Spinner Collision
		if (line.m_type == eLine_Spinner) {
			float overlapDist = radius - line.DistanceToLine(this->getGameObject()->getComponent<TransformComponent>()->_position.m_x, this->getGameObject()->getComponent<TransformComponent>()->_position.m_y);

			if (overlapDist >= 0.0f)
			{
				//Add score
				score += 1.0;
			}
		}

		//Flipper Collision
		if (line.m_type == eLine_Flipper) {
			float overlapDist = radius - line.DistanceToLine(this->getGameObject()->getComponent<TransformComponent>()->_position.m_x, this->getGameObject()->getComponent<TransformComponent>()->_position.m_y);

			if (overlapDist >= 0.0f)
			{
				App::PlaySoundW("ping_pong_8bit_beeep.wav");
				_normal = line.NormalAwayFromLine(this->getGameObject()->getComponent<TransformComponent>()->_position.m_x, this->getGameObject()->getComponent<TransformComponent>()->_position.m_y);
				this->getGameObject()->getComponent<TransformComponent>()->_position = this->getGameObject()->getComponent<TransformComponent>()->_position + _normal * overlapDist * 1.1f;
				_normal = _normal.Normalize();
				CollisionResolve(this->getGameObject(), 1.1f);

				//Add score
				score += 100;
				break;
			}
		}

		//Mushroom Collision
		if (line.m_type == eLine_Mushroom) {

			float overlapDist = radius - line.DistanceToLine(this->getGameObject()->getComponent<TransformComponent>()->_position.m_x, this->getGameObject()->getComponent<TransformComponent>()->_position.m_y);

			if (overlapDist >= 0.0f)
			{
				App::PlaySoundW("ping_pong_8bit_beeep.wav");
				_normal = line.NormalAwayFromLine(this->getGameObject()->getComponent<TransformComponent>()->_position.m_x, this->getGameObject()->getComponent<TransformComponent>()->_position.m_y);
				this->getGameObject()->getComponent<TransformComponent>()->_position = this->getGameObject()->getComponent<TransformComponent>()->_position + _normal * overlapDist * 5.1f;
				_normal = _normal.Normalize();
				CollisionResolve(this->getGameObject(), 1.1f);

				//Add score
				score += 100;
				break;
			}
		}

		//Teleporter Collision
		if (line.m_type == eLine_Teleporter) {
			float overlapDist = radius - line.DistanceToLine(this->getGameObject()->getComponent<TransformComponent>()->_position.m_x, this->getGameObject()->getComponent<TransformComponent>()->_position.m_y);

			if (overlapDist >= 0.0f)
			{
				App::PlaySoundW("ping_pong_8bit_beeep.wav");
				//Left and right distance
				if (this->getGameObject()->getComponent<TransformComponent>()->_position.m_x > APP_INIT_WINDOW_WIDTH / 2)
				{
					this->getGameObject()->getComponent<TransformComponent>()->_position.m_x -= this->getGameObject()->getComponent<TransformComponent>()->_position.m_x - 500;
				}
				else
				{
					this->getGameObject()->getComponent<TransformComponent>()->_position.m_x += 200;
				}

				//Going up or down Check
				if (this->getGameObject()->getComponent<RigidBodyComponent>()->_velocity.m_y > 0.0f)
				{
					this->getGameObject()->getComponent<TransformComponent>()->_position.m_y += 30.0f;
				}
				else
				{
					this->getGameObject()->getComponent<TransformComponent>()->_position.m_y -= 30.0f;
				}

				//Add score
				score += 100;
				break;
			}
		}

		//Hittings the restart line
		if (line.m_type == eLine_Fail) {
			float overlapDist = radius - line.DistanceToLine(this->getGameObject()->getComponent<TransformComponent>()->_position.m_x, this->getGameObject()->getComponent<TransformComponent>()->_position.m_y);

			if (overlapDist >= 0.0f)
			{
				this->getGameObject()->getComponent<TransformComponent>()->_position.m_x = 832;
				this->getGameObject()->getComponent<TransformComponent>()->_position.m_y = 50;
				this->getGameObject()->getComponent<RigidBodyComponent>()->_velocity.m_x = 0.0f;
				this->getGameObject()->getComponent<RigidBodyComponent>()->_velocity.m_y = 0.0f;
				this->getGameObject()->getComponent<RigidBodyComponent>()->_angularVelocity = 0.0f;
				this->getGameObject()->getComponent<RigidBodyComponent>()->bIsFirstTimeLuanch = true;
				this->getGameObject()->getComponent<RigidBodyComponent>()->_bGravityEnable = false;

				//Reset Score
				score = 0;
				break;
			}
		}

		//Walls
		if (line.m_type == eLine_Power) {
			float overlapDist = radius - line.DistanceToLine(this->getGameObject()->getComponent<TransformComponent>()->_position.m_x, this->getGameObject()->getComponent<TransformComponent>()->_position.m_y);

			if (overlapDist >= 0.0f)
			{
				App::PlaySoundW("ping_pong_8bit_plop.wav");
				_normal = line.NormalAwayFromLine(this->getGameObject()->getComponent<TransformComponent>()->_position.m_x, this->getGameObject()->getComponent<TransformComponent>()->_position.m_y);
				this->getGameObject()->getComponent<TransformComponent>()->_position = this->getGameObject()->getComponent<TransformComponent>()->_position + _normal * overlapDist * 1.1f;
				_normal = _normal.Normalize();
				bIsCollision = true;
				break;
			}
		}

		//Out of bounds check
		if (this->getGameObject()->getComponent<TransformComponent>()->_position.m_x < 0 || this->getGameObject()->getComponent<TransformComponent>()->_position.m_x > APP_INIT_WINDOW_WIDTH  || this->getGameObject()->getComponent<TransformComponent>()->_position.m_y < 0 || this->getGameObject()->getComponent<TransformComponent>()->_position.m_y > APP_INIT_WINDOW_HEIGHT) {
			this->getGameObject()->getComponent<TransformComponent>()->_position.m_x = 832;
			this->getGameObject()->getComponent<TransformComponent>()->_position.m_y = 50;
			this->getGameObject()->getComponent<RigidBodyComponent>()->_velocity.m_x = 0.0f;
			this->getGameObject()->getComponent<RigidBodyComponent>()->_velocity.m_y = 0.0f;
			this->getGameObject()->getComponent<RigidBodyComponent>()->_angularVelocity = 0.0f;
			this->getGameObject()->getComponent<RigidBodyComponent>()->bIsFirstTimeLuanch = true;
			this->getGameObject()->getComponent<RigidBodyComponent>()->_bGravityEnable = false;
			bIsCollision = false;

			//Reset Score
			score = 0;
			break;
		}
	}
	return bIsCollision;
}

//@desc to resolve after collision is true
//------------------------------------------------------------------------------------------------------
void PhysicsComponent::CollisionResolve(GameObject* a, float attenuation)
{
	float dotProduct = _normal.m_x * a->getComponent<RigidBodyComponent>()->_velocity.m_x + _normal.m_y * a->getComponent<RigidBodyComponent>()->_velocity.m_y;
	a->getComponent<RigidBodyComponent>()->_velocity = a->getComponent<RigidBodyComponent>()->_velocity + _normal * (-2.0f * dotProduct);

	a->getComponent<RigidBodyComponent>()->_velocity.m_x *= attenuation;
	a->getComponent<RigidBodyComponent>()->_velocity.m_y *= attenuation;
}

//@desc Adds torque so that i can spin the paddles/spinners
//------------------------------------------------------------------------------------------------------
void PhysicsComponent::ApplyTorque(float a)
{
	this->getGameObject()->getComponent<RigidBodyComponent>()->_angularAcceleration += a;
}