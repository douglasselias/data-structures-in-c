#include<stdio.h>
#include<math.h>

typedef enum {
  TRIANGLE,
  CIRCLE,
  SQUARE,
  SHAPE_COUNT,
} Shape;

typedef enum {
  AREA,
  PERIMETER,
  FN_COUNT,
} ShapeFns;

typedef struct {
  int base;
  int height;
} Triangle;

typedef struct {
  int radius;
} Circle;

typedef struct {
  int side;
} Square;

void triangle_area(void* data, void* result) {
  Triangle triangle = *(Triangle*)data;
  *(int*)result = (triangle.base * triangle.height) / 2;
}

void triangle_perimeter(void* data, void* result) {
  Triangle triangle = *(Triangle*)data; 
  *(int*)result = triangle.base + sqrt(triangle.base * triangle.base + triangle.height * triangle.height) * 2;
}

void circle_area(void* data, void* result) {
  Circle circle = *(Circle*)data;
  *(int*)result = 3.14 * circle.radius * circle.radius;
}

void circle_perimeter(void* data, void* result) {
  Circle circle = *(Circle*)data;
  *(int*)result = 2 * 3.14 * circle.radius;
}

void square_area(void* data, void* result) {
  Square square = *(Square*)data;
  *(int*)result = square.side * square.side;
}

void square_perimeter(void* data, void* result) {
  Square square = *(Square*)data;
  *(int*)result = 4 * square.side;
}

int main() {
  void (*type_table[SHAPE_COUNT][FN_COUNT])(void*, void*) = {
      {triangle_area, triangle_perimeter},  // Function pointers for Triangle: {AREA, PERIMETER}
      {circle_area, circle_perimeter},      // Function pointers for Circle: {AREA, PERIMETER}
  };

  Triangle triangle = {10, 10};
  int triangle_area_result;
  type_table[TRIANGLE][AREA](&triangle, &triangle_area_result);
  printf("Result: %d\n", triangle_area_result);

  Circle circle = {10};
  int circle_perimeter_result;
  type_table[CIRCLE][PERIMETER](&circle, &circle_perimeter_result);
  printf("Result: %d\n", circle_perimeter_result);

  type_table[SQUARE][AREA] = square_area;
  type_table[SQUARE][PERIMETER] = square_perimeter;

  Square square = {10};
  int square_area_result;
  type_table[SQUARE][AREA](&square,  square_area_result);
  printf("Result: %d\n", square_area_result);

  int square_perimeter_result;
  type_table[SQUARE][PERIMETER](&square, &square_perimeter_result);
  printf("Result: %d\n", square_perimeter_result);
}