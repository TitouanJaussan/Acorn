# Changelog

Date format: `YYYY`-`MM`-`DD`

<details>
<summary><b>Versions list</b></summary>

- [v0.2.3](#v023---2026-07-04)
- [v0.2.2](#v022---2026-06-28)
- [v0.2.1](#v021---2026-06-14)
- [v0.2.0](#v020---2026-06-05)
- [v0.1.1](#v011---2026-06-02)
- [v0.1.0](#v010---2026-06-01)
- [v0.0.2](#v002---2026-06-01)
- [v0.0.1](#v001---2026-06-01)

</details>

## [v0.2.3] - 2026-07-04
### Added
- `Filesystem` utility for reading / writing to files & setting cwd
- `toml` deserialization via `tomlplusplus`
- New ctor for `ArrayList`

### Changed
- Manifest now present in the `manifest.toml` file in module
- Cleaned up & updated module loading code

### Removed
- Manifest in dynamic library

## [v0.2.2] - 2026-06-28
### Added
- Module APIs for inter-module communication
- Module `APIHandle` for reload safe shared api handles
- `operator+` for `String` concatenation
- More methods to the `BaseWindow` interface (`WindowModule` specific)
- New `String` unit test

### Changed
- Heavily reworked the module structure (file structure and code architecture, WIP)
- Logger factory now uses `String` instead of `const char*` for the logger name parameter

### Fixed
- Bugs in `ArrayList` that could lead to double free
- Weird rvalue only constructor in `Pair` ???
- Name of logger provided to modules missing the `Module` suffix
- Clearing the services `ArrayList` before the automatic destructor to destroy services before closing the module that allocated them

## [v0.2.1] - 2026-06-14
### Added
- `String` as a replacement for `std::string`
- `String` support for `fmt` & `std::format`
- `Core::format` as a replacement for direct usage of `std::format`
- Dependencies solving for modules and ordered mod loading based off the dependencies (WIP)
- More unit tests

### Changed
- Updated `setup.py` to not regenerate the runtime version header if it's unchanged (saving compilation time)
- Replaced a lot of `std::string` by `String` in order to move towards the full use of the engine's string class
- Updated the modules manifest to use more of the engine's default containers (`String`, `ArrayList`, etc...)
- `Runtime` instance now stored within a `UniquePtr` in the `Application` class to manage lifetime and memoy more explicitly

### Fixed
- Incorrect copy constructor of `UniquePtr`
- Incorrect move assignment operator of `UniquePtr`

## [v0.2.0] - 2026-06-05
### Added
- `ThreadingManager` containing `ServiceManager` & `JobScheduler`
- Services, through `ServiceManager` & `Service` & `ServiceDescriptor`

### Changed
- Updated `RuntimeAPI` & `Runtime` to include Services
- Gave the GLFW window it's own `Logger` instance
- Renamed `UniquePtr::createUniquePtr` to `UniquePtr`
- Refactored `JobScheduler` (check diff)

### Fixed
- Uncommented destructor call in `ArrayList::setCapacity`
- Fixed move semantics in `DetailedError` ctor
- Fixed move semantics in `Module` ctor

### Removed
- `WorkerThread` move ctor (also a fix, it caused dangling refs)

## [v0.1.1] - 2026-06-02
### Added
- Render module, doing nothing for now
- A `Core::Logger` inside the `ModuleManager`

### Fixed
- Fixed a bug in `ArrayList` that caused the size to reset on reallocation

## [v0.1.0] - 2026-06-01
### Added
- Full `JobScheduler` to runtime, working

### Changed
- Updated Runtime API to allow using the new job scheduler

## [v0.0.2] - 2026-06-01
### Added
- `Pair` template as a replacement for `std::pair`

### Changed
- Replaced all uses of `std::pair` in favor of `Pair`

## [v0.0.1] - 2026-06-01
### Added
- Basic versionning of the Runtime and it's modules, forcing API cohesion between modules and Runtime
- `ArrayList` template as a replacement for `std::vector`
- `UniquePtr` template as a replacement for `std::unique_ptr`
- Basic memory tracker
- Basic unit testing

### Changed
- Switched from raw `.sh` / `.bat` files to `.py` for better cross-platform setup
- Replaced all uses of `std::vector` in favor of `ArrayList`
- Replaced all uses of `std::unique_ptr` in favor of `UniquePtr`
