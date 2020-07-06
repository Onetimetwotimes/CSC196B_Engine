#include "core.h"
#include "vector.h"
#include "shape.h"

int main() { 
	char name[] = "put window name here"; 
	Core::Init(name, 800, 600); 
	Core::GameLoop(); 
	Core::Shutdown(); }