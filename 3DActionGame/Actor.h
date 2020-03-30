//======================================================================
//
//	Actor
//
//	アクターを規定しコンポーネントを管理するクラス
//
//======================================================================

#pragma once

#include <vector>
#include <typeinfo>

using namespace std;

class Actor{
	public:
		enum State{
			active,
			inactive,
			deleted
		};

		enum Tag{
			none,
			player,
			platform
		};

	protected:
		State state;
		Tag tag;

		vector<class Component*> components;

		class Level* level;

	public:
		Actor(class Level* level);
		virtual ~Actor();

		virtual void update();
		void addComponent(class Component* component);
		void removeComponent(class Component* component);

		State getState(){return state;}
		void setState(State state){this->state = state;}

		Tag getTag(){return tag;}
		void setTag(Tag tag){this->tag = tag;}

		class Level* getLevel(){return level;}

		template <typename Type>
		Type* getComponent(){
			auto iterator = components.begin();
			for(; iterator != components.end(); ++iterator){
				auto elementPointer = *iterator;

				if(typeid(*elementPointer) == typeid(Type)){
					return dynamic_cast<Type*>(*iterator);
				}
			}

			return nullptr;
		}
};
