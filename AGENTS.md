# AGENTS.md - Adaptive Shooter C++/Lua Project

## Quick Build Commands

### Fresh Clone
```bash
git clone --recurse-submodules https://github.com/killerasus/adaptive_shooter.git
cd adaptive_shooter
```

### Existing Clone
```bash
git submodule update --init --recursive
```

### Linux Build
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
./build/bin/AdaptiveShooter
```

### Windows Build
- Open folder in Visual Studio 2019/2022, select x64-Release, press F5 (recommended)
- Or from CLI: `cmake -B build && cmake --build build --config Release` then `.\\build\\bin\\Release\\AdaptiveShooter.exe`
  - On first build, CMake builds the ClanLib submodule in-tree via `add_subdirectory()` (modules App/Display/GL/Sound + Core)
  - **No `configure.exe` is used** - fully CMake-driven from the bundled `cmake`-branch submodule source
  - ClanLib DLLs are placed next to `AdaptiveShooter.exe` automatically
  - **Requires**: Visual Studio 2019/2022 with MSBuild in PATH (Developer Command Prompt, or `vswhere`-discoverable install)

## Dependency Management

- **ClanLib 3.0**: `dependencies/clanlib/` on branch **`cmake`** (see `.gitmodules`) - Built in-tree via `add_subdirectory()` with `CLANLIB_BUILD_ALL=ON` (upstream per-module cache vars are shadowed by its own defaults, so ALL is the reliable switch) on both Linux and Windows. No autotools, no `configure.exe`. A system ClanLib is still honored if `find_package` finds one (e.g. `-DCLANLIB_ROOT_DIR=`).
- **Upstream fixes on the `cmake` branch** (commit `d196a8e`, required for this build): root `CMakeLists.txt` uses `CMAKE_CURRENT_SOURCE_DIR` + appends real include roots (upstream used `CMAKE_SOURCE_DIR`, broken under `add_subdirectory`); `Sources/App/Win32/clanapp.cpp` exports `WinMain` via `/EXPORT` pragma for DLL consumers. Must be pushed to origin for fresh clones to get them.
- **`cmake/FindXrender.cmake` is ours, not upstream's**: the ClanLib `cmake` branch calls `find_package(Xrender REQUIRED)` but no finder ships with CMake or libxrender-dev, so Linux configure fails without it (needs `pkg-config` + `libxrender-dev` at build time).
- **Windows DLL consumption** (see `src/AdaptiveShooter/CMakeLists.txt`): game defines `CL_API_DLL`, sets `/SUBSYSTEM:WINDOWS` (entry is ClanLib's `WinMain`; game has no `main()`), and `NODEFAULTLIB`s the legacy `clan*-*.lib` pragma names.
- **Lua 5.1.4**: `dependencies/lua/` - Compiled from source submodule. CMake auto-detects and builds.

**Never run** `cmake -B build` without first ensuring submodules are initialized.

## Lua Scripting

- Lua scripts live in `src/scripts/`: `config.lua` (game settings), `demoscene.lua` (wave patterns), `test.lua` (basic test)
- C++ exposes ClanLib functions to Lua via `CL` table (`luafunctions.cpp:52-61`). Use `CL.ConsolePrint(...)` for console output.
- Lua state is managed by `AIManager` class (`src/AIManager/AIManager.cpp:15`) - do not close or reopen without updating references.
- `config.lua` defines `Player` and `Enemies` tables with stats used for difficulty adaptivity.

## Testing

- Google Test framework is used (v1.6.0 in `dependencies/gtest-1.6.0/`)
- Run tests: `cmake --build build --target AdaptiveShooter_test` or use IDE test runner
- `src/AIManager_Test/` contains additional test fixtures

## Project Structure

- `src/AdaptiveShooter/` - Main game code (C++ + Lua integration)
- `src/AIManager/` - AI framework with trait-based learning (static library)
- `src/scripts/` - Lua scripts for configuration and demo scenes
- `dependencies/` - Bundled submodules: `clanlib`, `lua`, `gtest-1.6.0`
- CMake auto-initializes submodules; manual `git submodule update --init --recursive` required if missed.

## Key Conventions

- C++11 standard with `-Wall` (GNU/Clang) or `/W4` (MSVC) warnings enabled
- `ccache` is auto-used as compiler launcher when installed (`-DADAPTIVESHOOTER_USE_CCACHE=OFF` to disable); CI persists `~/.cache/ccache` via `actions/cache`
- Static library `AIManager` links publicly to Lua when `LUA51_FOUND`
- Game assets (`data/`, `scripts/`) must reside alongside executable; CMake post-build copies them automatically
- Asset paths in game code must stay exe-relative (`./data/...`, `./Scripts/...`) in both configs — do not reintroduce `#ifdef _DEBUG` path variants (old `../../` Debug paths predate the CMake build and break Debug asset loading)
- ClanLib components used: `App`, `Display`, `GL`, `Sound`
- **Linux build fix**: If encountering "ClanLib display.h not found", the checkout is on the old ClanLib branch. Switch once with `git submodule set-branch --branch cmake dependencies/clanlib && git submodule update --init --recursive --remote`, then re-run cmake. The `cmake` branch is built with `CLANLIB_BUILD_ALL` on, so all four modules are always compiled.