struct Pt {
    int x, y;
};

struct Pt points[20];

int count() {
    int i, n;
    for (i = n = 0; i < 10; i = i + 1) {
        if (points[i].x >= 0 && points[i].y >= 0) n = n + 2;
    }
    return n;
}

void main() {
    put_i(count());
}