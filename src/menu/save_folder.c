/**
 * @file save_folder.c
 * @brief Save-folder mode parsing and save path construction.
 * @ingroup menu
 */

#include <string.h>
#include <strings.h>

#include "save_folder.h"

save_folder_mode_t save_folder_mode_parse(const char *value, save_folder_mode_t default_value) {
    if (value == NULL) {
        return default_value;
    }

    if ((strcasecmp(value, "true") == 0) || (strcasecmp(value, "on") == 0) ||
        (strcasecmp(value, "yes") == 0) || (strcmp(value, "1") == 0)) {
        return SAVE_FOLDER_MODE_LOCAL;
    }

    if ((strcasecmp(value, "false") == 0) || (strcasecmp(value, "off") == 0) ||
        (strcasecmp(value, "no") == 0) || (strcmp(value, "0") == 0)) {
        return SAVE_FOLDER_MODE_OFF;
    }

    if ((strcasecmp(value, "root") == 0) || (strcmp(value, "2") == 0)) {
        return SAVE_FOLDER_MODE_ROOT;
    }

    return default_value;
}

const char *save_folder_mode_serialize(save_folder_mode_t mode) {
    switch (mode) {
        case SAVE_FOLDER_MODE_OFF: return "false";
        case SAVE_FOLDER_MODE_ROOT: return "root";
        case SAVE_FOLDER_MODE_LOCAL:
        default: return "true";
    }
}

const char *save_folder_mode_format(save_folder_mode_t mode) {
    switch (mode) {
        case SAVE_FOLDER_MODE_OFF: return "Off";
        case SAVE_FOLDER_MODE_ROOT: return "Root";
        case SAVE_FOLDER_MODE_LOCAL:
        default: return "On";
    }
}

path_t *save_folder_build_path(const char *storage_prefix, path_t *rom_path, save_folder_mode_t mode) {
    path_t *save_path = path_clone(rom_path);
    path_ext_replace(save_path, "sav");

    if (mode == SAVE_FOLDER_MODE_LOCAL) {
        path_push_subdir(save_path, SAVE_DIRECTORY_NAME);
    } else if (mode == SAVE_FOLDER_MODE_ROOT) {
        char *filename = path_last_get(save_path);
        path_t *root_save_path = path_init(storage_prefix, SAVE_DIRECTORY_NAME);
        path_push(root_save_path, filename);
        path_free(save_path);
        save_path = root_save_path;
    }

    return save_path;
}
