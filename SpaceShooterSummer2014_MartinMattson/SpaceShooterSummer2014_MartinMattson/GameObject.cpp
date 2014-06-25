// GameObject.cpp //

#include "GameObject.h"

GameObject::GameObject(){
	
}

GameObject::~GameObject(){
	/*RemoveParent();
	
	for (int i = m_xpaChildren.size() - 1; i >= 0; i--){
		RemoveChild(m_xpaChildren[i]);
	}*/
}

void GameObject::AddParent(GameObject *p_xpParent){
	RemoveParent();
	m_xpParent = p_xpParent;
}

void GameObject::RemoveParent(){
	if (HasParent()){
		//m_xpParent->RemoveChild(this);
	}

	m_xpParent = NULL;
	delete m_xpParent;
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

Hitbox* GameObject::GetHitbox(){
	return m_xpHitbox;
}

bool GameObject::HasHitbox(){
	return (m_xpHitbox != NULL);
}

bool GameObject::IsColliding(sf::Vector2f p_vPos, Hitbox *p_xpHitbox){
	return false;
}

void GameObject::OnUpdate(){
	OnUpdateThis();
	OnUpdateChildren();
}

void GameObject::OnDraw(){
	OnDrawThis();
	OnDrawChildren();
}

void GameObject::OnUpdateChildren(){
	for (int i = 0; i < m_xpaChildren.size(); i++){
		m_xpaChildren[i]->OnUpdate();
	}
}

void GameObject::OnDrawChildren(){
	for (int i = 0; i < m_xpaChildren.size(); i++){
		m_xpaChildren[i]->OnDraw();
	}
}