/**
 * @file save_folder.h
 * @brief Save-folder mode parsing and save path construction.
 * @ingroup menu
 */

#ifndef SAVE_FOLDER_H__
#define SAVE_FOLDER_H__

#include "path.h"

#ifndef SAVE_DIRECTORY_NAME
#define SAVE_DIRECTORY_NAME "saves"
#endif

/** @brief Determines where ROM save files are stored. */
typedef enum {
    SAVE_FOLDER_MODE_OFF = 0,   /**< Store the save alongside the ROM. */
    SAVE_FOLDER_MODE_LOCAL = 1, /**< Store the save in a sibling saves folder. */
    SAVE_FOLDER_MODE_ROOT = 2,  /**< Store the save in the root saves folder. */
} save_folder_mode_t;

/** Parse legacy boolean and tri-state configuration values. */
save_folder_mode_t save_folder_mode_parse(const char *value, save_folder_mode_t default_value);

/** Serialize a save-folder mode for menu/config.ini. */
const char *save_folder_mode_serialize(save_folder_mode_t mode);

/** Return the settings-editor label for a save-folder mode. */
const char *save_folder_mode_format(save_folder_mode_t mode);

/** Build the .sav path for a ROM according to the selected mode. */
path_t *save_folder_build_path(const char *storage_prefix, path_t *rom_path, save_folder_mode_t mode);

#endif
