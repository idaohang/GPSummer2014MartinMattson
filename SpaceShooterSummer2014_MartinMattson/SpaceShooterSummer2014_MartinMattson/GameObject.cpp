// GameObject.cpp //

#include "GameObject.h"

#include "CollisionMngr.h"
#include "DrawMngr.h"
#include "GameObjectMngr.h"

#include <iostream>

GameObject::GameObject(){
	GameObjectMngr::AddGameObject(this);

	m_xpParent = NULL;
	m_xpHitbox = NULL;

	m_bDeleteMe = false;
	m_bJustBorn = true;
}

GameObject::~GameObject(){
	/*WriteTags();
	std::cout << " deleted!\n";*/
	if (HasHitbox()){
		CollisionMngr::DeleteHitbox(m_xpHitbox);
	}

	m_xpHitbox = NULL;

	if (HasChild()){
		for (int i = m_xpaChildren.size() - 1; i >= 0; i--){
			delete m_xpaChildren[i];
			/*m_xpaChildren[i] = NULL;
			m_xpaChildren.erase(m_xpaChildren.begin() + i);*/
		}
	}

	RemoveParent();

	GameObjectMngr::ClearGameObject(this);
}

void GameObject::AddParent(GameObject *p_xpParent){
	m_xpParent = p_xpParent;
}

void GameObject::RemoveParent(){
	if (HasParent()){
		GetParent()->ClearChild(this);
	}

	m_xpParent = NULL;
}

bool GameObject::HasParent(){
	return (m_xpParent != NULL);
}

GameObject* GameObject::GetParent(){
	return m_xpParent;
}

void GameObject::AddChild(GameObject *p_xpChild){
	m_xpaChildren.push_back(p_xpChild);
	p_xpChild->AddParent(this);
}

void GameObject::RemoveChild(GameObject *p_xpChild){
	if (HasChild()){
		for (int i = m_xpaChildren.size() - 1; i >= 0; i--){
			if (m_xpaChildren[i] == p_xpChild){
				delete m_xpaChildren[i];
				m_xpaChildren[i] = NULL;
				m_xpaChildren.erase(m_xpaChildren.begin() + i);
			}
		}
	}
}

void GameObject::ClearChild(GameObject *p_xpChild){
	if (HasChild()){
		for (int i = m_xpaChildren.size() - 1; i >= 0; i--){
			if (p_xpChild == m_xpaChildren[i]){
				m_xpaChildren[i] = NULL;
				m_xpaChildren.erase(m_xpaChildren.begin() + i);
			}
		}
	}
}

GameObject* GameObject::GetChild(GameObject *p_xpChild){
	for (int i = m_xpaChildren.size() - 1; i >= 0; i--){
		if (m_xpaChildren[i] == p_xpChild){
			return m_xpaChildren[i];
		}
	}

	return NULL;
}

std::vector<GameObject*> GameObject::GetChildren(){
	return m_xpaChildren;
}

bool GameObject::HasChild(){
	return (m_xpaChildren.size() > 0);
}

int GameObject::ChildrenNumber(){
	return m_xpaChildren.size();
}

void GameObject::AddTag(std::string p_sTag){
	m_saTags.push_back(p_sTag);
}

bool GameObject::HasTag(std::string p_sTag){
	for (int i = 0; i < m_saTags.size(); i++){
		if (m_saTags[i].compare(p_sTag) == 0){
			return true;
		}
	}

	return false;
}

std::vector<std::string> GameObject::GetTags(){
	return m_saTags;
}

void GameObject::WriteTags(){
	for (int i = m_saTags.size() - 1; i >= 0; i--){
		std::cout << m_saTags[i];

		if (i > 0){
			std::cout << ", ";
		}
		else {
			std::cout << ".";
		}
	}
}

Hitbox* GameObject::GetHitbox(){
	return m_xpHitbox;
}

void GameObject::SetHitbox(Hitbox *p_xpHitbox){
	m_xpHitbox = p_xpHitbox;
}

bool GameObject::HasHitbox(){
	return (m_xpHitbox != NULL);
}

void GameObject::SetAllPositions(sf::Vector2f p_vPosition){
	setPosition(p_vPosition);
}

bool GameObject::OnScreen(){
	if (getPosition().x > DrawMngr::GetScreen()->getDefaultView().getSize().x || getPosition().x < 0.f){
		return false;
	}

	if (getPosition().y > DrawMngr::GetScreen()->getDefaultView().getSize().y || getPosition().y < 0.f){
		return false;
	}

	return true;
}

void GameObject::DeleteMe(){
	m_bDeleteMe = true;
}

bool GameObject::CanDelete(){
	return m_bDeleteMe;
}

void GameObject::DeleteChildren(){
	for (int i = m_xpaChildren.size() - 1; i >= 0; i--){
		if (m_xpaChildren[i]->CanDelete()){
			delete m_xpaChildren[i];
			/*m_xpaChildren[i] = NULL;
			m_xpaChildren.erase(m_xpaChildren.begin() + i);*/
		}
	}
}

void GameObject::OnUpdate(){
	if (m_bJustBorn){
		OnCreate();
		m_bJustBorn = false;
	}

	OnUpdateThis();
	OnUpdateChildren();

	DeleteChildren();
}

void GameObject::OnDraw(){
	OnDrawThis();
	OnDrawChildren();
}

void GameObject::OnUpdateChildren(){
	for (int i = m_xpaChildren.size() - 1; i >= 0; i--){
		if (m_xpaChildren[i] != NULL){
			m_xpaChildren[i]->OnUpdate();
		}
		else {
			break;
		}
	}
}

void GameObject::OnDrawChildren(){
	for (int i = m_xpaChildren.size() - 1; i >= 0; i--){
		if (m_xpaChildren[i] != NULL){
			m_xpaChildren[i]->OnDraw();
		}
		else {
			break;
		}
	}
}