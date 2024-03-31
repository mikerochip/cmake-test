#include <string>
#include "CLI/CLI.hpp"
#include "fmt/core.h"
#include "MyApp/Foo.h"
#include "MyLibrary/Foo.h"
#include "Poco/MD5Engine.h"
#include "Poco/DigestStream.h"

using namespace fmt;
using namespace std;

#define ERGONOMIC_CPP_APP_NAME "1.0.0"
#define ERGONOMIC_CPP_APP_VERSION "1.0.0"

void BuildCommandParser(CLI::App& app);
string GeneratePocoMd5Hex();

int main(int argc, char** argv)
{
    print("Hello, World!\n");

    MyApp::Foo myAppFoo;
    print("MyApp::Foo={}\n", myAppFoo.GenerateNumber());

    MyLibrary::Foo myLibraryFoo;
    print("MyLibrary::Foo={}\n", myLibraryFoo.GenerateNumber());

    string md5Hex = GeneratePocoMd5Hex();
    print("Poco::MD5::Hex={}\n", md5Hex);

    CLI::App app;
    BuildCommandParser(app);
    CLI11_PARSE(app, argc, argv)

    auto&& options = app.get_options();
    print("CLI::App::Options={}\n", options.size());
    for (auto&& option : options)
        print("{}\n", option->get_name());
    return 0;
}

void BuildCommandParser(CLI::App& app)
{
    app.name(ERGONOMIC_CPP_APP_NAME);
    app.set_version_flag("--version", ERGONOMIC_CPP_APP_VERSION);
    app.allow_extras(true);

    int count = 0;
    app.add_option("-c,--count", count, "Counter");

    double value = 0.0;
    app.add_option("-d,--double", value, "Some Value");

    // NOTE: Passing an int as the flag value causes memory corruption in the CLI::App object.
    bool flag = false;
    app.add_flag("--flag", flag, "Some flag that can be passed multiple times");
}

string GeneratePocoMd5Hex()
{
    Poco::MD5Engine md5;
    Poco::DigestOutputStream ds(md5);
    ds << "abcdefghijklmnopqrstuvwxyz";
    ds.close();
    return Poco::DigestEngine::digestToHex(md5.digest());
}
