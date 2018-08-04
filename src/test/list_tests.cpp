#include "../list.c"

TEST(List, GetAt) {
    list_t *list = list_init();
    EXPECT_EQ(NULL, list_get_at(list, 0));

    list_push_back(list, (char *)"1", false);
    list_push_back(list, (char *)"2", false);

    EXPECT_EQ("1", list_get_at(list, 0)->data);
    EXPECT_EQ("2", list_get_at(list, 1)->data);
    EXPECT_EQ(NULL, list_get_at(list, 2));

    free(list_remove_at(list, 0, active_null));
    free(list_remove_at(list, 0, active_null));

    list_destruct(list);
}

TEST(List, RemoveAt) {
    list_t *list = list_init();
    node_t *node;

    list_push_back(list, (char *)"1", false);
    list_push_back(list, (char *)"2", false);

    //EXPECT_EQ("1", list_remove_at(list, 0)->data);
    EXPECT_EQ("2", (node = list_remove_at(list, 1, active_null))->data);
    EXPECT_EQ(NULL, list_remove_at(list, 2, active_null));

    free(node);
    free(list_remove_at(list, 0, active_null));

    list_destruct(list);
}

TEST(List, AddRemoveAddElement) {
    list_t *list = list_init();
    node_t *node;
    int popped = 0;

    // Push 10
    for (int i = 0; i < 10; i++) {
        list_push_back(list, NULL, false);
    }

    // Pop 7
    for (int i = 0; i < 7; i++) {
        free(list_remove_at(list, 0, active_null));
    }

    // Push 3
    for (int i = 0; i < 3; i++) {
        list_push_back(list, NULL, false);
    }

    // Pop remaining
    while((node = list_remove_at(list, 0, active_null)) != NULL) {
        free(node);
        popped++;
    }
    list_destruct(list);

    // Should be 6 left
    EXPECT_EQ(6, popped);
}

TEST(List, Count) {
    list_t *list = list_init();

    ASSERT_EQ(0, list_count(list));

    list_push_back(list, NULL, false);

    ASSERT_EQ(1, list_count(list));

    list_push_back(list, NULL, false);
    list_push_back(list, NULL, false);

    ASSERT_EQ(3, list_count(list));

    free(list_remove_at(list, 0, active_null));
    free(list_remove_at(list, 0, active_null));

    ASSERT_EQ(1, list_count(list));

    free(list_remove_at(list, 0, active_null));

    list_destruct(list);
}

TEST(List, ActiveNextAndPrev) {
    list_t *list = list_init();

    EXPECT_EQ(NULL, list->active);

    list_active_next(list);
    EXPECT_EQ(NULL, list->active);

    list_push_back(list, NULL, true);
    EXPECT_EQ(list->active, list->last->prev);
    list_push_back(list, NULL, false);
    EXPECT_EQ(list->active, list->last->prev->prev);
    list_active_next(list);
    EXPECT_EQ(list->active, list->last->prev);
    list_active_next(list);
    EXPECT_EQ(list->active, list->first->next);

    free(list_remove_at(list, 0, active_null));
    free(list_remove_at(list, 0, active_null));

    list_active_next(list);
    EXPECT_EQ(NULL, list->active);

    list_active_prev(list);
    EXPECT_EQ(NULL, list->active);

    list_push_back(list, NULL, true);
    list_push_back(list, NULL, true);
    list_push_back(list, NULL, true);
    list_active_prev(list);
    EXPECT_EQ(list->active, list->first->next->next);
    list_active_prev(list);
    list_active_prev(list);
    EXPECT_EQ(list->active, list->last->prev);

    free(list_remove_at(list, 0, active_null));
    free(list_remove_at(list, 0, active_null));
    free(list_remove_at(list, 0, active_null));

    list_destruct(list);
}

TEST(List, ActiveRemoveAndTransfer) {
    list_t *list = list_init();

    list_push_back(list, NULL, true);
    list_push_back(list, NULL, true);
    // Two nodes, last active, pop last
    free(list_remove_at(list, 1, active_null));
    EXPECT_EQ(NULL, list->active);

    list_push_back(list, NULL, true);
    list_push_back(list, NULL, true);
    // Three nodes, last active
    EXPECT_EQ(list->active, list->last->prev);
    // Remove last, active to prev, two nodes left, last active
    free(list_remove_at(list, 2, active_prev));
    EXPECT_EQ(list->active, list->last->prev);

    // Remove all but one which is active
    free(list_remove_at(list, 0, active_null));
    EXPECT_EQ(list->active, list->last->prev);

    // Remove the only node, active to prev (which does not work)
    free(list_remove_at(list, 0, active_prev));
    EXPECT_EQ(NULL, list->active);


    // Three elements, active last, remove active transferring to next
    list_push_back(list, NULL, false);
    list_push_back(list, NULL, false);
    list_push_back(list, NULL, true);
    free(list_remove_at(list, 2, active_next));
    EXPECT_EQ(list->active, list->last->prev);

    // Three elements, active first, remove active transferring to first
    list_push_back(list, NULL, false);
    list->active = list->first->next;
    free(list_remove_at(list, 0, active_prev));
    EXPECT_EQ(list->active, list->first->next);

    free(list_remove_at(list, 0, active_null));
    free(list_remove_at(list, 0, active_null));
    list_destruct(list);
}

