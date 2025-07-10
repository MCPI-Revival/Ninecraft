{
  description = "A mcpe 0.1.0-0.10.5 launcher for linux and windows ";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    nixgl = {
      url = "github:nix-community/nixGL";
      inputs.nixpkgs.follows = "nixpkgs";
      inputs.flake-utils.follows = "flake-utils";
    };
    glad = {
      flake = false;
      url = "github:Dav1dde/glad/56e406e90a802e963bb18d9c94cf6589e5a6b0a9";
    };
    ancmp = {
      flake = false;
      url = "github:MFDGaming/ancmp";
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
    stb,
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
    in rec {
      packages =
        (import ./nix/pkgs {
          inherit pkgs;
          internal_overrides = ./internal_overrides;
          inherit glad stb ancmp;
          # ancmp = ./ancmp;
        })
        // {
          default = packages.ninecraft;
        };
      apps = {
        extract = {
          type = "app";
          program = "${pkgs.callPackage ./nix/pkgs/extract.nix {}}/bin/ninecraft-extract";
        };
      };
      formatter = pkgs.alejandra;
      devShell = pkgs.callPackage ./nix/shell.nix {
        inherit (packages) ninecraft ninecraft-nixgl;
      };
    })
    // {
      nixosModule = {pkgs, ...}: {
        imports = [./nix/nixos];
        programs.ninecraft.package = self.packages.${pkgs.system}.ninecraft;
      };
      homeManagerModule = {pkgs, ...}: {
        imports = [./nix/home];
        programs.ninecraft.package = self.packages.${pkgs.system}.ninecraft;
      };
    };
}
