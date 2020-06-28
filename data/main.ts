{
    int i;
    bool j;
    j = true;
    i = 0;

    while (true) {
        write("hello");
    }

    while ((i<10) && j) {
        write(i);
        i = i + 1;

        if (i == 5) {
            j = false;
        }
    }

    write(i);
}