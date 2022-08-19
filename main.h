//Precompiled Header for Project
#pragma once

#ifndef __MAIN_H__
#define __MAIN_H__

//SFML includes
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

/*  Std lib includes  */

//containers
#include <string>
#include <array>
#include <vector>
#include <list>
#include <stack>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <functional>

//Threads
#include <thread>
#include <mutex>

//files
#include <filesystem>

//stream ops
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ostream>

	//Math ops
#include <cmath>
#include <math.h>
#include <algorithm>
#include <cstdlib>
#include <random>

//Exception ops
#include <exception>
#include <stdexcept>

//Libs
#include <boost/algorithm/string.hpp>
#include  <boost/format.hpp>
#include "TinyEXIF.h"
#include <nlohmann/json.hpp>

//Other
#include <ctime>
#include <memory>

//JSON



//Project includes


//Usings
using namespace std;
namespace fs = std::filesystem;
using json = nlohmann::json;



#endif