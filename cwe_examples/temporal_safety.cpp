class Bob {
    int *n;
public:
    Bob(int x) {
        this->n = new int[x];
    }
    ~Bob() {
        delete[] this->n;
    }
    int* get_n() {
        return this->n;
    }
};
int main() {
    Bob *b = new Bob(5);
    int *xs = b->get_n();
    delete b;
    printf("%d", xs[0]);
}
