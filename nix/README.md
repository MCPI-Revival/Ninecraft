# How to install system wide

Following the nix install 


## NixOS
### With Flakes
```nix
{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
	 ninecraft = {
      url = "github:MCPI-Revival/Ninecraft";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = { self, nixpkgs, ninecraft }: {
    nixosConfigurations = {
      # NOTE: change "host" to your system's hostname
      host = nixpkgs.lib.nixosSystem {
		system = "x96_64-linux";
		specialArgs = [ninecraft];
        modules = [
          ./configuration.nix
        ];
      };
    };
  };
}
```

> configuration.nix
```nix
{ninecraft, ...}: {
  imports = [
    ninecraft.nixosModules.default
  ];
  nix.settings.experimental-features = [ "nix-command" "flakes" ];

  programs.ninecraft = {
    enable = true;
    openFirewall = true;
  };
}

```

and then you can use `ninecraft` command system wide.

### Without Flakes


> configuration.nix
```nix
{pkgs,lib,...}:
let
ninecraft = builtins.getFlake github:MCPI-Revival/Ninecraft;
in
{
	nix.settings.experimental-features = [ "nix-command" "flakes" ];
	enviroment.systemPackages = [
		ninecraft.packages.${pkgs.system}.ninecraft
	];
}
```

## Home Manager
[Install home-manager](https://nix-community.github.io/home-manager/index.xhtml#ch-installation)

> ~/.config/home-manager/home.nix
```nix
{pkgs,lib,...}:
let
ninecraft = builtins.getFlake git+https://github.com/MCPI-Revival/Ninecraft?submodules=1;
in
{
	#state username etc...
	nix.settings.experimental-features = [ "nix-command" "flakes" ];
	home.packages = [
		ninecraft.packages.${pkgs.system}.ninecraft
	];
}
```


# ok so how is this going to work

have a shell and a module

# packages
ninecraft-extract - extract an apk into res lib and assets
ninecraft-gl - ninecraft wrapped with gl
