# How to install system wide

Following the nix install 


## NixOS
### With Flakes
```nix
{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
	 ninecraft = {
      url = "git+https://github.com/MCPI-Revival/Ninecraft?submodules=1";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = { self, nixpkgs, ninecraft }: {
    nixosConfigurations = {
      # NOTE: change "host" to your system's hostname
      host = nixpkgs.lib.nixosSystem {
        modules = [
          ./configuration.nix
        ];
		extra
      };
    };
  };
}
```

> configuration.nix
```nix
{pkgs,lib, ninecraft,...}:
{
	nix.settings.experimental-features = [ "nix-command" "flakes" ];
	enviroment.systemPackages = [
		ninecraft.packages.${pkgs.system}.ninecraft
	];
}
```

and then you can use `ninecraft` command system wide.

### Without Flakes


> configuration.nix
```nix
{pkgs,lib,...}:
let
ninecraft = builtins.getFlake git+https://github.com/MCPI-Revival/Ninecraft?submodules=1;
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

## Channels
```bash
sudo nix-channel --add https://github.com/MCPI-Revival/Ninecraft/archive/master.tar.gz ninecraft
sudo nix-channel --update
```

configuration.nix
```nix
{pkgs,lib,...}:
{
	imports = [
		(import <ninecraft>).nixos
	];
	programs.ninecraft = {
		enable = true;
		openFirewall = true;
	};
}
```