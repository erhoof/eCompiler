{
    int[2][2] i;
    int c1;
    int c2;
    int temp;

    i[0][0] = 0;
    i[0][1] = 1;
    i[1][0] = 1;
    i[1][1] = 2;

    c1 = 0;
    c2 = 0;
    while (c1 < 2) {
        c2 = 0;

        while(c2 < 2) {
            temp = i[c1][c2];
            write(temp);

            c2 = c2 + 1;
        }

        c1 = c1 + 1;
    }
}