#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "menu/path.h"
#include "menu/save_folder.h"

static void test_parse_legacy_and_root_values(void) {
    assert(save_folder_mode_parse("true", SAVE_FOLDER_MODE_OFF) == SAVE_FOLDER_MODE_LOCAL);
    assert(save_folder_mode_parse("ON", SAVE_FOLDER_MODE_OFF) == SAVE_FOLDER_MODE_LOCAL);
    assert(save_folder_mode_parse("yes", SAVE_FOLDER_MODE_OFF) == SAVE_FOLDER_MODE_LOCAL);
    assert(save_folder_mode_parse("1", SAVE_FOLDER_MODE_OFF) == SAVE_FOLDER_MODE_LOCAL);

    assert(save_folder_mode_parse("false", SAVE_FOLDER_MODE_LOCAL) == SAVE_FOLDER_MODE_OFF);
    assert(save_folder_mode_parse("OFF", SAVE_FOLDER_MODE_LOCAL) == SAVE_FOLDER_MODE_OFF);
    assert(save_folder_mode_parse("no", SAVE_FOLDER_MODE_LOCAL) == SAVE_FOLDER_MODE_OFF);
    assert(save_folder_mode_parse("0", SAVE_FOLDER_MODE_LOCAL) == SAVE_FOLDER_MODE_OFF);

    assert(save_folder_mode_parse("root", SAVE_FOLDER_MODE_OFF) == SAVE_FOLDER_MODE_ROOT);
    assert(save_folder_mode_parse("2", SAVE_FOLDER_MODE_OFF) == SAVE_FOLDER_MODE_ROOT);
    assert(save_folder_mode_parse(NULL, SAVE_FOLDER_MODE_LOCAL) == SAVE_FOLDER_MODE_LOCAL);
    assert(save_folder_mode_parse("invalid", SAVE_FOLDER_MODE_OFF) == SAVE_FOLDER_MODE_OFF);
}

static void test_serialize_and_format_modes(void) {
    assert(strcmp(save_folder_mode_serialize(SAVE_FOLDER_MODE_OFF), "false") == 0);
    assert(strcmp(save_folder_mode_serialize(SAVE_FOLDER_MODE_LOCAL), "true") == 0);
    assert(strcmp(save_folder_mode_serialize(SAVE_FOLDER_MODE_ROOT), "root") == 0);

    assert(strcmp(save_folder_mode_format(SAVE_FOLDER_MODE_OFF), "Off") == 0);
    assert(strcmp(save_folder_mode_format(SAVE_FOLDER_MODE_LOCAL), "On") == 0);
    assert(strcmp(save_folder_mode_format(SAVE_FOLDER_MODE_ROOT), "Root") == 0);
}

static void assert_save_path(const char *source, save_folder_mode_t mode, const char *expected) {
    path_t *source_path = path_create(source);
    path_t *save_path = save_folder_build_path("sd:/", source_path, mode);
    assert(strcmp(path_get(save_path), expected) == 0);
    path_free(save_path);
    path_free(source_path);
}

static void test_save_paths(void) {
    assert_save_path("sd:/Games/Racing/F-Zero X.z64", SAVE_FOLDER_MODE_OFF,
                     "sd:/Games/Racing/F-Zero X.sav");
    assert_save_path("sd:/Games/Racing/F-Zero X.z64", SAVE_FOLDER_MODE_LOCAL,
                     "sd:/Games/Racing/saves/F-Zero X.sav");
    assert_save_path("sd:/Games/Racing/F-Zero X.z64", SAVE_FOLDER_MODE_ROOT,
                     "sd:/saves/F-Zero X.sav");
    assert_save_path("sd:/Mario.v1.2.z64", SAVE_FOLDER_MODE_ROOT,
                     "sd:/saves/Mario.v1.2.sav");
}

static void test_root_mode_shares_identical_basenames(void) {
    path_t *first = path_create("sd:/By Genre/Platformers/Mario 64.z64");
    path_t *second = path_create("sd:/By Series/Mario/Mario 64.v64");
    path_t *first_save = save_folder_build_path("sd:/", first, SAVE_FOLDER_MODE_ROOT);
    path_t *second_save = save_folder_build_path("sd:/", second, SAVE_FOLDER_MODE_ROOT);

    assert(strcmp(path_get(first_save), "sd:/saves/Mario 64.sav") == 0);
    assert(strcmp(path_get(first_save), path_get(second_save)) == 0);

    path_free(second_save);
    path_free(first_save);
    path_free(second);
    path_free(first);
}

int main(void) {
    test_parse_legacy_and_root_values();
    test_serialize_and_format_modes();
    test_save_paths();
    test_root_mode_shares_identical_basenames();
    puts("save folder tests passed");
    return 0;
}
