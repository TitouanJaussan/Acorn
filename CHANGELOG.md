# Changelog

Date format: `YYYY`-`MM`-`DD`

<details>
<summary><b>Versions table </b></summary>

- [v0.0.1](#v001---2026-05-28)

</details>

## [v0.0.1] - 2026-05-28
### Added
- Basic versionning of the Runtime and it's modules, forcing API cohesion between modules and Runtime
- ArrayList template as a replacement for std::vector
- UniquePtr template as a replacement for std::unique_ptr
- Basic memory tracker
- Basic unit testing

### Changed
- Switched from raw .sh / .bat files to .py for better cross-platform setup
- Replaced all uses of std::vector in favor of ArrayList
- Replaced all uses of std::unique_ptr in favor of UniquePtr
