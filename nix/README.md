# How to install system wide
# Setup
## without flakes
```sh
nix-channel --add https://github.com/MCPI-Revival/ninecraft/archive/master.tar.gz ninecraft
nix-channel --update
```

## with flakes 
Please don't just blindly copy and paste the below, please [learn about nix flakes](https://jade.fyi/blog/flakes-arent-real/) or just use the above without flakes

```nix
{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
   ninecraft = {
      url = "github:MCPI-Revival/Ninecraft";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = { self, nixpkgs, ninecraft }:
  let pkgs = import nixpkgs {system = "x86_64-linux";};
  in {
    nixosConfigurations = {
      # NOTE: change "host" to your system's hostname
      host = nixpkgs.lib.nixosSystem {
    system = "x86_64-linux";
    specialArgs = [ninecraft];
        modules = [
          ./configuration.nix
        ];
      };
    };
    homeConfigurations = {
      # NOTE: change "user" to your username
      user = lib.homeManagerConfiguration {
          extraSpecialArgs = moduleArgs;

    specialArgs = [ninecraft];
        modules = [
          ./home.nix
        ];
    system
      };
    };
  };
}
```


# Configuration

## NixOS

> configuration.nix
```nix
{pkgs,lib,...}:
{
  imports = [
    # without flakes
    <ninecraft/nix/nixos>
    #with flakes
      ninecraft.nixosModule
  ];

  # ... other stuff

  programs.ninecraft = {
    enable = true;
    openFirewall = true;
  };
}
```

## HomeManager

> home.nix

This is a work in progress and many options may not function yet.

```nix
{pkgs,lib,...}:
{
  imports = [
    # without flakes
    <ninecraft/nix/home>
    #with flakes
      ninecraft.homeManagerModule
  ];

  # ... other stuff

  programs.ninecraft = {
    enable = true;
    version = "0.6.0";
    #apk = fetchzip {
      #   url = "https://archive.org/download/MCPEAlpha/PE-a0.7.0-x86.apk"
      #   hash = lib.fakeHash;
      # }
    options = {
      "mp_username"="Steve";
      "mp_server"="Steve";
      "mp_server_visible_default"=true;
      "gfx_fancygraphics"=true;
      "gfx_lowquality"=false;
      "ctrl_sensitivity"=0.5
      "ctrl_invertmouse"=false;
      "ctrl_islefthanded"=false;
      "ctrl_usetouchscreen"=false;
      "ctrl_usetouchjoypad"=false;
      "feedback_vibration"=false;
      "game_difficulty"=4;
    };
    
    #extracts into mod folder
    mods = with pkgs; [
      (fetchzip {
        url = "example.com/mod.zip";
        hash = lib.fakeHash;
      })
      (fetchgit {
        url = "https://.../ok.git";
        hash = lib.fakeHash;
      })
      (fetchFromGitHub {
        owner = "a";
        repo = "b";
        rev = "main";
        hash = lib.fakeHash;
      })
    ]
  }
}
```

# Modding

## Create Mod

```nix
with import <ninecraft/nix/pkgs> {}:
buildNinecraftModNDK {
  pname = "mymod";
  version = "0.1.0";
  src = ./src;
}
```
```nix
with import <ninecraft/nix/pkgs> {}:
buildNinecraftModNDK {
  pname = "mymod";
  version = "0.1.0";
  src = fetchurl {
    url = "example.com/path/to/mod.zip";
    hash = lib.fakeHash;
  };
  precompiled = true;
  compiled = {
    x86 = "x86/mod.so";
    x86 = "arm/mod.so";
  };
}
```

```nix
with import <nixpkgs> {};
with import <ninecraft/nix/pkgs> {}:
buildNinecraftModNDK {
  pname = "mymod";
  version = "0.1.0";
  src = fetchurl {
    url = "example.com/path/to/mod/${system}/mod.so";
    hash = lib.fakeHash;
  };
  precompiled = true;
}
```
