# Changelog

Date format: `YYYY`-`MM`-`DD`

<details>
<summary><b>Versions list</b></summary>

- [v0.1.1](#v011---2026-06-02)
- [v0.1.0](#v010---2026-06-01)
- [v0.0.2](#v002---2026-06-01)
- [v0.0.1](#v001---2026-06-01)

</details>

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
