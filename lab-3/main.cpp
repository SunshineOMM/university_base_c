
#include"UniquePtr.h"
#include"SharedPtr.h"


int main() {
	UniquePtr p1(new int (6));
	UniquePtr p3(new int(6));
	if (p1 == p3) throw"yes";
	SharedPtr p2(new int(6));
}