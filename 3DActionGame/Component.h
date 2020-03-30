//======================================================================
//
//	Component
//
//	コンポーネントの基底クラス
//
//======================================================================

#pragma once

class Component{
	public:
		enum State{
			active,
			inactive
		};

	protected:
		State state;
		int updateOrder;

		class Actor* owner;

	public:
		Component(class Actor* owner, int updateOrder = 0);
		virtual ~Component();

		virtual void update();

		State getState(){return state;}
		void setState(State state){this->state = state;}

		int getUpdateOrder(){return updateOrder;}

		class Actor* getOwner(){return owner;}
};
