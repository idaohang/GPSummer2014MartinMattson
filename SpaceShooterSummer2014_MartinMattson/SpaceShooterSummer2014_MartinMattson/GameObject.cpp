// GameObject.cpp //

#include "GameObject.h"

GameObject::GameObject(){
	
}

GameObject::~GameObject(){

}

void GameObject::AddParent(GameObject *p_xpParent){
	m_xpParent = p_xpParent;
}

void GameObject::RemoveParent(){
	m_xpParent = NULL;
}

bool GameObject::HasParent(){
	return (m_xpParent != NULL);
}

GameObject* GameObject::GetParent(){
	return m_xpParent;
}

void GameObject::AddChild(GameObject *p_xpChild){
	/*for (int i = 0; i < m_xpaChildren.size(); i++){
		if (m_xpaChildren[i] == NULL){
			m_xpaChildren[i] = std::unique_ptr<GameObject>(p_xpChild);
			return;
		}
	}*/

	m_xpaChildren.push_back(std::unique_ptr<GameObject>(p_xpChild));
	p_xpChild->AddParent(this);
}

void GameObject::RemoveChild(GameObject *p_xpChild){
	if (HasChild()){
		for (int i = m_xpaChildren.size() - 1; i >= 0; i--){
			if (m_xpaChildren[i].get() == p_xpChild){
				//delete m_xpaChildren[i];
				m_xpaChildren[i] = NULL;
				m_xpaChildren.erase(m_xpaChildren.begin() + i);
			}
		}
	}
}

GameObject* GameObject::GetChild(GameObject *p_xpChild){
	for (int i = m_xpaChildren.size() - 1; i >= 0; i--){
		if (m_xpaChildren[i].get() == p_xpChild){
			return m_xpaChildren[i].get();
		}
	}

	return NULL;
}

/*std::vector<std::unique_ptr<GameObject>> GameObject::GetChildren(){
	return m_xpaChildren;
}*/

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