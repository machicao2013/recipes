bool has_circle(list *head)
{
    bool result = false;
    int j = 1;

    list *fast, *slow;

    // for(fast = slow = head; fast != NULL;) {
        // if (j & 2 == 0) {
            // fast = fast->next;
        // } else {
            // fast = fast->next;
            // slow = slow->next;
        // }
        // j++;
        // if (fast == slow) {
            // result = true;
            // break;
        // }
    // }

    for(fast = slow = head; fast != NULL; fast = fast->next) {
        if (j & 1 == 0) {
            if (fast == slow) {
                result = true;
                break;
            }
            slow = slow->next;
        }
        j++;
    }
    return result;
}
