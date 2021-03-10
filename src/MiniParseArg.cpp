#include "MiniParseArg.hpp"

MiniParseArg::MiniParseArg(const std::string &binaryName, const MiniParseOption *opts, size_t n, bool helpFlag) noexcept
    : _binaryName(binaryName), _opts(opts, opts + n)
{
    if (helpFlag) {
        setHelpFlag();
    }
    for (auto &&i : _opts) {
        _sets[i.opt] = &i;
        _sets[i.optlong] = &i;
    }
}

void MiniParseArg::setHelpFlag(const std::string &opt, const std::string &optlong) noexcept
{
    const MiniParseOption option = {
        .opt = opt,
        .optlong = optlong,
        .callback = std::bind(&MiniParseArg::displayHelp, this,
                              std::placeholders::_1, std::placeholders::_2),
        .help = "Display this help",
        .argType = "",
    };
    _opts.emplace_back(option);
}

int MiniParseArg::parse(int ac, const char **av) const noexcept
{
    int ret = 0;

    for (int i = 0; i < ac; ++i) {
        if (av[i][0] == '-') {
            ret += checkOpt(ac - i, &av[i]);
        }
    }
    return ret;
}

int MiniParseArg::checkOpt(int ac, const char **av) const noexcept
{
    auto it = _sets.find(av[0]);

    if (it == _sets.end()) {
        std::cerr << "Unknown parameter: '" << av[0] << "'." << std::endl;
        return 1;
    }
    else if (!it->second->argType.empty() && (ac == 1 || av[1][0] == '-')) {
        std::cerr << "Option: '" << av[0] << "' needs an argument." << std::endl;
        return 1;
    }
    try {
        if (it->second->callback(ac, av) == false) {
            std::cerr << "Invalid parameter after '" << av[0] << "' option." << std::endl;
            return 1;
        }
    }
    catch (const std::bad_function_call &err) {
        std::cerr << err.what() << ": " << it->first << std::endl;
        return 1;
    }
    return 0;
}

bool MiniParseArg::displayHelp(int, const char **) const noexcept
{
    std::cout << "USAGE: " << _binaryName << " [OPTIONS]" << std::endl;
    for (auto &&i : _opts) {
        std::cout << std::endl << " " << i.opt;
        if (!i.optlong.empty()) {
            std::cout << ", " << i.optlong;
        }
        if (!i.argType.empty()) {
            std::cout << " [" << i.argType << "]" << std::endl;
        }
        else {
            std::cout << std::endl;
        }
        std::cout << "    " << i.help << std::endl;
    }
    return true;
}