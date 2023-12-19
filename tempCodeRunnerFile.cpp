void quickSort(vector<User> &users, int bottom, int top, int choice)
{
    if (bottom < top)
    {
        int pivot = partition(users, bottom, top, choice);
        quickSort(users, bottom, pivot - 1, choice);
        quickSort(users, pivot + 1, top, choice);
    }
}