#pragma once

#include <functional>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

class MiniParseArg {
    public:
        struct MiniParseOption {
            std::string opt;
            std::string optlong;
            std::function<bool (int, const char **)> callback;
            std::string help = "";
            std::string argType = "STRING";
        };

        MiniParseArg(const std::string &binaryName, const MiniParseOption *opts = NULL, size_t n = 0, bool helpFlag = true) noexcept;
        int parse(int ac, const char **av) const noexcept;
    protected:
        void setHelpFlag(const std::string &opt = "-h", const std::string &optlong = "--help") noexcept;
        int checkOpt(int ac, const char **av) const noexcept;
        bool displayHelp(int ac, const char **av) const noexcept;
        std::string _binaryName;
        std::vector<MiniParseOption> _opts;
        std::unordered_map<std::string, MiniParseOption *> _sets;
};