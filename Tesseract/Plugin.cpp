#include "Plugin.h"

Plugin::Plugin() {
    Essential=0;
}

void Plugin::clientLoad(World&) {}

void Plugin::clientUnload(World&) {}

void Plugin::serverLoad(World&) {}

void Plugin::serverUnload(World&) {}

Plugin::~Plugin() {}
