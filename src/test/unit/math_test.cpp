#include <catch.hpp>
#include "../../core/math/math_util.h"
#include "../../core/math/vector2.h"
#include "../../core/math/matrices.h"


TEST_CASE("Math Util", "[math]") {
    SECTION("Lerp") {
        float source = 0.0f;
        float destination = 10.0f;

        REQUIRE(MathUtil::Lerp(source, destination, 0.5f) == 5.0f);
        REQUIRE(MathUtil::Lerp(source, destination, 0.25f) == 2.5f);
        REQUIRE(MathUtil::Lerp(source, destination, 0.75f) == 7.5f);

    }
}

TEST_CASE("Vector2", "[math]") {
    SECTION("General") {
        Vector2 test = Vector2(1.0f, 1.0f);

        REQUIRE(test == Vector2(1.0f, 1.0f));

        test += Vector2(1.0, 1.0);

        REQUIRE(test == Vector2(2.0f, 2.0f));
    }

    SECTION("Lerp") {
        Vector2 test = Vector2(5.0f, 5.0f);

        REQUIRE(test.Lerp(Vector2(10.0f, 10.0f), 0.5f) == Vector2(7.5f, 7.5f));
    }
}

TEST_CASE("Matrix4", "[math]") {
    SECTION("General") {
        Matrix4 test = Matrix4(1.0f, 1.0f, 1.0f, 1.0f,
                               1.0f, 1.0f, 1.0f, 1.0f,
                               1.0f, 1.0f, 1.0f, 1.0f,
                               1.0f, 1.0f, 1.0f, 1.0f);

        REQUIRE(test == Matrix4(1.0f, 1.0f, 1.0f, 1.0f,
                                1.0f, 1.0f, 1.0f, 1.0f,
                                1.0f, 1.0f, 1.0f, 1.0f,
                                1.0f, 1.0f, 1.0f, 1.0f));

        test.SetRow(1, 0.0f, 2.0f, 3.0f, 10.0f);

        REQUIRE(test == Matrix4(1.0f, 1.0f, 1.0f, 1.0f,
                                0.0f, 2.0f, 3.0f, 10.0f,
                                1.0f, 1.0f, 1.0f, 1.0f,
                                1.0f, 1.0f, 1.0f, 1.0f));
    }

    SECTION("Multiplication") {
        Matrix4 test1 = Matrix4(0.0f, 1.0f, 0.0f, 0.0f,
                                1.0f, 0.0f, 1.0f, 1.0f,
                                0.0f, 1.0f, 0.0f, 1.0f,
                                0.0f, 1.0f, 1.0f, 0.0f);

        Matrix4 test2 = Matrix4(0.0f, 1.0f, 0.0f, 0.0f,
                                1.0f, 0.0f, 1.0f, 1.0f,
                                0.0f, 1.0f, 0.0f, 1.0f,
                                0.0f, 1.0f, 1.0f, 0.0f);

        REQUIRE(test1 * test2 == Matrix4(1.0f, 0.0f, 1.0f, 1.0f,
                                         0.0f, 3.0f, 1.0f, 1.0f,
                                         1.0f, 1.0f, 2.0f, 1.0f,
                                         1.0f, 1.0f, 1.0f, 2.0f));

        Matrix4 test3 = Matrix4(2.0f, 1.0f, 2.0f, 0.0f,
                                4.0f, 3.0f, 1.0f, 1.0f,
                                2.0f, 4.0f, 1.0f, 1.0f,
                                5.0f, 5.0f, 1.0f, 1.0f);

        Matrix4 test4 = Matrix4(2.0f, 1.0f, 2.0f, 3.0f,
                                1.0f, 1.0f, 1.0f, 1.0f,
                                2.0f, 1.0f, 3.0f, 1.0f,
                                3.0f, 1.0f, 1.0f, 3.0f);

        REQUIRE(test3 * test4 == Matrix4(9.0f, 5.0f, 11.0f, 9.0f,
                                         16.0f, 9.0f, 15.0f, 19.0f,
                                         13.0f, 8.0f, 12.0f, 14.0f,
                                         20.0f, 12.0f, 19.0f, 24.0f));
    }
}
