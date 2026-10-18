{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/?ref=nixpkgs-unstable";
  };

  outputs =
    { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        packages = with pkgs; [
          gcc16
          cmake
          ninja

          raylib

          llvmPackages_latest.clang-tools
          neocmakelsp
        ];
      };
    };
}
