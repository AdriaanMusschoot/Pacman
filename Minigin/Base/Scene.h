#pragma once
#include "GameObject.h"
#include <vector>
#include <memory>
#include <string>

namespace amu
{
	class Scene final
	{
	public:
		explicit Scene(const std::string& name);
		~Scene();

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void Add(std::unique_ptr<GameObject> object);
		void Remove(const std::unique_ptr<GameObject>& object);
		void RemoveAll();

		void Update();
		void Render() const;

	private:
		std::string m_name = "";
		std::vector<std::unique_ptr<GameObject>> m_GameObjectUPtrVec{};

		static unsigned int m_idCounter; 
	};

}
