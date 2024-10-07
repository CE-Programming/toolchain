{
  description = "A Hello World demo for the TI-84 Plus CE.";

  inputs = {
    cedev = {
      url = "https://github.com/CE-Programming/toolchain";
      submodules = true;
      type = "git";
    };
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, cedev, flake-utils }:
    flake-utils.lib.eachSystem [ "x86_64-linux" "x86_64-darwin" ] (system: {
      packages.default = cedev.packages.${system}.mkDerivation {
        name = "hello-world";
        src = self;
      };
    });
}
