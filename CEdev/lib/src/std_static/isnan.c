static int double_ne(double n1, double n2) {
    return n1 != n2;
}

int isnan(double n) {
    return double_ne(n, n);
}