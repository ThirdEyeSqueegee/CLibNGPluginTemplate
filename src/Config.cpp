#include "Config.h"

const Config& Config::GetSingleton() noexcept {
    static Config instance;

    static std::atomic_bool initialized;
    static std::latch latch(1);
    if (!initialized.exchange(true)) {
        std::ifstream inputFile(R"(Data\SKSE\Plugins\BookAutoReader.yaml)");
        if (inputFile.good()) {
            instance.Deserialize(inputFile);
        }
        latch.count_down();
    }
    latch.wait();

    return instance;
}

void Debug::Deserialize(std::istream& in) {
    // TODO: Implement this.
}

void Config::Deserialize(std::istream& in) {
    _debug.Deserialize(in);
}
