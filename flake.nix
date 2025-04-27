{
  description = "A mcpe 0.1.0-0.10.5 launcher for linux and windows ";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    nixgl = {
      url = "github:nix-community/nixGL";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    glad = {
      flake = false;
      url = "github:Dav1dde/glad/56e406e90a802e963bb18d9c94cf6589e5a6b0a9";
    };
    ancmp = {
      flake = false;
      url = "github:MFDGaming/ancmp/f15e841a4a888b4dd09ba09d04a95dfb92839207";
    };
    stb = {
      flake = false;
      url = "github:nothings/stb/5736b15f7ea0ffb08dd38af21067c314d6a3aae9";
    };
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
    nixgl,
    glad,
    ancmp,
    stb
  }: let
    mkPkgs = system:
      import nixpkgs {
        inherit system;
        config.allowUnfree = true;
        overlays = [nixgl.overlay];
      };
  in
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = mkPkgs system;
    in {
      packages = rec {
        extract = pkgs.callPackage ./nix/pkgs/extract.nix {};
        ninecraft = pkgs.pkgsi686Linux.callPackage ./nix/pkgs/ninecraft.nix {
          ninecraft-extract = extract;
          internal_overrides = ./internal_overrides;
          inherit glad ancmp stb;
        };
        default = ninecraft;
      };
      formatter = pkgs.alejandra;
    })
    // {
      nixosModules.default = {pkgs, ...}: {
        imports = [./nix/nixos];
        programs.ninecraft.package = self.packages.${pkgs.system}.ninecraft;
      };
    };
}
