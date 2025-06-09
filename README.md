# CS2 Internal Triggerbot (Detect)

A simple internal triggerbot for Counter Strike 2, written in C++.

> ⚠️ Educational use only. Do not use in online matchmaking.

---

## Features

- Internal DLL injection
- Triggerbot logic using `m_iIDEntIndex`
- Entity resolution from handles via `dwEntityList`
- Enemy detection and automatic mouse click (`mouse_event`)
- WinAPI-based memory access
- Console logging for debugging

---

## How It Works

1. Inject DLL into `cs2.exe`
2. Find local player and resolve pawn using handle
3. Read `m_iIDEntIndex` to find entity under crosshair
4. Compare teams
5. If enemy detected — simulate left click

---

## Structure

📁 Project Root
├── dllmain.cpp # Core logic and entry point
├── include.h # Imports, headers, WinAPI
├── offsets.h # Reversed game offsets (cs2 dumper)
├── minhook/ # (Included but unused)

---

## Build Instructions

- Build as DLL using Visual Studio (x64, Release)
- Inject with any DLL injector (Xenos, GH Injector)
- Press `END` to stop the trigger thread

---

## License

This project is released under the MIT License.
For educational and reverse engineering practice only.
