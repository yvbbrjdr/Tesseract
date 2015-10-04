#include "Plugin.h"

Plugin::Plugin() {
    Essential=0;
}

void Plugin::clientLoad(World*,Socket*) {}

void Plugin::clientUnload() {}

void Plugin::serverLoad(World*,Server*) {}

void Plugin::serverUnload() {}

Plugin::~Plugin() {}
