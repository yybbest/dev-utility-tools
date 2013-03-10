#pragma once

#include "BaseObjLib\export.h"

#include "BaseObjLib\Ref.h"

#include "BaseObjLib\IBaseObj.h"

#include "BaseObjLib\IPluginObj.h"

#include "BaseObjLib\PluginFactory.h"


#ifdef _DEBUG

#pragma comment(lib,"BaseObjLibD.lib")
#pragma message("Automatically linking with BaseObjLibD.lib")

#else

#pragma comment(lib,"BaseObjLib.lib")
#pragma message("Automatically linking with BaseObjLib.lib")

#endif