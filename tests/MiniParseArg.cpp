#include <criterion/criterion.h>

#include "MiniParseArg.hpp"

Test(parse, simple_args)
{
    struct human {
        bool isFrench;
        int age;
        float height;
        std::string name;
    } data;

    const MiniParseArg::MiniParseOption options[] = {
        {
            .opt = "-f",
            .optlong = "--french",
            .callback = [&](int, const char **) -> bool {
                data.isFrench = true;
                return true;
            },
            .help = "Set the human to French.",
            .argType = ""
        },
        {
            .opt = "-a",
            .optlong = "--age",
            .callback = [&](int, const char **argv) -> bool {
                try {
                    data.age = std::stoi(argv[1]);
                    return true;
                } catch (const std::invalid_argument &) {
                    return false;
                }
            },
            .help = "Set the human age.",
            .argType = "INT"
        },
        {
            .opt = "-h",
            .optlong = "--height",
            .callback = [&](int, const char **argv) -> bool {
                try {
                    data.height = std::stof(argv[1]);
                    return true;
                } catch (const std::invalid_argument &) {
                    return false;
                }
            },
            .help = "Set the human height.",
            .argType = "FLOAT"
        },
        {
            .opt = "-n",
            .optlong = "--name",
            .callback = [&](int, const char **argv) {
                if (strlen(argv[1]) == 0)
                    return false;
                data.name = argv[1];
                return true;
            },
            .help = "Set the human age.",
            .argType = "INT"
        },
    };
    const char *ARGV[] = {
        "-f",
        "--age",
        "22",
        "--height",
        "1.87",
        "-n",
        "Léandre",
        "-h"
    };
    const int ARGC = sizeof(ARGV) / sizeof(*ARGV);
    MiniParseArg parser("tester", options, sizeof(options) / sizeof(*options));

    int res = parser.parse(ARGC, ARGV);
    cr_assert(res == 0);
    cr_assert(data.age == 22);
    cr_assert(data.isFrench == true);
    cr_assert(data.height == 1.87f);
    cr_assert(data.name == "Léandre");

}