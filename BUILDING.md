# Building AdaptiveShooter

AdaptiveShooter is a 2D space shooter with dynamic AI difficulty adjustment powered by Lua and ClanLib.

External dependencies (**ClanLib 3.0** and **Lua 5.1.4**) are managed via **Git submodules** and built **transparently and automatically** by CMake.

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

---

## 2. Linux Build Instructions

Tested on Ubuntu / Debian distributions.

### Step 1: Install System Prerequisites
Install the compiler toolchain, CMake, and ClanLib library dependencies:
```bash
sudo apt-get update
sudo apt-get install -y make g++ automake libtool cmake \
    libfreetype6-dev libfontconfig1-dev libgl1-mesa-dev \
    libxrender-dev libasound2-dev
```

### Step 2: Configure & Build
Both ClanLib 3.0 and Lua 5.1.4 are built automatically by CMake:
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
```

> [!NOTE]
> During the initial `cmake -B build`, CMake detects the `dependencies/clanlib` submodule and compiles it locally into a dedicated sandbox prefix (`build/external/clanlib`). No manual compilation, root permissions, or global `sudo make install` are required!

### Step 3: Run the Game
Game assets (`data/` and `src/Scripts/`) are automatically copied next to the executable:
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
```cmd
.\build\bin\Release\AdaptiveShooter.exe
```

---

## 4. How Dependency Management Works

Everything is handled transparently behind the scenes:

### ClanLib 3.0 (`dependencies/clanlib`)
- Managed via `cmake/ManageClanLib.cmake`.
- If ClanLib 3.0 is not already installed on the system, CMake detects the submodule and:
  - **On Linux**: Automatically runs `./autogen.sh`, `./configure`, and compiles ClanLib locally into `build/external/clanlib`.
  - **On Windows**: Generates the Visual Studio project files and compiles the required ClanLib libraries automatically via MSBuild.
- The compiled ClanLib libraries are then automatically linked to `AdaptiveShooter`.

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

#### Q: The game crashes on startup with asset missing errors
Ensure that `data/` and `Scripts/` are located in the same directory as the executable. CMake's post-build command copies them automatically, but if you launch the executable from a custom working directory, verify that those folders are present.
