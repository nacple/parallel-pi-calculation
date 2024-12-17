#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

#define radius 1.0
#define edge 2.0

typedef struct point_struct {
    double x;
    double y;
} point;

point newPoint() {
    point pt;
    pt.x = (double)rand() / (RAND_MAX) * edge;
    pt.y = (double)rand() / (RAND_MAX) * edge;
    return pt;
}

double distance(point pt) {
    return (pt.x - radius) * (pt.x - radius) + (pt.y - radius) * (pt.y - radius);
}

int main() {
    int point_count;
    int n = 0;
    printf("Enter point count: ");
    fflush(stdout);
    scanf("%d", &point_count);
    srand(time(NULL));

    double timer = omp_get_wtime();

    for(int i = 0; i < point_count; i++) {
        point pt = newPoint();
        if(distance(pt) < radius) {
            n++;
        }
    }

    timer = omp_get_wtime() - timer;

    printf("Serial | Points: %d, PI: %lf, time: %lf\n", point_count, 4.0*n/point_count, timer);

    n = 0;
    timer = omp_get_wtime();

    #pragma omp parallel for reduction(+:n)
    for(int i = 0; i < point_count; i++) {
        point pt = newPoint();
        if(distance(pt) < radius) {
            n++;
        }
    }

    timer = omp_get_wtime() - timer;

    printf("Parallel | Points: %d, PI: %lf, time: %lf\n", point_count, 4.0*n/point_count, timer);

    return 0;
}