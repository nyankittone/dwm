{pkgs, stdenv, libX11, libXinerama, libXft}:
stdenv.mkDerivation rec {
  pname = "dwm";
  version = "6.5-nyan";

  src = ./.;

  buildInputs = [
    libX11
    libXinerama
    libXft
  ];

  buildPhase = ''
    make CC=gcc
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp -f dwm $out/bin
    chmod 755 $out/bin/dwm
  '';
}
