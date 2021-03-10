#include "MiniParseArg.hpp"

int main(int ac, const char **av)
{
    struct flags {
        bool lflag = false;
        int magicNumber = 0;
    } userFlags;
    static const MiniParseArg::MiniParseOption options[] = {
        {
            .opt = "-l",
            .optlong = "--list",
            .callback = [&](int, const char **) -> bool {
                userFlags.lflag = true;
                return true;
            },
            .help = "List the program arguments.",
            // This is a boolean setter, we don't need a following argument
            .argType = "",
        },
        {
            .opt = "-m",
            .optlong = "--magic",
            .callback = [&](int, const char **av) -> bool {
                try {
                    // av[0] contains the flag itself, av[1] the first argument and so on
                    userFlags.magicNumber = std::stoi(av[1]);
                    return true;
                } catch (const std::invalid_argument &) {
                    return false;
                }
            },
            .help = "Set a useless magic number.",
            .argType = "INT"
        },
    };
    // I use av[0] as the program name
    MiniParseArg parser(av[0], options, sizeof(options) / sizeof(*options));
    int res = parser.parse(ac, av);

    if (res != 0) {
        return res;
    }
    if (userFlags.lflag == true) {
        for (int i = 0; i < ac; ++i)
            std::cout << av[i] << std::endl;
    }
    std::cout << "The magic number is " << userFlags.magicNumber << std::endl;
    return 0;
}