#include "level_manager.hpp"

LevelManager::LevelManager() {}

std::shared_ptr<entcosy::Registry> LevelManager::getRegistry()
{

    // std::cout << "Use count: " << m_registries.front().use_count() << "\n";
    return m_registries.front();
}

void LevelManager::load(const char* file)
{
    {
        std::shared_ptr<entcosy::Registry> loadedRegistry;
        std::cout << "Loading " << file << " data...\n";
        {
            std::ifstream is(file, std::ios::binary);
            cereal::BinaryInputArchive archive(is);
            archive(loadedRegistry);
            is.close();
        }
        if(m_registries.size() > 0)
        {
            m_defferedLoad = true;
        }
        m_registries.emplace_back(loadedRegistry);
    }
    // std::cout << "Size: "<< m_registries.size() <<" Use count: " << m_registries.back().use_count() << "\n";
    m_registries.back()->registerSystem(std::make_shared<CameraSystem>());
    m_registries.back()->registerSystem(std::make_shared<PolygonSystem>());
    m_registries.back()->registerSystem(std::make_shared<PhysicsSystem>(50.0f));
    m_registries.back()->registerSystem(std::make_shared<PlayerControlSystem>());
    m_registries.back()->registerSystem(std::make_shared<BulletSystem>());
    std::cout << file << " data loaded\n";
}

void LevelManager::save(const char* file)
{
    std::cout << "Saving " << file << " data...\n";
    std::ofstream os(file, std::ios::binary);
    cereal::BinaryOutputArchive archive(os);
    archive(m_registries.front());
    std::cout << file << " data saved\n";
}

bool LevelManager::swap()
{

    if(m_defferedLoad)
    {
        for(auto i = m_registries.begin(); i != m_registries.end()-1; i++)
        {
            std::shared_ptr<entcosy::Registry> registry = *i;
            // std::cout << "Size : " << registry->getCount() << " Use count: " << registry.use_count() << "\n";
            registry->clear();
            // std::cout << "Size : " << registry->getCount() << " Use count: " << registry.use_count() << "\n";
        }
        // std::cout << "Size: "<< m_registries.size() <<" Use count: " << m_registries.front().use_count() << "\n";

        m_registries.front().swap(m_registries.back());

        // m_registries.back().reset();
        m_registries.erase(m_registries.begin()+1, m_registries.end());
        m_defferedLoad = false;
        return true;
    }
    return false;
}
