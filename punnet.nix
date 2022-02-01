{ stdenv }:

stdenv.mkDerivation {
	name = "punnet-v3.0.0";
	builder = cc main.c;
}