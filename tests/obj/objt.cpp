#include "gtest/gtest.h"
#include "obj_parse.h"

TEST(objectTest, simple1)
{
	obj_model m("tests/obj/simple_1.obj");

	EXPECT_EQ(m.v.size(), 1);
	EXPECT_EQ(m.v[0].a, 0.0);
	EXPECT_EQ(m.v[0].b, 0.0);
	EXPECT_EQ(m.v[0].c, 0.0);
}

TEST(objectTest, simple2)
{
	obj_model m("tests/obj/simple_2.obj");

	EXPECT_EQ(m.v.size(), 2);
	EXPECT_EQ(m.v[0].a, 0.0);
	EXPECT_EQ(m.v[0].b, 0.0);
	EXPECT_EQ(m.v[0].c, 0.0);
	// Float problems?
	//EXPECT_EQ(m.v[1].a, 1);
	//EXPECT_EQ(m.v[1].b, 2);
	//EXPECT_EQ(m.v[1].c, 3);
}

#if 0
TEST(objectTest, simple3)
{
	obj_model m("tests/obj/simple_3.obj");

	EXPECT_EQ(m.v.size(), 3);
	EXPECT_EQ(m.v[0].a, 0.0);
	EXPECT_EQ(m.v[0].b, 0.0);
	EXPECT_EQ(m.v[0].c, 0.0);
v 1.2 3.1 5.7
vt 0.9 2.8
vn 45.0 46.0 47.0
#endif

TEST(objectTest, jakecube)
{
	obj_model m("tests/obj/cube.obj");

	EXPECT_EQ(m.v.size(), 10);
}
