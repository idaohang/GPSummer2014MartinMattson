// EnemyObject0.h //

#include "EnemyObject0.h"

#include "CollisionMngr.h"
#include "DrawMngr.h"
#include "GameObjectMngr.h"
#include "KeybMngr.h"
#include "SpriteMngr.h"
#include "TimeMngr.h"

#include "Hitbox.h"
#include "Sprite.h"

#include "EnemyBulletObject.h"
#include "ScoreObject.h"

#include <iostream>

EnemyObject0::EnemyObject0(sf::Vector2f p_vPosition, sf::Vector2f p_vSpd, sf::Vector2f p_vDeaccel, sf::Vector2f p_vMaxSpd){
	setPosition(p_vPosition);
	m_vSpd = p_vSpd;
	m_vDeaccel = p_vDeaccel;
	m_vMaxSpd = p_vMaxSpd;

	m_iBulletAmmo = 4;
	m_iLife = 45;
	m_iScore = 8;

	m_fFireRateMax = .8f;
	m_fFireRate = m_fFireRateMax;

	m_xpSprite = SpriteMngr::GetSprite("Enemy0");
	AddTag("Enemy");

	SetHitbox(CollisionMngr::NewHitbox(this, getPosition(), 64.0f, 0));

	m_xpPlayer = GameObjectMngr::GetGameObject("Player");
}

EnemyObject0::~EnemyObject0(){
	for (int i = 0; i < m_iScore; i++){
		GetParent()->AddChild(new ScoreObject(getPosition()));
	}
}

void EnemyObject0::SetAllPositions(sf::Vector2f p_vPosition){
	setPosition(p_vPosition);
	m_xpSprite->SetPosition(getPosition());
	GetHitbox()->SetPosition(getPosition());
}

void EnemyObject0::OnCreate(){

}

void EnemyObject0::OnUpdateThis(){
	m_vSpd -= m_vDeaccel * TimeMngr::GetDtime();

	SetAllPositions(sf::Vector2f(getPosition().x + TimeMngr::GetDtime() * m_vSpd.x, getPosition().y + TimeMngr::GetDtime() * m_vSpd.y));

	if (CanFire()){
		float _iA = m_xpPlayer->getPosition().x - getPosition().x;
		float _iB = m_xpPlayer->getPosition().y - getPosition().y;
		float _iC = sqrt((_iA * _iA) + (_iB * _iB));

		GetParent()->AddChild(new EnemyBulletObject(getPosition(), sf::Vector2f((_iA / _iC), (_iB / _iC)), 95.f));
		GetParent()->AddChild(new EnemyBulletObject(getPosition(), sf::Vector2f((_iA / _iC), (_iB / _iC)), 60.f));
	}

	//std::cout << getPosition().x << " " << getPosition().y << " " << m_fVerticalSpd << std::endl;
}

void EnemyObject0::OnDrawThis(){
	DrawMngr::DrawSprite(m_xpSprite);
}

void EnemyObject0::OnCollision(GameObject *p_xpCollider){
	if (p_xpCollider->HasTag("PBullet")){
		m_iLife--;

		if (m_iLife <= 0){
			std::cout << "Dead!";
			DeleteMe();
		}
	}
}

bool EnemyObject0::CanFire(){
	if (m_iBulletAmmo > 0){

		if (m_fFireRate <= 0.f){
			m_iBulletAmmo--;
			m_fFireRate = m_fFireRateMax;

			return true;
		}

		m_fFireRate -= TimeMngr::GetDtime();
	}

	return false;
}