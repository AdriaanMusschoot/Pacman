#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include "Base/Scene.h"

namespace amu
{

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update();
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::unique_ptr<Scene>> m_ScenesUPtrVec{};
	};

}