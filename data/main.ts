{
    int i;
    bool j;
    i = 0;
    j = true;

    write("counting...");
    while ((i < 10) && j) {
        write("here");
        write(i);
        if (i == 5) {
            j = false;
        }

        i = i + 1;
    }
}