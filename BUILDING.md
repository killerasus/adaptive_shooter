# Building AdaptiveShooter

AdaptiveShooter is a 2D space shooter with dynamic AI difficulty adjustment powered by Lua and ClanLib.

External dependencies (**ClanLib 3.0** and **Lua 5.1.4**) are managed via **Git submodules** and built **transparently and automatically** by CMake.
ClanLib is consumed from the **`cmake` branch** of https://github.com/killerasus/ClanLib and built
in-tree with `add_subdirectory()` — no autotools/`configure`, no `configure.exe`, on any platform.

---

## 1. Quick Start

All dependencies are included as submodules. The only requirement is to clone with submodules (or initialize them):

### Fresh Clone
```bash
git clone --recurse-submodules https://github.com/killerasus/adaptive_shooter.git
cd adaptive_shooter
```

### Existing Clone
If you already cloned without `--recurse-submodules`:
```bash
git submodule update --init --recursive
```

### Switching an older checkout to the `cmake` branch
Older checkouts pin `dependencies/clanlib` to a different branch. Switch once:
```bash
git submodule set-branch --branch cmake dependencies/clanlib
git submodule update --init --recursive --remote
```

---

## 2. Linux Build Instructions

Tested on Ubuntu / Debian distributions.

### Step 1: Install System Prerequisites
Install the compiler toolchain, CMake, and the system libraries ClanLib links against
(X11/Xrender for Display, FreeType/Fontconfig for fonts, Mesa GL, ALSA for sound):
```bash
sudo apt install build-essential cmake pkg-config \
  libx11-dev libxrender-dev libxrandr-dev libfreetype-dev libfontconfig-dev \
  libgl1-mesa-dev libasound2-dev
```
No `libsqlite3-dev` needed (ClanLib bundles the SQLite amalgamation), and no
`automake`/`libtool` (the `cmake` branch does not use autotools). The `Xrender`
CMake finder that upstream lacks ships in-repo as `cmake/FindXrender.cmake`.

### Step 2: Configure & Build
Both ClanLib 3.0 and Lua 5.1.4 are built automatically by CMake:
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
```

> [!TIP]
> If `ccache` is installed, CMake uses it automatically to speed up rebuilds
> (ClanLib is big — this helps a lot). Disable with
> `cmake -B build -DADAPTIVESHOOTER_USE_CCACHE=OFF`. CI caches `~/.cache/ccache`
> between runs for the same effect.

> [!NOTE]
> During the initial `cmake -B build`, CMake builds the `dependencies/clanlib` submodule in-tree
> with `add_subdirectory()` (modules App/Display/GL/Sound + Core). No manual compilation, root
> permissions, or global `sudo make install` are required!

### Step 3: Run the Game
Game assets (`data/` and `src/Scripts/`) are automatically copied next to the executable.
Debug and Release share the same exe-relative asset layout — launch the binary from its
own folder:
```bash
./build/bin/AdaptiveShooter
```

---

## 3. Windows Build Instructions

### Prerequisites
- **Visual Studio 2019** or **Visual Studio 2022** (Community, Professional, or Enterprise)
  - During installation, make sure to check **Desktop development with C++** (which includes MSVC, CMake, and MSBuild).
- **Git for Windows**

### Option A: Visual Studio "Open Folder" (Recommended)
1. Launch **Visual Studio 2019/2022**.
2. Click **File** > **Open** > **Folder...** and select the `adaptive_shooter` repository root.
3. Visual Studio will automatically detect `CMakeLists.txt`, initialize dependencies, and configure the project.
4. Select `x64-Release` (or `x86-Release`) from the configuration dropdown.
5. Select `AdaptiveShooter.exe` from the startup target dropdown and press **F5** to build and run!

### Option B: Command Line (CMake CLI)
From a Developer Command Prompt or PowerShell:
```cmd
cmake -B build
cmake --build build --config Release
```

### Run the Game
Launch the executable from its own folder so it finds `data/` and `Scripts/`:
```cmd
.\build\bin\Release\AdaptiveShooter.exe
.\build\bin\Debug\AdaptiveShooter.exe
```

---

## 4. How Dependency Management Works

Everything is handled transparently behind the scenes:

### ClanLib 3.0 (`dependencies/clanlib`, branch `cmake`)
- Managed directly in the root `CMakeLists.txt` (there is no `cmake/ManageClanLib.cmake`).
- Unless a system ClanLib is found, CMake builds the submodule in-tree with `add_subdirectory()`,
  with `CLANLIB_BUILD_ALL=ON` (upstream per-module cache vars are shadowed by its own defaults, so ALL is the reliable switch):
  - **On Linux**: plain `cmake --build` compiles the modules; needs X11/OpenGL/ALSA dev packages (see step 1).
  - **On Windows**: the same `cmake --build` compiles the modules with MSBuild; ClanLib DLLs are placed
    next to `AdaptiveShooter.exe` automatically. **No `configure.exe` is used.**
- A system-installed ClanLib is still honored when `find_package(ClanLib)` finds one (e.g. via `-DCLANLIB_ROOT_DIR=`).

### Lua 5.1.4 (`dependencies/lua`)
- Managed via `dependencies/lua/CMakeLists.txt`.
- Compiles a static library (`lua51`) directly from source for your exact compiler and target architecture (both 32-bit and 64-bit).
- If system Lua 5.1 is already present, CMake can use it as a fallback.

---

## 5. Troubleshooting & FAQ

#### Q: CMake says `ClanLib 3.0 was not found` or `Lua 5.1 was not found`
Ensure you initialized submodules:
```bash
git submodule update --init --recursive
```
If CMake was run before submodules were fetched, simply re-run:
```bash
cmake -B build
```

#### Q: Can I use a pre-installed or custom ClanLib build?
Yes. You can pass the ClanLib installation path directly to CMake:
```bash
cmake -B build -DCLANLIB_ROOT_DIR=/path/to/clanlib
```

#### Q: Build fails with `lua_open` / `luaL_register` / `LUA_QL` "identifier not found"
The game requires the Lua 5.1 API, but CMake picked up a newer Lua (e.g. vcpkg's). That happens
when the vendored sources under `dependencies/lua/src/` are missing — verify `lapi.c` is there.
If the files were deleted, restore them with `git restore --source=HEAD -- dependencies/lua`
(or re-clone), then re-run cmake with a fresh cache (`cmake -B build --fresh`): the message
`Lua 5.1: building from submodule` confirms the right Lua is used.

#### Q: The game crashes on startup with asset missing errors
Ensure that `data/` and `Scripts/` are located in the same directory as the executable. CMake's post-build command copies them automatically, but if you launch the executable from a custom working directory, verify that those folders are present.

#### Q: Release runs, but Debug can't find sounds/images/scripts
This was caused by `#ifdef _DEBUG` asset-path variants (`../../data/...`) left over from the
old hand-maintained Visual Studio solution. Those are gone: all configurations now use the
same exe-relative paths (`./data/...`, `./Scripts/...`). If you see this again, check for
reintroduced `_DEBUG` path branches in `main.cpp`, `GameManager.cpp`, or `TestScenePlayer.cpp`.
