#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "minhook/include/MinHook.h" 
#include "minhook/src/trampoline.h"
#include "minhook/src/buffer.h"
#include "offsets.h"
#include "Windows.h"

using namespace offsets::client_dll;
using namespace offsets::C_BaseEntity;
using namespace offsets::CBasePlayerController;