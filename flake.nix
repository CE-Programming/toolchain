{
  description = "clevor's packages";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    llvm = {
      url = "github:jacobly0/llvm-project";
      flake = false;
    };
    toolchain = {
      flake = false;
      type = "git";
      url = "https://github.com/CE-Programming/toolchain?ref=v12.0";
      submodules = true;
    };
    convbin = {
      flake = false;
      type = "git";
      url = "https://github.com/mateoconlechuga/convbin";
      submodules = true;
    };
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { nixpkgs, llvm, toolchain, convbin, self, flake-utils }@inputs:
    flake-utils.lib.eachSystem [ "x86_64-linux" "x86_64-darwin" ] (system:
      let pkgsSelf = self.packages.${system}; in
    with import nixpkgs { inherit system; }; {
      templates.default = {
        path = ./examples/nix_flake;
        description = "A Hello World program for the TI-84 Plus CE";
      };
      packages = {
        fasmg-patch = pkgs.fasmg.overrideAttrs (final: old: {
          version = "kd3c";
          src = fetchzip {
            url = "https://flatassembler.net/fasmg.${final.version}.zip";
            sha256 = "sha256-duxune/UjXppKf/yWp7y85rpBn4EIC6JcZPNDhScsEA=";
            stripRoot = false;
          };
        });
        convbin-unstable = pkgs.convbin.overrideAttrs {
          src = inputs.convbin;
          version = "unstable";
        };
        llvm-ez80 = stdenv.mkDerivation (final: {
          pname = "llvm-ez80";
          version = "0-unstable";

          src = llvm;

          configurePhase = ''
            mkdir build
            cd build
            cmake ../llvm -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_PROJECTS=clang -DLLVM_TARGETS_TO_BUILD= -DLLVM_EXPERIMENTAL_TARGETS_TO_BUILD=Z80
            cd ..
          '';

          buildPhase = ''
            cd build
            cmake --build . --target clang llvm-link -j $NIX_BUILD_CORES
            cd ..
          '';

          installPhase = ''
            mkdir -p $out/bin
            cp build/bin/clang $out/bin/ez80-clang
            cp build/bin/llvm-link $out/bin/ez80-link
          '';
          doCheck = false;
          nativeBuildInputs = [ cmake python3 ];
        });
        clibs-stable = pkgsSelf.cedev-stable.overrideAttrs {
          name = "clibs.8xg";
          postBuild = ''
            make libs $makeFlags
          '';
          installPhase = ''
            cp clibs.8xg $out
          '';
        };
        clibs-nightly = pkgsSelf.cedev-nightly.overrideAttrs {
          name = "clibs.8xg";
          postBuild = ''
            make libs $makeFlags
          '';
          installPhase = ''
            cp clibs.8xg $out
          '';
        };
        cedev-stable = pkgsSelf.cedev-nightly.overrideAttrs {
          name = "cedev-12.0";
          src = toolchain;
        };
        default = pkgsSelf.cedev-nightly;
        cedev-nightly = stdenv.mkDerivation {
          src = self;
          name = "cedev-nightly";
          patchPhase = ''
            substituteInPlace src/common.mk --replace-fail \
              "INSTALL_DIR := \$(DESTDIR)\$(PREFIX)" "INSTALL_DIR := $out"
            substituteInPlace makefile --replace-fail \
              "TOOLS := fasmg convbin convimg convfont cedev-config" \
              "TOOLS := fasmg cedev-config" --replace-fail \
              "	\$(Q)\$(call COPY,\$(call NATIVEEXE,tools/convfont/convfont),\$(INSTALL_BIN))
          	\$(Q)\$(call COPY,\$(call NATIVEEXE,tools/convimg/bin/convimg),\$(INSTALL_BIN))
          	\$(Q)\$(call COPY,\$(call NATIVEEXE,tools/convbin/bin/convbin),\$(INSTALL_BIN))" "" \
              --replace-fail "tools/convbin/bin/" ""
            substituteInPlace tools/convimg/Makefile tools/cedev-config/Makefile \
              --replace-fail "-static" ""
            substituteInPlace src/makefile.mk \
              --replace-fail "\$(call NATIVEPATH,\$(BIN)/fasmg)" "${pkgsSelf.fasmg-patch}/bin/fasmg" \
              --replace-fail "\$(call NATIVEPATH,\$(BIN)/convbin)" "${pkgsSelf.convbin-unstable}/bin/convbin" \
              --replace-fail "\$(call NATIVEPATH,\$(BIN)/convimg)" "${convimg}/bin/convimg" \
              --replace-fail "\$(call NATIVEPATH,\$(BIN)/cemu-autotester)" "cemu-autotester" \
              --replace-fail "\$(call NATIVEPATH,\$(BIN)/ez80-clang)" "${pkgsSelf.llvm-ez80}/bin/ez80-clang" \
              --replace-fail "\$(call NATIVEPATH,\$(BIN)/ez80-link)" "${pkgsSelf.llvm-ez80}/bin/ez80-link" \
              --replace-fail "\$(shell cedev-config --comment)" "CE C Toolchain"
          '';
          doCheck = true;
          enableParallelBuilding = true;

          buildInputs = (with pkgs; [
            convimg convfont
          ]) ++ (with pkgsSelf; [
            llvm-ez80
            fasmg-patch
            convbin-unstable
          ]);
          meta.mainProgram = "cedev-config";
        };
        mkDerivation = attrs: stdenv.mkDerivation (final: {
          stableToolchain = false;      # Whether to use nightly or stable
          enableParallelBuilding = true;
          nativeBuildInputs = [];
          buildPhase = ''
            runHook preBuild
            make gfx $makeFlags || true
            make $makeFlags
            runHook postBuild
          '';
          installPhase = ''
            runHook preInstall
            mkdir -p $out/
            cp *.8x* */*.8x* */*/*.8x* */*/*/*.8x* $out/
            cp README* readme* license* LICENSE* LISEZMOI* lisezmoi* $out
            runHook postInstall
          '';
        } // attrs // {
          nativeBuildInputs = (if attrs ? nativeBuildInputs then attrs.nativeBuildInputs else []) ++ (with pkgsSelf; [
              (if final.stableToolchain then cedev-stable else cedev-nightly)
              convbin-unstable
              pkgs.convimg
              pkgs.convfont
              pkgsSelf.llvm-ez80
              fasmg
            ]);
          });
      };
    });
}
