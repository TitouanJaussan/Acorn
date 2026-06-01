class Version:
    """
    Version class following SemVer semantics.
    """
    major: int = 0
    minor: int = 0
    patch: int = 0

    def __init__(self, major: int, minor: int, patch: int) -> None:
        self.major = major
        self.minor = minor
        self.patch = patch

    def __str__(self) -> str:
        return f"v{self.major}.{self.minor}.{self.patch}"

RUNTIME_VERSION: Version = Version(
    major = 0,
    minor = 0,
    patch = 1
)
