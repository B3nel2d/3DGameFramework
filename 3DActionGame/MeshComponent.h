//======================================================================
//
//	MeshComponent
//
//	メッシュのコンポーネントクラス
//
//======================================================================

#pragma once

#include "Component.h"
#include "Graphics.h"

class MeshComponent : public Component{
	private:
		Mesh mesh;

		class TransformComponent* transform;

	public:
		MeshComponent(class Actor* owner, class Level* level);
		virtual ~MeshComponent();

		void initialize(const char* fileName);

		void draw();

		Mesh getMesh(){return mesh;}
};
