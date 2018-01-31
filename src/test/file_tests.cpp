#include "../file.c"

TEST(File, ReadFile) {
    EXPECT_EQ(0, file_read((char *)"hej"));
}

