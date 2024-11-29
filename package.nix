{
  cmake,
  lib,
  stdenv,
  nixfmt-rfc-style,
}:

stdenv.mkDerivation {
  pname = "logger";
  version = "0.0.1";

  outputs = [
    "out"
    "examples"
  ];

  src = ./.;

  nativeBuildInputs = [
    cmake
    nixfmt-rfc-style
  ];

  cmakeFlags = [
    "-DBUILD_STATIC_LIBS=ON"
    "-DEXAMPLES_INSTALL_PATH=${placeholder "examples"}"
  ];
}
