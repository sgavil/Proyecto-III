#include "NPC.h"
#include <iostream>

NPC::NPC()
{
}

NPC::~NPC()
{
}

void NPC::load(json file)
{
	hunger_ = file["hunger"];
	peepee_ = file["peepee"];
	fun_ = file["fun"];
}