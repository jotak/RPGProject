#include "Test.h"
#include "../Utils/utils.h"
#include "../Data/JoSon/JoSon.h"

bool almostEquals(double d1, double d2) {
	double diff = abs(d1-d2);
	bool ok = diff < 0.001f;
	if (ok && diff > 0.000001f) {
		cout << "WARNING: assertion ok but response no so much accurate!!" << endl;
	}
	return ok;
}

void testF3d() {
	cout << "Starting testF3d..." << endl;

	// Test ctors
	f3d d3;
	assert(d3.x == 0 && d3.y == 0 && d3.z == 0);
	f3d d3b(1,2,3);
	assert(d3b.x == 1 && d3b.y == 2 && d3b.z == 3);

	// Test operators
	d3 = f3d(1,2,3) + 5.1;
	assert(d3.x == 6.1 && d3.y == 7.1 && d3.z == 8.1);

	d3 = f3d(1,2,3) + f3d(0.1,0.2,0.3);
	assert(d3.x == 1.1 && d3.y == 2.2 && d3.z == 3.3);

	d3 = f3d(1,2,3) - f3d(0.1,0.2,0.3);
	assert(d3.x == 0.9 && d3.y == 1.8 && d3.z == 2.7);

	d3 = f3d(1,2,3) * f3d(4,5,6);
	assert(d3.x == 4 && d3.y == 10 && d3.z == 18);

	d3 = f3d(1,2,3) / 2;
	assert(d3.x == 0.5 && d3.y == 1 && d3.z == 1.5);

	d3 = f3d(1,2,3) * 2.5;
	assert(d3.x == 2.5 && d3.y == 5 && d3.z == 7.5);

	// Test trigonometry
	f3d angle(PI/2, 0, PI/4);
	// Check cos
	f3d cosAngle = cos(angle);
	assert(almostEquals(cosAngle.x, 0));
	assert(almostEquals(cosAngle.y, 1));
	assert(almostEquals(cosAngle.z, 0.707106781));

	// Check sin
	f3d sinAngle = sin(angle);
	assert(almostEquals(sinAngle.x, 1));
	assert(almostEquals(sinAngle.y, 0));
	assert(almostEquals(sinAngle.z, 0.707106781));

	// Check tan
	f3d tanHalfAngle = tan(angle / 2);
	assert(almostEquals(tanHalfAngle.x, 1));
	assert(almostEquals(tanHalfAngle.y, 0));
	assert(almostEquals(tanHalfAngle.z, 0.414213562));

	// Check atan
	f3d resAtan = atan(f3d(1, 0, 0.414213562));
	assert(almostEquals(resAtan.x, PI/4));
	assert(almostEquals(resAtan.y, 0));
	assert(almostEquals(resAtan.z, PI/8));

	// Check sqrt
	f3d resSqrt = sqrt(f3d(9, 25, 100));
	assert(resSqrt.x == 3);
	assert(resSqrt.y == 5);
	assert(resSqrt.z == 10);

	cout << "testF3d OK" << endl;
}

void testJoSon() {
	cout << "Starting testJoSon..." << endl;

	string sError;
	JoSon * jsonPtr = JoSon::fromString(string("{a:1, b:[2, 3, \"toto et tata\"], c : foo}"), &sError);
	JoSon& json = *jsonPtr;

	assert(json.isMap());
	assert(json["a"].isLeaf());
	string a = json["a"].toString();
	assert(a == "1");
	assert(json["b"].isList());
	assert(json["b"][0].isLeaf());
	double b0 = json["b"][0].toDouble();
	assert(b0 == 2.0f);
	assert(json["b"][1].isLeaf());
	int b1 = json["b"][1].toInt();
	assert(b1 == 3);
	assert(json["b"][2].isLeaf());
	string b2 = json["b"][2].toString();
	assert(b2 == "toto et tata");
	assert(json["c"].isLeaf());
	string c = json["c"].toString();
	assert(c == "foo");
	assert(json["d"].isNull());
	string d = json["d"].toString();
	assert(d == "");
	assert(json["e"][9].isNull());
	int e = json["e"][9].toInt();
	assert(e == 0);

	delete jsonPtr;
	cout << "testJoSon OK" << endl;
}

void runAllTests() {
	testF3d();
	testJoSon();
}
