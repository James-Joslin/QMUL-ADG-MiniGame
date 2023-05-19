#include <memory>

class AudioManager;

class ServiceLocator {

public:
    ServiceLocator();
    ~ServiceLocator();

    static std::shared_ptr<AudioManager> getAudioManager();

private:
    static std::shared_ptr<AudioManager> audioManagerService;
};