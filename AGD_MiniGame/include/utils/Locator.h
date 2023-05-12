#include <memory>

class AudioManager;

class ServiceLocator {

public:
    ServiceLocator();
    ~ServiceLocator();

    std::shared_ptr<AudioManager> getAudioManager();

private:
    std::shared_ptr<AudioManager> audioManagerService;
};