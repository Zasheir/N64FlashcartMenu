# Modified Version Notice

This repository contains an unofficial modified version of N64FlashcartMenu V0.3.2.

Modified by **Zasheir** on **2026-08-23**.

## Changes

- Added `ROOT` as a third **Use Saves Folder** mode.
- Added centralized save loading and storage at `/saves/<ROM basename>.sav`.
- Made ROMs with identical basenames intentionally share one root save across organizational folders.
- Preserved compatibility with existing `use_saves_folder=true` and `use_saves_folder=false` configurations.
- Applied the selected save-folder mode to native N64 ROMs and emulator-backed ROMs.
- Added host tests for configuration parsing, path resolution, and shared-basename behavior.
- Integrated the host tests into the GitHub Actions build.
- Generalized save-directory error handling.
- Fixed an adjacent path-memory leak in the unsupported Fast Reboot error path.
- Updated menu settings documentation.

The ROOT save-folder behavior has been validated on a physical SummerCart64.

## Original Project

- Original repository: <https://github.com/Polprzewodnikowy/N64FlashcartMenu>
- Base release: [V0.3.2](https://github.com/Polprzewodnikowy/N64FlashcartMenu/releases/tag/V0.3.2)

This modified work remains licensed under the [GNU Affero General Public License v3.0](LICENSE.md). Original copyright, contributor, third-party software, asset attribution, and warranty notices remain intact.
